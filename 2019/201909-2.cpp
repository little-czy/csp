#include <iostream>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

int n, m, d, e, a[maxn];
bool drop[maxn];

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m >> a[i];
        int tmp, tmp_sum = 0;
        for (int j = 1; j < m; j++)
        {
            cin >> tmp;
            if (tmp <= 0)
            {
                tmp_sum += tmp;
            }
            else
            {
                a[i] += tmp_sum;
                if (a[i] > tmp) //发生苹果掉落
                {
                    drop[i] = true;
                    a[i] = tmp;
                }
                tmp_sum = 0;
            }
        }
        a[i] += tmp_sum;
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (drop[i])
        {
            d++;
            if (drop[(i + 1) % n] && drop[(i + 2) % n])
                e++;
        }
    }

    cout << sum << " " << d << " " << e << endl;
    return 0;
}