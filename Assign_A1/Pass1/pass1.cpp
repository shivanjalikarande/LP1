#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
using namespace std;


class Pass1
{
public:
    map<string, pair<string, string>> opcode;
    map<string, pair<int, string>> symtab;
    vector<pair<string, int>> littab;
    vector<string> pooltab;
    int litindex = 0, lc = -1;

    void initializeOpcodeMap()
    {
        opcode = {
            {"STOP", {"IS", "00"}}, {"ADD", {"IS", "01"}}, {"SUB", {"IS", "02"}}, {"MULT", {"IS", "03"}}, {"MOVER", {"IS", "04"}}, {"MOVEM", {"IS", "05"}}, {"COMP", {"IS", "06"}}, {"BC", {"IS", "07"}}, {"DIV", {"IS", "08"}}, {"READ", {"IS", "09"}}, {"PRINT", {"IS", "10"}}, {"START", {"AD", "01"}}, {"END", {"AD", "02"}}, {"ORIGIN", {"AD", "03"}}, {"EQU", {"AD", "04"}}, {"LTORG", {"AD", "05"}}, {"DC", {"DL", "01"}}, {"DS", {"DL", "02"}}, {"AREG", {"1", ""}}, {"BREG", {"2", ""}}, {"CREG", {"3", ""}}, {"DREG", {"4", ""}}, {"LT", {"1", ""}}, {"LE", {"2", ""}}, {"EQ", {"3", ""}}, {"GT", {"4", ""}}, {"GE", {"5", ""}}, {"ANY", {"6", ""}}};
    }

