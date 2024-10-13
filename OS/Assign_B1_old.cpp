#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Task
{
    int no;
    int at, bt;
    int ct, tat, wt;

public:
    Task()
    {
        no = 0;
        at = bt = 0;
        ct = tat = wt = 0;
    }
    void input_info()
    {
        cout << "Enter the process number: ";
        cin >> no;
        cout << "Enter the arrival time: ";
        cin >> at;
        cout << "Enter the burst time: ";
        cin >> bt;
    }
    void display()
    {
        cout << "\n | " << no << " | " << at << " | " << bt << " | " << ct << " | " << tat << " | " << wt << " | " << endl;
    }
    friend class schedule;
};

class schedule
{
    vector<Task> arr;
    int n;

public:
    schedule()
    {
        n = 0;
        arr.resize(n);
    }

    void set_tasks()
    {
        cout << "\nEnter the number of tasks: ";
        cin >> n;
        arr.resize(n);
        for (int i = 0; i < n; i++)
        {
            Task obj;
            obj.input_info();
            arr[i] = obj;
        }
    }
    void display()
    { // fcfs and sjf
        int t = 0;
        for (int i = 0; i < n; i++)
        {
            if (t < arr[i].at)
            {
                t = arr[i].at;
            }
            arr[i].ct = t + arr[i].bt;
            arr[i].tat = arr[i].ct - arr[i].at;
            arr[i].wt = arr[i].tat - arr[i].bt;

            t = arr[i].ct;
        }
        cout << "\n----------------------------------------------" << endl;
        cout << " | Pr | AT | BT | CT | TAT | WT | " << endl;
        cout << "----------------------------------------------";
        for (int i = 0; i < n; i++)
        {
            arr[i].display();
            cout << "----------------------------------------------";
        }
    }
    void fcfs()
    {
        sort(arr.begin(), arr.end(), [](Task &t1, Task &t2)
             { return t1.at < t2.at; });
    }

    void sjf()
    {
        sort(arr.begin(), arr.end(), [](Task &t1, Task &t2)
             { return t1.at < t2.at; });

        int t = arr[0].at + arr[0].bt;
        for (int i = 1; i < (n - 1); i++)
        {
            int j = i + 1;
            int b = arr[i].bt;
            int job = i;
            while (j < n && arr[j].at <= t)
            {
                if (arr[j].bt < b)
                {
                    b = arr[j].bt;
                    job = j;
                }
                j++;
            }
            t += arr[job].at + arr[job].bt;
            swap(arr[i], arr[job]);
        }
        for (int i = 0; i < n; i++)
        {
            cout << arr[i].no << " ";
        }
    }

    void round_robin(int q)
    {
        vector<int> remaining(n);
        int total_slots = 0;
        for (int i = 0; i < n; i++)
        {
            remaining[i] = arr[i].bt;
            total_slots += arr[i].bt / q;
            if (arr[i].bt % q != 0)
            {
                total_slots++;
            }
        }
        sort(arr.begin(), arr.end(), [](Task &t1, Task &t2)
             { return t1.at < t2.at; });
        queue<int> ready;
        int temp_time = 0;
        int t = arr[0].at;
        int added = 1;
        ready.push(arr[0].no);
        for (int i = 0; i < total_slots; i++)
        {
            if (ready.empty())
            {
                t = arr[added].at;
                ready.push(arr[added].no);
                added++;
            }
            int curr = ready.front();
            cout << curr << " ";
            ready.pop();
            if (remaining[curr - 1] > q)
            {
                remaining[curr - 1] -= q;
                t += q;
                while (added < n && arr[added].at <= t)
                {
                    ready.push(arr[added].no);
                    added++;
                }

                ready.push(curr);
            }
            else
            {
                t += remaining[curr - 1];
                remaining[curr - 1] = 0;
                while (added < n && arr[added].at <= t)
                {
                    ready.push(arr[added].no);
                    added++;
                }

                for (int i = 0; i < n; i++)
                {
                    if (arr[i].no == curr)
                    {
                        arr[i].ct = t;
                        break;
                    }
                }
            }
        }

        // display
        for (int i = 0; i < n; i++)
        {
            arr[i].tat = arr[i].ct - arr[i].at;
            arr[i].wt = arr[i].tat - arr[i].bt;
        }

        cout << "\n----------------------------------------------" << endl;
        cout << " | Pr | AT | BT | CT | TAT | WT | " << endl;
        cout << "----------------------------------------------";
        for (int i = 0; i < n; i++)
        {
            arr[i].display();
            cout << "----------------------------------------------";
        }
    }

    void priority()
    {
        vector<int> priority(n);
        vector<int> remaining(n);
        int total_time = 0;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter priority for process " << (i + 1) << endl;
            cin >> priority[i];
            total_time += arr[i].bt;
            remaining[i] = arr[i].bt;
        }
        sort(arr.begin(), arr.end(), [](Task &t1, Task &t2)
             { return t1.at < t2.at; });
        int t = arr[0].at;
        queue<int> ready;

        ready.push(arr[0].no);
        int added = 1;
        for (int i = arr[0].at; i < total_time; i++)
        {
            int curr = ready.front();
            ready.pop();
            int j = added;
            while (j < n && arr[j].at <= i)
            {
                if (priority[arr[j].no] < p)
                {
                    added = j;
                    p = priority[arr[j].no];
                }
                j++;
            }
        }
    }
};

int main()
{
    schedule s;
    s.set_tasks();
    s.round_robin(2);
    // s.display();
    cout << "\nThanks!";
    return 0;
}