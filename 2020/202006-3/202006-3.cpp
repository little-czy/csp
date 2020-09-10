#include <bits/stdc++.h>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

int n, cur_line;
vector<string> s, ans;
bool cur_is_list = false, cur_is_empty = true;

bool is__empty(string ss)
{
    regex re("\\s*");
    return regex_match(ss, re);
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
    int begin = ans[cur_line].size();
    string tmp = trim(ss);
    if (cur_is_list && begin != 3)
        ans[cur_line].insert(ans[cur_line].end(), ' '), begin++;
    else if (!cur_is_list && begin != 0)
        ans[cur_line].insert(ans[cur_line].end(), ' '), begin++;
    // if (begin != 0 && !cur_is_empty)
    //     ans[cur_line].insert(ans[cur_line].end(), ' '), begin++;
    if (begin >= n) //该换行了
    {
        ans.push_back("");
        if (cur_is_list)
        {
            begin = 3;
            ans[++cur_line] = "   ";
        }
        else
        {
            begin = 0;
            cur_line++;
        }
    }
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == ' ')
        {
            if (cur_is_list && begin == 3)
                continue;
            else if (!cur_is_list && begin == 0)
                continue;
        }
        ans[cur_line].insert(ans[cur_line].end(), tmp[i]);
        if (++begin >= n) //该换行了
        {
            ans.push_back("");
            if (cur_is_list)
            {
                begin = 3;
                ans[++cur_line] = "   ";
            }
            else
            {
                begin = 0;
                cur_line++;
            }
        }
    }
}

int main()
{
    string tmp;
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    getchar();
    while (getline(cin, tmp))
        s.push_back(tmp);
    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << endl;
    // }
    ans.push_back("");
    for (int i = 0; i < s.size(); i++)
    {
        tmp = s[i];
        // cout << trim(tmp) << endl;
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
                if (is__empty(ans[cur_line])) //当前答案行为空
                {
                    ans[cur_line] = " . ";
                    _append(tmp.substr(2));
                }
                else
                {
                    ans.push_back("");
                    cur_line++;
                    ans[cur_line] = " . ";
                    _append(tmp.substr(2));
                }
            }
            else //上一行不属于列表
            {
                if (!is__empty(ans[cur_line]))     //当前答案行不为空
                    ans.push_back(""), cur_line++; //额外增加一行空行
                ans.push_back("");
                cur_line++;
                ans[cur_line] = " . ";
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
                    if (!is__empty(ans[cur_line]))     //当前答案行不为空
                        ans.push_back(""), cur_line++; //额外增加一行空行
                    ans.push_back("");                 //额外增加一行空行
                    cur_line++;
                    _append(tmp);
                    cur_is_list = false;
                }
                cur_is_empty = false;
            }
            else //上一级不属于列表
            {
                if (cur_is_empty) //上一行不是段落
                {
                    if (!is__empty(ans[cur_line]))     //当前答案行不为空
                        ans.push_back(""), cur_line++; //额外增加一行空行
                    ans.push_back("");                 //额外增加一行空行
                    cur_line++;
                    _append(tmp);
                }
                else //上一行是段落
                {
                    _append(tmp);
                }
                cur_is_empty = false;
                cur_is_list = false;
            }
        }
    }
    // for (int i = 0; i < ans.size(); i++)
    // {
    //     cout << ans[i] << endl;
    // }

    int i;
    for (i = ans.size() - 1; is__empty(ans[i]); i--)
        ;
    cout << i << endl;
    return 0;
}