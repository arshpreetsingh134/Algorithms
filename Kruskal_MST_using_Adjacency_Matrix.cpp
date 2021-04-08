#include <iostream>
#define Inf 10000
using namespace std;

int set[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

int edges[3][9] =
    {{1, 1, 2, 2, 3, 4, 4, 5, 5},
     {2, 6, 3, 7, 4, 5, 7, 6, 7},
     {25, 5, 12, 10, 8, 16, 14, 20, 18}};

int included[9] = {0};
int t[2][6];

void weightedunion(int u, int v)
{
    if (set[u] < set[v])
    {
        set[u] += set[v];
        set[v] = u;
    }
    else
    {
        set[v] += set[u];
        set[u] = v;
    }
}

int find(int u)
{
    int x = u, v = 0;
    while (set[x] > 0)
    {
        x = set[x];
    }
    while (u != x)
    {
        v = set[u];
        set[u] = x;
        u = v;
    }
    return x;
}

int main()
{
    int k, v1, v2, min = Inf, v = 7, e = 9;
    int i = 0;
    while (i < v - 1)
    {
        min = Inf;
        for (int j = 0; j < e; j++)
        {
            if (included[j] == 0 && edges[2][j] < min)
            {
                min = edges[2][j];
                v1 = edges[0][j];
                v2 = edges[1][j];
                k = j;
            }
        }

        if (find(v1) != find(v2))
        {
            t[0][i] = v1;
            t[1][i] = v2;
            weightedunion(find(v1), find(v2));
            i++;
        }
        included[k] = 1;
    }
    for (i = 0; i < v - 1; i++)
    {
        cout << "(" << t[0][i] << "," << t[1][i] << ")" << endl;
    }
}