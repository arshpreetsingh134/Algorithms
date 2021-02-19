// Infix to Postfix Expression Conversion
#include <iostream>
#include <stack>
using namespace std;

// To return the precedence of respective operators
int Precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string toPostfix(string exp)
{
    stack<char> s;
    string op;
    s.push('N');    // To indicate the end of stack
    int l = exp.length();

    int i = 0;
    for (int i = 0; i < l; i++)
    {
        // If the scanned character is an operand, add
        // it to the output string
        if ((exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z'))
            op += exp[i];

        // If the scanned character is a '(', push it
        // to the stack
        else if (exp[i] == '(')
            s.push('(');

        // If the scanned character is a ')', pop from
        // the stack until a '(' is encountered
        else if (exp[i] == ')')
        {
            // Add the whole expression within the parenthesis
            // to the output string
            while (s.top() != 'N' && s.top() != '(')
            {
                char ch = s.top();
                s.pop();
                op += ch;
            }
            // If '(' reached, pop it from the stack
            if (s.top() == '(')
                s.pop();
        }

        // If an operator is scanned, then check if the precedence of 
        // the scanned operator is greater than that inside the stack,
        // or if the stack is empty('N'). If not, keep poppin' until
        // the stack is empty or until the precedence of operator becomes
        // greater than the precedence of operator in the stack, then finally
        // push it to the stack
        else
        {
            while(s.top()!='N' && Precedence(exp[i]) <= Precedence(s.top()))
            {
                char ch = s.top();
                s.pop();
                op+=ch;
            }
            s.push(exp[i]);
        }
    }
    
    // Add the remaining characters in the stack to the output string
    while(s.top()!='N')
    {
        char ch = s.top();
        s.pop();
        op+=ch;
    }

    return op;
}

int main()
{
    string exp = "(a+(b*c))/d+e-f";

    cout<<"Postfix expression for "<<exp<<" is: "<<toPostfix(exp);
}