#include <iostream>
#include <cstdio>

using namespace std;

struct S
{
    int x, y;
} s; //起始位置坐标

struct T
{
    int x, y;
} t; //结束位置坐标

char chess[60][60];                              //棋盘
bool s_can_arrive[60][60], t_can_arrive[60][60]; //可达性信息
int r, c;                                        //棋盘行列数

inline bool s_can_up(int x, int y)
{
    if (x > 0 && !s_can_arrive[x - 1][y] && (chess[x][y] == 'S' || chess[x][y] == 'T') && chess[x - 1][y] != '#')
        return 1;
    if (x > 0 && !s_can_arrive[x - 1][y] && chess[x - 1][y] != '#' && (chess[x][y] == '+' || chess[x][y] == '|'))
        return 1;
    return 0;
}
inline bool s_can_down(int x, int y)
{
    if (x < r - 1 && !s_can_arrive[x + 1][y] && (chess[x][y] == 'S' || chess[x][y] == 'T') && chess[x + 1][y] != '#')
        return 1;
    if (x < r - 1 && !s_can_arrive[x + 1][y] && chess[x + 1][y] != '#' && (chess[x][y] == '+' || chess[x][y] == '|' || chess[x][y] == '.'))
        return 1;
    return 0;
}
inline bool s_can_left(int x, int y)
{
    if (y > 0 && !s_can_arrive[x][y - 1] && (chess[x][y] == 'S' || chess[x][y] == 'T') && chess[x][y - 1] != '#')
        return 1;
    if (y > 0 && !s_can_arrive[x][y - 1] && chess[x][y - 1] != '#' && (chess[x][y] == '+' || chess[x][y] == '-'))
        return 1;
    return 0;
}
inline bool s_can_right(int x, int y)
{
    if (y < c - 1 && !s_can_arrive[x][y + 1] && (chess[x][y] == 'S' || chess[x][y] == 'T') && chess[x][y + 1] != '#')
        return 1;
    if (y < c - 1 && !s_can_arrive[x][y + 1] && chess[x][y + 1] != '#' && (chess[x][y] == '+' || chess[x][y] == '-'))
        return 1;
    return 0;
}

inline bool t_can_up(int x, int y)
{
    if (x > 0 && !t_can_arrive[x - 1][y] && (chess[x - 1][y] == '+' || chess[x - 1][y] == '|' || chess[x - 1][y] == '.' || chess[x - 1][y] == 'S'))
        return 1;
    return 0;
}
inline bool t_can_down(int x, int y)
{
    if (x < r - 1 && !t_can_arrive[x + 1][y] && (chess[x + 1][y] == '+' || chess[x + 1][y] == '|' || chess[x + 1][y] == 'S'))
        return 1;
    return 0;
}
inline bool t_can_left(int x, int y)
{
    if (y > 0 && !t_can_arrive[x][y - 1] && (chess[x][y - 1] == '+' || chess[x][y - 1] == '-' || chess[x][y - 1] == 'S'))
        return 1;
    return 0;
}
inline bool t_can_right(int x, int y)
{
    if (y < c - 1 && !t_can_arrive[x][y + 1] && (chess[x][y + 1] == '+' || chess[x][y + 1] == '-' || chess[x][y + 1] == 'S'))
        return 1;
    return 0;
}

void from_t(int x, int y)
{
    if (t_can_up(x, y))
    {
        t_can_arrive[x - 1][y] = 1;
        from_t(x - 1, y);
    }
    if (t_can_down(x, y))
    {
        t_can_arrive[x + 1][y] = 1;
        from_t(x + 1, y);
    }
    if (t_can_left(x, y))
    {
        t_can_arrive[x][y - 1] = 1;
        from_t(x, y - 1);
    }
    if (t_can_right(x, y))
    {
        t_can_arrive[x][y + 1] = 1;
        from_t(x, y + 1);
    }
}

void from_s(int x, int y)
{
    if (s_can_up(x, y))
    {
        s_can_arrive[x - 1][y] = 1;
        from_s(x - 1, y);
    }
    if (s_can_down(x, y))
    {
        s_can_arrive[x + 1][y] = 1;
        from_s(x + 1, y);
    }
    if (s_can_left(x, y))
    {
        s_can_arrive[x][y - 1] = 1;
        from_s(x, y - 1);
    }
    if (s_can_right(x, y))
    {
        s_can_arrive[x][y + 1] = 1;
        from_s(x, y + 1);
    }
}

int main()
{
    cin >> r >> c;
    getchar();
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            chess[i][j] = getchar();
            if (chess[i][j] == 'S') //记录起始位置坐标
            {
                s.x = i;
                s.y = j;
                s_can_arrive[i][j] = 1;
                // t_can_arrive[i][j] = 1;
            }
            if (chess[i][j] == 'T') //记录终点位置坐标
            {
                t.x = i;
                t.y = j;
                t_can_arrive[i][j] = 1;
            }
        }
        getchar();
    }
    if (r == 1 && c == 1)
    {
        cout << "0" << endl;
        return 0;
    }
    from_s(s.x, s.y);
    from_t(t.x, t.y);
    bool canArrive = 0;
    int num = 0;
    // cout << s.x << " " << s.y << endl;
    // cout << t.x << " " << t.y << endl
    //      << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            // cout << chess[i][j];
            if (s_can_arrive[i][j] && t_can_arrive[i][j])
            {
                canArrive = 1;
                // cout << "-" << i << " " << j << "-" << endl;
            }

            if (s_can_arrive[i][j] && !t_can_arrive[i][j])
            {
                num++;
                // cout << i << " " << j << endl;
            }
        }
        // cout << endl;
    }
    if (canArrive)
        cout << num << endl;
    else
        cout << "I'm stuck!" << endl;
    return 0;
}