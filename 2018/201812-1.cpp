#include <iostream>

using namespace std;

int r, y, g, n, op, t, ans;

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> r >> y >> g >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op >> t;
        if (op == 0 || op == 1)
            ans += t;
        else if (op == 2)
            ans += t + r;
    }
    cout << ans << endl;
    return 0;
}