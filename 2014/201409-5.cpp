// #include <iostream>
// #include <cstdio>

// #define MOD 1000000007
// using namespace std;

// long long n, num;
// int m;

// inline long long f6(long long num)
// {
//     if (num < 5)
//         return 1 << num;
//     return (8 * f6(num - 3) + 4 * f6(num - 2)) % MOD;
// }

// int main()
// {
//     cin >> n >> m;
//     switch (m)
//     {
//     case 2:
//     {
//         if (n % 3 != 0)
//             cout << "0" << endl;
//         else
//         {
//             num = 1;
//             for (long long i = n / 3; i > 0; i--)
//             {
//                 num <<= 1;
//                 if (num > MOD)
//                     num -= MOD;
//             }
//             cout << num << endl;
//         }
//     }
//     break;
//     case 3:
//     {
//         if (n % 2 != 0)
//             cout << "0" << endl;
//         else
//         {
//             num = 1;
//             for (long long i = n / 2; i > 0; i--)
//             {
//                 num <<= 1;
//                 if (num > MOD)
//                     num -= MOD;
//             }
//             cout << num << endl;
//         }
//     }
//     break;
//     case 4:
//     {
//         if (n % 3 != 0)
//             cout << "0" << endl;
//         else
//         {
//             num = 1;
//             for (long long i = n / 3; i > 0; i--)
//             {
//                 num <<= 2;
//                 if (num > MOD)
//                     num -= MOD;
//             }
//             cout << num << endl;
//         }
//     }
//     break;
//     case 5:
//     {
//         if (n % 6 != 0)
//             cout << "0" << endl;
//         else
//         {
//             num = 1;
//             for (long long i = n / 6; i > 0; i--)
//             {
//                 num <<= 6;
//                 if (num > MOD)
//                     num -= MOD;
//             }
//             cout << num << endl;
//         }
//     }
//     break;
//     case 6:
//     {
//         if (n < 2)
//             cout << "0" << endl;
//         else
//         {
//             cout << f6(n) << endl;
//         }
//     }
//     break;
//     case 7:
//     {
//         if (n % 6 != 0)
//             cout << "0" << endl;
//         else
//         {
//             num = 1;
//             for (long long i = n / 6; i > 0; i--)
//             {
//                 num <<= 7;
//                 num *= 3;
//                 if (num > MOD)
//                     num -= MOD;
//             }
//             cout << num << endl;
//         }
//     }
//     break;
//     default:
//         cout << "0" << endl;
//         break;
//     }
//     return 0;
// }

#include <iostream>

#define MOD 1000000007
#define MAXCOL 7

using namespace std;

long long n;
int m;
int status[1 << MAXCOL][1 << MAXCOL]; //状态转移矩阵
int res[1 << MAXCOL][1 << MAXCOL];    //保存结果

bool check(int s, int col) //判断s状态下，第col列是否为空
{
    if (col < 0 || col >= m)
        return 0;
    if ((s & (1 << col)) == 0)
        return 1;
    return 0;
}

int put(int s, int col1, int col2) //在s状态下的第col1和col2列放入方块
{
    s |= 1 << col1;
    if (col2 != -1)
        s |= 1 << col2;
    return s;
}

void search(int s, int s1, int s2, int col)
{
    if (s1 == ((1 << m) - 1))
    {
        status[s][s2]++;
        return;
    }
    if (!check(s1, col)) //当前列不为空，无法放置方块
        search(s, s1, s2, col + 1);
    else
    {
        if (check(s1, col + 1) && check(s2, col))
            search(s, put(s1, col, col + 1), put(s2, col, -1), col + 2);
        if (check(s2, col + 1) && check(s2, col))
            search(s, put(s1, col, -1), put(s2, col, col + 1), col + 1);
        if (check(s2, col - 1) && check(s2, col))
            search(s, put(s1, col, -1), put(s2, col - 1, col), col + 1);
        if (check(s1, col + 1) && check(s2, col + 1))
            search(s, put(s1, col, col + 1), put(s2, col + 1, -1), col + 2);
    }
}

void mul(int a[1 << MAXCOL][1 << MAXCOL], int b[1 << MAXCOL][1 << MAXCOL])
{
    long long tmp[1 << MAXCOL][1 << MAXCOL] = {0};
    for (int i = 0; i < (1 << MAXCOL); i++)
        for (int j = 0; j < (1 << MAXCOL); j++)
            for (int k = 0; k < (1 << MAXCOL); k++)
                tmp[i][j] = (tmp[i][j] + (long long)a[i][k] * (long long)b[k][j]) % MOD;
    for (int i = 0; i < (1 << MAXCOL); i++)
        for (int j = 0; j < (1 << MAXCOL); j++)
            a[i][j] = (int)tmp[i][j];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < (1 << m); i++)
        search(i, i, 0, 0);
    for (int i = 0; i < (1 << MAXCOL); i++) //构建单位矩阵
        for (int j = 0; j < (1 << MAXCOL); j++)
            res[i][j] = (i == j) ? 1 : 0;
    long long t = n << 1;
    while ((t >>= 1) > 0)
    {
        if (t & 1)
            mul(res, status);
        mul(status, status);
    }
    cout << res[0][0] << endl;
    return 0;
}