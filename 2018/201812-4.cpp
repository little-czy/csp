#include <iostream>
#include <algorithm>

using namespace std;
const int maxm = 1e5 + 5;

struct node
{
    int v, u, t;
    bool operator<(const node &a) const
    {
        return t < a.t;
    }
} no[maxm];

int n, m, r;
int fa[maxm];

int find_fa(int x)
{
    if (x == fa[x])
        return x;
    return fa[x] = find_fa(fa[x]);
}

int kruskal()
{
    int edgenum = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    sort(no, no + m);
    for (int i = 0; i < m; i++)
    {
        int fu = find_fa(no[i].u);
        int fv = find_fa(no[i].v);
        if (fu != fv)
        {
            fa[fu] = fv;
            edgenum++;
            if (edgenum == n - 1)
                return no[i].t;
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    freopen("in", "r", stdin);
    cin >> n >> m >> r;
    for (int i = 0; i < m; i++)
        cin >> no[i].v >> no[i].u >> no[i].t;
    cout << kruskal() << endl;
    return 0;
}