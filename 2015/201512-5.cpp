#include <iostream>
#include <cstdio>

#define MAXM 1005
using namespace std;

int m, n;
long long K;
bool a[MAXM][MAXM];
bool b[MAXM];
bool tmp_a[MAXM][MAXM];
bool tmp_x[MAXM][MAXM];
bool tmp_y[MAXM][MAXM];
bool ans[MAXM][MAXM];
bool res[MAXM];

void mul(bool x[MAXM][MAXM], bool y[MAXM][MAXM])
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            tmp_x[i][j] = x[i][j];
            tmp_y[i][j] = y[i][j];
        }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            x[i][j] = 0;
            for (int k = 0; k < m; k++)
            {
                x[i][j] ^= (tmp_x[i][k] & tmp_y[k][j]);
            }
        }
    }
}

void init(bool x[MAXM][MAXM]) //³õÊ¼»¯¶Ô½Ç¾ØÕó
{
    for (int i = 0; i < m; i++)
    {
        res[i] = 0;
        for (int j = 0; j < m; j++)
        {
            tmp_a[i][j] = a[i][j];
            if (i == j)
                x[i][j] = 1;
            else
                x[i][j] = 0;
        }
    }
}

int main()
{
    cin >> m;
    getchar();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] = getchar() - '0';
        }
        getchar();
    }
    for (int i = 0; i < m; i++)
        b[i] = getchar() - '0';
    getchar();
    cin >> n;
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << a[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << m << n << endl;
    // for (int k = 0; k < m; k++)
    // {
    //     printf("%d", b[k]);
    // }
    // printf("\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &K);
        init(ans);
        while (K > 0)
        {
            if (K & 1)
            {
                mul(ans, tmp_a);
            }
            mul(tmp_a, tmp_a);
            K >>= 1;
        }

        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < m; k++)
            {
                res[j] ^= (ans[j][k] & b[k]);
            }
        }
        for (int k = 0; k < m; k++)
        {
            printf("%d", res[k]);
        }
        printf("\n");
    }

    return 0;
}