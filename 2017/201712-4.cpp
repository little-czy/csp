// #include <iostream>
// #include <cstdio>
// #include <vector>
// #include <queue>

// #define MAXN 505
// #define INF 0x3f3f3f3f
// #define ll long long

// using namespace std;

// struct node
// {
//     int t;
//     ll v, w;
//     node(ll _t, ll _v, ll _w) : t(_t), v(_v), w(_w) {}
// };

// struct dis
// {
//     bool valid = false;
//     ll max_road_length;
//     ll min_road_length;
//     long long get_dis()
//     {
//         if (valid)
//             return max_road_length + min_road_length * min_road_length;
//         return INF;
//     }
// } d[MAXN];

// int n, m;
// vector<node> g[MAXN];
// bool inq[MAXN];
// ll x[MAXN][MAXN]; //小路

// void floyd()
// {
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             for (int k = 0; k < n; k++)
//             {
//                 if (x[j][k] > x[j][i] + x[i][k] && x[j][i] != INF && x[i][k] != INF)
//                     x[j][k] = x[j][i] + x[i][k];
//             }
//         }
//     }
// }

// void SPFA(int s)
// {
//     queue<int> q;
//     q.push(s);
//     inq[s] = true;
//     d[1].valid = true;
//     d[1].max_road_length = d[1].min_road_length = 0;
//     int u, t, v, w;
//     while (!q.empty())
//     {
//         u = q.front();
//         q.pop();
//         for (int i = 0; i < g[u].size(); i++)
//         {
//             t = g[u][i].t;
//             v = g[u][i].v;
//             w = g[u][i].w;
//             if (t) //u与v之间为小路
//             {
//                 ll tmp = d[u].max_road_length + (d[u].min_road_length + w) * (d[u].min_road_length + w);
//                 if (tmp < d[v].get_dis())
//                 {
//                     d[v].valid = true;
//                     d[v].max_road_length = d[u].max_road_length;
//                     d[v].min_road_length += (d[u].min_road_length + w);
//                     if (!inq[v])
//                     {
//                         q.push(v);
//                         inq[v] = true;
//                     }
//                 }
//             }
//             else //u与v之间为大路
//             {
//                 ll tmp = w + d[u].get_dis();
//                 if (tmp < d[v].get_dis())
//                 {
//                     d[v].valid = true;
//                     d[v].max_road_length = tmp;
//                     d[v].min_road_length = 0;
//                     if (!inq[v])
//                     {
//                         q.push(v);
//                         inq[v] = true;
//                     }
//                 }
//             }
//         }
//     }
// }

// // void put(int t, int a, int b, int c)
// // {
// //     for (int i = 0; i < g[b].size(); i++)
// //     {
// //         if (g[b][i].t == t && g[b][i].v == a) //已存在该边
// //         {
// //             g[b][i].w = c < g[b][i].w ? c : g[b][i].w;
// //             break;
// //         }
// //     }
// //     for (int i = 0; i < g[a].size(); i++)
// //     {
// //         if (g[a][i].t == t && g[a][i].v == b) //已存在该边
// //         {
// //             g[a][i].w = c < g[a][i].w ? c : g[a][i].w;
// //             return;
// //         }
// //     }
// //     g[a].push_back(node(t, b, c));
// //     g[b].push_back(node(t, a, c));
// // }

// int main()
// {
//     cin >> n >> m;
//     int t;
//     int a, b, c;
//     for (int i = 0; i < m; i++)
//     {
//         scanf("%d%d%d%d", &t, &a, &b, &c);
//         // put(t, a, b, c);
//         if (t && x[a][b] > c)
//         {
//             x[a][b] = c;
//             x[b][a] = c;
//         }
//         else
//         {
//             g[a].push_back(node(t, b, c));
//             g[b].push_back(node(t, a, c));
//         }
//     }
//     SPFA(1);
//     cout << d[n].get_dis() << endl;
//     return 0;
// }

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>

#define MAXN 505
#define INF 0x3f3f3f3f
#define ll long long

using namespace std;

int n, m;
bool inq[MAXN];
ll x[MAXN][MAXN]; //小路
ll d[MAXN][MAXN]; //大路
ll dis1[MAXN], dis2[MAXN];

void floyd()
{

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = j + 1; k <= n; k++)
            {
                if (x[j][i] != INF && x[i][k] != INF && x[j][i] + x[i][k] < x[j][k])
                {
                    x[j][k] = x[k][j] = x[j][i] + x[i][k];
                }
            }
        }
    }
}

void SPFA(int s)
{
    queue<int> q;
    q.push(s);
    inq[s] = true;
    dis1[s] = dis2[s] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        inq[now] = false;
        for (int i = 2; i <= n; i++)
        {
            bool update = false;
            if (d[now][i] < INF)
            {
                ll w = dis1[now] + d[now][i]; //之前走大路,现在还是从大路走到i
                if (w < dis1[i])
                {
                    dis1[i] = w;
                    update = true;
                }
                w = dis2[now] + d[now][i]; //之前走小路，现在走大路
                if (w < dis1[i])
                {
                    dis1[i] = w;
                    update = true;
                }
            }
            if (x[now][i] < INF)
            {
                ll w = dis1[now] + x[now][i] * x[now][i]; //之前走大路,现在走小路走到i
                if (w < dis2[i])
                {
                    dis2[i] = w;
                    update = true;
                }
            }
            if (update && !inq[i])
            {
                q.push(i);
                inq[i] = true;
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    int t, a, b;
    ll c;
    memset(x, INF, sizeof(x));
    memset(d, INF, sizeof(d));
    memset(dis1, INF, sizeof(dis1));
    memset(dis2, INF, sizeof(dis2));
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d%lld", &t, &a, &b, &c);
        if (t == 1 && x[a][b] > c)
        {
            x[a][b] = c;
            x[b][a] = c;
        }
        else if (t == 0 && d[a][b] > c)
        {
            d[a][b] = c;
            d[b][a] = c;
        }
    }
    floyd();
    SPFA(1);
    cout << min(dis1[n], dis2[n]) << endl;
    return 0;
}