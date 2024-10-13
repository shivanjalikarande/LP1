#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

class Process
{
    int pID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;

    public:
        Process()
        {
            pID = arrivalTime = burstTime = completionTime = turnAroundTime = waitingTime = 0;
        }

        void scanProcess()
        {
            cout<<"Enter pID: ";
            cin>>pID;
            cout<<"Arrival Time: ";
            cin>>arrivalTime;
            cout<<"Burst Time: ";
            cin>>burstTime;
        }

        void displayProcess()
        {
            cout<<"|\t "<<pID<<"\t\t|\t"<<arrivalTime<<"\t|\t"<<burstTime<<"\t|\t"<<completionTime<<"\t|\t"<<turnAroundTime<<"\t|\t"<<waitingTime<<"\t|"<<endl;
            cout<<"+-----------------------+---------------+---------------+---------------+---------------+---------------+"<<endl;
        }
        friend class Schedule;
};

class Schedule
{
    vector<Process>v;

    public:

        void scanData()
        {
            int n;
            cout<<"\nEnter no of processes: ";
            cin>>n;
            cout<<endl;
            Process p;
            for(int i=0;i<n;i++)
            {
                cout<<"\nFor process "<<(i+1)<<endl;
                p.scanProcess();
                v.push_back(p);
            }
        }

        void display()
        {
            cout<<"+-----------------------+---------------+---------------+---------------+---------------+---------------+"<<endl;
            cout<<"|\tProcessId\t|\tAT\t|\tBT\t|\tCT\t|\tTAT\t|\tWT\t|"<<endl;
            cout<<"+-----------------------+---------------+---------------+---------------+---------------+---------------+"<<endl;
            for(int i=0;i<v.size();i++)
            {
                v[i].displayProcess();
            }
        }

        void sortBYArrivalTime()
        {
            sort(v.begin(),v.end(), [](Process &p1, Process &p2)
            {
                return p1.arrivalTime < p2.arrivalTime;
            });
        }

        void FCFS()
        {
            sortBYArrivalTime();
            int  t = 0;
            for(int i=0;i<v.size();i++)
            {
                if(t <= v[i].arrivalTime)
                {
                    t = t + v[i].arrivalTime;
                }
                v[i].completionTime = t + v[i].burstTime;
                v[i].turnAroundTime = v[i].completionTime - v[i].arrivalTime;
                v[i].waitingTime = v[i].turnAroundTime - v[i].burstTime;

                t = v[i].completionTime;

            }
        }

        void Priority()
        {
            vector<int>priority(v.size(),0);
            cout<<"\nEnter priority for each process"<<endl;
            for(int i=0;i<v.size();i++)
            {
                cout<<"Process "<<(i+1)<<": ";
                cin>>priority[i];
            }
            sortBYArrivalTime();
            int i = 0;
            int t = 0;
            int ind;
            while(i < v.size())
            {
                for(int j = i+1; v[j].arrivalTime <= t && j < v.size();j++)
                {
                    if(priority[j] < priority[ind])
                    {
                        ind = j;
                    }
                }
                swap(v[i],v[ind]);
                if(v[i].arrivalTime < t)
                {
                    t = t + v[i].arrivalTime;
                }

                t = t + v[i].burstTime;
                v[i].completionTime = t;
                i++;
            }
            for(int i=0;i<v.size();i++)
            {
                v[i].turnAroundTime = v[i].completionTime - v[i].arrivalTime;
                v[i].waitingTime = v[i].turnAroundTime - v[i].burstTime;
            }
        }
};



int main()
{

    Schedule schl;
    schl.scanData();

    cout<<"\n**************************** FCFS *********************************\n"<<endl;
    schl.FCFS();
    schl.display();

    cout<<"\n***************************** PRIORITY ********************************\n"<<endl;
    schl.Priority();
    schl.display();

    return 0;
}