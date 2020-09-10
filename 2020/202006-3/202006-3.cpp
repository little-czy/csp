#include <bits/stdc++.h>

using namespace std;

int n, cur_line = -1, cur_begin = 0;
vector<string> s;
bool cur_is_list = false, cur_is_empty = true;

bool is__empty(string ss)
{
    for (int i = 0; i < ss.size(); i++)
        if (ss[i] != ' ')
            return false;
    return true;
}

string trim(string ss)
{
    if (is__empty(ss))
        return "";
    int begin = 0, end = ss.size() - 1;
    while (begin < ss.size() && ss[begin] == ' ')
        begin++;
    while (end >= begin && ss[end] == ' ')
        end--;
    return ss.substr(begin, end - begin + 1);
}

void _append(string ss)
{
    string tmp = trim(ss);
    if (!tmp.empty())
        if ((cur_is_list && cur_begin != 3) || (!cur_is_list && cur_begin != 0))
            cur_begin++;
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == ' ' && cur_begin == n)
            continue;
        cur_begin++;
        if (cur_begin > n) //该换行了
        {
            cur_line++;
            if (cur_is_list)
                cur_begin = 4;
            else
                cur_begin = 1;
        }
    }
}

int main()
{
    string tmp;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    while (getline(cin, tmp))
        s.push_back(tmp);
    for (int i = 0; i < s.size(); i++)
    {
        tmp = s[i];
        if (is__empty(tmp)) //是否空行
        {
            cur_is_list = false;
            cur_is_empty = true;
            continue;
        }
        if (tmp.size() >= 2 && tmp[0] == '*' && tmp[1] == ' ') //列表
        {
            if (cur_is_list) //上一行属于列表
            {
                cur_line++;
                cur_begin = 3;
                _append(tmp.substr(2));
            }
            else //上一行不属于列表
            {
                cur_line++; //额外增加一行空行
                cur_line++;
                cur_begin = 3;
                cur_is_list = true;
                _append(tmp.substr(2));
            }
            cur_is_empty = false;
        }
        else //非列表
        {
            if (cur_is_list) //上一级属于列表
            {
                if (tmp.size() >= 2 && tmp[0] == ' ' && tmp[1] == ' ') //当前隶属于列表
                    _append(tmp.substr(2));
                else //当前不属于列表
                {
                    cur_line++; //额外增加一行空行
                    cur_line++;
                    cur_begin = 0;
                    _append(tmp);
                    cur_is_list = false;
                }
                cur_is_empty = false;
            }
            else //上一级不属于列表
            {
                if (cur_is_empty) //上一行不是段落
                {
                    cur_line++; //额外增加一行空行
                    cur_line++;
                    cur_begin = 0;
                    _append(tmp);
                }
                else //上一行是段落
                    _append(tmp);
                cur_is_empty = false;
                cur_is_list = false;
            }
        }
    }
    cout << cur_line << endl;
    return 0;
}