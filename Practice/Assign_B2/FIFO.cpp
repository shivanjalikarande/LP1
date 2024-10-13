#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <deque>
#include <queue>

using namespace std;


int FIFO(int pages[],int n,int frsize)
{
    unordered_set<int>s;
    queue<int>que;

    int missCount = 0;
    for(int i=0;i<n;i++)
    {
        if(s.size()<frsize)
        {
            if(s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                que.push(pages[i]);
                missCount++;
                cout<<"Miss "<<pages[i]<<"   Frame: ";
            }
            else
            {
                cout<<"Hit "<<pages[i]<<"   Frame: ";
            }
        }
        else
        {
            if(s.find(pages[i]) == s.end())
            {
                int curr = que.front();
                que.pop();
                s.erase(curr);
                s.insert(pages[i]);
                que.push(pages[i]);
                missCount++;
                cout<<"Miss "<<pages[i]<<"   Frame: ";
            }
            else
            {
                cout<<"Hit "<<pages[i]<<"   Frame: ";
            }
        }
        vector<int>tempqueue;
        while(!que.empty())
        {
            tempqueue.push_back(que.front());
            que.pop();
        }
        for(int i: tempqueue)
        {
            cout<<i<<" ";
            que.push(i);
        }
        cout<<endl;
    }

    return missCount;
}

int main()
{
    int *pages;
    int n;
    cout<<"Enter no of pages: ";
    cin>>n;
    pages = new int[n];
    cout<<"Enter pages "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"\nPage "<<(i+1)<<": ";
        cin>>pages[i];
    }
    int frsize;
    cout<<"\nEnter frame size: ";
    cin>>frsize;

    int miss = FIFO(pages,n,frsize);
    cout<<"Miss Count = "<<miss<<endl;
    int hits = n - miss;
    cout<<"Hits Count = "<<hits<<endl;
    float hitRatio = hits;
    hitRatio/=n;
    cout<<"\nHit Ratio: "<<hitRatio<<" ";

    return 0;
}