#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <fstream>
using namespace std;

class macroExpand
{
    vector<string> mdt;
    vector<pair<string, vector<int>>> mnt;
    vector<pair<string, string>> kpdtab;

public:
    macroExpand()
    {
        get_mdt();
        get_mnt();

        get_kpdtab();
    }
    vector<string> split(string &line, char del)
    {
        vector<string> ans;
        string temp = "";
        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i];
            if (ch == del)
            {
                ans.push_back(temp);
                temp = "";
                while (i < line.length() && line[i] == del)
                {
                    i++;
                }
                i--;
            }
            else
            {
                temp += (ch);
            }
        }
        if (!temp.empty())
        {
            ans.push_back(temp);
        }
        return ans;
    }

    void open_file(string f_name)
    {
        ifstream obj;
        obj.open(f_name);
        if (!obj.is_open())
        {
            cerr << "File cannot be opened " << endl;
            return;
        }
        process_code(obj);
    }
    void get_mdt()
    {
        ifstream obj;
        obj.open("../Pass1/mdt.txt");
        if (!obj.is_open())
        {
            cerr << "Error in opening file\n";
            return;
        }
        string line;
        while (getline(obj, line))
        {
            mdt.push_back(line);
        }
        cout << "MDT: " << endl;
        for (auto i : mdt)
        {
            cout << i << endl;
        }
    }
    void get_mnt()
    {
        ifstream obj;
        obj.open("../Pass1/mnt.txt");
        if (!obj.is_open())
        {
            cerr << "Error in opening file\n";
            return;
        }
        string line;

        while (getline(obj, line))
        {
            vector<string> ans = split(line, ' ');
            for (string i : ans)
            {
                cout << i << " ";
            }
            cout << endl;
            string name = ans[0];
            vector<int> param;
            for (int i = 1; i < ans.size(); i++)
            {
                param.push_back(stoi(ans[i]));
            }
            mnt.push_back({name, param});
        }
        cout << "\nMNT: \n";
        for (auto i : mnt)
        {
            cout << i.first << " ";
            for (auto j : i.second)
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
    void get_kpdtab()
    {
        ifstream obj;
        obj.open("../Pass1/kpdtab.txt");
        if (!obj.is_open())
        {
            cerr << "Error in opening file\n";
            return;
        }
        string line;
        while (getline(obj, line))
        {
            vector<string> ans = split(line, ' ');
            string name = ans[0];
            string val = "";
            if (ans.size() > 1)
            {
                val = ans[1];
            }

            kpdtab.push_back({name, val});
        }
        cout << "\nKPDTAB:\n";
        for (auto i : kpdtab)
        {
            cout << i.first << " " << i.second << endl;
        }
    }

    void process_code(ifstream &obj)
    {
        ofstream output1;
        output1.open("macro_expanded.txt");
        if (!output1.is_open())
        {
            cerr << "Cannot open file" << endl;
            return;
        }

        string line;
        while (getline(obj, line))
        {
            vector<string> ans = split(line, ' ');
            // for(string i:ans){
            //     cout<<i<<" ";
            // }
            cout << endl;
            string name = ans[0];
            int pp = 0;
            int kp = 0;
            int mdtp = 0;
            int kpdtp = 0;
            for (auto i : mnt)
            {
                if (i.first == name)
                {
                    pp = i.second[0];
                    kp = i.second[1];
                    mdtp = i.second[2];
                    kpdtp = i.second[3];
                    break;
                }
            }
            // cout<<pp<<" "<<kp<<" "<<mdtp<<" "<<kpdtp<<endl;
            vector<string> aptab(pp + kp);
            int i = 1;
            int a = 0;
            while (pp > 0)
            {
                aptab[a] = ans[i];
                a++;
                // aptab.push_back(ans[i]);
                i++;
                pp--;
            }
            int original_kp = kp;
            bool f = 0;
            vector<string> keys = {};
            while (kp > 0)
            {
                if (i == ans.size())
                {
                    f = 1;
                    break;
                }

                string key = "";
                string val = "";
                int ind;

                for (ind = 0; ind < ans[i].size(); ind++)
                {
                    if (ans[i][ind] == '=')
                    {
                        break;
                    }
                    else
                    {
                        key += ans[i][ind];
                    }
                }
                keys.push_back(key);
                ind++;
                for (ind; ind < ans[i].size(); ind++)
                {
                    if (ans[i][ind] == ',')
                    {
                        break;
                    }
                    else
                    {
                        val += ans[i][ind];
                    }
                }
                // cout<<"\nkey="<<key<<" val="<<val<<endl;
                ind = 0;
                int j = kpdtp - 1;
                f = 0;
                for (j; j < kpdtp + original_kp - 1; j++)
                {
                    string x = kpdtab[j].first;
                    if (x == key)
                    {
                        aptab[ind + a] = val;
                        break;
                    }
                    ind++;
                }

                kp--;
                i++;
            }
            for (string k : keys)
            {
                // cout<<k<<" ";
            }
            cout << endl;
            if (f == 1)
            {
                bool present = 0;
                int j = kpdtp - 1;
                int ind = 0;
                for (j; j < kpdtp + original_kp - 1; j++)
                {
                    present = 0;
                    for (string x : keys)
                    {
                        if (x == kpdtab[j].first)
                        {
                            // cout<<"present"<<x;
                            present = 1;
                        }
                    }
                    if (present == 0)
                    {

                        aptab[ind + a] = kpdtab[j].second;
                        // cout<<"index="<<kpdtab[j].second<<" ";
                        // cout<<aptab[2]<<" ";
                    }
                    ind++;
                }
            }
            // cout<<name<<endl;
            // for(string x:aptab){
            //     cout<<x<<" ";
            // }
            // cout<<"---"<<endl;
            int pointer = mdtp - 1;
            for (pointer; pointer < mdt.size(); pointer++)
            {
                if (mdt[pointer] == "MEND")
                {
                    break;
                }
                else
                {
                    vector<string> def = split(mdt[pointer], ' ');
                    int ind = 0;
                    output1 << def[ind] << " ";
                    ind++;
                    while (ind < def.size())
                    {
                        if (def[ind][0] == '(' && def[ind][1] == 'P')
                        {
                            int x = def[ind][3] - '0';
                            output1 << aptab[x - 1] << " ";
                        }
                        else
                        {
                            output1 << def[ind] << " ";
                        }
                        ind++;
                    }
                }
                output1 << endl;
            }
            output1 << endl;
        }
    }
};

int main()
{
    // cout<<"hello\n";
    macroExpand obj;
    obj.open_file("../Pass1/input.txt");

    
}