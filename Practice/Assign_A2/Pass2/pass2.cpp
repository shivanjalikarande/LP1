#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Pass2
{
    int loc = 0;
    int mntInd = 0;
    ifstream fin,fmnt,fmdt;
    ofstream fout;

public:
    Pass2()
    {
        fin.open("../Pass1.input.txt");
        fmnt.open("../Pass1/mnt.txt");
        fmdt.open("../Pass1/mdt.txt");
        fout.open("output.txt");
    }

    void execute()
    {
        string line;
        string word;

        while (getline(fin, line))
        {
            stringstream ss(line);
            ss >> word;

            if (word == "MACRO")
            {
                while(getline(fin,line))
                {
                    ss.clear();
                    ss.str(line);
                    ss >> word;
                    if(word == "MEND")
                    {
                        break;
                    }
                }
            }
            else if (word == "END")
            {
                break; // Stop execution on "END"
            }
            else
            {
                string mname, no;
                while(getline(fmnt,line))
                {
                    stringstream smnt(line);
                    smnt >> no;
                    smnt >> mname;
                    if(word == mname)
                    {
                        smnt >> no;
                        int mdtIdx = stoi(no);

                        //handling arglist

                        for(int i=1;i<=mdtIdx;i++)
                        {
                            getline(fmdt,line);
                        }
                        fout<<line;
                        while(getline(fmdt,line))
                        {
                            stringstream ss(line);
                            ss >> word;
                            ss >> word;
                            if(word == "MEND")
                            {
                                break;
                            }
                            string str = word;

                            
                        }

                    }
                }
                else
                {
                    fout<<line<<endl;
                }
            }
        }
    }

    void displayMNT()
    {
        cout << "\n---------MNT------" << endl;
        int i = 1;
        for (const auto &m : MNT)
        {
            cout << i << " " << m.first << "\t" << m.second << endl; 
            fmnt << i << " " << m.first << "\t" << m.second << endl;
            i++;
        }
        cout << endl;
    }

    void displayMDT()
    {
        cout << "\n--------MDT--------" << endl;
        int i = 1;
        for (const auto &md : MDT)
        {
            cout << i << " " << md << endl;
            fmdt << i << " " << md << endl;
            i++;
        }
        cout << endl;
    }

    void displayALA()
    {
        cout << "\n--------ALA--------" << endl;
        int i = 1;
        for (const auto &arg : ALA)
        {
            cout << i << " " << arg.first << " " << arg.second << endl;
            fala << i << " " << arg.first << " " << arg.second << endl;
            i++;
        }
        cout << endl;
    }
};

int main()
{
    Pass2 obj;
    obj.execute();
    
    return 0;
}
