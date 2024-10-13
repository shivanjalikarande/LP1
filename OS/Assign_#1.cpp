#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


class Task
{
    int no;
    int arrival_time;
    int Brust_time;
    int comp_time;
    int TAT;
    int waiting_time;

public:
    Task()
    {
        no = 0;
        arrival_time = 0;
        Brust_time = 0;
        comp_time = 0;
        TAT = 0;
        waiting_time = 0;
    }
    void inputTask()
    {
        cout << "\nEnter no of task:";
        cin >> no;
        cout << "Enter the arrival time:";
        cin >> arrival_time;
        cout << "\nEnter Brust time:";
        cin >> Brust_time;
    }
    void displayTask()
    {
        cout << no << setw(5) << arrival_time << setw(5) << Brust_time
             << setw(5) << comp_time << setw(5) << TAT << setw(5) << waiting_time << endl;
    }
    friend class shedule;
};
class shedule
{
    vector<Task> v;

public:
    shedule()
    {
    }
    void input()
    {
        int n;
        cout << "\nEnter number of task:";
        cin >> n;
        Task t;
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter the task " << i + 1 << endl;
            t.inputTask();
            v.push_back(t);
        }
    }
    void sort_According_to_arrival()
    {
        sort(v.begin(), v.end(), [](Task &T1, Task &T2)
             { return T1.arrival_time < T2.arrival_time; });
    }
    void display()
    {
        cout << "pno" << setw(5) << "AT" << setw(5) << "BT" << setw(5)
             << "CT" << setw(5) << "TAT" << setw(5) << "WT" << endl;
        for (int i = 0; i < v.size(); i++)
        {
            v[i].displayTask();
        }
    }
    void fcfs()
    {
        sort_According_to_arrival();
        int t = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (t <= v[i].arrival_time)
            {
                t = t + v[i].arrival_time;
            }
            v[i].comp_time = t + v[i].Brust_time;
            v[i].TAT = v[i].comp_time - v[i].arrival_time;
            v[i].waiting_time = v[i].TAT - v[i].Brust_time;
            t = v[i].comp_time;
        }
    }
    void SJF()
    {
        sort_According_to_arrival();
        int t = 0;
        for (int i = 0; i < v.size() - 1; i++)
        {
            t = t + v[i].Brust_time;
            int index = i + 1;
            Task tk = v[index];
            for (int j = i + 1; v[j].arrival_time <= t && j < v.size();
                 j++)
            {
                if (tk.Brust_time > v[j].Brust_time)
                {
                    cout << index << " ";
                    index = j;
                    tk = v[j];
                }
            }
            swap(v[i + 1], v[index]);
        }
        t = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (t < v[i].arrival_time)
            {
                t = v[i].arrival_time;
            }
            v[i].comp_time = t + v[i].Brust_time;
            v[i].TAT = v[i].comp_time - v[i].arrival_time;
            v[i].waiting_time = v[i].TAT - v[i].Brust_time;
            t = v[i].comp_time;
        }
    }
    void RR()
    {
        sort_According_to_arrival();
        int Time_quantum;
        cout << "\nEnter time quantum:";
        cin >> Time_quantum;
        vector<int> Remaining_time(v.size(), 0);
        for (int i = 0; i < v.size(); i++)
        {
            Remaining_time[i] = v[i].Brust_time;
        }
        int i = 0;
        int t = 0;
        int n = v.size();
        queue<int> q;
        int prev;
        q.push(v[i].no - 1);
        while (!q.empty())
        {
            cout << t << endl;
            int p = q.front();
            q.pop();
            int flag = 0;
            prev = t;
            if (t < v[p].arrival_time)
            {
                t = t + v[p].arrival_time;
            }
            if (Remaining_time[p] > Time_quantum)
            {
                Remaining_time[p] = Remaining_time[p] - Time_quantum;
                t = t + Time_quantum;
                flag = 1;
            }
            else if (Remaining_time[p] != 0 && Remaining_time[p] <=
                                                   Time_quantum)
            {
                t = t + Remaining_time[p];
                Remaining_time[p] = 0;
                v[p].comp_time = t;
            }
            for (int j = p + 1; j < n; j++)
            {
                if (v[j].arrival_time <= t && v[j].arrival_time > prev)
                {
                    q.push(j);
                }
            }
            if (flag == 1)
            {
                q.push(p);
                flag = 0;
            }
        }
        for (int i = 0; i < v.size(); i++)
        {
            v[i].TAT = v[i].comp_time - v[i].arrival_time;
            v[i].waiting_time = v[i].TAT - v[i].Brust_time;
        }
    }
    void priority()
    {
        vector<int> priority(v.size(), 0);
        for (int i = 0; i < v.size(); i++)
        {
            cout << "\nEnter priority of " << v[i].no << " process :";
            cin >> priority[i];
        }
        sort_According_to_arrival();
        int t = 0;
        int i = 0;
        while (i < v.size())
        {
            int ind = i;
            for (int j = i + 1; j < v.size(); j++)
            {
                if (v[j].arrival_time <= t && priority[j] <
                                                  priority[ind])
                {
                    ind = j;
                }
            }
            swap(v[ind], v[i]);
            if (t < v[i].arrival_time)
            {
                t = t + v[i].arrival_time;
            }
            t = t + v[i].Brust_time;
            v[i].comp_time = t;
            i++;
        }
        for (int i = 0; i < v.size(); i++)
        {
            v[i].TAT = v[i].comp_time - v[i].arrival_time;
            v[i].waiting_time = v[i].TAT - v[i].Brust_time;
        }
    }
};


int main()
{
    shedule s;
    int choise;
    while (1)
    {
        cout << "\n--------- CPU scheduling options --------------\n";
        cout << "\n1.Input\n2-FCFS (first come first serve)\n3-SJF (shortest job first)\n4-RR (round robin)\n5-priority\n";
        cout << "---------------------------------------------------\n";
        cout << "\nEnter choise:";
        cin >> choise;
        switch (choise)
        {
            case 1:
                s.input();
                break;
            case 2:
                s.fcfs();
                s.display();
                break;
            case 3:
                s.SJF();
                s.display();
                break;
            case 4:
                s.RR();
                s.display();
                break;
            case 5:
                s.priority();
                s.display();
                break;
            default:
                cout << "\n--Invalid choise ---";
                exit(0);
            }
    }
            return 0;
}

