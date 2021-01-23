// Tower of Hanoi
// A -> Source Tower, B -> Auxilliary Tower, C -> Destination Tower
// 'From' A 'to' C 'using' B

#include<iostream>
using namespace std;

int TOH(int n, int A, int B, int C)
{
    int steps = 0;
    if(n>0)
    {
        steps+=TOH(n-1, A, C, B);
        cout<<"\nMove tower "<<n<<" from "<<A<<" to "<<C;
        steps+=1;
        steps+=TOH(n-1, B, A, C);
    }
    else
    {
        //cout<<"\nMove tower 1 from "<<A<<" to "<<C;
        return 1;
    }
    return steps;
}

int main()
{
    int n;
    cout<<"Enter the number of disks: ";
    cin>>n;
    cout<<"\n\nNumber of calls required: "<<TOH(n, 1,2,3);
}