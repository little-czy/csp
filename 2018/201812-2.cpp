#include <iostream>

using namespace std;

long long r, y, g, n, op, t, ans;

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    long long last_t;
    cin >> r >> y >> g >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op >> t;
        if (op == 0)
            ans += t;
        else if (op == 1)
        {
            last_t = ans % (r + y + g);
            if (last_t <= t)
                ans += t - last_t;
            else if (t + g <= last_t && last_t <= t + g + y + r)
                ans += t + g + y + r - last_t;
        }
        else if (op == 2)
        {
            last_t = ans % (r + y + g);
            if (last_t <= r + t)
                ans += r + t - last_t;
            else if (t + r + g <= last_t)
                ans += t + r + g + y + r - last_t;
        }
        else if (op == 3)
        {
            last_t = ans % (r + y + g);
            if (t <= last_t && last_t < t + y + r)
                ans += t + y + r - last_t;
        }
    }
    cout << ans << endl;
    return 0;
}