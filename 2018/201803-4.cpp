#include <iostream>

using namespace std;

int n;
int f[3][3];

bool judge(int num) // 1-alice, 2-bob
{
    for (int i = 0; i < 3; i++)
    {
        if (f[i][0] == num && f[i][1] == num && f[i][2] == num)
            return true;
        if (f[0][i] == num && f[1][i] == num && f[2][i] == num)
            return true;
    }
    if (f[0][0] == num && f[1][1] == num && f[2][2] == num)
        return true;
    if (f[2][0] == num && f[1][1] == num && f[0][2] == num)
        return true;
    return false;
}

inline int count_empty()
{
    int c = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (f[i][j] == 0)
                c++;
    return c;
}

int dfs(int num)
{
    int empty_num = count_empty();
    if (num == 1 && judge(2)) // bob赢
        return -empty_num - 1;
    if (num == 2 && judge(1)) //alice赢
        return empty_num + 1;
    if (empty_num == 0) //平局
        return 0;
    int mn = 0x3f3f3f3f, mx = -0x3f3f3f3f;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (f[i][j] == 0)
            {
                f[i][j] = num;
                if (num == 1)
                    mx = max(mx, dfs(2));
                if (num == 2)
                    mn = min(mn, dfs(1));
                f[i][j] = 0; //回溯
            }
    if (num == 1)
        return mx;
    else
        return mn;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                cin >> f[j][k];
        cout << dfs(1) << endl;
    }
    return 0;
}