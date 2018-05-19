/*
VM_Translator class open the VM file and the assembly file in the constructor and has methods :

-VM_Into_ASM():trigger the VM translation by calling parsing() function in Parser class
-StartTranslation(): check the input path if it file convert it directly else if it is directory convert VM files
in it to assembly code into the assembly file
-ReadAllFiles(): read all VM files in the directory in list.
-GetInFile(): return VM code file without extension
_ Also there are some help functions such as Isfile(), setouputpath(),Bsename()

**/
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include<dirent.h>
#include "Parser.h"
#include "VMT.h"
using namespace std;

VM_Translator::VM_Translator(char* p)
{
    strcpy(path,p);
    StartTranslation();
}
//start translate the input file if the path refers to file
//or translate all files in dir if the path refers to dir
void VM_Translator::StartTranslation()
{
    if(Isfile(string(path)))
    {
        strcpy(infile,path);
        Setoutputpath();

        //open I/O files
        outputfile.open(outfile);
        inputfile.open(infile);

        p.Initialization();
        p.Parsing();
    }
    else
    {
        vector<string> Files;
        if(ReadAllfiles(Files))
        {
            //create the output assembly file
             string asmout = string(path)+"/"+Basename()+".asm";
             strcpy(outfile,asmout.c_str());
             outputfile.open(outfile);
             p.Initialization();

             //Read all vm files in this directory
             //read Sys.vm if exist
             vector<string>::iterator it;
             if((it = find(Files.begin(), Files.end(), "Sys.vm")) != Files.end())
             {
                 //Translate the Sys.vm file
                 VM_Into_ASM("Sys.vm");
                 Files.erase(it);
                 outputfile<<"\n\n";
            }

            //Read Main.vm if exist
            if((it = find(Files.begin(), Files.end(), "Main.vm")) != Files.end())
             {
                 //translate the Main.vm
                outputfile<<"//   This the assembly code of Main.vm \n\n";
                 VM_Into_ASM("Main.vm");
                 Files.erase(it);
                 outputfile<<"\n\n";
            }

            //Translate the remaining vm files
            for( it=Files.begin(); it<Files.end();it++){

                outputfile<<"// This is the assembley code of "<<*it<<endl;
                 VM_Into_ASM(*it);
                 outputfile<<"\n\n";
            }

        }
    }
}

void VM_Translator::VM_Into_ASM(string file)
{
    if(file == "Sys.vm")
    {
        outputfile<<"//     Bootstrap code\n";
        //initialize SP pointer to 256
        outputfile<<"@256\n";
        outputfile<<"D = A\n";
        outputfile<<"@SP\n";
        outputfile<<"M = D\n";

        //call sys.init
        components.push_back("call");
        components.push_back("Sys.init");
        components.push_back("0");
        outputfile<<"//call Sys.init 0\n";
        CodeWriter codewr;
        codewr.WriteCall();

        //translate vm code of Sys.vm
        outputfile<<"//    assembly code of Sys\n";
    }

    vmfilename = Getinfile(file);
    string inputfile_path = string(path)+"/"+file;

    inputfile.close();
    inputfile.open(inputfile_path.c_str());

    outputfile<<"(" + vmfilename + ")\n";

    p.Parsing();
}
 bool VM_Translator::Isfile(string f)
{
   size_t i = f.size();
   if(f[--i]=='m' && f[--i]=='v' && f[--i] == '.')
        return true;
    return false;
}

void VM_Translator::Setoutputpath()
{
  size_t i = 0;

  while(i<strlen(path) && path[i] != '.'){
    outfile[i]= path[i];

    i++;
}
   outfile[i]='\0';
   strcat(outfile,".asm");
}

bool MatchPathSeparator(const char& ch)
{
      return (ch=='/' || ch=='\\');
}
//
string VM_Translator::Basename()
{
    string pathname = string(path);
    return string(find_if( pathname.rbegin(), pathname.rend(),MatchPathSeparator).base(), pathname.end() );
}

string VM_Translator::Getinfile(string filevm)
{
    string s = "";

   for(size_t i=0; i<filevm.size() && filevm[i] != '.'; i++)
     s.append(1,filevm[i]);

   return s;
}

bool VM_Translator::ReadAllfiles(vector<string>& files)
{
    DIR *dir = opendir(path);
    struct dirent *ent;

    if (dir != NULL)
     {
       while ((ent = readdir (dir)) != NULL) {
          string file = string(ent->d_name);

         if(Isfile(file))
           files.push_back(file);
        }

      closedir (dir);
      return true;
    }

  return false;
}
