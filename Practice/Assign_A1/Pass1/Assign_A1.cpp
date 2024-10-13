#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>

using namespace std;


class Pass1
{
    public:   
        map<string,pair<string,string>>opcode;
        map<string,pair<int,string>>symtab;
        vector<pair<string,int>>littab;
        vector<string>pooltab;
        int lc = -1;
        int litindex = 0;
     
        Pass1()
        {
            opcode = {
                {"STOP",{"IS","01"}},{"ADD",{"IS","02"}},
                {"SUB",{"IS","03"}},{"MUL",{"IS","04"}},
                {"MOVER",{"IS","05"}},{"MOVEM",{"IS","06"}},
                {"COMP",{"IS","07"}},{"DIV",{"IS","08"}},
                {"READ",{"IS","09"}},{"PRINT",{"IS","10"}},
                
                {"START",{"AD","01"}},
                {"END",{"AD","02"}},
                {"ORIGIN",{"AD","03"}},
                {"EQU",{"AD","04"}},
                {"LTORG",{"AD","05"}},
                
                {"DC",{"DL","01"}},
                {"DS",{"DL","02"}},
                
                {"AREG",{"1",""}},{"BREG",{"2",""}},
                {"CREG",{"3",""}},{"DREG",{"4",""}},
                
                {"LT",{"1",""}},{"LE",{"2",""}},
                {"EQ",{"3",""}},{"GT",{"4",""}},
                {"GE",{"5",""}},{"ANY",{"6",""}}
            };
        }

        void execute()
        {
            ifstream fin("input1.txt");
            ofstream fout("output.txt");
            string word,line;
            symtab.clear();
            littab.clear();
            pooltab.clear();
            
            while(getline(fin,line))
            {
                stringstream st(line);
                st >> word;
                string label = "";
                
                if(opcode.count(word) == 0)
                {
                    if(symtab.count(word) == 0)
                    {
                        symtab[word] = {lc,to_string(symtab.size()+1)};   
                    }
                    else
                    {
                        symtab[word].first = lc;
                    }
                    
                    label = word;
                    st >> word;
                }
                
                string operation = word;
                if(operation == "START")
                {
                    fout <<"    ("<<opcode[word].first<<", "<<opcode[word].second<<")";
                    st >> word;
                    fout<<"(C, "<<word<<")";
                    lc = stoi(word);
                }
                else if(operation == "END")
                {
                    fout <<"    ( "<<opcode[word].first<<", "<<opcode[word].second<<")";
                    fout<<endl;
                    pooltab.push_back("#"+to_string(litindex+1));
                    while(litindex<littab.size())
                    {
                        fout<<lc<<" ";
                        fout<<"( "<<opcode["DC"].first<<", "<<opcode["DC"].second<<") ";
                        littab[litindex].second = lc;
                        string literal = littab[litindex].first;
                        string sublit = literal.substr(2,literal.size()-3);
                        fout<<"(C, "<<sublit<<") ";
                        fout<<endl;
                        lc++;
                        litindex++;
                    }
                }
                else if(operation == "LTORG")
                {
                    fout <<"    ( "<<opcode[word].first<<", "<<opcode[word].second<<")";
                    fout<<endl;
                    pooltab.push_back("#"+to_string(litindex+1));
                    while(litindex<littab.size())
                    {
                        fout<<lc<<" ";
                        fout<<"( "<<opcode["DC"].first<<", "<<opcode["DC"].second<<") ";
                        littab[litindex].second = lc;
                        string literal = littab[litindex].first;
                        string sublit = literal.substr(2,literal.size()-3);
                        fout<<"(C, "<<sublit<<") ";
                        fout<<endl;
                        lc++;
                        litindex++;
                    }
                }
                else if(operation == "EQU")
                {
                    fout<<" ";
                    st >> word;
                    
                }
                else if(operation == "ORIGIN")
                {
                    fout <<"    ( "<<opcode[word].first<<", "<<opcode[word].second<<")";
                    
                }
                else
                {
                    fout << lc << " ";
                    fout<<"("<<opcode[word].first<<", "<<opcode[word].second<<")";
                    
                    while(st >> word)
                    {
                        if(operation == "DC")
                        {
                            fout<<" (C, "<<word<<") ";
                        }
                        else if(operation == "DL")
                        {
                            fout<<" (C, "<<word<<") ";
                            lc += stoi(word)-1;
                        }
                        else if(word[0] == '=')
                        {
                            littab.push_back({word,lc});
                            fout<<" (L, "<<littab.size()<<") ";
                        }
                        //Rgisters
                        else if(opcode.count(word) > 0)
                        {
                            fout<<" ("<<opcode[word].first<<") ";
                        }
                        else
                        {
                            if(symtab.count(word) == 0)
                            {
                                symtab[word] = {lc,to_string(symtab.size()+1)};
                            }
                            fout<<" (S, "<<symtab[word].second<<") ";
                        }
                    }
                    lc++;
                }
                fout<<endl;
            }
            fin.close();
            fout.close();
            writeSymtab();
            writePooltab();   
        }
    
    void writeSymtab()
    {
        ofstream sout("sym.txt");
        for(auto &i : symtab)
        {
            sout<<i.second.second<<" "<<i.first<<" "<<i.second.first;
            sout<<endl;
        }
        sout.close();
    }

    void writeLittab()
    {
        ofstream lout("lit.txt");
        for(auto &i: littab)
        {
            lout<<i.first<<" "<<i.second;
            lout<<endl;
        }
        lout.close();
    }
    
    void writePooltab()
    {
        ofstream pout("pool.txt");
        for(auto &i : pooltab)
        {
            cout<<i<<endl;
        }
        pout.close();
    }
    void displaySymtab()
    {
        ifstream fin("sym.txt");
        string line;
        cout<<"Symbol Table"<<endl;
        while(getline(fin,line))
        {
            cout<<line<<endl;
        }
        fin.close();
    }
    
};

int main()
{
    Pass1 obj;
    cout<<"Scanning the input..."<<endl;
    obj.execute();
    
    
    
    return 0;
}
