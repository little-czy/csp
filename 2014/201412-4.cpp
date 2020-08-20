#include <iostream>
#include <cstdio>

#define INF 0x3f3f3f3f
#define MAXV 1005

using namespace std;

int n, m;
int grap[MAXV][MAXV], dis[MAXV];
bool vis[MAXV] = {0};

int main()
{
    int x, y, c;
    long long ans = 0;
    cin >> n >> m;
    fill(dis, dis + MAXV, INF);
    for (int i = 0; i <= n; i++)
    {
        fill(grap[i], grap[i] + n + 1, INF);
    }
    dis[1] = 0;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &x, &y, &c);
        grap[x][y] = c, grap[y][x] = c;
    }
    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF;
        for (int j = 1; j <= n; j++)
        {
            if (vis[j] == 0 && dis[j] < MIN)
            {
                u = j;
                MIN = dis[j];
            }
        }
        vis[u] = 1; //标记为已访问
        ans += dis[u];
        for (int v = 1; v <= n; v++)
        {
            if (vis[v] == 0 && grap[u][v] != INF && grap[u][v] < dis[v])
            {
                dis[v] = grap[u][v];
            }
        }
    }
    cout << ans << endl;

    return 0;
}