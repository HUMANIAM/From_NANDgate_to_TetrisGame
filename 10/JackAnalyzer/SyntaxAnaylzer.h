#ifndef SYNTAXANAYLZER_H_INCLUDED
#define SYNTAXANAYLZER_H_INCLUDED
using namespace std;

extern string keywords;
extern string symbols;
extern string intergerConstant;
extern string stringConstant;
extern string identifier;
extern string regularExpr;

class SyntaxAnlyzer{
    char path[200];
public:
    SyntaxAnlyzer(char*);
    void Initialization_RegExpres();
    void run();
};

#endif // SYNTAXANAYLZER_H_INCLUDED
