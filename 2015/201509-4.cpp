#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define MAXN 10005
using namespace std;

int n, m, num = 0;
long ans = 0;
vector<int> g0[MAXN]; //邻接表
vector<int> g1[MAXN]; //原图的逆序
stack<int> s;         //逆后序遍历栈
bool visit1[MAXN];    //逆后序遍历标记
bool visit0[MAXN];    //原图遍历标记
int v[MAXN];          //记录每个强连通分量的节点个数

void dfs1(int begin)
{
    stack<int> s0;
    bool flag;
    int now;
    s0.push(begin);
    visit1[begin] = 1;
    while (!s0.empty())
    {
        now = s0.top();
        flag = 0; //初始化进栈标记
        for (vector<int>::iterator it = g1[now].begin(); it != g1[now].end(); it++)
        {
            if (visit1[*it] == 0)
            {
                s0.push(*it);
                visit1[*it] = 1;
                flag = 1; //有元素进栈标记
                break;
            }
        }
        if (!flag) //无元素进栈, 访问该节点
        {
            s.push(now);
            s0.pop();
        }
    }
}

void dfs0(int begin, int no)
{
    stack<int> s0;
    bool flag;
    int now;
    s0.push(begin);
    v[no] = 1;
    visit0[begin] = 1;
    while (!s0.empty())
    {
        now = s0.top();
        flag = 0; //初始化进栈标记
        for (vector<int>::iterator it = g0[now].begin(); it != g0[now].end(); it++)
        {
            if (visit0[*it] == 0)
            {
                s0.push(*it);
                v[no]++;
                visit0[*it] = 1;
                flag = 1; //有元素进栈标记
                break;
            }
        }
        if (!flag) //无元素进栈, 访问该节点
        {
            s0.pop();
        }
    }
}

inline int count_pair(int i) //计算每个强连通分量的节点组合数
{
    return i * (i - 1) / 2;
}

int main()
{
    cin >> n >> m;
    int x, y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &x, &y);
        g0[x].push_back(y);
        g1[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!visit1[i])
            dfs1(i);
    }
    for (int i = 0; i < n; i++)
    {
        if (!visit0[s.top()])
        {
            dfs0(s.top(), num);
            num++;
        }
        s.pop();
    }
    for (int i = 0; i < num; i++)
        ans += count_pair(v[i]);
    cout << ans << endl;
    return 0;
}
