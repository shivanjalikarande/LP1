#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Pass2
{
    vector<pair<string, int>> MNT; // Macro Name Table
    vector<string> MDT;            // Macro Definition Table
    ifstream fin, fmnt, fmdt;
    ofstream fout;

public:
    Pass2()
    {
        fin.open("input.txt"); // Input source file with macro invocation
        fmnt.open("../Pass1/mnt.txt");
        fmdt.open("../Pass1/mdt.txt");
        fout.open("output.txt"); // Output file with expanded macros

        loadMNT();
        loadMDT();
    }

    void loadMNT()
    {
        string line, macroName;
        int index, loc;
        while (getline(fmnt, line))
        {
            stringstream ss(line);
            ss >> index >> macroName >> loc;
            MNT.push_back({macroName, loc});
        }
    }

    void loadMDT()
    {
        string line;
        stringstream ss;
        string word;
        while (getline(fmdt, line))
        {
            ss.str(line);
            ss>>word;
            string remainingStr = line.substr(word.size());
            MDT.push_back(remainingStr);
            ss.clear();
        }
    }

    void printMDT()
    {
        ofstream fmdt;
        fmdt.open("MDT.txt");
        for(const auto& line:MDT)
        {
            fmdt << line << endl;
        }
    }

    void printMNT()
    {
        ofstream fmnt;
        fmnt.open("MNT.txt");
        for(const auto& line:MNT)
        {
            fmnt << line.first << " "<< line.second<<endl;
        }
    }

    void expandMacro(string macroName, vector<string> actualArgs)
    {
        // Find the macro in MNT
        int mntIndex = -1;
        for (const auto &m : MNT)
        {
            if (m.first == macroName)
            {
                mntIndex = m.second;
                break;
            }
        }
        // cout<<mntIndex<<endl;

        if (mntIndex == -1)
        {
            cerr << "Macro " << macroName << " not found in MNT" << endl;
            return;
        }

        // Start expanding the macro from MDT[mntIndex] until "MEND"
        for (int i = mntIndex+1; i < MDT.size(); i++)
        {
            cout<<i<<": "<<endl;
            string line = MDT[i-1];
            if(line == " MEND")
            {
                break;
            }
            cout<<line<<endl;
            stringstream ss(line);
            string word;
            ss >> word;

            // Skip the macro name (e.g., INCR, PVG) and start processing arguments
            // if (i == mntIndex)
            //     continue;

            // Perform argument substitution for #1, #2, etc.
            for (int j = 0; j < actualArgs.size(); ++j)
            {
                string placeholder = "#" + to_string(j + 1);
                size_t pos = line.find(placeholder);
                while (pos != string::npos)
                {
                    line.replace(pos, placeholder.length(), actualArgs[j]);
                    pos = line.find(placeholder, pos + actualArgs[j].length());
                }
            }

            fout << line << endl; // Output the expanded macro line
        }
    }

    void execute()
    {
        string line, word;
        while (getline(fin, line))
        {
            stringstream ss(line);
            ss >> word;

            if (word == "MACRO")
            {
                // Skip the macro definition part entirely
                while (word != "MEND")
                {
                    getline(fin, line);
                    ss.clear();
                    ss.str(line);
                    ss >> word;
                }
            }
            else
            {
                // Check if the word is a macro name (present in MNT)
                bool isMacro = false;
                for (const auto &m : MNT)
                {
                    if (m.first == word)
                    {
                        isMacro = true;
                        break;
                    }
                }

                if (isMacro)
                {
                    // Split the rest of the line to get actual arguments
                    vector<string> actualArgs;
                    string remainingStr = line.substr(word.size());
                    stringstream argStream(remainingStr);
                    string arg;

                    while (getline(argStream, arg, ','))
                    {
                        arg.erase(0, arg.find_first_not_of(" "));
                        actualArgs.push_back(arg);
                    }

                    // Expand the macro
                    expandMacro(word, actualArgs);
                }
                else
                {
                    fout << line << endl; // If not a macro, just copy the line to output
                }
            }
        }
    }
    void print()
    {
        stringstream ss;
        for(const auto& line:MDT)
        {
            cout << line << endl;
        }
    }
};

int main()
{
    Pass2 obj;
    obj.loadMDT();
    obj.printMDT();
    obj.loadMNT();
    obj.printMNT();
    obj.execute();

    cout<<endl;
    obj.print();
    cout << "Macro expansion completed! Check output.txt" << endl;
    return 0;
}
