#include <iostream>
#include <cstdio>

using namespace std;

int n, m;
int f[1005][1005];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> f[i][j];
        }
    }
    for (int i = m - 1; i >= 0; i--)
    {
        int j = 0;
        for (; j < n - 1; j++)
        {
            cout << f[j][i] << " ";
        }
        cout << f[j][i] << endl;
    }
    return 0;
}
