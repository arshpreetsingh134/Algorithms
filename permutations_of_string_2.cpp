// Steinhaus-Johnson-Trotter Algorithm for calculating the permutations of the string

#include <iostream>
#include <vector>
#define RIGHT_TO_LEFT false
#define LEFT_TO_RIGHT true
using namespace std;

int indexof(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return (ch - 'A' + 1) - 1;
    else if (ch >= 'A' && ch <= 'Z')
        return (ch - 'a' + 1) - 1;
    else
        return (ch - '0' + 1) - 2;
}

char indexto(int i)
{
    char ch = 'A';
    while (true)
    {
        if (i == indexof(ch))
            break;
        ch = ch + 1;
    }
    return ch;
}

int position(string str, char mobile)
{
    for (int i = 0; i < str.length(); i++)
        if (str[i] == mobile)
            return i;
    return 0;
}

// Calculate the no. of possible permutations of the string, i.e., n!
int fact(int num)
{
    int i = 1;
    int j = num;
    while (j > 0)
    {
        num *= i;
        i = --j;
    }
    return num;
}

// To carry out step 1 of the algorithm i.e. to find the largest mobile
// integer's index. A directed integer is said to be mobile if it is greater
// than its immediate neighbor in the direction it is looking at.
char getMobile(string &str, vector<bool> &dir, int n)
{
    char mobile_prev = '0', mobile = '0';

    for (int i = 0; i < n; i++)
    {
        // Right to Left Direction
        if (dir[indexof(str[i])] == RIGHT_TO_LEFT && i != 0)
        {
            if (str[i] > str[i - 1] && str[i] > mobile_prev)
            {
                mobile = str[i];
                mobile_prev = mobile;
            }
        }

        // Left to Right Direction
        if (dir[indexof(str[i])] == LEFT_TO_RIGHT && i != n - 1)
        {
            if (str[i] > str[i + 1] && str[i] > mobile_prev)
            {
                mobile = str[i];
                mobile_prev = mobile;
            }
        }
    }

    if (mobile == '0' && mobile_prev == '0')
        return '0';
    else
        return mobile;
}

// Prints a single permutation
void printOnePerm(string &str, vector<bool> &dir, int n, int ind)
{
    char mobile = getMobile(str, dir, n);
    // char mobile_elem = indexto(mobile);

    int mob_ind = indexof(mobile);
    int pos = position(str, mobile);

    // swapping the elements according to the direction of the
    // mobile element
    if (dir[mob_ind] == RIGHT_TO_LEFT)
        swap(str[pos], str[pos - 1]);
    else if (dir[mob_ind] == LEFT_TO_RIGHT)
        swap(str[pos], str[pos + 1]);

    // changing the directions for elements greater than the
    // largest mobile element
    for (int i = 0; i < n; i++)
    {
        if (str[i] > mobile)
        {
            if (dir[indexof(str[i])] == LEFT_TO_RIGHT)
                dir[indexof(str[i])] = RIGHT_TO_LEFT;
            else if (dir[indexof(str[i])] == RIGHT_TO_LEFT)
                dir[indexof(str[i])] = LEFT_TO_RIGHT;
        }
    }

    cout << str << " ";
}

// This function mainly calls printOnePerm()
// one by one to print all permutations.
void printPermutation(string str)
{
    int N = str.length();

    // Initially, every element's direction is from right to left
    vector<bool> dir(26, RIGHT_TO_LEFT);

    // Print the first element in the permutation
    cout << str << " ";

    for (int i = 1; i < fact(N); i++)
        printOnePerm(str, dir, N, i);
}

int main()
{
    string str = "ABCD";

    printPermutation(str);
}