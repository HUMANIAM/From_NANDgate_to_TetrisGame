#ifndef VMT_H_INCLUDED
#define VMT_H_INCLUDED
#include "Parser.h"
using namespace std;

 extern vector<string> memo_segm_ops;
 extern vector<string> arthim_logic_ops;
 extern vector<string> function_ops;
 extern vector<string> brancing_ops;
 extern vector<string> components;
 extern ifstream inputfile;
 extern ofstream outputfile;
 extern string lastoperation;
 extern string vmfilename;
 extern char infile[200];
 extern char outfile[200];
 extern int operorder;
 extern string lastfn;
 extern int nextaddress;

class VM_Translator{
    private:
        Parser p;
        char path[120];
    public:
        VM_Translator(char*);
        void StartTranslation();
        void VM_Into_ASM(string );
        string Basename();
        string Getinfile(string );
        bool Isfile(string);
        void Setoutputpath();
        bool ReadAllfiles(vector<string>&);

};
#endif // VMT_H_INCLUDED
