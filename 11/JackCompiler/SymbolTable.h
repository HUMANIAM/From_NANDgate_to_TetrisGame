#ifndef SYMBOLTABLE_H_INCLUDED
#define SYMBOLTABLE_H_INCLUDED
using namespace std;

//this structure holds properties of variables
struct VarProperties{
    string type;
    string kind;
    int index;
    //constructor
    VarProperties(){}
    VarProperties(string t, string k, int i)
    {
        type = t;
        kind = k;
        index = i;
    }
};

extern string classname;
extern ifstream inputfile;
extern ofstream outputfile;

class SymbolTable{
private:
   int countargument;
   int countstatic;
   int countlocal;
   int countfield;
   map<string, VarProperties> var_Classlevel;
   map<string, VarProperties> var_Subroutinelevel;
public:
    SymbolTable ();
    //reset the subroutine symbol table
    void StartSubroutine(string);
    //add entries to the class_level symbol table or subroutine level symbol table
    bool Define(string, string, string);
    //count number of occurrence of specific type
    int Varcount(string);
    //return the kind of variable
    string Kindof(string);
    //retun the type of variable
    string Typeof(string);
    //return the index of variable
    int Indexof(string );
    void Displaysymboltables();

};
#endif // SYMBOLTABLE_H_INCLUDED
