#include<iostream>
using namespace std;
class Graph
{
    int a[10][10],b[10][10];
    int n,e;
    int visited[10],from[10],dist[10];
    public:
   
    Graph(int n)
    {
        for(int i=0;i<n;i++)
        {
            visited[i]=0;
        }
        for(int i=0;i<n;i++)
        {
            dist[i]=100;
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                b[i][j]=0;
            }
        }
    }
    void input(int n)
    {  
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<"Enter Office "<<i+1<<" to Office "<<j+1<<" cost : ";
                cin>>a[i][j];
            }
        }
        cout<<"\nInput Matrix:"<<endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
           
        }
    }
    void display(int n)
    {
        cout<<"\nOutput matrix: "<<endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<b[i][j]<<" ";
            }
            cout<<endl;

        }
    }
   
    void Prims(int n)
    {
        int u,v,Sum;
        Sum=0;
       
        int cost[10][10];
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(a[i][j]==0)
                {
                    cost[i][j]=100;
                }
                else
                {
                    cost[i][j]=a[i][j];
                }
            }
        }
        visited[0]=1;

        for(int i=1;i<n;i++)
        {
            dist[i]=cost[0][i];
            from[i]=0;
        }
       

        e=n-1;
        while(e>=0)
        {
            int mindist=100;
            for(int i=1;i<n;i++)
            {
                if(dist[i]<mindist && visited[i]==0)
                {
                    mindist=dist[i];
                    v=i;
                }
            }

            u=from[v];
            b[u][v]=cost[u][v];
            b[v][u]=cost[v][u];

            // Sum=Sum+cost[u][v];
            e--;
            visited[v]=1;

            for(int i=1;i<n;i++)
            {
                if(dist[i]>cost[v][i] && visited[i]==0)
                {
                    dist[i]=cost[v][i];
                    from[i]=v;
                }
            }

        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                Sum=Sum+b[i][j];
            }
        }
        cout<<"Minimum Cost = "<<Sum/2<<endl;
    }
};
int main()
{
    int n;
   
    cout<<"Enter no. of Offices: "<<endl;
    cin>>n;
    cout<<"\nEnter 0 if there is no connection between offices."<<endl;
   
    Graph g(n);
   
    g.input(n);
    g.Prims(n);
    g.display(n);
   
    return 0;
} 



// Output :-

// Enter no. of Offices: 
// 4
// Enter 0 if there is no connection between offices.
// Enter Office 1 to Office 1 cost : 0
// Enter Office 1 to Office 2 cost : 3
// Enter Office 1 to Office 3 cost : 4
// Enter Office 1 to Office 4 cost : 5
// Enter Office 2 to Office 1 cost : 3
// Enter Office 2 to Office 2 cost : 0
// Enter Office 2 to Office 3 cost : 1
// Enter Office 2 to Office 4 cost : 4
// Enter Office 3 to Office 1 cost : 4
// Enter Office 3 to Office 2 cost : 1
// Enter Office 3 to Office 3 cost : 0
// Enter Office 3 to Office 4 cost : 5
// Enter Office 4 to Office 1 cost : 5
// Enter Office 4 to Office 2 cost : 4
// Enter Office 4 to Office 3 cost : 5
// Enter Office 4 to Office 4 cost : 0
// Input Matrix:
// 0 3 4 5 
// 3 0 1 4 
// 4 1 0 5 
// 5 4 5 0 
// Minimum Cost = 12

// Output matrix: 
// 0 3 0 0 
// 3 0 1 4 
// 0 1 0 0 
// 0 4 0 0 

