#include <iostream>
#include <cmath>

#define MAXN 1005

using namespace std;

int n, a[MAXN];

int main()
{
    cin >> n;
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (abs(a[i] - a[j]) < ans)
            {
                ans = abs(a[i] - a[j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}