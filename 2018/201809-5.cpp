#include <iostream>
#define ull unsigned long long
using namespace std;

const ull Q = 998244353;
ull m, l, r;
ull k[100005], a[100005];

int main()
{
    cin >> m >> l >> r;
    a[0] = 1;
    for (int i = 0; i < m; i++)
    {
        cin >> k[i];
    }
    for (int i = 1; i <= r; i++)
    {
        a[i] = 0;
        if (i < m)
        {
            for (int j = 0; j < i; j++)
            {
                a[i] += (k[j] * a[i - j - 1]) % Q;
            }
        }
        else
        {
            for (int j = 0; j < m; j++)
            {
                a[i] += (k[j] * a[i - j - 1]) % Q;
            }
        }
        if (i >= l)
            cout << a[i] << endl;
    }
    return 0;
}