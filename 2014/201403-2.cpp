#include <iostream>

using namespace std;

int n, m;
struct win
{
    int x1, y1, x2, y2;
} win[15];
int pro[15]; //”≈œ»º∂

int find(int x, int y)
{
    for (int i = 0; i < n; i++)
    {
        if (win[pro[i]].x1 <= x && x <= win[pro[i]].x2 && win[pro[i]].y1 <= y && y <= win[pro[i]].y2)
        {
            int t_pro = pro[i];
            for (int j = i; j > 0; j--)
            {
                pro[j] = pro[j - 1];
            }
            pro[0] = t_pro;
            return t_pro;
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> win[i].x1 >> win[i].y1 >> win[i].x2 >> win[i].y2;
        pro[n - i] = i;
    }
    int t_x, t_y, t_num;
    for (int i = 0; i < m; i++)
    {
        cin >> t_x >> t_y;
        if ((t_num = find(t_x, t_y)) == 0)
        {
            cout << "IGNORED" << endl;
        }
        else
        {
            cout << t_num << endl;
        }
    }

    return 0;
}