#include <iostream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <string>

using namespace std;

struct option
{
    char p;         //参数选项
    bool have_prim; //有无参数标记
} op[30];
typedef struct result
{
    char p;         //参数选项
    bool have_prim; //有无参数标记
    char prim[256]; //参数
} result;

int op_num = 0; //参数选项个数

int inOption(char *s) //判断s是否为合法参数选项 0:非法  1:无参  2:有参
{
    if (strlen(s) == 2 && s[0] == '-')
    {
        for (int i = 0; i < op_num; i++)
        {
            if (op[i].p == s[1])
            {
                if (op[i].have_prim)
                    return 2;
                else
                    return 1;
            }
        }
        return 0;
    }
    else
    {
        return 0;
    }
}

bool cmp(result x, result y)
{
    return x.p < y.p;
}

int main()
{
    char c;
    for (int i = 0; (c = getchar()) != '\n'; i++)
    {
        if (c == ':')
        {
            op[--i].have_prim = 1; //表示上个字符属于有参数字符
        }
        else
        {
            op[i].p = c;
            op_num++;
        }
    }
    // for (int i = 0; i < prim_num; i++)
    // {
    //     cout << op[i].p << " " << op[i].have_prim << endl;
    // }
    int n;
    char s[300], t_p[256];
    cin >> n;
    getchar();
    for (int i = 1; i <= n; i++)
    {

        gets(s);
        // puts(s);
        if (sscanf(s, "%s %[^\n]", t_p, s) == 1)
        {
            cout << "Case " << i << ": " << endl;
            // cout << t_p << " --- " << s << endl;
            continue;
        }
        map<char, string> mp;
        bool rec_flag = 0; //当前需要接收的数据类型：参数选项：0、参数：1
        char temp_p;
        while (sscanf(s, "%s %[^\n]", t_p, s) != 1)
        {
            // cout << t_p << " --- " << s << endl;
            if (!rec_flag) //当前需要接收参数选项
            {
                int ret = inOption(t_p);
                if (ret == 1) //为合法无参参数选项
                {
                    mp[t_p[1]] = "";
                }
                else if (ret == 2) //为合法有参参数选项
                {
                    temp_p = t_p[1];
                    // mp[t_p[1]] = "";
                    rec_flag = 1;
                }
                else //参数选项不合法
                {
                    break;
                }
            }
            else //当前需要接收参数
            {
                mp[temp_p] = t_p;
                rec_flag = 0;
            }
        }
        // cout << t_p << " --- " << s << endl;
        if (!rec_flag) //当前需要接收参数选项
        {
            int ret = inOption(t_p);
            if (ret == 1) //为合法无参参数选项
            {
                mp[t_p[1]] = "";
            }
            else if (ret == 2) //为合法有参参数选项
            {
                temp_p = t_p[1];
                // mp[t_p[1]] = "";
                rec_flag = 1;
            }
        }
        else //当前需要接收参数
        {
            mp[temp_p] = t_p;
            rec_flag = 0;
        }
        cout << "Case " << i << ":";
        map<char, string>::iterator it;
        for (it = mp.begin(); it != mp.end(); it++)
        {
            if (it->second == "")
                cout << " -" << it->first;
            else
                cout << " -" << it->first << " " << it->second;
        }
        cout << endl;
    }
    return 0;
}