#include <iostream>
using namespace std;

int goodnessScore(string str)
{
    int N = str.length();
    int score=0;

    for(int i=0; i<=N/2; i++)
    {
        if(str[i]==str[N-i-1])
            score++;
    }
    return score;
}

int main()
{
    string str = "CABABC";
    cout<<"score: "<<goodnessScore(str);
}