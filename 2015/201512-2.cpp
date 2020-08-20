#include <iostream>

using namespace std;

int n, m;
int f[40][40];
bool del[40][40];

void check_row() //检查行
{
    int cur_color = 0; //当前检索的颜色
    int cur_num = 0;   //当前检索的颜色连续出现的次数
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (f[i][j] == cur_color)
            {
                cur_num++;
            }
            else
            {
                if (cur_num > 2)
                {
                    for (int k = j - cur_num; k < j; k++) //将之前的连续颜色消除
                    {
                        del[i][k] = true;
                    }
                }
                cur_color = f[i][j];
                cur_num = 1;
            }
        }
    }
}

void check_col() //检查列
{
    int cur_color = 0; //当前检索的颜色
    int cur_num = 0;   //当前检索的颜色连续出现的次数
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (f[j][i] == cur_color)
            {
                cur_num++;
            }
            else
            {
                if (cur_num > 2)
                {
                    for (int k = j - cur_num; k < j; k++) //将之前的连续颜色消除
                    {
                        del[k][i] = true;
                    }
                }
                cur_color = f[j][i];
                cur_num = 1;
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> f[i][j];
    check_row();
    check_col();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (del[i][j])
                f[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << f[i][0];
        for (int j = 1; j < m; j++)
        {
            cout << " " << f[i][j];
        }
        cout << endl;
    }
    return 0;
}