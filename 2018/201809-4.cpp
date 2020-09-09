#include <bits/stdc++.h>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 305;

struct node
{
    int v, w;
    node() {}
    node(int _v, int _w) : v(_v), w(_w) {}
};

int n, s[maxn], b[maxn], d[maxn];
bool inq[maxn];
vector<node> adj[maxn];

bool spfa(int s)
{
    queue<int> q;
    for (int i = 0; i <= n; i++)
        q.push(i), d[i] = 0, inq[i] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].v;
            int w = adj[u][i].w;
            if (d[v] < d[u] + w)
            {
                d[v] = d[u] + w;
                if (!inq[v])
                {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        adj[0].push_back(node(i, 0));
    for (int i = 3; i <= n; i++)
    {
        adj[i - 3].push_back(node(i, 3 * b[i - 1]));
        adj[i].push_back(node(i - 3, -3 * b[i - 1] - 2));
    }
    adj[0].push_back(node(2, 2 * b[1]));
    adj[2].push_back(node(0, -1 - 2 * b[1]));
    adj[n].push_back(node(n - 2, -1 - 2 * b[n]));
    adj[n - 2].push_back(node(n, 2 * b[n]));
    for (int i = 1; i <= n; i++)
        adj[i - 1].push_back(node(i, 1));
    spfa(0);
    for (int i = 1; i <= n; i++)
        cout << d[i] - d[i - 1] << " ";
    return 0;
}