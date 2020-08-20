#include <iostream>
#include <string>
#include <map>

using namespace std;

int n;
map<string, int> mp[2];

inline int get_num(string s, int &pos)
{
    int ans = 0;
    pos = s.length();
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]))
            ans = ans * 10 + s[i] - '0';
        else
        {
            pos = i;
            break;
        }
    return ans;
}

inline int get_kuohao(string s)
{
    int kuohao_num = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
            kuohao_num++;
        else if (s[i] == ')')
        {
            kuohao_num--;
            if (kuohao_num == 0)
                return i;
        }
    }
}

void deal(int no, string s, int count)
{
    if (isdigit(s[0])) //处理单词前数字
    {
        int alp_begin, word_num;
        word_num = get_num(s, alp_begin);
        s.erase(0, alp_begin);
        // cout << tmp_s << endl;
        deal(no, s, count * word_num);
    }
    else
    {
        string cur;
        for (int i = 0; i < s.length(); i++)
        {
            if (isupper(s[i])) //大写
            {
                if (i + 1 < s.length() && islower(s[i + 1])) //大写、小写
                {
                    cur = s.substr(i, 2);
                    if (i + 2 < s.length() && isdigit(s[i + 2])) //大写、小写、数字
                    {
                        int num_len, word_num;
                        word_num = get_num(s.substr(i + 2), num_len);

                        mp[no][cur] += word_num * count;
                        i += 1 + num_len;
                    }
                    else //大写、小写、结束
                    {
                        mp[no][cur] += count;
                        i++;
                    }
                }
                else if (i + 1 < s.length() && isdigit(s[i + 1])) //大写、数字
                {
                    cur = s[i];
                    int num_len, word_num;
                    word_num = get_num(s.substr(i + 1), num_len);
                    mp[no][cur] += word_num * count;
                    i += num_len;
                }
                else //大写、结束
                {
                    cur = s[i];
                    mp[no][cur] += count;
                }
            }
            else if (s[i] == '(')
            {
                int r_pos = get_kuohao(s.substr(i));
                r_pos += i;
                if (r_pos + 1 < s.length() && isdigit(s[r_pos + 1])) //括号后有数字
                {
                    int word_num, num_len;
                    word_num = get_num(s.substr(r_pos + 1), num_len);
                    deal(no, s.substr(i + 1, r_pos - i - 1), count * word_num);
                    i = r_pos + num_len;
                }
                else
                {
                    deal(no, s.substr(i + 1, r_pos - i - 1), count);
                    i = r_pos;
                }
            }
        }
    }
}

void deal_add(int no, string s)
{
    int pos = 0, last = 0;
    while ((pos = s.find("+", pos)) != string::npos)
    {
        deal(no, s.substr(last, pos - last), 1);
        // cout << s.substr(last, pos - last) << endl;
        last = ++pos;
    }
    // cout << s.substr(last) << endl;
    deal(no, s.substr(last), 1);
}

bool equal()
{
    map<string, int>::iterator it1;
    // cout << mp[0].size() << " " << mp[1].size() << endl;
    if (mp[0].size() != mp[1].size())
        return false;
    for (it1 = mp[0].begin(); it1 != mp[0].end(); it1++)
    {
        // cout << it1->first << " " << it1->second << " " << mp[1][it1->first] << endl;
        if (mp[1][it1->first] != it1->second)
            return false;
    }
    return true;
}

int main()
{
    string s;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        mp[0].clear(), mp[1].clear();
        int pos = s.find("=");
        // cout << s.substr(0, pos) << endl;
        deal_add(0, s.substr(0, pos));
        // cout << s.substr(pos + 1) << endl;
        deal_add(1, s.substr(pos + 1));
        if (equal())
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }
    return 0;
}