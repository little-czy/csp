#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>

#define MAXN 100005
#define INF 0x3f3f3f3f

using namespace std;

struct node
{
    int v; //后继节点
    int w; //边权
    node(int _v, int _w) : v(_v), w(_w) {}
};

int n, m;
int price[MAXN];       //每个城市的食品价格
vector<node> no[MAXN]; //邻接表
bool inq[MAXN];        //记录节点是否在队列中
int d[MAXN];           //记录最短距离
set<int> pre[MAXN];    //前驱
long long ans;         //最小花费

bool SPFA(int s)
{
    fill(d, d + MAXN, INF);
    fill(inq, inq + MAXN, false);
    for (int i = 0; i < MAXN; i++)
    {
        pre[i].clear();
    }
    queue<int> q;
    q.push(s);  //源节点入队
    inq[s] = 1; //源点已入队
    d[s] = 0;   //源点的d的值为0
    while (!q.empty())
    {
        int u = q.front(); //获取队首元素
        q.pop();
        inq[u] = false;
        for (int i = 0; i < no[u].size(); i++)
        {
            int v = no[u][i].v;  //后继节点
            int w = no[u][i].w;  //边权
            if (d[u] + w < d[v]) //松弛
            {
                d[v] = d[u] + w;
                if (!inq[v]) //邻接节点不在队中，进队
                {
                    q.push(v);
                    inq[v] = true;
                }
                pre[v].clear();
                pre[v].insert(u);
            }
            else if (d[u] + w == d[v]) //找到相同长度的最短路径
            {
                pre[v].insert(u);
            }
        }
    }
    return true;
}

// void print_road(int s, int d)
// {
//     for (set<int>::iterator it = pre[s].begin(); it != pre[s].end(); it++)
//     {
//         if (*it == d)
//             cout << endl;
//         else
//         {
//             cout << *it << " ";
//             print_road(*it, d);
//         }
//     }
// }

inline int get_length(int s, int d)
{
    for (int i = 0; i < no[s].size(); i++)
    {
        if (no[s][i].v == d)
        {
            return no[s][i].w;
        }
    }
    return INF;
}

void print_road(int s, int d, int tmp_price, long long cost)
{
    for (set<int>::iterator it = pre[s].begin(); it != pre[s].end(); it++)
    {
        long long tmp_cost = cost + tmp_price * get_length(s, *it);
        if (*it == d) //到达终点
        {
            if (tmp_cost < ans)
            {
                ans = tmp_cost;
            }
        }
        else
        {
            if (price[*it] < tmp_price) //走到的节点食物更加便宜了
            {
                print_road(*it, d, price[*it], tmp_cost);
            }
            else
            {
                print_road(*it, d, tmp_price, tmp_cost);
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    int u, v, w;
    for (int i = 1; i <= n; i++)
        cin >> price[i];
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        no[u].push_back(node(v, w));
        no[v].push_back(node(u, w));
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        SPFA(v);
        ans = INF;
        print_road(u, v, price[u], 0);
        cout << ans << endl;
    }
    return 0;
}