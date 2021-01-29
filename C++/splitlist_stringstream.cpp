// Split List

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<int> ab;
// std::string your_code_goes_here(std::string input) {
//   // Use this function to return the solution.
//   return input;
// }

void splitList(string str)
{
    int i = 0, count = 0;
    istringstream buf(str);
    istream_iterator<string> beg(buf), end;
    vector<string> tok(beg, end);

    for (auto &s : tok)
    {
        stringstream parser(s);
        int x = 0;
        parser >> x;
        ab.push_back(x);
        i++;
    }
    int size = (ab.size() + 1) / 2;

    for (auto &v : ab)
    {
        cout << v << " ";

        if (count + 1 == size)
            cout << endl;
        else
            cout << " ";

        count++;
    }
}

int main()
{

    std::istreambuf_iterator<char> begin(std::cin), end;
    std::string input(begin, end);

    vector<string> stt;
    string line;
    istringstream ff(input);

    while (getline(ff, line))
    {
        stt.push_back(line);
    }

    splitList(stt[1]);

    return 0;
}
