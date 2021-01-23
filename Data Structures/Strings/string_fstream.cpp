#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>  // For file stream (std::ifstream)
#include <cstring>
using namespace std;

int main()
{
    // vector<int> A{8, 9, 1, 2, 4, 7, 6, 12, 10, 16, 3, 20, 88, 44};

    // fstream myfile("a.txt", ios_base::in);

    // int a;
    // while (myfile >> a)
    // {
    //     cout<<a<<" ";
    // }

    // cout<<endl;

    // ifstream is("a.txt");
    // int x;

    // while (is >> x)
    //     cout<<x<<" ";

    // getchar();

    ifstream inFile("kargerMinCut.txt");
    string line;
    //ofstream outFile("b.txt");

    while (getline(inFile, line))
    {
        vector<int> temp;
        //cout << line << endl;

        // Returns first token
        char char_array[line.length() +1];
        strcpy(char_array, line.c_str());

        char *token = strtok(char_array, "	");

        // Keep printing tokens while one of the
        // delimiters present in str[].
        while (token != NULL)
        {
            int num;
            sscanf(token, "%d", &num);
            temp.push_back(num);

            token = strtok(NULL, "	");
        }

        for(int i = 1; i<temp.size(); i++)
            cout<<temp[i]<<" ";

        cout<<endl;
    }

    
}