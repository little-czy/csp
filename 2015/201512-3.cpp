#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, m, q;
char f[110][110];
bool visit[110][110];

void draw_row(int x1, int y1, int x2, int y2) //画行
{
    for (int i = x1; i <= x2; i++)
    {
        if (f[y1][i] == '|' || f[y1][i] == '+')
        {
            f[y1][i] = '+';
        }
        else
        {
            f[y1][i] = '-';
        }
    }
}

void draw_col(int x1, int y1, int x2, int y2) //画列
{
    for (int i = y1; i <= y2; i++)
    {
        if (f[i][x1] == '-' || f[i][x1] == '+')
        {
            f[i][x1] = '+';
        }
        else
        {
            f[i][x1] = '|';
        }
    }
}

void fill_empty(int x, int y, char c)
{
    f[y][x] = c;
    visit[y][x] = true;
    if (y + 1 < n && !visit[y + 1][x] && f[y + 1][x] != '-' && f[y + 1][x] != '|' && f[y + 1][x] != '+') //向上填充
    {
        fill_empty(x, y + 1, c);
    }
    if (y - 1 >= 0 && !visit[y - 1][x] && f[y - 1][x] != '-' && f[y - 1][x] != '|' && f[y - 1][x] != '+') //向下填充
    {
        fill_empty(x, y - 1, c);
    }
    if (x + 1 < m && !visit[y][x + 1] && f[y][x + 1] != '-' && f[y][x + 1] != '|' && f[y][x + 1] != '+') //向右填充
    {
        fill_empty(x + 1, y, c);
    }
    if (x - 1 >= 0 && !visit[y][x - 1] && f[y][x - 1] != '-' && f[y][x - 1] != '|' && f[y][x - 1] != '+') //向左填充
    {
        fill_empty(x - 1, y, c);
    }
}

int main()
{
    cin >> m >> n >> q;
    for (int i = 0; i < n; i++)
    {
        fill(f[i], f[i] + m, '.');
    }
    int x1, y1, x2, y2;
    int op;
    char c;
    for (int i = 0; i < q; i++)
    {
        scanf("%d", &op);
        if (op == 1) //填充
        {
            scanf("%d%d %c", &x1, &y1, &c);
            // cout << c << endl;
            for (int j = 0; j < n; j++)
            {
                fill(visit[j], visit[j] + m, 0);
            }
            fill_empty(x1, y1, c);
        }
        else //画线
        {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            if (x1 == x2) //画列
            {
                if (y1 < y2)
                    draw_col(x1, y1, x2, y2);
                else
                    draw_col(x1, y2, x2, y1);
            }
            else //画行
            {
                if (x1 < x2)
                    draw_row(x1, y1, x2, y2);
                else
                    draw_row(x2, y1, x1, y2);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c", f[i][j]);
        }
        printf("\n");
    }
    return 0;
}