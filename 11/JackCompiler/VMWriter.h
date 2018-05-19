#ifndef VMWRITER_H_INCLUDED
#define VMWRITER_H_INCLUDED
#include "Tokenizer.h"
#include "SymbolTable.h"
using namespace std;

extern string classname;
extern ifstream inputfile;
extern ofstream outputfile;
extern map< string ,map<string,SubroutineProp> > Classes_Methods;


class VMWriter{
private:
    vector<string> components;
    SymbolTable symtable;
public:
    VMWriter();
    void GenerateStatements();
    bool GenerateStatement();
    void GenerateSubBody(string);
    void StartGeneration();
    bool Advance(bool);
    void AddEntriesToTables();
    void GenerateSubDec();
    void GenerateSymbol();
    void GenerateExpression();
    bool GenerateWhile();
    bool GenerateIf();
    bool GenerateDo();
    bool GenerateLet();
    bool GenerateReturn();
    void Generateoperations(vector<string>&);
    void GenerateArrays(string, string);
    void GenerateExpressionList(int&);
    void GenerateTerm();
    void GenerateSubCall(string);
    void WriteFunction(string, int);
    void AddSubArguments(string);
};


#endif // VMWRITER_H_INCLUDED
