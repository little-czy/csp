#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 10005
using namespace std;

int a[MAXN];

int main()
{
    memset(a, 0, MAXN);
    int n, m, max_m = 0, max_n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        a[m]++;
        if (a[m] > max_m)
        {
            max_m = a[m];
            max_n = m;
        }
        else if (a[m] == max_m)
        {
            if (m == max_n)
                max_m++;
            else if (m < max_n)
                max_n = m;
        }
    }
    cout << max_n << endl;
    return 0;
}