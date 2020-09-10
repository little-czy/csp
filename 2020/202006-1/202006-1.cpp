#include <bits/stdc++.h>
// #include <iostream>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

struct node
{
    int x, y;
} a[maxn], b[maxn];

int n, m, totala, totalb;

int main()
{
    int x, y, z;
    char c;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> c;
        if (c == 'A')
            a[totala].x = x, a[totala++].y = y;
        else
            b[totalb].x = x, b[totalb++].y = y;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> z;
        int res = x + y * a[0].x + z * a[0].y;
        bool flag = true;
        for (int j = 1; j < totala; j++)
        {
            int tmp = x + y * a[j].x + z * a[j].y;
            if ((res < 0 && tmp < 0) || (res > 0 && tmp > 0))
                continue;
            else
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            for (int j = 0; j < totalb; j++)
            {
                int tmp = x + y * b[j].x + z * b[j].y;
                if ((res < 0 && tmp > 0) || (res > 0 && tmp < 0))
                    continue;
                else
                {
                    flag = false;
                    break;
                }
            }
        }
        else
        {
            cout << "No" << endl;
            continue;
        }
        if (flag)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}