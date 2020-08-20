#include <iostream>
#include <cstdio>

using namespace std;

int l;
int f[20][20];
int a[6][6]; //下降方块
int bottom;  //下降方块最底方块位置

bool canDown(int x, int y)
{
    if (y - (3 - bottom) >= 14)
        return false;
    int y0 = y - 2, x0 = x - 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (a[i][j] && f[y0 + i][x0 + j])
                return false;
        }
    }
    return true;
}

int main()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cin >> f[i][j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 1)
                bottom = i;
        }
    }
    cin >> l;
    int y = 3;
    while (canDown(l, y))
    {
        y++;
    }
    int y0 = y - 3, x0 = l - 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (a[i][j])
                f[y0 + i][x0 + j] = 1;
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", f[i][j]);
        }
        printf("\n");
    }
    return 0;
}