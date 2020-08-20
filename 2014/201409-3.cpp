#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int n;
bool sensitive;
string flag, t_str;

string toLower(string s)
{
    string d = s;
    for (int i = 0; i < d.size(); i++)
    {
        if ('A' <= d[i] && d[i] <= 'Z')
            d[i] = d[i] + 'a' - 'A';
    }
    return d;
}

int main()
{
    cin >> flag >> sensitive >> n;
    string t_flag;
    if (!sensitive) //大小写不敏感
        t_flag = toLower(flag);
    else
        t_flag = flag;
    for (int i = 0; i < n; i++)
    {
        cin >> t_str;
        if (sensitive) //大小写敏感
        {
            if (t_str.find(t_flag) != string::npos)
                cout << t_str << endl;
        }
        else
        {
            string tt_str = toLower(t_str);
            // cout << tt_str << endl;
            if (tt_str.find(t_flag) != string::npos)
                cout << t_str << endl;
        }
    }
    return 0;
}