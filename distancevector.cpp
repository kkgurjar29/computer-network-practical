//distance vector routing
#include<stdio.h>
#include<iostream>
using namespace std;

struct node
{
    unsigned dist[6];
    unsigned from[6];
}DVR[10];

int main()
{

    int costmat[6][6];
    int nodes, i, j, k;
    cout<<"\n Enter the number of nodes : ";
    cin>>nodes; //Enter the nodes
    cout<<"\n Enter the cost matrix : \n" ;

	for(i = 0; i < nodes; i++)
    {
        for(j = 0; j < nodes; j++)
        {
            cin>>costmat[i][j];
            costmat[i][i] = 0;
            DVR[i].dist[j] = costmat[i][j];
            DVR[i].from[j] = j;
        }
    }
    for(i = 0; i < nodes; i++)
        for(j = i+1; j < nodes; j++)
            for(k = 0; k < nodes; k++)
                if(DVR[i].dist[j] > costmat[i][k] + DVR[k].dist[j])
                {
                    DVR[i].dist[j] = DVR[i].dist[k] + DVR[k].dist[j];
                    DVR[j].dist[i] = DVR[i].dist[j];
                    DVR[i].from[j] = k;
                    DVR[j].from[i] = k;
                }
			for(i = 0; i < nodes; i++)
			{
				cout<<"\n\n For router: "<<i+1;
				for(j = 0; j < nodes; j++)
			    	cout<<"\t\n node "<<j+1<<" via "<<DVR[i].from[j]+1<<" Distance "<<DVR[i].dist[j];
			}
		cout<<" \n ";

	return 0;
}

//output
//Enter the number of nodes : 3
//
// Enter the cost matrix :
//0 5 8
//3 8 6
//2 9 7
//
//
// For router: 1
// node 1 via 1 Distance 0
// node 2 via 2 Distance 5
// node 3 via 3 Distance 8
//
// For router: 2
// node 1 via 1 Distance 3
// node 2 via 2 Distance 0
// node 3 via 3 Distance 6
//
// For router: 3
// node 1 via 1 Distance 2
// node 2 via 2 Distance 9
// node 3 via 3 Distance 0
