// #include <iostream>
// #include <cstdio>

// #define MOD 1000000007

// using namespace std;

// int n;
// int a[1005];
// int ans;

// bool check1(int num) //验证第一条法则
// {
//     int count = 0;
//     for (int i = 0; i < num; i++)
//     {
//         count |= (1 << a[i]);
//     }
//     if (count == 15)
//         return 1;
//     else
//         return 0;
// }

// bool check2(int num) //验证第二条法则
// {
//     for (int i = 0; i < num; i++)
//     {
//         if (a[i] == 1)
//         {
//             for (int j = i + 1; j < num; j++)
//             {
//                 if (a[j] == 0)
//                     return 0;
//             }
//         }
//         if (a[i] == 3)
//         {
//             for (int j = i + 1; j < num; j++)
//             {
//                 if (a[j] == 2)
//                     return 0;
//             }
//         }
//     }
//     return 1;
// }

// int main()
// {
//     // a[0] = 2, a[1] = 1, a[2] = 0, a[3] = 3, a[4] = 0;
//     // cout << check1(5) << " " << check2(4) << endl;
//     cin >> n;
//     int bit_n = 1; //当前搜索到的位数
//     int flag_3 = 0, flag_1 = 0;
//     a[0] = 2; //第一位必为2
//     a[1] = -1;
//     while (bit_n > 0)
//     {
//         if (bit_n == n)
//         {
//             if (check1(bit_n))
//             {
//                 ans++;
//                 if (ans >= MOD)
//                     ans -= MOD;
//             }
//             bit_n--;
//             if (a[bit_n] == 1)
//                 flag_1--;
//             else if (a[bit_n] == 3)
//                 flag_3--;
//         }
//         a[bit_n]++;
//         if (a[bit_n] == 4) //当前深度搜索完毕, 回退到上一层
//         {
//             a[bit_n] = -1;
//             bit_n--;
//             if (a[bit_n] == 1)
//                 flag_1--;
//             else if (a[bit_n] == 3)
//                 flag_3--;
//             continue;
//         }
//         else if (a[bit_n] == 1)
//             flag_1++;
//         else if (a[bit_n] == 3)
//             flag_3++;
//         else if (a[bit_n] == 0 && flag_1 != 0)
//             continue;
//         else if (a[bit_n] == 2 && flag_3 != 0)
//             continue;
//         // if (check2(bit_n + 1)) //当前搜索值满足第二条规则
//         // {
//         bit_n++;
//         a[bit_n] = -1;
//         // }
//     }
//     cout << ans << endl;
//     return 0;
// }

#include <iostream>
#define MOD 1000000007
using namespace std;

long long a[1005][6];
int n;

int main()
{
    cin >> n;
    a[4][0] = 1;
    a[4][1] = 7;
    a[4][2] = 3;
    a[4][3] = 5;
    a[4][4] = 9;
    a[4][5] = 3;
    for (int i = 5; i <= n; i++)
    {
        a[i][0] = 1;
        a[i][1] = (2 * a[i - 1][1] + a[i - 1][0]) % MOD;
        a[i][2] = (a[i - 1][2] + a[i - 1][0]) % MOD;
        a[i][3] = (2 * a[i - 1][3] + a[i - 1][1]) % MOD;
        a[i][4] = (2 * a[i - 1][4] + a[i - 1][2] + a[i - 1][1]) % MOD;
        a[i][5] = (2 * a[i - 1][5] + a[i - 1][4] + a[i - 1][3]) % MOD;
    }
    cout << a[n][5] << endl;
    return 0;
}