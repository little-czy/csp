#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a[505][505];
bool flag = 0;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }
    int x, y, num;
    for (int i = 1; i < 2 * n; i++)
    {
        flag = i % 2;
        if (flag) //±éÀú·½Ïò
        {
            if (i <= n)
            {
                x = i, y = 1;
                num = i;
            }
            else
            {
                x = n, y = i - n + 1;
                num = 2 * n - i;
            }
        }
        else
        {
            if (i <= n)
            {
                x = 1, y = i;
                num = i;
            }
            else
            {
                x = i - n + 1, y = n;
                num = 2 * n - i;
            }
        }
        if (flag)
        {
            for (int j = 1; j <= num; j++)
            {
                cout << a[x][y] << " ";
                x--, y++;
            }
        }
        else
        {
            for (int j = 1; j <= num; j++)
            {
                cout << a[x][y] << " ";
                x++, y--;
            }
        }
    }
    return 0;
}