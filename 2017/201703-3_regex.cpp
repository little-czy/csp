#include <iostream>
#include <string>
#include <regex>

using namespace std;

string s, tmp;

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (getline(cin, tmp))
    {
        s.append(tmp);
        s.append("\n");
    }

    // cout << s;
    regex r_h1("#\\s*(.*)"), r_h2("(#)\\1{1}\\s*(.*)"), r_h3("(#)\\1{2}\\s*(.*)");
    regex r_h4("(#)\\1{3}\\s*(.*)"), r_h5("(#)\\1{4}\\s*(.*)"), r_h6("(#)\\1{5}\\s*(.*)");
    s = regex_replace(s, r_h6, "\n<h6>$2</h6>\n");
    s = regex_replace(s, r_h5, "\n<h5>$2</h5>\n");
    s = regex_replace(s, r_h4, "\n<h4>$2</h4>\n");
    s = regex_replace(s, r_h3, "\n<h3>$2</h3>\n");
    s = regex_replace(s, r_h2, "\n<h2>$2</h2>\n");
    s = regex_replace(s, r_h1, "\n<h1>$1</h1>\n");
    s = regex_replace(s, regex("\\n{3,}"), "\n\n");
    regex r_l("\\*\\s*(.*)");
    s = regex_replace(s, r_l, "<ul>\n<li>$1</li>\n</ul>");
    s = regex_replace(s, regex("</ul>\\n<ul>\\n"), "");
    s = regex_replace(s, regex("</ul>\\n(?!<ul>)"), "</ul>\n\n");
    regex r_link("\\[(.*)\\]\\((.*)\\)");
    s = regex_replace(s, r_link, "<a href=\"$2\">$1</a>");
    regex r_em("_(.*?)_");
    s = regex_replace(s, r_em, "<em>$1</em>");
    while (s[0] == '\n')
        s.erase(s.begin());
    s.insert(0, "<p>");
    while (s[s.size() - 1] == '\n')
        s.erase(s.size() - 1);
    s = regex_replace(s, regex("\\n\\n"), "</p>\n\n<p>");
    // cout << s;
    s.append("</p>");
    s = regex_replace(s, regex("<p>(<[hu][\\d\\D]*?>)</p>"), "$1");
    s = regex_replace(s, regex("\\n\\n"), "\n");
    cout << s;
    return 0;
}