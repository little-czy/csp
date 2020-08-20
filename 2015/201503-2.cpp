#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int a[1005];
struct ans
{
    int num;
    int count;
} res[1005];

bool cmp(struct ans x, struct ans y)
{
    if (x.count == y.count)
        return x.num < y.num;
    else
        return y.count < x.count;
}

int main()
{
    cin >> n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        a[x]++;
    }
    int j = 0;
    for (int i = 0; i < 1005; i++)
    {
        if (a[i] != 0)
        {
            res[j].count = a[i];
            res[j++].num = i;
        }
    }
    sort(res, res + j, cmp);
    for (int i = 0; i < j; i++)
    {
        // cout << res[i].num << " " << res[i].count << endl;
        printf("%d %d\n", res[i].num, res[i].count);
    }
    return 0;
}