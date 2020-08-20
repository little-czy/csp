#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#define MAXN 100005
#define INF 0x3f3f3f3f

using namespace std;

struct node
{
    int v;
    int w;
    node(int _v, int _w) : v(_v), w(_w) {}
};

int n, m;
int d[MAXN];
vector<node> g[MAXN];
bool inq[MAXN];

void SPFA(int s)
{
    queue<int> q;
    q.push(s);
    inq[s] = true;
    d[s] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        inq[now] = false;
        for (int i = 0; i < g[now].size(); i++)
        {
            int v = g[now][i].v;
            int w = g[now][i].w;
            if (w < d[v] && d[now] < d[v])
            {
                d[v] = w > d[now] ? w : d[now];
                if (!inq[v])
                {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back(node(v, w));
        g[v].push_back(node(u, w));
    }
    fill(d, d + MAXN, INF);
    SPFA(1);
    cout << d[n] << endl;
    return 0;
}
