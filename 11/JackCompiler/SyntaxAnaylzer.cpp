#include <string>
#include <regex>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <map>
#include "Tokenizer.h"
#include "Parser.h"
#include "SyntaxAnaylzer.h"
using namespace std;


SyntaxAnlyzer::SyntaxAnlyzer(char* p)
{
    strcpy(path, p);
    Initialization_RegExpres();
    run();
}
//Initialize the regular expression of lexemes of jack language
void SyntaxAnlyzer::Initialization_RegExpres()
{
    //regular expressions required patterns
    keywords = "(\\bclass\\b|\\bconstructor\\b|\\bfunction\\b|\\bmethod\\b|\\bfield\\b|\\bstatic\\b|"
              "\\bvar\\b|\\bint\\b|\\bchar\\b|\\bboolean\\b|\\bvoid\\b|\\btrue\\b|\\bfalse\\b|\\bnull\\b|"
              "\\bthis\\b|\\blet\\b|\\bdo\\b|\\bif\\b|\\belse\\b|\\breturn\\b|\\bwhile\\b)";
    symbols = "(\\{|}|\\(|\\)|\\[|]|\\.|,|;|\\+|-|\\*|/|&|>|<|=|~|\\|)";
    intergerConstant = "([0-9]+)";
    stringConstant = "\"([^\"\\n]*)\"";
    identifier = "(\\b[a-zA-Z_][a-zA-Z0-9_]*)";
    regularExpr = keywords + "|" + symbols + "|" + intergerConstant + "|" + stringConstant + "|" + identifier;
}

void SyntaxAnlyzer::run()
{
    Tokenizer tok(path);
}
