#include <iostream>
#include <string>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1100;
const int maxm = 2000;

struct node
{
    int r, g, b;
} g1[maxn][maxm], gg[maxn][maxm];

int n, m, p, q;
string s;

inline void deal(int x, int y)
{
    int num;
    if (s.length() == 2)
    {
        num = s[1] >= 'a' ? s[1] + 10 - 'a' : s[1] - '0';
        num = (num << 4) + num;
        g1[x][y].r = g1[x][y].g = g1[x][y].b = num;
    }
    else if (s.length() == 4)
    {
        num = s[1] >= 'a' ? s[1] + 10 - 'a' : s[1] - '0';
        num = (num << 4) + num;
        g1[x][y].r = num;
        num = s[2] >= 'a' ? s[2] + 10 - 'a' : s[2] - '0';
        num = (num << 4) + num;
        g1[x][y].g = num;
        num = s[3] >= 'a' ? s[3] + 10 - 'a' : s[3] - '0';
        num = (num << 4) + num;
        g1[x][y].b = num;
    }
    else
    {
        num = s[1] >= 'a' ? s[1] + 10 - 'a' : s[1] - '0';
        num <<= 4;
        num += s[2] >= 'a' ? s[2] + 10 - 'a' : s[2] - '0';
        g1[x][y].r = num;
        num = s[3] >= 'a' ? s[3] + 10 - 'a' : s[3] - '0';
        num <<= 4;
        num += s[4] >= 'a' ? s[4] + 10 - 'a' : s[4] - '0';
        g1[x][y].g = num;
        num = s[5] >= 'a' ? s[5] + 10 - 'a' : s[5] - '0';
        num <<= 4;
        num += s[6] >= 'a' ? s[6] + 10 - 'a' : s[6] - '0';
        g1[x][y].b = num;
    }
    // cout << g1[x][y].r << " " << g1[x][y].g << " " << g1[x][y].b << endl;
}

inline void count_avg(int x, int y)
{
    int r = 0, g = 0, b = 0, xbase = x * q, ybase = y * p;
    for (int i = xbase; i < xbase + q; i++)
    {
        for (int j = ybase; j < ybase + p; j++)
        {
            r += g1[i][j].r;
            g += g1[i][j].g;
            b += g1[i][j].b;
        }
    }
    gg[x][y].r = r / (p * q);
    gg[x][y].g = g / (p * q);
    gg[x][y].b = b / (p * q);
    // cout << gg[x][y].r << " " << gg[x][y].g << " " << gg[x][y].b << endl;
}

string change()
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'b')
            ans.append("\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B");
        else if (s[i] == 'e')
            ans.append("\\x1B\\x5B\\x30\\x6D");
        else if (s[i] == ' ')
            ans.append("\\x20");
        else if (s[i] == 'm')
            ans.append("\\x6D");
        else if (s[i] == 'n')
            ans.append("\\x0A");
        else if (s[i] == ';')
            ans.append("\\x3B");
        else
        {
            ans.append("\\x3");
            ans.append(to_string(s[i] - '0'));
        }
    }
    return ans;
}

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n >> p >> q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> s;
            deal(i, j);
        }
    }
    for (int i = 0; i < n / q; i++)
    {
        for (int j = 0; j < m / p; j++)
        {
            count_avg(i, j);
        }
    }
    int cur_r = 0, cur_g = 0, cur_b = 0;
    for (int i = 0; i < n / q; i++)
    {
        s = "";
        for (int j = 0; j < m / p; j++)
        {
            if (cur_r != gg[i][j].r || cur_g != gg[i][j].g || cur_b != gg[i][j].b) //需要更改背景色
            {
                if (!gg[i][j].r && !gg[i][j].g && !gg[i][j].b)
                {
                    s.append("e "); //e：s[0m
                }
                else
                {
                    s.append("b"); //b：s[48;2;
                    s.append(to_string(gg[i][j].r));
                    s.append(";");
                    s.append(to_string(gg[i][j].g));
                    s.append(";");
                    s.append(to_string(gg[i][j].b));
                    s.append("m ");
                }

                cur_r = gg[i][j].r, cur_g = gg[i][j].g, cur_b = gg[i][j].b;
            }
            else //与上一个字符背景色相同
            {
                s.append(" ");
            }
        }
        // cout << cur_r << cur_g << cur_b << endl;
        if (cur_r || cur_g || cur_b) //当前终端颜色不是默认值
        {
            cur_r = cur_g = cur_b = 0;
            s.append("e"); //e：s[0m
        }
        s.append("n");
        // cout << s << endl;
        cout << change();
    }

    // cout << (int)'8' << endl;
    return 0;
}