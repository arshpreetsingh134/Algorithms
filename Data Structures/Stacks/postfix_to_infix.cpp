// Postfix to Infix Notation Conversion

#include <iostream>
#include <stack>
using namespace std;

string toInfix(string exp)
{
    stack<string> s;

    int i = 0;
    while(exp[i]!='\0')
    {
        // If there is an operand, push it to the stack
        if((exp[i]>='a' && exp[i]<='z') || (exp[i]>='A' && exp[i]<='Z')) 
        {
            string op(1, exp[i]);
            s.push(op);
        }   
            
        // There is an operator; pop the first two operands 
        // from the stack and add the concatenated string
        else     
        {       
            string a = s.top();
            s.pop();
            string b = s.top();
            s.pop();
            s.push("(" + b + exp[i] + a + ")");
        }
        i++;
    }
    return s.top();
}


int main()
{
    string exp = "abc*+d/e+f-";

    cout<<"Infix expression for "<<exp<<" is: "<<toInfix(exp);
}