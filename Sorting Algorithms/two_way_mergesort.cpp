// Two-Way Merge Sort of 4 lists

#include<iostream>
#include<vector>
using namespace std;

vector<int> merge(vector<int> L, vector<int> R){
    // Two lists A and B are given, and we have to merge them into 1
    int n1 = L.size();
    int n2 = R.size();
    vector<int> A(n1+n2-1);

    int i=0, j=0;

    for(int k = 0; k<=(n1+n2-1); k++){
        if( (i<n1) && (j>=n2 || L[i]<=R[j])){
            A[k]=L[i];
            i++;
        }

        else{
            A[k]=R[j];
            j++;
        }
    }

    return A;
}

int main()
{
    vector<int> A{5,6,22,41,84};
    vector<int> B{11,46,77,82,94};
    vector<int> C{23,25,41,56,89};
    vector<int> D{4,21,33,66,75};

    vector<int> A_new;

    A_new = merge(merge(A,B), merge(C,D));

    for(auto i:A_new)
    {
        cout<<i<<" ";
    }
    
}