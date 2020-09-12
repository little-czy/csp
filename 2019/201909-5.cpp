#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int maxn = 5e4 + 5;

struct node
{
    int v, w;
    node(int _v, int _w) : v(_v), w(_w) {}
};

int n, m, k, num[maxn];
ll dp[maxn][105], tmp[105];
bool vital[maxn];
vector<node> adj[maxn];

void dfs(int x, int fa)
{
    dp[x][0] = 0;
    if (vital[x])
    {
        dp[x][1] = 0;
        num[x] = 1;
    }
    for (int i = 0; i < adj[x].size(); i++)
    {
        int v = adj[x][i].v, w = adj[x][i].w;
        if (v != fa)
        {
            dfs(v, x);
            for (int j = 0; j <= k; j++)
                tmp[j] = dp[x][j];
            int nu = min(k, num[x]);
            int nv = min(k, num[v]);
            num[x] += num[v];
            for (int j = 0; j <= nu; j++)
                for (int l = 0; l <= nv && j + l <= k; l++)
                    dp[x][j + l] = min(dp[x][j + l], (ll)(k - l) * l * w + tmp[j] + dp[v][l]);
        }
    }
}

int main()
{
    int a, b, c;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        cin >> a;
        vital[a] = true;
    }
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b >> c;
        adj[a].push_back(node(b, c));
        adj[b].push_back(node(a, c));
    }
    fill(dp[0], dp[0] + maxn * 105, inf);
    dfs(1, -1);
    cout << dp[1][k] << endl;
    return 0;
}