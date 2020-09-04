#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 505;
const int maxm = 1e4 + 5;

struct node
{
    int u, v, nxt;
} edge[maxm << 1];

struct node1
{
    int a, c;
    node1() {}
    node1(int _a, int _c) : a(_a), c(_c) {}
};

struct message
{
    int time;         //当前消息到达时刻
    vector<int> lian; //消息链
    message() {}
    message(int _t, vector<int> _v) : time(_t), lian(_v) {}
};

int n, m, t, k, total, head[maxn];
vector<int> no[maxn];
queue<message> q[maxn];
vector<node1> increase;

inline int get_num()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x;
}

inline int get_num(bool &over)
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    // while (ch == ' ')
    //     ch = getchar();
    over = false;
    if (ch == '\n' || ch == EOF)
        over = true;
    return x;
}

inline void addedge(int u, int v)
{
    edge[++total].u = u;
    edge[total].v = v;
    edge[total].nxt = head[u];
    head[u] = total;
}

void inc_send(int x)
{
    for (int i = 0; i < increase.size(); i++)
    {
        int a = increase[i].a, c = increase[i].c;
        no[a].push_back(c);
        for (int j = head[a]; j; j = edge[j].nxt)
        {
            int v = edge[j].v;
            q[v].push(message(x + t, no[a]));
            // cout << "---" << q[v].size() << "\n";
        }
    }
    increase.clear();
}

void resieve(int last_t, int cur_t)
{
    for (int i = last_t; i <= cur_t; i++)
    {
        for (int j = 1; j <= n; j++) //对于每一个顶点
        {
            bool flag = false;
            while (!q[j].empty() && q[j].front().time == i) //传送队列非空且当前时刻需要接收消息
            {
                // cout << q[j].size() << "---" << endl;
                if (q[j].front().lian.size() > no[j].size())
                {
                    no[j] = q[j].front().lian;
                    flag = true;
                }
                else if (q[j].front().lian.size() == no[j].size() && q[j].front().lian.back() < no[j].back())
                {
                    no[j] = q[j].front().lian;
                    flag = true;
                }
                q[j].pop();
            }
            if (flag)
                for (int l = head[j]; l; l = edge[l].nxt)
                    q[edge[l].v].push(message(t + i, no[j]));
        }
    }
}

int main()
{
    int u, v, a, b, c;
    int inc_t = 0, cur_t = 0;
    bool over;
    freopen("in", "r", stdin);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cin >> n >> m;
    n = get_num(), m = get_num();
    for (int i = 0; i < m; i++)
    {
        // cin >> u >> v;
        u = get_num(), v = get_num();
        addedge(u, v), addedge(v, u);
    }
    // cin >> t >> k;
    for (int i = 1; i <= n; i++) //创世块
        no[i].push_back(0);
    t = get_num(), k = get_num();
    for (int i = 0; i < k; i++)
    {
        // getline(cin, tmp);
        a = get_num(), b = get_num(over);
        // cout << a << " " << b << " ";
        if (!over)
        {
            c = get_num();
            if (b > inc_t) //发生时刻跳转
            {
                inc_send(inc_t);
                resieve(inc_t + 1, b);
            }
            //在当前时刻继续增加块
            increase.push_back(node1(a, c));
            inc_t = b;
        }
        else
        {
            inc_send(inc_t);       //添加上一次增加的块
            resieve(inc_t + 1, b); //从增加块后运行到b时刻
            cout << no[a].size();
            // printf("%d", (int)no[a].size());
            for (int j = 0; j < no[a].size(); j++)
                cout << " " << no[a][j];
            // printf(" %d", no[a][j]);
            cout << "\n";
            // printf("\n");
            inc_t = b;
        }
    }
    return 0;
}
