#include <bits/stdc++.h>
using namespace std;

class Foo
{
public:
    int a;
    int b;
    Foo *node;



    Foo(int a, int b, Foo* node = NULL)
    {
        this->a = a;
        this->b = b;
        this->node = node;
    }

    Foo changeNode(Foo *node)
    {
        node->a = 2;
        node->b = 5;
    }

    void Print()
    {
        cout<<this->a<<" "<<this->b<<" ";
        if(this->node != NULL)
            cout<<this->node->a<<" "<<this->node->b<<endl;
    }
};

void PrintData(Foo *f)
{
    if(f==NULL)
        f = new Foo(55, 75);
        f->Print();
}

Foo *findNext(Foo *f)
{
    if(f==NULL)
        return NULL;

    while(f->node!=NULL)
        f = f->node;

    return f;
}

int main()
{
    Foo *f1 = new Foo(6, 10, NULL);
    Foo *f2 = new Foo(66,88, f1);
    Foo *f3 = new Foo(99, 100, f2);

    f2->changeNode(f1);

    f3->Print();
    f2->Print();

    Foo *f4 = findNext(f3);

    f4->Print();
}