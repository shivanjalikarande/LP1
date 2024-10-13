#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>
#include <utility>
#include <sstream>
#include <fstream>

using namespace std;

class Pass2
{
    private:
        vector<pair<string,int>>symtab;
        vector<pair<string,int>>littab;
        ifstream sy,li,fin;
        ofstream fout;
    public:
    
        Pass2()
        {
            
            sy.open("../Pass1/sym.txt");
            li.open("../Pass1/lit.txt");
            fin.open("../Pass1/output.txt");
            fout.open("machine.txt");
        }
        
        void generate()
        {
            string line="";
            string word ="";
            //generate symbol tbl
            while(getline(sy,line))
            {
                stringstream ss(line);
                string label;
                int address;
                ss >> label >> word >> address;
                symtab.push_back({label,address});
            }

            //generate literal tbl
            while(getline(li,line))
            {
                stringstream ss(line);
                int address;
                string label;
                ss >> label >> address;
                littab.push_back({label,address});
            }
            
            //generate machine code
            while(getline(fin,line))
            {
                stringstream ss(line);
                string location,opcode,operand;
                ss >> location >> opcode;
                
                string code="";
                if(opcode == "(IS,")
                {
                    ss >> code;
                    string instructionCode = code.substr(0,code.size()-1);
                    fout << location << " " << instructionCode<<" ";
                    
                    while(ss >> word)
                    {
                        if(word == "(S,")
                        {
                            ss >> operand;
                            int symIndex = stoi(operand.substr(0,operand.size()-1));
                            fout << symtab[symIndex].second<<" "<<endl;
                        }
                        else if(word == "(L,")
                        {
                            ss >> operand;
                            int litIndex = stoi(operand.substr(0,operand.size()-1));
                            fout << littab[litIndex].second<<" "<<endl;
                        }
                        else if(word == "(C,")
                        {
                            
                        }
                        else
                        {
                            fout << word <<" ";
                        }
                    }
                    
                }
                else if(opcode == "(DL,")
                {
                    string directive;
                    ss >> directive;
                    if(directive == "01")
                    {
                        ss >> word;
                        fout<<location<<" 00 00 "<<word.substr(3,word.size()-4);
                    }
                    else if(directive == "02")
                    {
                        fout << location << " 00 00 00";
                    }   
                }
                fout<<"\n";
            }
        }
        void show()
            {
                cout<<"======== SYMBOL TABLE ========="<<endl;
                for(auto x : symtab)
                {
                    cout<<x.first <<" "<<x.second<<endl;
                }
                cout<<"\n======== LITERAL TABLE========="<<endl;
                for(auto x : littab)
                {
                    cout<<x.first<<" "<<x.second<<endl;
                }
            }
            
        
        ~Pass2()
        {
            sy.close();
            li.close();
            fin.close();
            fout.close();
        }
};

int main()
{
    Pass2 obj;
    cout<<"Scanning the input..."<<endl;
    obj.generate();
    obj.show();
    
    
    return 0;
}
