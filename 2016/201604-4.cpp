#include <iostream>
#include <queue>

using namespace std;

int n, m, t;
bool visit[105][105][300];
struct g
{
    int begin, end;
} g[105][105];
struct node
{
    int x, y, time;
    node() {}
    node(int _x, int _y, int _t) : x(_x), y(_y), time(_t) {}
};
queue<node> q;

bool canUp(node a)
{
    if (a.x < n)
    {
        if (g[a.x + 1][a.y].begin == 0 && g[a.x + 1][a.y].end == 0)
            return true;
        else
            return g[a.x + 1][a.y].begin > a.time + 1 || g[a.x + 1][a.y].end < a.time + 1;
    }
    return false;
}

bool canDown(node a)
{
    if (a.x > 1)
    {
        if (g[a.x - 1][a.y].begin == 0 && g[a.x - 1][a.y].end == 0)
            return true;
        else
            return g[a.x - 1][a.y].begin > a.time + 1 || g[a.x - 1][a.y].end < a.time + 1;
    }
    return false;
}

bool canLeft(node a)
{
    if (a.y > 1)
    {
        if (g[a.x][a.y - 1].begin == 0 && g[a.x][a.y - 1].end == 0)
            return true;
        else
            return g[a.x][a.y - 1].begin > a.time + 1 || g[a.x][a.y - 1].end < a.time + 1;
    }
    return false;
}

bool canRight(node a)
{
    if (a.y < m)
    {
        if (g[a.x][a.y + 1].begin == 0 && g[a.x][a.y + 1].end == 0)
            return true;
        else
            return g[a.x][a.y + 1].begin > a.time + 1 || g[a.x][a.y + 1].end < a.time + 1;
    }
    return false;
}

int main()
{
    cin >> n >> m >> t;
    int x, y, b, e;
    for (int i = 0; i < t; i++)
    {
        cin >> x >> y >> b >> e;
        g[x][y].begin = b;
        g[x][y].end = e;
    }
    q.push(node(1, 1, 0));
    visit[1][1][0] = true;
    while (!q.empty())
    {
        node now = q.front();
        q.pop();
        if (now.x == n && now.y == m)
        {
            cout << now.time << endl;
            break;
        }
        if (canUp(now))
        {
            if (!visit[now.x + 1][now.y][now.time + 1])
            {
                visit[now.x + 1][now.y][now.time + 1] = true;
                q.push(node(now.x + 1, now.y, now.time + 1));
            }
        }
        if (canDown(now))
        {
            if (!visit[now.x - 1][now.y][now.time + 1])
            {
                visit[now.x - 1][now.y][now.time + 1] = true;
                q.push(node(now.x - 1, now.y, now.time + 1));
            }
        }
        if (canLeft(now))
        {
            if (!visit[now.x][now.y - 1][now.time + 1])
            {
                visit[now.x][now.y - 1][now.time + 1] = true;
                q.push(node(now.x, now.y - 1, now.time + 1));
            }
        }
        if (canRight(now))
        {
            if (!visit[now.x][now.y + 1][now.time + 1])
            {
                visit[now.x][now.y + 1][now.time + 1] = true;
                q.push(node(now.x, now.y + 1, now.time + 1));
            }
        }
    }

    return 0;
}