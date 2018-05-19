#include <iostream>
#include <string>
#include <string.h>
#include <bitset>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

map<string , int> symbol_table;
map<string , string> des;
map<string , string> comp;
map<string , string> jump;

//Assembler class convert the prog.assm to prog.hack
class Assembler{

    private:
        ifstream inputfile;
        ofstream outputfile;
        char command[100];
        int nextlocation;
        int emptyramloc;
        string refinedcommand;

    public:
        //Initialize fields by the constructor
        Assembler(char*, char*);

        //first pass load the label symbols into the symbol table
        void FirstPass();
        void SecondPass();
        void Thirdpass();
        void ConvertA();
        void ConvertC();
        void Intialization();
        void Refinecommand();
        string CommandType();
        string Des();
        string Comp();
        string Jump();
        bool Isnumber();
        bool HasThisSymb(string);
        bool HasThisJump(string);

};

//the constructor of Assembler
Assembler::Assembler(char* progassm, char* proghack): 
            {
                nextlocation = 0;
                emptyramloc = 16;
                refinedcommand = "";
                 inputfile.open(progassm, ios::in);
                 outputfile.open(proghack, ios::out);

                Intialization();
                FirstPass();
            }

//First pass Add labels to the symbol table
void
Assembler::FirstPass()
{
    while(!inputfile.eof())
    {
        inputfile.getline(command, 100, '\n');
        Refinecommand();
        string type = CommandType();

        if(type == "command_L")
        {
            string label = refinedcommand.substr(1, refinedcommand.length()-2);

            if(!HasThisSymb(label))
             symbol_table[label] = nextlocation;
        }
    }

    SecondPass();
}

//Second pass Add symbols to the symbol table
void
Assembler::SecondPass()
{
    inputfile.clear();
    inputfile.seekg(0, ios::beg);

    while(!inputfile.eof())
    {
        inputfile.getline(command, 100, '\n');
        Refinecommand();
        string type = CommandType();
        if(type == "command_A")
            if( !Isnumber() )
            {
                string symbol = refinedcommand.substr(1, refinedcommand.length()-1);

                if(!HasThisSymb(symbol))
                {
                    symbol_table[symbol] = emptyramloc;
                    emptyramloc++;
                }
            }
    }

    Thirdpass();
}

//Third pass convert from assembly code to binary code
void
Assembler::Thirdpass()
{
    inputfile.clear();
    inputfile.seekg(0, ios::beg);

    while(!inputfile.eof())
    {
        inputfile.getline(command, 100, '\n');
        Refinecommand();
        string type = CommandType();

        if(type == "command_A")
                ConvertA();

        else if(type == "command_C")
            ConvertC();

        else{}

    }
}

//ConvertA convert A-instruction according to its value decimal or symbol
void
Assembler::ConvertA()
{
    string binary;
    string symbol = refinedcommand.substr(1, refinedcommand.length());

    if( !Isnumber() )
            {
                int symbel_val = symbol_table[symbol];

                //convert the decimal value to binary
                binary = bitset<15>(symbel_val).to_string();
            }
     else
     {
        //convert string number to int number
        char * cstr = new char [symbol.length()+1];
        strcpy (cstr, symbol.c_str());
        int decnumber = atoi(cstr);

        //convert the int to binary
        binary = bitset<15>(decnumber).to_string();
     }

     outputfile<<"0"+binary<<endl;
}

//ConvertC gets the 3 parts of C-instruction then concatenate them then out them
//into the hack file
void
Assembler::ConvertC()
{
    string des = Des();
    string comp = Comp();
    string jump = Jump();

    outputfile<< ( "111" + comp + des + jump ) << endl;
}

//isnumber check the type of value
bool
Assembler::Isnumber()
{
    for(int i=1; i<refinedcommand.length(); i++)
    {
        if(!isdigit(refinedcommand[i]))
            return false;
    }

    return true;
}

//CommandType check the type of command (comment or label or A or C instruction)
string
Assembler::CommandType()
{
    if(refinedcommand[0] == '/')
        return "command_com";

    else if(refinedcommand[0] == '@')
    {
        nextlocation++;
        return "command_A";
    }

    else if(refinedcommand[0] == '(')
        return "command_L";

    else if( refinedcommand.length() !=0 )
    {
        nextlocation++;
        return "command_C";
    }
    else
    {
        return "space_line";
    }
}

//Des get des part from the C-instruction
string
Assembler::Des()
{
   string d="";
   int p = refinedcommand.find_first_of("=");

    if( p!=string::npos )
       {
            for (int i=0; i<p; i++)
               d.append(1,refinedcommand[i]);
        }

    return des[d];
}

