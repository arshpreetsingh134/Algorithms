// Dynamic Programming- Top-Down "Memoized" Approach for Optimized Rod Cutting

#include<iostream>
using namespace std;

// price[0..n]
int rodCutAux(int*, int, int*);

int rodCut(int* p, int n){
    int *r = new int[n+1];
    for(int i=0; i<n+1; i++)
        r[i]=-10000;
    return rodCutAux(p, n, r);
}

int rodCutAux(int* p, int n, int* r){
    int max_price, temp;
    if(r[n]>=0)
        return r[n];

    if(n==0)
        max_price = 0;

    else{
        max_price = -10000;
        for(int i=1; i<=n; i++){

            temp = rodCutAux(p, n-i, r);      //n-i from 3 to 0
            if((p[i-1] + temp) > max_price){
                max_price = p[i-1] + temp;
            }
        }
    }

    r[n]=max_price;
    return max_price;
}

int main(){
    int p[] = {1,5,8,9,10,17,17,20,24,30};
    int n = 8;
    cout<<"The most optimized solution for "<<n<<" is: "<<rodCut(p,n);
}