#include <iostream>
#include <stack>
using namespace std;

bool checkParenthesis(string paren)
{
    stack<char> st;
    char x;

    for (int i = 0; i < paren.length(); i++)
    {
        // If the current bracket is an opening bracket, push it to the stack
        if (paren[i] == '[' || paren[i] == '{' || paren[i] == '(')
        {
            st.push(paren[i]);
            continue;
        }

        // If the current character is not an opening
        // bracket, then it must be a closing one. So
        // stack cannot be empty at this point
        if (st.empty())
            return false;

        switch (paren[i])
        {
        case ')':
            x = st.top();
            st.pop();
            if (x != '(')
                return false;
            break;

        case '}':
            x = st.top();
            st.pop();
            if (x != '{')
                return false;
            break;

        case ']':
            x = st.top();
            st.pop();
            if (x != '[')
                return false;
            break;
        }
    }

    // Check empty stack
    return (st.empty());
}

int main()
{
    string paren = "[()]{}[{()}]";

    if (checkParenthesis(paren))
        cout << "\nParenthesis " << paren << " are balanced.\n";
    else
        cout << "\nParenthesis " << paren << " are not balanced.\n";
}