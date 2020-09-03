#include <iostream>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

int n, m, k = 1, p, a[maxn];

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        int tmp, tmp_sum = 0;
        for (int j = 0; j < m; j++)
        {
            cin >> tmp;
            tmp_sum += tmp;
        }
        if (p > tmp_sum)
        {
            p = tmp_sum;
            k = i;
        }
        a[i] += tmp_sum;
    }
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += a[i];
    }
    cout << sum << " " << k << " " << -p << endl;
    return 0;
}