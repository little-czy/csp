#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
#include <set>
#include <map>

using namespace std;

int n;
map<string, int> m1, m2;
clock_t b, e;

inline bool is_num(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}

inline bool is_upper(char c)
{
    if (c >= 'A' && c <= 'Z')
        return true;
    else
        return false;
}

inline bool is_lower(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;
    else
        return false;
}

inline int find_bracket(string s)
{
    int num = 1;
    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] == '(')
            num++;
        if (s[i] == ')')
        {
            if (num == 1)
                return i;
            num--;
        }
    }
    return 0;
}

int count_each(string s, string t) //统计t的个数
{
    if (s.empty())
        return 0;
    { //字符串以数字开始
        int i;
        for (i = 0; i < s.size(); i++)
            if (!is_num(s[i]))
                break;
        if (i > 0)
            return atoi(s.substr(0, i).c_str()) * count_each(s.substr(i), t);
    }
    if (s.find(t) != string::npos)
    {
        if (s[0] == '(')
        {
            int pos1 = find_bracket(s), num_pos = pos1 + 1;
            for (; num_pos < s.size(); num_pos++)
                if (!is_num(s[num_pos]))
                    break;
            if (num_pos != pos1 + 1) //括号后面包括数字
                return atoi(s.substr(pos1 + 1, num_pos - pos1 - 1).c_str()) * count_each(s.substr(1, pos1 - 1), t) + count_each(s.substr(num_pos), t);
            else //括号后面无数字
                return count_each(s.substr(1, pos1 - 1), t) + count_each(s.substr(num_pos), t);
        }
        if (t.size() == 2) //待查找元素为双字母
        {
            if (s[0] == t[0] && s[1] == t[1])
            {
                int num_pos = 2;
                while (num_pos < s.size())
                {
                    if (!is_num(s[num_pos]))
                        break;
                    num_pos++;
                }

                if (num_pos != 2)
                    return atoi(s.substr(2, num_pos - 2).c_str()) + count_each(s.substr(num_pos), t);
                else
                    return 1 + count_each(s.substr(num_pos), t);
            }
            else if (is_upper(s[0]) && is_upper(s[1]))
                return count_each(s.substr(1), t);
            else if (is_upper(s[0]) && is_lower(s[1]))
                return count_each(s.substr(2), t);
        }
        else
        {
            if (s[0] == t[0])
            {
                if (s.size() <= 1 || (s.size() > 1 && !is_lower(s[1])))
                {
                    int num_pos = 1;
                    while (num_pos < s.size())
                    {
                        if (!is_num(s[num_pos]))
                            break;
                        num_pos++;
                    }

                    if (num_pos != 1)
                        return atoi(s.substr(1, num_pos - 1).c_str()) + count_each(s.substr(num_pos), t);
                    else
                        return 1 + count_each(s.substr(num_pos), t);
                }
            }
            else if (1 < s.size() && is_num(s[1]))
            {
                int num_pos = 2;
                while (num_pos < s.size())
                {
                    if (!is_num(s[num_pos]))
                        break;
                    num_pos++;
                }
                return count_each(s.substr(num_pos), t);
            }
            else if (1 < s.size() && is_lower(s[1])) //字符串以双字母元素开头
            {
                if (2 < s.size() && is_num(s[2])) //双字母元素开头后还有数字
                {
                    int num_pos = 3;
                    while (num_pos < s.size())
                    {
                        if (!is_num(s[num_pos]))
                            break;
                        num_pos++;
                    }
                    return count_each(s.substr(num_pos), t);
                }
                else
                    return count_each(s.substr(2), t);
            }
            else
            {
                return count_each(s.substr(1), t);
            }
        }
    }
    else
        return 0;
}

void count_num_l(string s) //统计等式左边的各元素个数
{
    int pos = s.find("+");
    if (pos != string::npos)
    {
        count_num_l(s.substr(0, pos));
        count_num_l(s.substr(pos + 1));
    }
    else
    {
        set<string> temp_set;
        for (int i = 0; i < s.size(); i++) //从字符串中找出每个元素并统计次数
        {
            if (is_upper(s[i]))
            {
                if (i + 1 < s.size() && is_lower(s[i + 1])) //为双字母元素
                {
                    if (temp_set.find(s.substr(i, 2)) != temp_set.end())
                        continue;
                    temp_set.insert(s.substr(i, 2));
                    int num = count_each(s, s.substr(i, 2));
                    m1[s.substr(i, 2)] += num;
                    i++;
                }
                else
                {
                    if (temp_set.find(s.substr(i, 1)) != temp_set.end())
                        continue;
                    temp_set.insert(s.substr(i, 1));
                    int num = count_each(s, s.substr(i, 1));
                    m1[s.substr(i, 1)] += num;
                }
            }
        }
    }
}

void count_num_r(string s) //统计等式右边的各元素个数
{
    int pos = s.find("+");
    if (pos != string::npos)
    {
        count_num_r(s.substr(0, pos));
        count_num_r(s.substr(pos + 1));
    }
    else
    {
        set<string> temp_set;
        for (int i = 0; i < s.size(); i++) //从字符串中找出每个元素并统计次数
        {
            if (is_upper(s[i]))
            {
                if (i + 1 < s.size() && is_lower(s[i + 1])) //为双字母元素
                {
                    if (temp_set.find(s.substr(i, 2)) != temp_set.end())
                        continue;
                    temp_set.insert(s.substr(i, 2));
                    int num = count_each(s, s.substr(i, 2));
                    m2[s.substr(i, 2)] += num;
                    i++;
                }
                else
                {
                    if (temp_set.find(s.substr(i, 1)) != temp_set.end())
                        continue;
                    temp_set.insert(s.substr(i, 1));
                    int num = count_each(s, s.substr(i, 1));
                    m2[s.substr(i, 1)] += num;
                }
            }
        }
    }
}

inline bool check()
{
    if (m1.size() != m2.size())
        return false;
    map<string, int>::iterator it1 = m1.begin(), it2 = m2.begin();
    for (; it1 != m1.end(); it1++, it2++)
    {
        if (it1->first != it2->first || it1->second != it2->second)
            return false;
    }
    return true;
}

int main()
{
    string temp_s;
    cin >> n;
    b = clock();
    for (int i = 0; i < n; i++)
    {
        cin >> temp_s;
        m1.clear(), m2.clear();
        int pos = temp_s.find("=");
        // cout << temp_s.substr(0, pos) << endl;
        // cout << temp_s.substr(pos + 1) << endl;
        count_num_l(temp_s.substr(0, pos));
        count_num_r(temp_s.substr(pos + 1));
        if (check())
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }
    e = clock();
    cout << double(e - b) * 1000 / CLOCKS_PER_SEC << endl;
    return 0;
}