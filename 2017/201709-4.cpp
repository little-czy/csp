// floyd算法，得分 60
// #include <iostream>
// #include <cstdio>
// #define MAXN 1005
// using namespace std;

// int n, m, ans = 0;
// bool g1[MAXN][MAXN];
// bool g2[MAXN][MAXN];

// void floyd1()
// {
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             for (int k = 1; k <= n; k++)
//             {
//                 if (g1[j][k])
//                     continue;
//                 if (g1[j][i] != 0 && g1[i][k] != 0)
//                 {
//                     g1[j][k] = true;
//                 }
//             }
//         }
//     }
// }

// void floyd2()
// {
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             for (int k = 1; k <= n; k++)
//             {
//                 if (g2[j][k])
//                     continue;
//                 if (g2[j][i] != 0 && g2[i][k] != 0)
//                 {
//                     g2[j][k] = true;
//                 }
//             }
//         }
//     }
// }

// int main()
// {
//     cin >> n >> m;
//     int a, b;
//     for (int i = 1; i <= n; i++)
//     {
//         g1[i][i] = g2[i][i] = true;
//     }

//     for (int i = 0; i < m; i++)
//     {
//         scanf("%d%d", &a, &b);
//         g1[a][b] = true;
//         g2[b][a] = true;
//     }
//     floyd1();
//     floyd2();
//     for (int i = 1; i <= n; i++)
//     {
//         int flag = true;
//         for (int j = 1; j <= n; j++)
//         {
//             if (!g1[i][j] && !g2[i][j])
//             {
//                 flag = false;
//                 break;
//             }
//         }
//         if (flag)
//             ans++;
//     }
//     cout << ans << endl;
//     return 0;
// }

// dfs深搜，得分 100
#include <iostream>
#include <cstdio>
#include <vector>

#define MAXN 1005

using namespace std;

int n, m, ans = 0;
vector<int> g[MAXN];
bool d[MAXN][MAXN];
bool vis[MAXN];

void dfs(int s, int t)
{
    vis[s] = true;
    d[s][t] = d[t][s] = true;
    for (int i = 0; i < g[s].size(); i++)
    {
        if (!vis[g[s][i]])
            dfs(g[s][i], t);
    }
}

int main()
{
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; i++)
    {
        fill(vis, vis + MAXN, 0);
        dfs(i, i);
    }
    for (int i = 1; i <= n; i++)
    {
        int flag = true;
        for (int j = 1; j <= n; j++)
        {
            if (!d[i][j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            ans++;
    }
    cout << ans << endl;
    return 0;
}