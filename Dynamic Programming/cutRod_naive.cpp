// Recursive (Naive) Approach

#include<iostream>
using namespace std;

// price[0..n]
int rodCut(int* p, int n){
    int max_price, temp;
    if(n==0)
        return 0;
    
    max_price = -11000;
    for(int i=1; i<=n; i++){

        temp = rodCut(p, n-i);      //n-i from 3 to 1

        if((p[i-1] + temp) > max_price)
            max_price = p[i-1] + temp;
    }
    return max_price;
}

int main(){
    int p[] = {1,5,8,9,10,17,17,20,24,30};
    int n = 10;
    cout<<"The most optimized solution for "<<n<<" is: "<<rodCut(p,n);
}