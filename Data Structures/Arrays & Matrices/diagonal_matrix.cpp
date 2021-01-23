#include<iostream>
using namespace std;

class Matrix
{
    private:
        int n;
        int *A;

    public:
        Matrix(int n)
        {
            this->n = n;
            A = new int[n];
        }

        void set(int i, int j, int x)
        {
            if(i==j)
                A[i-1] = x;
        }

        int get(int i, int j)
        {
            if(i==j)
                return A[i-1];
            else
                return 0;
        }

        void display()
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(i==j)
                        cout<<A[i-1]<<" ";
                    else
                        cout<<"0"<<" ";
                }
                cout<<endl;
            }   
        }

        ~Matrix()
        {
            delete []A;
        }
};

int main()
{
    int n;
    Matrix obj(5);

    obj.set(0,0,6);
    obj.set(1,1,3);
    obj.set(2,2,7);
    obj.set(3,3,4);
    obj.set(4,4,9);

    obj.display();
}