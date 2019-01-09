#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <iostream>
using namespace std;

bool BFS (vector <vector<int> > graph , int s , int t ,int n , int path[]){

    bool visited[n];
	int i;
	for(i=0; i<n;i++)
		visited[i] = 0;
    std :: queue <int> q;
    q.push(s);
    visited[s] = true;
    path[s]=-1;

    while (!q.empty()){
        int y = q.front();
        q.pop();
        for (i = 0 ; i < n ; i++){
            if (visited[i]==false &&graph[y][i])
            {
                q.push(i);
                path[i] = y;
               visited[i] = 1;
                //    std :: cout<<y << "  sfh  "<< i<<"\n";
            }
        }
    }

    return (visited[t] == true);
}


bool dfs(vector <vector<int> >RC, int s, int t, int n, int path[] )
{
	bool visited[n];
	int i;
	for(i=0; i<n;i++)
		visited[i] = 0;
	std::stack<int> list;
	list.push(s);
	visited[s] = true;
    path[s] = -1;

    while(!list.empty())
    {
		int j = list.top();
		list.pop();

		int i;
		for(i=0; i<n;i++)
		{
			//*(RC + j*n + i)
			if(visited[i]==false && RC[j][i]> 0)
			{
				list.push(i);
				path[i]= j;
				visited[i]= 1;
				cout << j<<"   "<<i<<"\n";
			}
		}
	}
	for(i=0; i<n; i++ )
    	std::cout<<"its\n"<<path[i]<<"\n";

	return (visited[t] == true);
}


void maximum_flow(int n, int s, int t, int *cap, int *flow)
{
	vector <vector<int> > currentFlow;
  vector <vector<int> > currentRC;
  vector<int> tmp, tmp2;
  //int currentFlow [n][n] , currentRC[n][n];
	int flowsum=0, i, j;
	int path[n];  // new int[n];




	for(i=0;i<n;i++)
	{
    for(j=0;j<n;j++)
		{
			tmp.push_back(0);
			tmp2.push_back(  *(cap + i*n + j)  );
		}
      currentFlow.push_back (tmp) ;
			currentRC.push_back (tmp2);
      tmp.clear();
      tmp2.clear();

  }


	//when there is at least one path from s to t
	while( dfs( (currentRC), s,t,n,path))
	{

		int tempFlow = INT_MAX;
		//find the minimum
		for(j = t; j != s; j= path[j])
		{
			i= path[j];
			if(tempFlow > currentRC[i][j] )
				tempFlow = currentRC[i][j];
		}
		flowsum += tempFlow;
		cout<<"tempFlow = " <<tempFlow<<"\n";
		//undate flows
		for(j = t; j != s; j= path[j])
		{
			i= path[j];
			currentRC[i][j] -= tempFlow;
			currentRC[j][i] += tempFlow;
			currentFlow[j][i]  += tempFlow;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			*(flow + i*n + j)= currentFlow[j][i];
    	   // std::cout<<*(flow + i*n + j)<<" ";
    	  //  if(j==n-1) std::cout<<std::endl;
    	}
}






int main()
{

    int cap[6][6], flow[6][6], *path= new int[6], n=6, s=0, t=5;
   int i,j, flowsum;
   for(i=0; i< 6; i++)
     for( j =0; j< 6; j++ )
     {
       flow[i][j] = 0;
       cap[i][j]=0;
   		}
    cap[0][1] = 10;
    cap[0][3] = 10;
    cap[1][2] = 4;
    cap[1][3] = 2;
     cap[1][4] = 8;
   cap[2][5] = 10;
   cap[3][4] = 9;
   cap[4][2] = 6;
   cap[4][5] = 10;

    maximum_flow( n, s, t, &(cap[0][0]), &(flow[0][0]));
   for(int a=0;a<n;a++)
    	for(int b=0;b<n;b++)
    	{
    	    std::cout<<flow[a][b]<<" ";
    	    if(b==n-1) std::cout<<std::endl;
    	}









    return 0;
}

