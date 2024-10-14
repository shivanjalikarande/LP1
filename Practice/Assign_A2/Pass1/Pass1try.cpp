#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class Pass1
{
    int loc = 0;
    int mntIndex = 0;
    vector<pair<string,int>>MNT;
    vector<string>MDT;
    vector<pair<string,string>>ALA;
    ifstream fin,fmdt,fmnt;
    ofstream fout;

    public:
        Pass1()
        {
            fin.open("input.txt");
            fmdt.open("mdt.txt");
            fmnt.open("mnt.txt");
            fout.open("output.txt");
        }
        void execute()
        {
            string line,word;
            while(getline(fin,line))
            {
                stringstream ss(line);
                ss>>word;
                if(word == "MACRO")
                {
                    loc++;
                    getline(fin,line);
                    MDT.push_back(line);
                    ss.clear();
                    ss.str(line);
                    ss>>word;
                    mntIndex++;
                    MNT.push_back({word,loc});
                    
                    vector<string>args;
                    if(line.size() > word.size())
                    {
                        string remainingStr = line.substr(word.size());
                        stringstream argStr(remainingStr);
                        string arg;

                        while(getline())
                    }
                }
                else if(word == "END")
                {
                    break;
                }
            }
        }
};

int main()
{
    Pass1 pass1;
    pass1.execute();
}