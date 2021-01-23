// Finding Binomial Coefficient using Dynamic Programming.

// A binomial coefficient C(n, k) can be defined as the coefficient of X^k in the expansion of (1 + X)^n.
// C(n,k) = C(n-1,k-1) + C(n-1,k)
// Base Case -> C(n,0) = 1

#include<iostream>
using namespace std;

int min(int a, int b){
    if(a<b)
        return a;
    else
        return b;
}

int binomial(int n, int k){
    int lookup[n+1][k+1];
    for(int i=0; i<=n; i++){
        for(int j=0; j<=min(i,k); j++){
            if(k==0 || k==i)
                lookup[i][j]=1;
            else
                lookup[i][j]= lookup[i-1][j-1] + lookup[i-1][j];
        }
    }

    return lookup[n][k];
}

int main(){
    int n = 4;
    int k = 2;
    cout<<"C("<<n<<","<<k<<") is: "<<binomial(n,k);
}