#include <iostream>
#include <string>
#include <map>

using namespace std;

int n;
map<string, int> mp1, mp2;

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

void deal1(string s)
{
    int pos = 0, last = 0;
    while ((pos = s.find("+", pos)) != string::npos)
    {
        deal1(s.substr(last, pos - last));
        // cout << s.substr(last, pos - last) << endl;
        last = ++pos;
    }
    if (last != 0)
    {
        // cout << s.substr(last) << endl;
        deal1(s.substr(last));
    }
    else //以分解为没有加号的单词
    {
        if (isdigit(s[0])) //处理单词前数字
        {
            int alp_begin, word_num;
            string tmp_s = "";
            word_num = get_num(s, alp_begin);
            s.erase(0, alp_begin);
            for (int i = 0; i < word_num; i++)
                tmp_s.append(s);
            // cout << tmp_s << endl;
            deal1(tmp_s);
        }
        else
        {
            string now, cur = " ";
            // cout << "begin  " << s << endl;
            for (int i = 0; i < s.length(); i++)
            {
                if (islower(s[i]))
                {
                    now = s.substr(i - 1, 2);
                    if (i + 1 >= s.length() || !isdigit(s[i + 1])) //双字母元素后面不是数字
                    {

                        mp1[now]++;
                        cur = s[i];
                    }
                    else //双字母元素后面是数字
                    {
                        int word_num, num_end;
                        word_num = get_num(s.substr(i + 1), num_end);
                        while (word_num--)
                            mp1[now]++;
                        cur = s[i];
                        i += num_end;
                    }
                }
                else if (isupper(s[i]))
                {
                    if (i + 1 < s.length())
                    {
                        if (isdigit(s[i + 1]))
                        {
                            int word_num, num_end;
                            word_num = get_num(s.substr(i + 1), num_end);
                            cur = s[i];
                            while (word_num--)
                                mp1[cur]++;
                            i += num_end;
                        }
                        else if (islower(s[i + 1]))
                        {
                            cur = s[i];
                        }
                        else
                        {
                            cur = s[i];
                            mp1[cur]++;
                        }
                    }
                    else
                    {
                        cur = s[i];
                        mp1[cur]++;
                    }

                    // if (isupper(cur[0]))
                    // {
                    //     mp1[cur]++;
                    // }
                    // cur = s[i];
                    // cout << "isupper  " << cur << " " << mp1[cur] << endl;
                }
                else
                {
                    int r_pos = get_kuohao(s.substr(i));
                    r_pos += i;
                    if (r_pos + 1 < s.length() && isdigit(s[r_pos + 1])) //括号后有数字
                    {
                        int word_num, num_end = 0;
                        string tmp_s, tts = "";
                        word_num = get_num(s.substr(r_pos + 1), num_end);
                        tmp_s = s.substr(i + 1, r_pos - i - 1);
                        // cout << tmp_s << "-- " << word_num << " " << num_end << endl;
                        while (word_num--)
                            tts.append(tmp_s);
                        deal1(tts);
                        i = r_pos + num_end;
                        // cout << tts << endl;
                    }
                    else
                    {
                        string tmp_s = s.substr(i + 1, r_pos - i - 1);
                        // cout << tmp_s << "-0-" << endl;
                        deal1(tmp_s);
                        i = r_pos;
                    }
                }
            }
        }
    }
}

void deal2(string s)
{
    int pos = 0, last = 0;
    while ((pos = s.find("+", pos)) != string::npos)
    {
        deal2(s.substr(last, pos - last));
        // cout << s.substr(last, pos - last) << endl;
        last = ++pos;
    }
    if (last != 0)
    {
        // cout << s.substr(last) << endl;
        deal2(s.substr(last));
    }
    else //以分解为没有加号的单词
    {
        if (isdigit(s[0])) //处理单词前数字
        {
            int alp_begin, word_num;
            string tmp_s = "";
            word_num = get_num(s, alp_begin);
            s.erase(0, alp_begin);
            for (int i = 0; i < word_num; i++)
                tmp_s.append(s);
            // cout << tmp_s << endl;
            deal2(tmp_s);
        }
        else
        {
            string now, cur = " ";
            // cout << "begin  " << s << endl;
            for (int i = 0; i < s.length(); i++)
            {
                if (islower(s[i]))
                {
                    now = s.substr(i - 1, 2);
                    if (i + 1 >= s.length() || !isdigit(s[i + 1])) //双字母元素后面不是数字
                    {
                        // cout << "now1  " << now << endl;
                        mp2[now]++;
                    }
                    else //双字母元素后面是数字
                    {
                        int word_num, num_end;
                        word_num = get_num(s.substr(i + 1), num_end);
                        // cout << "now2  " << now << endl;
                        while (word_num--)
                            mp2[now]++;
                        i += num_end;
                    }
                }
                else if (isupper(s[i]))
                {
                    if (i + 1 < s.length())
                    {
                        if (isdigit(s[i + 1]))
                        {
                            int word_num, num_end;
                            word_num = get_num(s.substr(i + 1), num_end);
                            cur = s[i];
                            while (word_num--)
                                mp2[cur]++;
                            i += num_end;
                        }
                        else if (islower(s[i + 1]))
                        {
                            cur = s[i];
                        }
                        else
                        {
                            cur = s[i];
                            mp2[cur]++;
                        }
                    }
                    else
                    {
                        cur = s[i];
                        mp2[cur]++;
                    }

                    // if (isupper(cur[0]))
                    // {
                    //     mp2[cur]++;
                    // }
                    // cur = s[i];
                    // cout << "isupper  " << cur << " " << mp2[cur] << endl;
                }
                else
                {
                    int r_pos = get_kuohao(s.substr(i));
                    r_pos += i;
                    if (r_pos + 1 < s.length() && isdigit(s[r_pos + 1])) //括号后有数字
                    {
                        int word_num, num_end = 0;
                        string tmp_s, tts = "";
                        word_num = get_num(s.substr(r_pos + 1), num_end);
                        tmp_s = s.substr(i + 1, r_pos - i - 1);
                        // cout << tmp_s << "-- " << word_num << " " << num_end << endl;
                        while (word_num--)
                            tts.append(tmp_s);
                        deal2(tts);
                        i = r_pos + num_end;
                        // cout << tts << endl;
                    }
                    else
                    {
                        string tmp_s = s.substr(i + 1, r_pos - i - 1);
                        // cout << tmp_s << "-0-" << endl;
                        deal2(tmp_s);
                        i = r_pos;
                    }
                }
            }
        }
    }
}

bool equal()
{
    map<string, int>::iterator it1;
    // cout << mp1.size() << " " << mp2.size() << endl;
    if (mp1.size() != mp2.size())
        return false;
    for (it1 = mp1.begin(); it1 != mp1.end(); it1++)
    {
        // cout << it1->first << " " << it1->second << " " << mp2[it1->first] << endl;
        if (mp2[it1->first] != it1->second)
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
        mp1.clear(), mp2.clear();
        int pos = s.find("=");
        // cout << s.substr(0, pos) << endl;
        deal1(s.substr(0, pos));
        // cout << s.substr(pos + 1) << endl;
        deal2(s.substr(pos + 1));
        if (equal())
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }
    return 0;
}