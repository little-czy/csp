#include <iostream>
#include <cstdio>
#include <vector>

struct node
{
    int f1, f2;
} nod[20010];

using namespace std;

int n, m;
long ans = 0;
vector<int> no[20010];

int main()
{
    cin >> n >> m;
    int far;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &far);
        no[far].push_back(i);
    }
    for (int i = 10005; i < 10005 + m; i++)
    {
        scanf("%d", &far);
        no[far].push_back(i);
    }
    for (int i = n; i > 0; i--)
    {
        for (int j = 0; j < no[i].size(); j++) //遍历叶节点
        {
            if (nod[no[i][j]].f1 + 1 > nod[i].f2) //当前子节点最大叶深度大于当前节点次深叶深度
            {
                if (nod[no[i][j]].f1 + 1 > nod[i].f1) //当前子节点最大叶深度大于当前节点最深叶深度
                {
                    int temp = nod[i].f1;
                    nod[i].f1 = nod[no[i][j]].f1 + 1;
                    nod[i].f2 = temp;
                }
                else
                {
                    nod[i].f2 = nod[no[i][j]].f1 + 1;
                }
            }
        }
        if (nod[i].f1 + nod[i].f2 > ans)
        {
            ans = nod[i].f1 + nod[i].f2;
        }
    }

    printf("%ld", ans);
    return 0;
}