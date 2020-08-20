#include <iostream>
#include <queue>

using namespace std;

int n, m, k;
long long r;
int num;               //路径数目统计
bool visit[1000][210]; //访问标记
struct
{
    long long x, y;
} in[210];

typedef struct node
{
    long long x, y;
    int k_num;    //增加新的路由器的数目
    int step;     //路径长度
    int path_num; //路径编号
} node;

int bfs(int begin, int end)
{
    node s, now;
    int range;
    s.x = in[begin].x;
    s.y = in[begin].y;
    s.step = 0;
    s.k_num = 0;
    s.path_num = num++;
    visit[s.path_num][begin] = true;
    queue<node> q;
    q.push(s);
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        if (now.x == in[end].x && now.y == in[end].y) //到达终点
            return now.step - 1;
        if (now.k_num < k) //判断可选路由器是否达到限制
            range = n + m;
        else
            range = n;
        for (int i = 0; i < range; i++) //从未访问节点中选择
        {
            if (visit[now.path_num][i]) //访问过则跳过
                continue;
            if ((now.x - in[i].x) * (now.x - in[i].x) + (now.y - in[i].y) * (now.y - in[i].y) > r * r) //判断是否在连接范围内
                continue;
            node v;
            v.x = in[i].x, v.y = in[i].y;
            v.step = now.step + 1;
            if (i < n)
                v.k_num = now.k_num;
            else
                v.k_num = now.k_num + 1;
            v.path_num = num++;
            if (num >= 1000)
                num = 0;
            for (int j = 0; j < n + k; j++)
                visit[v.path_num][j] = visit[now.path_num][j];
            visit[v.path_num][i] = true;
            q.push(v);
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m >> k >> r;
    for (int i = 0; i < n + m; i++)
    {
        cin >> in[i].x >> in[i].y;
    }
    cout << bfs(0, 1) << endl;
    return 0;
}