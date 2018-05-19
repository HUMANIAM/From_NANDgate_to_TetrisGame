#include <fstream>
#include <string>
#include<cstring>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
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
map<string,map<string, SubroutineProp> > Classes_Methods;


// main function
int main(int argc, char* argv[])
{

SyntaxAnlyzer syntaxanaylzer(argv[1]);

return 0;
}
