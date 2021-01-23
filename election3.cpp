#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void calculate(vector<char> &candidate, int num){

    int candidateA=0;
    int candidateB=0;
    int n=0;

    for(int i=0; i<num; i++){
            if(candidate[i]=='A')
                candidateA++;
            else if(candidate[i]=='B')
                candidateB++;
    }

    while(candidate[n]=='-'){
            ++n;
            //cout<<n;
        }
    if(candidate[n]=='A'){
            //cout<<"\n"<<n;
            candidateA = candidateA + n;
    }

    int i=n;

    while(n<num){

        //end case
        while(candidate[n]=='-' && n<num){
            n++;
        }

        if(n==num)
            break;

        //Case A
        if(candidate[n]== 'A'){
            if(i==n){
                n++;
                continue;
            }

            candidateA = candidateA + n-i-1;
            i= n;
            n++;
            continue;
        }
        i=n;
        n++;

        //Case B

        while(candidate[n]=='-' && n<num){
            n++;
        }
        if(n == num)
            candidateB = candidateB + n-i-1;
        else
        {
            if(candidate[n] =='A'){

                    candidateA = candidateA + (n-i-1)/2;

                    candidateB = candidateB + (n-i-1)/2;

                    i = n;

                    n++;

            }

            else

            {

                candidateB = candidateB + (n-i-1);

            }

        }

    }

    if(candidateA > candidateB)
            cout<<'A';
        else if(candidateA < candidateB)
            cout<<'B';
        else
            cout<<"Coalition Government";

}

int main(){
    int num;
    vector<char> candidate;
    cin>>num;
    char* name = new char[num];

    cin>>name;

    for(int i=0; i<num; i++){
        candidate.push_back(name[i]);
    }

    calculate(candidate, num);
}

