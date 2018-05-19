
#ifndef CODEWRITER_H_INCLUDED
#define CODEWRITER_H_INCLUDED
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
 extern string lastfn;
 extern int nextaddress;

class CodeWriter{
public:
       void CodeWritting();
    bool Find(string, vector<string>&);
    void ConvertArith_Logic();
    void ConvertMemoSegment();
    void ConvertBranching();
    void ConvertFunction();
    void Arth_Log_TwoOperands(string);
    void ConvetAddress(string, string);
    string __int_to_string(int);
    void WriteLabel();
    void WriteGoto();
    void WriteIf();
    void WriteCall();
    void WriteReturn();
    void WriteFunction();
    void SaveValue(string, char);
    void SetPointer(string);
    void RestoreValue(string, string);
};


#endif // CODEWRITER_H_INCLUDED
