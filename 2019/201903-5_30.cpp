#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e4 + 5;

struct node
{
    int v, w;
    node(int _v, int _w) : v(_v), w(_w) {}
};

int n, m, k, d[maxn], td[maxn], tdnum;
bool type[maxn], vis[maxn];
vector<node> adj[maxn];

void spfa(int s)
{
    fill(d, d + maxn, inf);
    fill(vis, vis + maxn, 0);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    d[s] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        vis[now] = false;
        for (int i = 0; i < adj[now].size(); i++)
        {
            int v = adj[now][i].v;
            int w = adj[now][i].w;
            if (d[v] > d[now] + w)
            {
                d[v] = d[now] + w;
                if (!vis[v])
                {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    tdnum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (type[i] && d[i] != inf)
            td[tdnum++] = d[i];
    }
}

int main()
{
    int u, v, w;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> type[i];
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back(node(v, w));
        adj[v].push_back(node(u, w));
    }
    for (int i = 1; i <= n; i++)
    {
        int ans = 0;
        spfa(i);
        sort(td, td + tdnum);
        for (int j = 0; j < k && j < tdnum; j++)
        {
            ans += td[j];
        }
        cout << ans << endl;
    }

    return 0;
}