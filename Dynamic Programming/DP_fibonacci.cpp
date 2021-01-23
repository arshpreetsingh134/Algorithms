// Dynamic Programming
//Fibonacci Series- Top-Down (Memoization) and Bottom-up Approach

#include<iostream>
using namespace std;

static int A[20]={0};
static int B[20]={0};

int fibonacci_top_down(int n){
    if(A[n]>0)
        return A[n];

    if(n<=1){
        A[n]=n;
        return n;
    }

    A[n] = fibonacci_top_down(n-1) + fibonacci_top_down(n-2);
    return A[n];
}

int fibonacci_bottom_up(int n){
    for(int i=0; i<n; i++){
        if(i<=1)
            B[i]=i;
        else{
            B[i]=B[i-1]+B[i-2];
        }

    }
}

int main(){
    int n;
    cout<<"Enter the limit of Fibonacci Series: ";
    cin>>n;
    fibonacci_top_down(n);
    fibonacci_bottom_up(n);

    for(int i=0; i<n; i++){
        cout<<A[i]<<" ";
    }

    cout<<endl;

    for(int i=0; i<n; i++){
        cout<<B[i]<<" ";
    }

}