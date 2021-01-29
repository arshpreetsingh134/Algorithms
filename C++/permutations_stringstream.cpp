// String Permutations

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> sorted_str;

void permutations(string str, int l, int r)
{
    if (l == r)
        sorted_str.push_back(str);
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(str[l], str[i]);
            permutations(str, l + 1, r);
            swap(str[l], str[i]);
        }
    }
}

void printPermute(string str)
{
    int l = 0;
    int r = str.size() - 1;
    sorted_str.clear();
    permutations(str, l, r);
    sort(sorted_str.begin(), sorted_str.end());
    for (auto i : sorted_str)
        cout << i << " ";
    cout << endl;
}

int main()
{
    string line;
    vector<string> ss;
    vector<int>::iterator itr;

    cout<<"Enter the strings: ";

    std::istreambuf_iterator<char> begin(std::cin), end;
    std::string input(begin, end);

    istringstream ff(input);

    while (getline(ff, line))
    {
        cout<<line<<" ";
        ss.push_back(line);
    }

    int tests = 0;
    stringstream tempv(ss[0]);
    tempv >> tests;

    for (int i = 1; i <= tests; i++)
    {
        printPermute(ss[i]);
    }

    return 0;
}
