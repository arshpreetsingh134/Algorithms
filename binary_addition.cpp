//Binary Addition of 2 4-bit numbers

#include<iostream>
using namespace std;

int* method1(int *A, int *B, int Base){
    int i;
    int *C = new int[5];
    int carry=0;
    for(i=3; i>=0; i--){
        C[i+1] = (A[i]+B[i]+carry) % Base;
        carry = (A[i]+B[i]+carry) / Base;
    }
    C[i+1]=carry;
    return C;
}

int* method2(int *A, int *B){
    int i;
    int *C = new int[5];
    int carry=0;
    for(i=3; i>=0; i--){
        C[i+1] = (A[i] ^ B[i]) ^ carry;
        carry = (A[i] && B[i]) || (B[i] && carry) || (A[i] && carry);
    }
    C[i+1]=carry;
    return C;
}


int main(){
    int A[] = {1,0,0,1};
    int B[] = {0,1,1,0};
    int *C = method2(A, B);

    cout<<"A+B is: ";
    for(int i=0; i<5; i++){
        cout<<*(C+i)<<" ";
    }
}
