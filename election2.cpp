#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void solve()

{

   int n;

   cin >> n;

   string s;

   cin >> s;

   int i=0;

   int voters1 = 0;

   int voters2 = 0;

   int j=0;

   while(s[j]!='\0')

   {

       if(s[j] == 'A')

            voters1++;

       else if(s[j] == 'B')

            voters2++;

       j++;

   }

   while(s[i]=='-')

   {

       i++;

   }

   if(s[i]=='A')

   {

       voters1+=i;

   }

   //cout << voters1 << " " << voters2 << endl;

       int start = i;

        for(;i<n;)

        {

                while(s[i]=='-' && i<n)

                {

                    i++;

                }

                if(i==n)

                {

                    break;

                }

                if(s[i]=='A')

                {

                    if(start == i)

                    {

                        i++;

                        continue;

                    }

                    voters1 = voters1 + (i-start-1);

                    start = i;

                    i++;

                    continue;

                }

                start = i;

                i++;

            while(s[i]=='-' && i<n)

            {

                i++;

            }

            if(i == n)

                voters2 = voters2 + (i-start-1);

            else

            {

                if(s[i] =='A')

                {

                    //cout << "HEY " << i << " " << start << " " << voters1 << " " << voters2 << endl;

                    voters1 = voters1 + (i-start-1)/2;

                    voters2 = voters2 + (i-start-1)/2;

                    //cout << voters1 << " " << voters2 << endl;

                    start = i;

                    i++;

                }

                else

                {

                    voters2 = voters2 + (i-start-1);

                }

            }

        //cout << voters1 << " " << voters2 << endl;

        }

    //cout << voters1 <<" " << voters2 << endl;

   if(voters1 > voters2)

   {

       cout << "A" << endl;

   }

   else if(voters1 == voters2)

   {

       cout << "Coalition government" << endl;

   }

   else

   {

       cout << "B" << endl;

   }

}

int main(){
    solve();
}