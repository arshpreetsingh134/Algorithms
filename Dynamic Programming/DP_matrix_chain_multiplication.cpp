// Dynamic Porgramming
// Matrix Chain Multiplication- Method 1

#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

bool checkDims(int num_matrices, vector<vector<int>> dims){
    int flag=0;     // If flag=0, dimensions are not equal, so multiplication not possible

    for(int i=0; i<dims.size()-1; i++){
        if(dims[i][1]==dims[i+1][0])
            flag=1;
        else{
            flag=0;
            return flag;
        }
    }
    return flag;
}

int productValue(int num_matrices, vector<vector<int>> dims){
    if(!checkDims(num_matrices, dims))
    {
        cout<<"Sorry, your dimensions don't match.";
        return 0;
    }

    vector<vector<int>> Cost(num_matrices, vector<int>(num_matrices,-1));
    vector<vector<int>> k_table(num_matrices, vector<int>(num_matrices,-1));
    int temp, j;

    for(int i=0; i<num_matrices; i++){
        temp=i;
        int min_cost = INT_MAX;
        int cost, min_k;
        for(j=0; j<num_matrices; j++){
            if(temp>num_matrices-1){
                break;
            }
            if(temp==j){
                Cost[j][temp]=0;
                temp++;
                continue;
            }

            // i-->j,  j--->temp

            for(int k=j; k<temp; k++){
                cost = Cost[j][k] + Cost[k+1][temp] + (dims[j][0] * dims[k][1] * dims[temp][1]);
                cout<<cost<<" "<<j<<temp<<" "<<i<<endl;
                if(min_cost>cost){
                    min_cost = cost;
                    min_k = k;
                }
                Cost[j][temp] = min_cost;
                k_table[j][temp] = min_k;
            }
            temp++;
            
        }
    }
    return Cost[j-1][temp-1];
}

int main(){
    int num_matrices = 4;
    vector<vector<int>> dims{{5,4},
                             {4,6},
                             {6,2},
                             {2,7}};

    cout<<"\nNumber of multiplications performed will be: "<<productValue(num_matrices, dims);

}