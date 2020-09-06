#include <iostream>
#include <vector>
#include <utility>
#include <regex>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e3 + 5;

int n, m;
vector<pair<string, string>> rules;

inline void deal_rules()
{
    regex reg_int("<int>"), reg_str("<str>"), reg_path("<path>");
    for (int i = 0; i < rules.size(); i++)
    {
        string tmp = regex_replace(rules[i].first, reg_int, "(\\d+)");
        tmp = regex_replace(tmp, reg_str, "([\\w.-]+)");
        tmp = regex_replace(tmp, reg_path, "([\\w.-/]+)");
        rules[i].first = tmp;
        // cout << rules[i].first << endl;
    }
}
void match(string a)
{
    smatch ans;
    int i;
    for (i = 0; i < rules.size(); i++)
        if (regex_match(a, ans, regex(rules[i].first)))
            break;
    if (i < rules.size())
    {
        cout << rules[i].second;
        for (smatch::iterator it = ++(ans.begin()); it != ans.end(); it++)
        {
            string tmp = *it;
            cout << " " << regex_replace(tmp, regex("^(0+)([1-9]+)"), "$2");
        }
    }
    else
        cout << 404;
    cout << endl;
}

int main()
{
    string a, b;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        rules.push_back(make_pair(a, b));
    }
    deal_rules();
    for (int i = 0; i < m; i++)
    {
        cin >> a;
        match(a);
    }

    return 0;
}