#include <bits/stdc++.h>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e4 + 5;
const int maxm = 1e4 + 5;

struct node
{
    int v, w, nxt;
} edge[maxm << 1];

int n, m, k, head[maxn], total, d[maxn];
bool isroot[maxn], vis[maxn];
priority_queue<int, vector<int>, less<int>> s[maxn];

inline void add_edge(int u, int v, int w)
{
    edge[++total].v = v;
    edge[total].w = w;
    edge[total].nxt = head[u];
    head[u] = total;
}

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
        for (int i = head[now]; i; i = edge[i].nxt)
        {
            int v = edge[i].v;
            int w = edge[i].w;
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
}

int main()
{
    int u, v, w;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> isroot[i];
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        if (u != v)
            add_edge(u, v, w), add_edge(v, u, w);
    }

    for (int i = 1; i <= n; i++)
    {
        if (isroot[i])
        {
            spfa(i);
            for (int j = 1; j <= n; j++)
            {
                if (d[j] != inf)
                {
                    if (s[j].size() < k)
                        s[j].push(d[j]);
                    else if (s[j].top() > d[j])
                        s[j].pop(), s[j].push(d[j]);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int ans = 0;
        while (!s[i].empty() && s[i].top() == inf)
            s[i].pop();
        while (!s[i].empty())
            ans += s[i].top(), s[i].pop();
        cout << ans << endl;
    }

    return 0;
}