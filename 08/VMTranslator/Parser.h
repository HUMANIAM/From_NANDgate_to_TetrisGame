#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "CodeWriter.h"
using namespace std;
  extern vector<string> memo_segm_ops;
 extern vector<string> arthim_logic_ops;
 extern vector<string> function_ops;
 extern vector<string> brancing_ops;
 extern vector<string> components;
 extern ifstream inputfile;
 extern ofstream outputfile;
 extern string vmfilename;
 extern char infile[200];
 extern char outfile[200];
 extern int operorder;
 extern int nextaddress;

class Parser{
private:
    CodeWriter cw;
public:
    void Parsing();
    void Split(char [], string&);
    void Initialization();
    void Initasmfile();
};

#endif // PARSER_H_INCLUDED
