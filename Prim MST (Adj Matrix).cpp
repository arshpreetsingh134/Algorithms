#include<iostream>
#include<cstdint>
#define Inf 1000000
using namespace std;




int main(){
    int V, E;
    cout<<"Enter the number of Vertices: ";
    cin>>V;
    cout<<"\nEnter the  number of Edges: ";
    cin>>E;

    //A Dynamic 2-D Array (Adjacency Matrix) for storing weights
    int** A = new int*[V];
    for(int i = 0; i <= V; ++i)
    A[i] = new int[V];

    for(int i=0; i<=V; i++){
        A[i][0]=Inf;
    }

    for(int j=0; j<=V; j++){
        A[0][j]=Inf;
    }

    for(int i=1; i<=V; i++){
        for(int j=1; j<=V; j++){
            cout<<"Enter weights for ("<<i<<", "<<j<<"): ";
            cin>>A[i][j];
            if(A[i][j]=='\n')
                A[i][j]=Inf;
            A[i][j]=getchar();

        }
    }
}