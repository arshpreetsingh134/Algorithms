#include<iostream>
#include<stdio.h>
#define Inf 1000000
using namespace std;

int main(){
    int E, a, b;
    int V=5;
    int A[V][V] = { { 0, 6, 0, 8, 15 }, 
                    { 6, 0, 4, 0, 0 }, 
                    { 0, 4, 0, 2, 13 }, 
                    { 8, 0, 2, 0, 12 }, 
                    { 15, 0, 13, 12, 0 } };

    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }

    // 2-D Array for storing edges
    int** t = new int*[2];
    for(int i = 0; i <2; ++i)
        t[i] = new int[V-1];

    // 1-D Array for keeping track of nearby vertices
    int* near = new int[V];
    for(int i=0; i<=V+1; i++){
        near[i]=Inf;
    }

    // Finding minimum weight from Adjacency Matrix
    int min = Inf; 
    int v1,v2;
    for(int i=0; i<V; i++){
        for(int j=i; j<V; j++){
            if(A[i][j]!=0 && min>A[i][j]){
                min=A[i][j];
                v1=i;
                v2=j;
            }
        }
    }

    // Updating near array to the visited vertices
    near[v1]=0;
    near[v2]=0;

    // Visited Edges
    t[0][0]=v1;
    t[1][0]=v2;

    // Updating near's values to smallest of the 2 visited nodes
    for(int j=0; j<V; ++j){
        if(near[j]!=0 && A[j][v1] >= A[j][v2])
            near[j]= v2;
        else
            near[j]= v1;
    }

    
    for(int i = 1; i<V-1; i++){   
    
        for(int k = 0; k<V; ++k){
            int min=Inf;
            if(near[k]!=0 && min>A[k][near[k]]){
                min=A[k][near[k]];
                a=k;
            }
        }
        t[0][i]=a;
        t[1][i]=near[a];
        near[a]=0;

        for(int j=0; j<V; j++){
            if(near[j]!=0 && A[j][a]<A[j][near[j]])
                near[j]=a;
        }
    }

    cout<<"\nThe edges are: \n";
    for(int i=0; i<2; i++){
        for(int j=0; j<V-1; j++){
            cout<<t[i][j]<<" ";
        }
        cout<<endl;
    }
}