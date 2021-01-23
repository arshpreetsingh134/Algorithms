// Travelling Salesman Problem using graphs, bitmasking and DP
#include<iostream>
#include<vector>
#include<limits.h>
#include<math.h>
using namespace std;

int V = 4;
int VISITED_ALL = (1<<V) -1;        //Left-shift (x*2^y) --> 0000

int tsp(int mask, int position, vector<vector<int>> costs, vector<vector<int>> &dp)
{
    if(mask==VISITED_ALL)
        return costs[position][0];

    if(dp[mask][position]!=-1)
        return dp[mask][position];

    int min_cost = INT_MAX;
    for(int i=0; i<costs.size(); i++)
    {
        if((mask&(1<<i))==0){
		    int current_cost = costs[position][i] + tsp( mask|(1<<i), i, costs, dp);
		    min_cost = min(min_cost, current_cost);
	    }
    }

    dp[mask][position] = min_cost;
    return dp[mask][position];
}



int main()
{
    vector<vector<int>> costs{{1,2,3,3},
                              {5,12,9,10},
                              {4,2,5,8},
                              {4,4,9,0}};

    int num_masks = pow(costs.size(),2);

    vector<vector<int>> dp(num_masks, vector<int>(costs.size(),-1));

    cout<<"Shortest Hamiltonian Path from A to B is: "<<tsp(1,0, costs, dp);
}




// #include<iostream>
// using namespace std;

// #define INT_MAX 999999

// int n=4;
// int dist[10][10] = {
//         {0,20,42,25},
//         {20,0,30,34},
//         {42,30,0,10},
//         {25,34,10,0}
// };
// int VISITED_ALL = (1<<n) -1;

// vector<vector<int>> dp(16, vector<int>(2,-1));


// int  tsp(int mask,int pos){
	
// 	if(mask==VISITED_ALL){
// 		return dist[pos][0];
// 	}
// 	if(dp[mask][pos]!=-1){
// 	   return dp[mask][pos];
// 	}

// 	//Now from current node, we will try to go to every other node and take the min ans
// 	int ans = INT_MAX;

// 	//Visit all the unvisited cities and take the best route
// 	for(int city=0;city<n;city++){

// 		if((mask&(1<<city))==0){

// 			int newAns = dist[pos][city] + tsp( mask|(1<<city), city);
// 			ans = min(ans, newAns);
// 		}

// 	}
	
// 	return dp[mask][pos] = ans;
// } 

// int main(){
//     /* init the dp array */
//     for(int i=0;i<(1<<n);i++){
//         for(int j=0;j<n;j++){
//             dp[i][j] = -1;
//         }
//     }
// 	cout<<"Travelling Salesman Distance is "<<tsp(1,0);

// return 0;
// }