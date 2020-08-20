// 普通数组版本
// #include <iostream>
// #include <cstdio>

// #define MAXN 100005

// using namespace std;

// int n, m;
// long long a[MAXN];
// long long count1[MAXN];

// int main()
// {
//     cin >> n >> m;
//     int op, l, r, v;
//     long long tmp_count = 0;
//     for (int i = 1; i <= n; i++)
//     {
//         scanf("%lld", &a[i]);
//     }
//     for (int j = 0; j <= n; j++)
//     {
//         tmp_count += a[j];
//         count1[j] = tmp_count;
//     }
//     for (int i = 0; i < m; i++)
//     {
//         scanf("%d", &op);
//         if (op == 1)
//         {
//             scanf("%d%d%d", &l, &r, &v);
//             for (int j = l; j <= r; j++)
//             {
//                 if (a[j] % v == 0)
//                 {
//                     a[j] /= v;
//                 }
//             }
//             tmp_count = 0;
//             for (int j = 0; j <= n; j++)
//             {
//                 tmp_count += a[j];
//                 count1[j] = tmp_count;
//             }
//         }
//         else
//         {
//             scanf("%d%d", &l, &r);
//             cout << count1[r] - count1[l - 1] << endl;
//         }
//     }
//     return 0;
// }

//树状数组版本
#include <iostream>
#define MAXN 100005
using namespace std;

int n, m;
int a[MAXN];
long long c[MAXN];

int lowbit(int x)
{
    return x & -x;
}

void update(int i, int k)
{
    while (i <= n)
    {
        c[i] += k;
        i += lowbit(i);
    }
}

long long sum(int i)
{
    long long r = 0;
    while (i > 0)
    {
        r += c[i];
        i -= lowbit(i);
    }
    return r;
}

int main()
{
    int op, l, r, v;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        update(i, a[i]);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d%d", &l, &r, &v);
            if (v == 1)
                continue;
            for (int j = l; j <= r; j++)
            {
                if (a[j] >= v && a[j] % v == 0)
                {
                    update(j, a[j] / v - a[j]);
                    a[j] /= v;
                }
            }
        }
        else
        {
            scanf("%d%d", &l, &r);
            cout << sum(r) - sum(l - 1) << endl;
        }
    }

    return 0;
}