#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED
//shared data among cpp files
using namespace std;
extern ofstream outputfile;
extern ifstream inputfile;
extern string keywords;
extern string symbols;
extern string intergerConstant;
extern string stringConstant;
extern string identifier;
extern string regularExpr;

class Tokenizer{
private:
    char path[120];
public:
    Tokenizer(char []);
    void InsertToken(string );
    void Tokenize_Line(string );
    void Tokenize_File();
    void Parsing_File(string);
    bool IsJackFile(string);
    bool ReadAllfiles(vector<string>&);
    void StartTokenization();
    string Getoutfile(string);
};


#endif // TOKENIZER_H_INCLUDED
