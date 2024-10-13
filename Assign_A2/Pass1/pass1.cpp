#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class MNT
{
    public:
    int index;
    string macroName;
    int loc;
};

struct ALA
{
    int index;
    string arg;
};

struct MDT
{
    string line;
};

vector<MNT> mnt;
vector<ALA> ala;
vector<MDT> mdt;


void pass1()
{
    int mntc = 0, mdtc = 0, alac = 0, index = 0;
    string s, prev = "", substring;

    ifstream inp("input.txt");
    ofstream output("pass1_output.txt");

    while (getline(inp, s))
    {
        if (s == "MACRO")
        {
            prev = s;
            while (getline(inp, s) && s != "MEND")
            {
                if (prev == "MACRO")
                {
                    istringstream iss(s);
                    string word;
                    vector<string> str;
                    while (iss >> word)
                    {
                        str.push_back(word);
                    }

                    MNT m;
                    m.index = ++mntc;
                    m.macroName = str[0];
                    m.loc = ++mdtc;
                    mnt.push_back(m);

                    istringstream argStream(str[1]);
                    string token;
                    while (getline(argStream, token, ','))
                    {
                        ALA a;
                        a.index = alac++;
                        index = token.find("=");
                        if (index != string::npos)
                        {
                            a.arg = token.substr(0, index);
                        }
                        else
                        {
                            a.arg = token;
                        }
                        ala.push_back(a);
                    }
                }
                else
                {
                    index = s.find("&");
                    if (index != string::npos)
                    {
                        substring = s.substr(index);
                        for (size_t i = 0; i < ala.size(); i++)
                        {
                            if (ala[i].arg == substring)
                            {
                                s.replace(index, substring.length(), "#" + to_string(ala[i].index));
                                break;
                            }
                        }
                    }
                }
                MDT md;
                md.line = s;
                mdt.push_back(md);
                prev = s;
            }
            MDT md;
            md.line = s;
            mdt.push_back(md);
        }
        else
        {
            output << s << endl;
        }
    }
}

void displayMNT()
{
    cout << "MACRO NAME TABLE (MNT)" << endl;
    cout << "i macro loc" << endl;
    for (const auto &m : mnt)
    {
        cout << m.index << " " << m.macroName << " " << m.loc << endl;
    }
    cout << endl;
}

void displayALA()
{
    cout << "ARGUMENT LIST ARRAY (ALA) for Pass1" << endl;
    for (const auto &a : ala)
    {
        cout << a.index << " " << a.arg << endl;
    }
    cout << endl;
}

void displayMDT()
{
    cout << "MACRO DEFINITION TABLE (MDT)" << endl;
    for (const auto &md : mdt)
    {
        cout << md.line << endl;
    }
    cout << endl;
}

int main()
{
    pass1();
    cout << "\n*********PASS-1 MACROPROCESSOR***********\n";
    displayMNT();
    displayALA();
    displayMDT();
    return 0;
}