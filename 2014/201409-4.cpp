#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct node
{
    int x, y, num;
} no;

int n, m, k, d;
int f[1010][1010];
long long ans;
vector<node> end1; //存放门店和客户位置
queue<node> q;

inline bool canUp(int x, int y) //可以更新上面一个位置
{
    if (x > 1 && f[x - 1][y] > f[x][y] + 1)
        return 1;
    else
        return 0;
}

inline bool canDown(int x, int y) //可以更新下面一个位置
{
    if (x < n && f[x + 1][y] > f[x][y] + 1)
        return 1;
    else
        return 0;
}
inline bool canLeft(int x, int y) //可以更新左边一个位置
{
    if (y > 1 && f[x][y - 1] > f[x][y] + 1)
        return 1;
    else
        return 0;
}
inline bool canRight(int x, int y) //可以更新右边一个位置
{
    if (y < n && f[x][y + 1] > f[x][y] + 1)
        return 1;
    else
        return 0;
}

void refush() //更新距离信息
{
    node st, now, next_node;
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        if (canUp(now.x, now.y))
        {
            next_node.x = now.x - 1;
            next_node.y = now.y;
            f[next_node.x][next_node.y] = f[now.x][now.y] + 1; //更新距离
            q.push(next_node);
        }
        if (canDown(now.x, now.y))
        {
            next_node.x = now.x + 1;
            next_node.y = now.y;
            f[next_node.x][next_node.y] = f[now.x][now.y] + 1; //更新距离
            q.push(next_node);
        }
        if (canLeft(now.x, now.y))
        {
            next_node.x = now.x;
            next_node.y = now.y - 1;
            f[next_node.x][next_node.y] = f[now.x][now.y] + 1; //更新距离
            q.push(next_node);
        }
        if (canRight(now.x, now.y))
        {
            next_node.x = now.x;
            next_node.y = now.y + 1;
            f[next_node.x][next_node.y] = f[now.x][now.y] + 1; //更新距离
            q.push(next_node);
        }
    }
}

int main()
{
    cin >> n >> m >> k >> d;
    int x, y, num;
    // fill(f, f + (1010 * 1010), INF);
    for (int i = 0; i < 1010; i++)
    {
        fill(f[i], f[i] + 1010, INF);
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &no.x, &no.y);
        // start.push_back(no);
        q.push(no);
        f[no.x][no.y] = 0; //店面位置
    }
    for (int i = 0; i < k; i++)
    {
        scanf("%d%d%d", &no.x, &no.y, &no.num);
        end1.push_back(no);
    }
    for (int i = 0; i < d; i++)
    {
        scanf("%d%d", &x, &y);
        f[x][y] = -1; //不可经过
    }
    refush();
    for (vector<node>::iterator it = end1.begin(); it != end1.end(); it++)
    {
        ans += (long long)(f[it->x][it->y] * it->num);
    }
    cout << ans << endl;
    return 0;
}