#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "SymbolTable.h"
using namespace std;
//constructor
SymbolTable::SymbolTable()
{
   countargument = countlocal = 0;
   countfield = countstatic = 0;
}

//reset the subroutine symbol table
void SymbolTable::StartSubroutine(string routinetype)
{
    var_Subroutinelevel.clear();
    countargument = countlocal = 0;
    if(routinetype == "method")
        var_Subroutinelevel["this"]= VarProperties (classname,"argument",countargument++);
}

//define new entry in the class level symbol table or the subroutine level symbol table
bool SymbolTable::Define(string name, string type, string kind)
{
    if(var_Classlevel.find(name) == var_Classlevel.end() && (kind == "static" || kind == "field"))
    {
        if(kind == "field")
            var_Classlevel[name] = VarProperties(type, "this", countfield++);
        else
            var_Classlevel[name] = VarProperties(type, kind, countstatic++);

        return true;
    }
    else if(var_Subroutinelevel.find(name) == var_Subroutinelevel.end() && (kind == "argument" || kind == "var"))
    {
       if(kind == "var")
            var_Subroutinelevel[name] = VarProperties(type, "local", countlocal++);
        else
            var_Subroutinelevel[name] = VarProperties(type, kind, countargument++);


        return true;
    }
    else
     return false;
}

int SymbolTable::Varcount(string var)
{
    if(var == "static")
        return countstatic;
    else if(var == "var")
        return countlocal;
    else if(var == "argument")
        return countargument;
    else
        return countfield;
}

string SymbolTable::Kindof(string name)
{
    if(var_Subroutinelevel.find(name) != var_Subroutinelevel.end())
        return var_Subroutinelevel[name].kind;
    else if(var_Classlevel.find(name) != var_Classlevel.end())
        return var_Classlevel[name].kind;
     else
         return "none";
     }

//return the type of variable
string SymbolTable::Typeof(string name)
{
    if(var_Subroutinelevel.find(name) != var_Subroutinelevel.end())
        return var_Subroutinelevel[name].type;
    else if(var_Classlevel.find(name) != var_Classlevel.end())
        return var_Classlevel[name].type;
     else
        return "none";
}

//return order of the variable in specific scope
int SymbolTable::Indexof(string name)
{
     if(var_Subroutinelevel.find(name) != var_Subroutinelevel.end())
        return var_Subroutinelevel[name].index;
    else if(var_Classlevel.find(name) != var_Classlevel.end())
        return var_Classlevel[name].index;
     else
        return -1;
}