//Comp get the comp part from the C-instruction
string
Assembler::Comp()
{
    string d="";
   int p1 = refinedcommand.find_first_of("=");
   int p2 = refinedcommand.find_first_of(";");
   int from, to;

    (p1 == string::npos)? from=0 : from = p1+1;
    (p2 == string::npos)? to=refinedcommand.length() : to = p2;

    for (int i=from; i<to; i++)
        d.append(1,refinedcommand[i]);
    if(!HasThisJump(d))
        return comp[d];
    else
        return comp[""];

}

//Jump get the jump part from the C-instruction
string
Assembler::Jump()
{
    string d="";
    int p1 = refinedcommand.find_first_of("=");
    int p2 = refinedcommand.find_first_of(";");
    int from;

    (p1 == string::npos && p2 == string::npos)? from = 0 : true;
    ( p2 != string::npos)? from = p2 + 1 : true;

            for (int i=from; i<refinedcommand.length(); i++)
               d.append(1,refinedcommand[i]);

        if(HasThisJump(d))
          return jump[d];
        else
          return jump[""];

}

//refine command from comments and whitespace
void
Assembler::Refinecommand()
{
    refinedcommand = "";
    int j=0;

    for(int i=0; i<strlen(command); i++ )
    {
        if(command[i] == '/')
               break;
        if(command[i] !=' ')
            refinedcommand.append(1,command[i]);
    }
}

//HasThisKey check if symbol table has this key or not
bool
Assembler::HasThisSymb(string key)
{
    if ( symbol_table.find(key) == symbol_table.end() )
        return false;
    else
        return true;
}

//HasThisJump check if jump table has this key or not
bool
Assembler::HasThisJump(string key)
{
    if ( jump.find(key) == jump.end() )
        return false;
    else
        return true;
}

//initialize the look up tables
void
Assembler::Intialization ()
{
//initialize symbol table
symbol_table["R0"] = 0;
symbol_table["R1"] = 1;
symbol_table["R2"] = 2;
symbol_table["R3"] = 3;
symbol_table["R4"] = 4;
symbol_table["R5"] = 5;
symbol_table["R6"] = 6;
symbol_table["R7"] = 7;
symbol_table["R8"] = 8;
symbol_table["R9"] = 9;
symbol_table["R10"] = 10;
symbol_table["R11"] = 11;
symbol_table["R12"] = 12;
symbol_table["R13"] = 13;
symbol_table["R14"] = 14;
symbol_table["R15"] = 15;
symbol_table["SP"] = 0;
symbol_table["LCL"] = 1;
symbol_table["ARG"] = 2;
symbol_table["THIS"] = 3;
symbol_table["THAT"] = 4;
symbol_table["SCREEN"] = 16384;
symbol_table["KBD"] = 24576;

//Initialize des table
des[""]    = "000";
des["M"]   = "001";
des["D"]   = "010";
des["MD"]  = "011";
des["A"]   = "100";
des["AM"]  = "101";
des["AD"]  = "110";
des["AMD"] = "111";

//Initialize the comp table
comp["0"] = "0101010";
comp["1"] = "0111111";
comp["-1"] = "0111010";
comp["D"] = "0001100";
comp["A"] = "0110000";
comp["!D"] = "0001101";
comp["!A"] = "0110001";
comp["-A"] = "0110011";
comp["-D"] = "0001111";
comp["D+1"] = "0011111";
comp["A+1"] = "0110111";
comp["D-1"] = "0001110";
comp["A-1"] = "0110010";
comp["D+A"] = "0000010";
comp["D-A"] = "0010011";
comp["A-D"] = "0000111";
comp["D&A"] = "0000000";
comp["D|A"] = "0010101";
comp["M"] = "1110000";
comp["!M"] = "1110001";
comp["-M"] = "1110011";
comp["M+1"] = "1110111";
comp["M-1"] = "1110010";
comp["D+M"] = "1000010";
comp["D-M"] = "1010011";
comp["M-D"] = "1000111";
comp["D&M"] = "1000000";
comp["D|M"] = "1010101";
comp[""] = "1001100";

//Initialize jump table
jump[""]="000";
jump["JGT"]="001";
jump["JEQ"]="010";
jump["JGE"]="011";
jump["JLT"]="100";
jump["JNE"]="101";
jump["JLE"]="110";
jump["JMP"]="111";
}


//main function
int main()
{
    Assembler assm("Max.asm","Max.hack");
//    Assembler ass("Rect.asm","Rect.hack");


    return 0;
}
