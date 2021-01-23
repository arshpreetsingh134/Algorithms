// --AB--AB---A--

#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void calculate(vector<char> &candidate, int num){
    int candidateA=0;
    int candidateB=0;

        for(int i=0; i<num; i++){
            if(candidate[i]=='A')
                candidateA++;
            else if(candidate[i]=='B')
                candidateB++;
        }

        int n=0, br=0;

        if(candidate[0]=='-'){
        while(candidate[n]=='-'){
            ++n;
            //cout<<n;
        }
        if(candidate[n]=='A'){
            //cout<<"\n"<<n;
            candidateA+=n;
            br=n;
        }
        else if(candidate[n]=='B'){
            candidateB+=n;
            br=n;
        }
        }

        int k;
        while(n!=num){
            k=0;
            if(br==num-1 || n==num-1)
                break;
            if(candidate[n]=='B'){
                if(candidate[n+1]=='-'){
                    while(candidate[n++]=='-'){
                        k++;
                        n++;
                    }
                    int l=0;
                    while(l<floor(k/2)){
                        l++;
                        candidateB++;

                    }
                    continue;         
                }
            }
            
            n++;
        }
    
        n=num-1;
        while(n!=br){
            k=0;
            if(candidate[n]=='A'){
                if(candidate[--n]=='-'){
                    while(candidate[n]=='-'){
                        k++;
                        n--;
                    }
                    int l=floor(k/2);
                    while(l>0){
                        l--;
                        candidateA++;
                    }
                    continue; 

                }
            }
            n--;
        }
    
        if(candidateA > candidateB)
            cout<<'A';
        else if(candidateA == candidateB)
            cout<<"Coalition Government";
        else
            cout<<'B';
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