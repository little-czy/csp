#include <iostream>
#include <queue>
#include <string>
#include <cstring>

using namespace std;
const int maxn = 1e4 + 5;

struct node
{
    int v;
    int sr;
    node(int _v, int _sr) : v(_v), sr(_sr) {}
};

int t, n;
queue<node> q[maxn];
bool wait[maxn];

inline int get_num(string &str, int pos, int &len)
{
    int ans = 0;
    len = 0;
    for (int i = pos; i < str.length(); i++)
    {
        if (isdigit(str[i]))
        {
            ans = (ans << 3) + (ans << 1) + str[i] - '0';
            len++;
        }
        else
            break;
    }
    return ans;
}

inline bool not_all_empty()
{
    for (int i = 0; i < n; i++)
        if (!q[i].empty())
            return true;
    return false;
}

bool work()
{
    bool change;
    while (not_all_empty())
    {
        change = false;
        for (int i = 0; i < n; i++)
        {
            if (!wait[i] && !q[i].empty())
            {
                int v = q[i].front().v;
                if (!q[v].empty() && q[v].front().v == i && q[v].front().sr + q[i].front().sr == 1)
                {
                    q[i].pop(), q[v].pop();
                    wait[v] = false;
                }
                else
                    wait[i] = true;
                change = true;
            }
        }
        if (!change)
            return false;
    }
    return true;
}

int main()
{
    freopen("in", "r", stdin);
    scanf("%d%d", &t, &n);
    getchar();
    while (t--)
    {
        memset(wait, 0, sizeof(wait));
        for (int i = 0; i < n; i++)
        {
            while (!q[i].empty())
                q[i].pop();
            string str;
            getline(cin, str);
            int num;
            for (int j = 0; j < str.length(); j++)
            {
                if (str[j] == 'R')
                {
                    int len, v;
                    v = get_num(str, j + 1, len);
                    j += len;
                    q[i].push(node(v, 0));
                }
                else if (str[j] == 'S')
                {
                    int len, v;
                    v = get_num(str, j + 1, len);
                    j += len;
                    q[i].push(node(v, 1));
                }
            }
        }
        if (work())
            cout << 0 << endl;
        else
            cout << 1 << endl;
    }
    return 0;
}