    void execute()
    {
        initializeOpcodeMap();
        ifstream fin("./input2/input2.txt");
        ofstream fout("./input2/output.txt");
        string line, word;
        symtab.clear();
        littab.clear();
        pooltab.clear();
        litindex = 0;
        lc = -1;

        while (getline(fin, line))
        {
            stringstream st(line);
            st >> word;
            string label = "";

            if (opcode.count(word) == 0)
            {
                if (symtab.count(word) == 0)
                {
                    symtab[word] = {lc, to_string(symtab.size() + 1)};
                }
                else
                {
                    symtab[word].first = lc;
                }
                label = word;
                st >> word;
            }

            string operation = word;
            if (operation == "START")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                st >> word;
                fout << "(C, " << word << ") ";
                lc = stoi(word);
            }
            else if (operation == "END")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                fout << endl;
                pooltab.push_back("#" + to_string(litindex + 1));
                for (; litindex < littab.size(); litindex++)
                {
                    fout << lc << " ";
                    fout << "( " << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                    littab[litindex].second = lc;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(2, literal.length() - 3);
                    fout << "( C, " << sublit << ") ";
                    fout << endl;
                    lc++;
                }
            }
            else if (operation == "LTORG")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                fout << endl;
                pooltab.push_back("#" + to_string(litindex + 1));
                for (; litindex < littab.size(); litindex++)
                {
                    fout << lc << " ";
                    fout << "( " << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                    littab[litindex].second = lc;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(2, literal.size() - 3);
                    fout << "(C, " << sublit << ") ";
                    fout << endl;
                    lc++;
                }
            }
            else if (operation == "EQU")
            {
                fout << "    ";
                st >> word;
                int plusminusindex = 0;
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] == '+' || word[i] == '-')
                    {
                        plusminusindex = i;
                        break;
                    }
                }
                char plusminus = '0';
                string aftersign = "0";
                string beforesign;
                if (plusminusindex != 0)
                {
                    plusminus = word[plusminusindex];
                    aftersign = word.substr(plusminusindex + 1);
                    beforesign = word.substr(0, plusminusindex);
                }
                else
                {
                    beforesign = word.substr(0, word.length());
                }
                symtab[label].first = symtab[beforesign].first;

                if (plusminus == '+')
                {
                    if (aftersign != "0")
                        symtab[label].first += stoi(aftersign);
                }
                else
                {
                    if (aftersign != "0")
                        symtab[label].first -= stoi(aftersign);
                }
            }
            else if (operation == "ORIGIN")
            {
                fout << "    ";
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
                st >> word;
                int plusminusindex = 0;
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] == '+' || word[i] == '-')
                    {
                        plusminusindex = i;
                        break;
                    }
                }
                char plusminus = '0';
                string beforesign, aftersign;
                if (plusminusindex != 0)
                {
                    plusminus = word[plusminusindex];
                    aftersign = word.substr(plusminusindex + 1);
                    beforesign = word.substr(0, plusminusindex);
                }
                else
                {
                    beforesign = word.substr(0, word.length());
                }
                lc = symtab[beforesign].first;
                fout << "(S , " << symtab[beforesign].second << ")";

                if (plusminus == '+')
                {
                    lc += stoi(aftersign);
                    fout << "+" << aftersign << "\n";
                }
                else if (plusminus == '-')
                {
                    lc -= stoi(aftersign);
                    fout << "-" << aftersign << "\n";
                }
            }
            else
            {
                fout << lc << " ";
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

                while (st >> word)
                {
                    if (operation == "DC")
                    {
                        // word = word.substr(1, word.length() - 2);
                        fout << "(C, " << word << ") ";
                    }
                    else if (operation == "DS")
                    {
                        fout << "(C, " << word << ") ";
                        lc += stoi(word) - 1;
                    }
                    else if (word[0] == '=')
                    {
                        littab.push_back({word, lc});
                        fout << "(L, " << littab.size() << ") ";
                    }
                    else if (opcode.count(word) > 0)
                    {
                        fout << "(" << opcode[word].first << ") ";
                    }
                    else
                    {
                        if (symtab.count(word) == 0)
                        {
                            symtab[word] = {lc, to_string(symtab.size() + 1)};
                        }
                        fout << "(S, " << symtab[word].second << ") ";
                    }
                }
                lc++;
            }
            fout << endl;
        }

        fin.close();
        fout.close();

        writeSymtab();
        writeLittab();
        writePooltab();

        cout << "\nInput file is Processed Successfully!" << endl;
    }

    void writeSymtab()
    {
        ofstream sout("./input2/sym.txt");
        for (auto &i : symtab)
        {
            sout << i.second.second << " " << i.first << " " << i.second.first;
            sout << endl;
        }
        sout.close();
    }

    void writeLittab()
    {
        ofstream lout("./input2/lit.txt");
        for (auto &i : littab)
        {
            lout << i.first << " " << i.second;
            lout << endl;
        }
        lout.close();
    }

    void writePooltab()
    {
        ofstream pout("./input2/pool.txt");
        for (auto &i : pooltab)
        {
            pout << i;
            pout << endl;
        }
        pout.close();
    }

    void displaySymtab()
    {
        ifstream fin("./input2/sym.txt");
        string line;
        cout << "\nSymbol Table:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }

    void displayLittab()
    {
        ifstream fin("./input2/lit.txt");
        string line;
        cout << "\nLiteral Table:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }

    void displayPooltab()
    {
        ifstream fin("./input2/pool.txt");
        string line;
        cout << "\nPool Table:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }
    void displayOutput()
    {
        ifstream fin("./input2/output.txt");
        string line;
        cout << "\nOutput:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }
};



int main()
{
    Pass1 obj;
    int choice;
    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Process the input file" << endl;
        cout << "2. Display Output" << endl;
        cout << "3. Display Symbol Table" << endl;
        cout << "4. Display Literal Table" << endl;
        cout << "5. Display Pool Table" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            obj.execute();
            break;
        case 2:
            obj.displayOutput();

            break;
        case 3:
            obj.displaySymtab();

            break;
        case 4:
            obj.displayLittab();
            break;
        case 5:
            obj.displayPooltab();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    return 0;
}