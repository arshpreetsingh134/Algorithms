// Dynamic Programming- Bottom-Up Approach for Optimized Rod Cutting
#include<iostream>
using namespace std;

int rodCut(int *p, int n){
    int max_price, temp;
    int *r = new int[n+1];
    r[0]=0;
    for(int i=1; i<=n; i++){
         max_price=-10000;
        for(int j=1; j<=i; j++){
            temp = p[j-1] + r[i-j]; 
            if(temp > max_price){
                max_price = temp;
            }
        }
        r[i]=max_price;
    }
    return r[n];
}

int main(){
    int p[] = {1,5,8,9,10,17,17,20,24,30};
    int n = 4;
    cout<<"The most optimized solution for "<<n<<" is: "<<rodCut(p,n);
}