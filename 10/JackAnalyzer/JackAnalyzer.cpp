#include <fstream>
#include <string>
#include<cstring>
#include "SyntaxAnaylzer.h"

using namespace std;
ofstream outputfile;
ifstream inputfile;
string keywords;
string symbols;
string intergerConstant;
string stringConstant;
string identifier;
string regularExpr;

// main function
int main(int argc, char* argv[])
{
// Start the Syntax analyzer

SyntaxAnlyzer syntaxanaylzer(argv[1]);

return 0;
}
