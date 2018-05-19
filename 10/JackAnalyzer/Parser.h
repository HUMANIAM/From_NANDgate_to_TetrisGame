#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
using namespace std;

extern ofstream outputfile;
extern ifstream inputfile;
extern vector<string> filesPath;        //hold Paths of *T.XML files

class Parser{
private:
    int margin;
    char token[200];
    string token_type[2];
public:
    //constructor of parser
    Parser();
    //margin every token to represent the parse tree correctly in XML file
    void Margin(int);
    //check if there is more tokens we continue parsing and apply rules
    bool MoreTokens();
    //write terminals to the parse tree in the XML file
    void WriteTerminal();
    //check that if the output terminal from lexical phase matches the terminal in the grammer
    bool IsMachToken(string );
    //check that type of terminal matches the type required in grammer
    bool IsMachTokenType(string );
    //check if terminal is data type
    bool IsType(bool);
    //check if terminal is Constructor or Function or method
    bool IsCmFOr(string );
    //class VarDec rule in the grammer is recursive so we need to cheek more than one variable declaration
    bool ClassVarDecRec();
    bool CompileClassVarDec();
    //ParameterList is recursive rule where parameter may be one or more
    bool ParamListRec();
    bool CompileParameterList();
    //declaration of variable inside a routine like function or method. this declaration is recursive
    bool IsFollowVarDec(string );
    bool VarDecRec();
    bool CompileVarDec();
    //check if terminal is keywordConstant.
    //boolean parameter refers check only or check and if is true write to the xml file
    bool IsKeywordConst(bool );
    bool IsUnaryOp(bool );
    //ExpressionList is recursive rule
    bool ExpressionListRec();
    bool CompileExpressionList();
    //subroutine call grammer
    bool CompileSubroutineCall();
    bool CompileArrayExpression();
    bool CompileTerm();
    bool CompileOp(bool );
    //Expression is a recursive rule
    bool ExpressionRec();
    bool CompileExpression();
    //Statements rule is a recursive rule and include (if, while, do, let, return)
    bool CompileStatements();
    bool Statement();
    bool CompileLetStat();
    bool CompileDoStat();
    bool CompileIfWhileStat();
    bool CompileReturnStat();
    bool IsStatement();
    //Subroutine body rule
    bool SubroutineBody();
    //subroutine declaration rule
    bool CompileSubroutineDec();
    //class rule is the main rule after language rule
    bool CompileClass();
    //language rule
    bool StartParsing();
};

#endif // PARSER_H_INCLUDED
