#include <bits/stdc++.h>
using namespace std;

void display(std::vector<int> v)
{
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

int main()
{
#ifndef ONLINE_JUDGE
	// for getting input from input.txt
	freopen("input.txt", "r", stdin);
	// for writing output to output.txt
	freopen("output.txt", "w", stdout);
#endif


	int n;
	cin >> n;

	int weight;
	string str;

	for (int i = 0; i < n; i++)
	{
		vector<int> A;
		string str;

		// Getting the weight for each test case
		cin >> weight;
		cout << "weight: " << weight << endl;

		cin.ignore();

		// Getting the line stream for each test case
		getline(cin, str);

		int a;

		istringstream iss(str);

		// Storing the elements in the stream into an int array
		while (iss >> a )
			A.push_back(a);

		display(A);
	}
}



// Inputs :-
// 5
// 5
// 2 2 1 4 6
// 2
// 6 5 4 8 2
// 3
// 9 8 5 6 3 5 3
// 1
// 2 3 5 4 8 3
// 2
// 7 8 9 6 3 2 3 5