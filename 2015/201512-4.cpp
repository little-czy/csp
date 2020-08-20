#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <stack>
#define MAXN 10005
using namespace std;

int n, m;
set<int> s[MAXN];
bool flag[MAXN][MAXN];
vector<int> line;
int v[MAXN];
class ufs
{
private:
    int length;

public:
    ufs(int n);
    ~ufs();
    int Find(int x)
    {
        if (x == v[x])
            return x;
        else
            return v[x] = Find(v[x]);
    }

    bool Union(int x, int y)
    {
        x = Find(x);
        y = Find(y);
        if (x == y)
        {
            return false;
        }
        else
        {
            v[x] = y;
            return true;
        }
    }
};

ufs::ufs(int n)
{
    length = n;
    for (int i = 0; i <= n; i++)
    {
        v[i] = i;
    }
}

ufs::~ufs()
{
}

int next(int node)
{
    for (set<int>::iterator it = s[node].begin(); it != s[node].end(); it++)
    {
        if (!flag[node][*it])
        {
            return *it;
        }
    }
    return -1;
}

void dfs(int now)
{
    stack<int> S;
    S.push(now);
    while (!S.empty())
    {

        int u = S.top();
        int v = next(u);
        if (v != -1)
        {
            flag[u][v] = true;
            flag[v][u] = true;
            S.push(v);
        }
        else
        {
            S.pop();
            line.push_back(u);
        }
    }
}

int main()
{
    cin >> n >> m;
    int x, y;
    ufs Ufs(n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &x, &y);
        s[x].insert(y);
        s[y].insert(x);
        Ufs.Union(x, y);
    }
    int root = Ufs.Find(1);
    for (int i = 2; i <= n; i++)
    {
        if (Ufs.Find(i) != root)
        {
            cout << -1 << endl;
            return 0;
        }
    }
    int num = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i].size() % 2 == 1)
        {
            num++;
        }
    }
    if (num == 0 || (num == 2 && s[1].size() % 2 == 1))
    {
        dfs(1);
        for (int i = line.size() - 1; i >= 0; i--)
            printf("%d ", line[i]);
        printf("\n");
    }
    else
        cout << -1 << endl;
    return 0;
}