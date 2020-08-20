#include <iostream>

using namespace std;

struct ball
{
    int loc;
    int l_r;
} b[105];

int n, l, t;

void next_t()
{
    for (int i = 0; i < n; i++)
    {
        b[i].loc += b[i].l_r;
        if (b[i].loc == l || b[i].loc == 0)
            b[i].l_r = -b[i].l_r;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (b[i].loc == b[j].loc)
            {
                b[i].l_r = -b[i].l_r;
                b[j].l_r = -b[j].l_r;
            }
        }
    }
}

int main()
{
    cin >> n >> l >> t;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i].loc;
        if (b[i].loc == l)
            b[i].l_r = -1;
        else
            b[i].l_r = 1;
    }
    for (int i = 0; i < t; i++)
    {
        next_t();
    }
    for (int i = 0; i < n; i++)
    {
        cout << b[i].loc << " ";
    }
    return 0;
}