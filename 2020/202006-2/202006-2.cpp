#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

ll n, a, b;
map<ll, ll> u, v;

int main()
{
    ll index, value;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> a >> b;
    for (int i = 0; i < a; i++)
    {
        cin >> index >> value;
        u[index] = value;
    }
    for (int i = 0; i < b; i++)
    {
        cin >> index >> value;
        v[index] = value;
    }
    ll ans = 0;
    if (u.size() < v.size())
        for (auto it = u.begin(); it != u.end(); it++)
            ans += it->second * v[it->first];
    else
        for (auto it = v.begin(); it != v.end(); it++)
            ans += it->second * u[it->first];
    cout << ans << endl;
    return 0;
}