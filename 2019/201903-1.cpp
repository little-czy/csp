#include <iostream>

using namespace std;
const int maxn = 1e5 + 5;

int n, a[maxn];

int main()
{
    freopen("in", "r", stdin);
    // ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    if (a[0] >= a[n - 1])
        cout << a[0] << " ";
    else
        cout << a[n - 1] << " ";
    if (n % 2 == 0)
    {
        double ans = 1.0 * (a[n >> 1] + a[(n >> 1) - 1]) / 2.0;
        // cout << a[n >> 1] << " " << a[(n >> 1) - 1] << endl;
        if (int(ans * 10) % 10 != 0)
            printf("%.1lf ", ans);
        else
            printf("%.0lf ", ans);
    }
    else
        printf("%d ", a[n >> 1]);
    if (a[0] < a[n - 1])
        cout << a[0] << endl;
    else
        cout << a[n - 1] << endl;
    return 0;
}