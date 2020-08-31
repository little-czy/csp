#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 1e3 + 5;

struct node
{
    char c[410000];
} no[maxn];

unsigned int n, m, s, l, len;
bool flag[maxn];

int main()
{
    unsigned int a;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s >> l;
    cin >> a;
    cin >> no[a].c;
    flag[a] = true;
    len = strlen(no[a].c);
    for (int i = 1; i < l; i++)
    {
        cin >> a;
        cin >> no[a].c;
        flag[a] = true;
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a;
        if ((n - 1) * (len >> 3) <= a)
        {
            cout << "-\n";
            continue;
        }
        int b = a / ((n - 1) * s);                //a位置所在条带层数
        int bb = b * (n - 1) * s;                 //b层条带开始的磁盘块号
        int bpos = (n - 1 - (b % n));             //b层条带所在的磁盘号
        int ax = (bpos + 1 + ((a - bb) / s)) % n; //a所在磁盘号
        int ay = b * s + a % s;                   //a所在磁盘的块号
        int ayb = ay << 3;                        //a所在磁盘的起始字节
        if (flag[ax])
        {
            for (int j = ayb; j < ayb + 8; j++)
            {
                cout << no[ax].c[j];
            }
            cout << endl;
        }
        else
        {
            if (n > l + 1)
                cout << "-" << endl;
            else
            {
                unsigned int tmpa, tmpb;
                char tmps[32], tmpc;
                for (int j = 0; j < 8; j++)
                {
                    tmpa = 0;
                    for (int k = 0; k < n; k++)
                    {
                        if (k != ax)
                        {
                            tmpc = no[k].c[ayb + j];
                            if (tmpc >= 'A')
                                tmpb = tmpc - 'A' + 10;
                            else
                                tmpb = tmpc - '0';
                            tmpa ^= tmpb;
                        }
                    }
                    if (tmpa >= 10)
                        cout << (char)(tmpa - 10 + 'A');
                    else
                        cout << (char)(tmpa + '0');
                }
                cout << endl;
            }
        }
    }
    return 0;
}