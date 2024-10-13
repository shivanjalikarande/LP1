#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Pass1
{
    int loc = 0;
    int mntInd = 0;
    vector<pair<string, int>> MNT;
    vector<string> MDT; 
    vector<pair<string,string>> ALA;
    ifstream fin;
    ofstream fmnt, fmdt, fala;

public:
    Pass1()
    {
        fin.open("input.txt");
        fmnt.open("mnt.txt");
        fmdt.open("mdt.txt");
        fala.open("ala.txt");
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
                loc++;
                getline(fin, line);
                MDT.push_back(line);
                ss.clear();
                ss.str(line);
                ss >> word;
                mntInd++;
                MNT.push_back({word, loc}); // Store macro name and location

                // Check if the line is long enough
                vector<string> args;
                if (line.size() > word.size())
                {
                    string remainingStr = line.substr(word.size()); // Safe to use now
                    stringstream argStream(remainingStr);
                    string arg;

                    // Split remainingStr by comma
                    while (getline(argStream, arg, ',')) 
                    {
                        arg.erase(0, arg.find_first_not_of(" "));
                        args.push_back(arg); // Store each argument
                    }

                    // Process arguments
                    for (int i = 0; i < args.size(); ++i) 
                    {
                        ALA.push_back({args[i], " #" + to_string(i + 1)});
                    }
                } 
                else 
                {
                    cout << "No arguments found for macro " << word << endl;
                }

                while (getline(fin, line))
                {
                    loc++;
                    ss.clear(); // Clear previous state
                    ss.str(line);
                    ss >> word;

                    if (word == "MEND")
                    {
                        break; // Stop reading when we find "MEND"
                    }
                    string str = "";
                    str += word + " ";
                    string remainingStr = line.substr(word.size()); // Safe to use now
                    stringstream argStream(remainingStr);
                    string arg;
                    while(getline(argStream,arg,','))
                    {
                        arg.erase(0, arg.find_first_not_of(" "));
                        if(arg[0] == '&')
                        {
                            for(const auto &a : ALA)
                            {
                                if(a.first == arg)
                                {
                                    str += a.second;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            str += arg;
                        }
                    }
                    MDT.push_back(str); // Store the macro definition
                }

                // Store "MEND" in MDT
                MDT.push_back("MEND");
                ALA.clear(); 
            }
            else if (word == "END")
            {
                break; // Stop execution on "END"
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
    Pass1 obj;
    obj.execute();
    obj.displayMNT();
    obj.displayMDT(); // Don't forget to display MDT
    obj.displayALA();
    return 0;
}
