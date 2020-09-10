#include <bits/stdc++.h>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

int n;
string ss[2], s;

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s;
    ss[0] = "1";
    int cur = 0;
    for (int i = 0; i < n; i++)
    {
        ss[cur ^ 1].clear();
        for (int j = 0; j < ss[cur].length(); j++)
        {
            switch (ss[cur][j])
            {
            case '1':
                ss[cur ^ 1].append("2");
                break;
            case '2':
                ss[cur ^ 1].append("4");
                break;
            case '4':
                ss[cur ^ 1].append("16");
                break;
            case '6':
                ss[cur ^ 1].append("64");
                break;
            }
        }
        cur ^= 1;
    }
    // cout << cur << endl;
    int ans = 0;
    for (int pos = 0; (pos = ss[cur].find(s, pos)) != string::npos; pos += s.length())
    {
        ans++;
    }
    cout << ans << endl;
    return 0;
}