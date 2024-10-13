#include <iostream>
#include <string.h>
using namespace std;

class CPU_Scheduling
{
public:
    int num;
    int *process;
    int *chart;
    int *AT;
    int *BT;

    CPU_Scheduling()
    {
        cout << "\nEnter the number of processes you want to execute ? ";
        cout << "\n>>";
        cin >> num;

        AT = new int[num];
        BT = new int[num];
        process = new int[num];
        chart = new int[num + 1];

        for (int i = 0; i < num; i++)
        {
            process[i] = i + 1;
            cout << "\nEnter Arrival time for P" << i + 1 << " : ";
            cin >> AT[i];
            cout << "\nEnter Burst time for P" << i + 1 << " : ";
            cin >> BT[i];
            chart[i] = 0;
        }
    }

    void FCFS()
    {
        int *CT = new int[num];
        int *TAT = new int[num];
        int *WT = new int[num];

        for (int i = 0; i < num; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                if (AT[i] > AT[j])
                {
                    int temp = AT[i];
                    AT[i] = AT[j];
                    AT[j] = temp;
                    temp = BT[i];
                    BT[i] = BT[j];
                    BT[j] = temp;
                    temp = process[i];
                    process[i] = process[j];
                    process[j] = temp;
                }
            }
        }

        int sum = 0;
        for (int i = 0; i < num; i++)
        {
            chart[i] = process[i];
            CT[i] = sum + BT[i];
            sum = CT[i];
            TAT[i] = CT[i] - AT[i];
            WT[i] = TAT[i] - BT[i];
        }
        cout << "\n----------------------------------------------------------------------------------------------";
        cout << "\n"
             << "PROCESS" << "\t | \t" << "AT" << "\t  |  \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t";
        cout << "\n----------------------------------------------------------------------------------------------";
        for (int i = 0; i < num; i++)
        {
            cout << "\n"
                 << "P" << process[i] << "\t | \t" << AT[i] << "\t  |  \t" << BT[i] << "\t | \t" << CT[i] << "\t | \t" << TAT[i] << "\t | \t" << WT[i] << "\t | \t";
        }
        cout << "\n----------------------------------------------------------------------------------------------";
        cout << "\n\nGantt Chart : ";
        for (int i = 0; i < num; i++)
        {
            cout << "P" << chart[i] << "  ->  ";
        }
    }

    void SJF()
    {
        int *CT = new int[num];
        int *TAT = new int[num];
        int *WT = new int[num];

        for (int i = 0; i < num; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                if (BT[i] > BT[j])
                {
                    int temp = AT[i];
                    AT[i] = AT[j];
                    AT[j] = temp;
                    temp = BT[i];
                    BT[i] = BT[j];
                    BT[j] = temp;
                    temp = process[i];
                    process[i] = process[j];
                    process[j] = temp;
                }
            }
        }

        CT[0] = AT[0] + BT[0];
        int sum = BT[0];
        for (int i = 1; i < num; i++)
        {
            chart[i] = process[i];
            CT[i] = sum + BT[i];
            sum = CT[i];
            TAT[i] = CT[i] - AT[i];
            WT[i] = TAT[i] - BT[i];
        }

        cout << "\n----------------------------------------------------------------------------------------------";
        cout << "\n"
             << "PROCESS" << "\t | \t" << "AT" << "\t  |  \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t";
        cout << "\n----------------------------------------------------------------------------------------------";
        for (int i = 0; i < num; i++)
        {
            cout << "\n"
                 << "P" << process[i] << "\t | \t" << AT[i] << "\t  |  \t" << BT[i] << "\t | \t" << CT[i] << "\t | \t" << TAT[i] << "\t | \t" << WT[i] << "\t | \t";
        }
        cout << "\n----------------------------------------------------------------------------------------------";
        cout << "\n\nGantt Chart : ";
        for (int i = 0; i < num; i++)
        {
            cout << "P" << chart[i] << "  ->  ";
        }
    }

    void RR()
    {
        int *CT = new int[num];
        int *TAT = new int[num];
        int *WT = new int[num];
        int *temp_BT = new int[num];
        int quantum;
        cout << "\nEnter the Time Slice : ";
        cin >> quantum;
        for (int i = 0; i < num; i++)
        {
            temp_BT[i] = BT[i];
            CT[i] = 0;
        }



        bool done;
        int t = 0;
        cout << "\n\nGANTT CHART : ";
        while (true)
        {
            done = true;

            for (int i = 0; i < num; i++)
            {
                if (AT[i] > t)
                {
                    // t = t + (AT[i] - t);
                    i = 0;
                    if (temp_BT[i] == 0)
                    {
                        t = t + (AT[i] - t);
                    }
                }
                if (temp_BT[i] != 0)
                {
                    done = false;
                    if (temp_BT[i] > quantum)
                    {
                        temp_BT[i] = temp_BT[i] - quantum;
                        CT[i] = t + quantum;
                        t = t + quantum;
                        cout << "P" << i + 1 << "  (" << t << ")  -> ";
                    }
                    else
                    {
                        CT[i] = t + temp_BT[i];
                        t = t + temp_BT[i];
                        temp_BT[i] = 0;
                        cout << "P" << i + 1 << "  (" << t << ")  -> ";
                    }
                }
            }
            if (done == true)
            {
                break;
            }
        }

        for (int i = 0; i < num; i++)
        {
            TAT[i] = CT[i] - AT[i];
            WT[i] = TAT[i] - BT[i];
        }

        cout << "\n----------------------------------------------------------------------------------------------";
        cout << "\n"
             << "PROCESS" << "\t | \t" << "AT" << "\t  |  \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t";
        cout << "\n----------------------------------------------------------------------------------------------";
        for (int i = 0; i < num; i++)
        {
            cout << "\n"
                 << "P" << process[i] << "\t | \t" << AT[i] << "\t  |  \t" << BT[i] << "\t | \t" << CT[i] << "\t | \t" << TAT[i] << "\t | \t" << WT[i] << "\t | \t";
        }
        cout << "\n----------------------------------------------------------------------------------------------";
    }
};

int main()
{
    CPU_Scheduling cpu;
    // cpu.FCFS();
    // cpu.SJF();
    cpu.RR();
}