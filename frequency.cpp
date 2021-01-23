#include<iostream>
#include<unordered_map>
using namespace std;

void frequency(int *A, int n){
    unordered_map<int, int> umap;

    for(int i = 0; i<n ; i++){
        if(umap[A[i]]==NULL)
            umap[A[i]]=1;
        else
        {
            umap[A[i]]++;
        }
    }

    for(auto i:umap){
        cout<<i.first<<" "<<i.second<<endl;
    }

}

int main(){
    int A[]= {25, 64, 88, 12, 12, 88, 64, 64, 25, 32, 25, 88};
    int size = sizeof(A)/sizeof(A[0]);
    frequency(A, size);
}