#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <string>

using namespace std;

int n, m;
vector<string> s;
map<string, string> map1;

int main()
{
    cin >> n >> m;
    getchar();
    string var_name, var_value;
    for (int i = 0; i < n; i++)
    {
        getline(cin, var_value);
        s.push_back(var_value);
    }

    for (int i = 0; i < m; i++)
    {
        cin >> var_name;
        getline(cin, var_value);
        map1[var_name] = var_value.substr(2, var_value.length() - 3);
    }
    int pre_pos = 0, last_pos = 0;
    string name;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        while ((pre_pos = s[i].find("{{ ", 0)) != string::npos)
        {
            for (int j = 0; j < count; j++)
            {
                pre_pos += 3;
                pre_pos = s[i].find("{{ ", pre_pos);
            }
            if (pre_pos == string::npos)
                break;
            last_pos = s[i].find(" }}", pre_pos);
            name = s[i].substr(pre_pos + 3, last_pos - pre_pos - 3);
            s[i].replace(pre_pos, last_pos - pre_pos + 3, map1[name]);
            for (int k = 0; (k = map1[name].find("{{ ", k)) != string::npos;)
            {
                k += 3;
                count++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << s[i] << endl;
    }
    return 0;
}