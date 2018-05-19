#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED
//shared data among cpp files
using namespace std;
//this structure holds properties of the subroutines
struct SubroutineProp{
string  type, returntype;
map<string,string> parameterlist;
int nargs;
//default constructor
SubroutineProp(){}
//constructor with 3 arguments
SubroutineProp(string t, string rt, int n, map<string,string>& parmlist): type(t), nargs(n), returntype(rt)
{ parameterlist= parmlist;}
};

extern ofstream outputfile;
extern ifstream inputfile;
extern string keywords;
extern string symbols;
extern string intergerConstant;
extern string stringConstant;
extern string identifier;
extern string regularExpr;
extern map< string ,map<string,SubroutineProp> > Classes_Methods;

class Tokenizer{
private:
    char path[120];
public:
    Tokenizer(char []);
    void InsertToken(string, string);
    void Tokenize_Line(string );
    void Tokenize_File();
    void SubroutineInfo(string, string);
    void Parsing_File();
    void Generating_File();
    int GetParmaterList(string, map<string,string>&);
    void AddSubroutine(vector<string>&, int, map<string,string>&);
    string GetClassName(string);
    bool IsJackFile(string);
    bool ReadAllfiles(vector<string>&);
    void Run();
    string Getoutfile(string);
    void Tokenize_Parsing_Generate(vector<string>&, string);
};


#endif // TOKENIZER_H_INCLUDED
