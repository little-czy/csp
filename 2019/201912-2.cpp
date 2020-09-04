#include <iostream>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

struct node
{
    int x, y;
} no[maxn];

int n, ans[5];

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> no[i].x >> no[i].y;
    for (int i = 0; i < n; i++)
    {
        int num = 0;
        for (int j = 0; j < n; j++)
        {
            if (no[i].x - 1 == no[j].x && no[i].y == no[j].y)
                num++;
            else if (no[i].x + 1 == no[j].x && no[i].y == no[j].y)
                num++;
            else if (no[i].x == no[j].x && no[i].y - 1 == no[j].y)
                num++;
            else if (no[i].x == no[j].x && no[i].y + 1 == no[j].y)
                num++;
        }
        if (num == 4) //可建回收站
        {
            num = 0;
            for (int j = 0; j < n; j++)
            {
                if (no[i].x - 1 == no[j].x && no[i].y - 1 == no[j].y)
                    num++;
                else if (no[i].x + 1 == no[j].x && no[i].y + 1 == no[j].y)
                    num++;
                else if (no[i].x + 1 == no[j].x && no[i].y - 1 == no[j].y)
                    num++;
                else if (no[i].x - 1 == no[j].x && no[i].y + 1 == no[j].y)
                    num++;
            }
            ans[num]++;
        }
    }
    for (int i = 0; i < 5; i++)
        cout << ans[i] << endl;
    return 0;
}