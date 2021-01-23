// Given a 2-D array describing the time duration interval of each
// class, find the minimum classrooms required to conduct these
// classes.

#include<iostream>
using namespace std;
int findMax(int lectures[][2], int n){
    int maxElement = -10000;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < 2; j++) { 
            if (lectures[i][j] > maxElement) { 
                maxElement = lectures[i][j]; 
            } 
        } 
    }
    return maxElement; 
}

int minClass(int lectures[][2], int n){
    int max = findMax(lectures, n);
    int T[max+1] = { 0 };

    for(int i=0; i<n; i++){
        T[lectures[i][0]]+=1;
        T[lectures[i][1]+1]-=1;
    }

    int soln = T[0];
    for(int i=1; i<max; i++){
        T[i]+=T[i-1];
        if(T[i]>soln){
            soln=T[i];
        }
    }
    return soln;
}

int main(){
    int A[][2] = {{0, 5},
                  {1, 6},
                  {2, 7},
                  {3, 8},
                  {6, 8}};

    int size = sizeof(A) / sizeof(A[0]);
    cout<<"Minimum no. of classrooms reqd: "<<minClass(A, size);
}