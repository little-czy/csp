#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define MAXN 10005
#define INF 0x3f3f3f3f

using namespace std;

struct node
{
    int v;
    int w;
    node(int _v, int _w) : v(_v), w(_w) {}
};

int n, m;
vector<node> g[MAXN];
int d[MAXN];      //最短距离
int cost[MAXN];   //该点与前驱之间的距离
bool inq[MAXN];   //节点是否在队中
bool visit[MAXN]; //标记该点是否被访问过
int ans = 0;

void SPFA(int begin)
{
    fill(d, d + MAXN, INF);
    queue<int> q;
    q.push(begin);
    inq[begin] = true;
    d[begin] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                cost[v] = w;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v] = true;
                }
            }
            else if (d[u] + w == d[v])
            {
                cost[v] = min(cost[v], w);
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        g[a].push_back(node(b, c));
        g[b].push_back(node(a, c));
    }
    SPFA(1);
    for (int i = 2; i <= n; i++)
    {
        ans += cost[i];
    }
    cout << ans << endl;
    return 0;
}