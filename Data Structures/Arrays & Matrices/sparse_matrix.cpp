#include<iostream>
using namespace std;

struct Element
{
    int i;
    int j;
    int x;
};

struct Sparse
{
    int row;
    int col;
    int num;
    struct Element *elem;
};

void create(struct Sparse *s)
{
    cout<<"Enter dimensions: ";
    cin>>s->row>>s->col;
    cout<<"Enter the number of non-zero elements: ";
    cin>>s->num;

    s->elem = 

}

int main()
{

}