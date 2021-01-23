// Dynamic Porgramming
// Matrix Chain Multiplication- Method 2

#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

int productValue(int num_matrices, vector<int> dims){

    vector<vector<int>> Cost(num_matrices, vector<int>(num_matrices,0));
    vector<vector<int>> k_table(num_matrices, vector<int>(num_matrices,0));
    int temp, j;
    
    for(int d=1; d<num_matrices; d++){
        for(int i=0; i<num_matrices-d; i++){
            int cost, k_min, min=INT_MAX;
            j=i+d;

            for(int k=i ; k<j; k++){
                cost = Cost[i][k] + Cost[k+1][j] + (dims[i]*dims[k+1]*dims[j+1]);
                if(min>cost){
                    min=cost;
                    k_min=k+1;
                }
                Cost[i][j]=min;
                k_table[i][j]=k_min;
            }
        }
    }

    cout<<"Perform Multiplications on first "<<k_table[0][num_matrices-1]<<" matrices first!";
    return Cost[0][num_matrices-1];
}

int main(){
    int num_matrices = 5;
    vector<int> dims{5,10,100,2,20,50};

    cout<<"\nNumber of multiplications performed will be: "<<productValue(num_matrices, dims);

}