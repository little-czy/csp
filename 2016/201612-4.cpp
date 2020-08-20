// #include <iostream>
// #include <vector>

// #define MAXT 0x3f3f3f3f
// using namespace std;

// struct node
// {
//     int t;
//     int x, y;
//     node(int _t, int _x, int _y) : t(_t), x(_x), y(_y) {}
// };

// int n, ans = 0;
// vector<node> t;
// int dep[1005], tt[1005];

// void bound() //ºÏ²¢
// {

//     int min_ans = t[1].t + t[2].t;
//     int min_i = 2;
//     int last_t = t[2].t;
//     for (int i = 3; i < t.size() - 1; i++)
//     {
//         int tmp_sum = last_t + t[i].t;
//         if (min_ans > tmp_sum && !(tmp_sum > t[i - 2].t && tmp_sum > t[i + 1].t))
//         {
//             min_ans = tmp_sum;
//             min_i = i;
//         }
//         last_t = t[i].t;
//     }
//     t[min_i].t += t[min_i - 1].t;
//     t[min_i].x = t[min_i - 1].x;
//     for (int i = t[min_i].x; i <= t[min_i].y; i++)
//     {
//         dep[i]++;
//     }
//     t.erase(t.begin() + min_i - 1);
// }

// int main()
// {
//     cin >> n;
//     t.push_back(node(MAXT, 0, 0));
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> tt[i];
//         t.push_back(node(tt[i], i, i));
//     }
//     t.push_back(node(MAXT, n + 1, n + 1));
//     for (int i = 0; i < n - 1; i++)
//     {
//         bound();
//     }
//     if (n == 1)
//         dep[1]++;
//     for (int i = 1; i <= n; i++)
//     {
//         ans += (dep[i] * tt[i]);
//     }
//     cout << ans << endl;
//     return 0;
// }

#include <iostream>

using namespace std;

#define MAXN 1005
#define INF 0x3f3f3f3f

int n;
int a[MAXN];
int sum[MAXN][MAXN];
int dp[MAXN][MAXN];

void init_sum()
{
    for (int i = 1; i <= n; i++)
    {
        int tmp_sum = a[i];
        for (int j = i + 1; j <= n; j++)
        {
            tmp_sum += a[j];
            sum[i][j] = tmp_sum;
        }
    }
}

inline int min_(int x, int y)
{
    int min_sum = INF;
    for (int i = x; i < y; i++)
    {
        int tmp_min = dp[x][i] + dp[i + 1][y];
        if (min_sum > tmp_min)
        {
            min_sum = tmp_min;
        }
    }
    if (min_sum == INF)
        return 0;
    else
        return min_sum;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    init_sum();
    for (int l = 0; l <= n; l++)
    {
        for (int i = 1; i <= n - l; i++)
        {
            int j = i + l;
            dp[i][j] = sum[i][j] + min_(i, j);
        }
    }
    if (n != 1)
        cout << dp[1][n] << endl;
    else
        cout << a[1] << endl;
    return 0;
}
