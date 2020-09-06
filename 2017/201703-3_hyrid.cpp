#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

string s;
vector<string> v;

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (getline(cin, s))
        v.push_back(s);
    bool flag_p = false;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].size())
        {
            if (v[i][0] == '#')
            {
                flag_p = false;
                regex r_h1("#\\s*(.*)"), r_h2("(#)\\1{1}\\s*(.*)"), r_h3("(#)\\1{2}\\s*(.*)");
                regex r_h4("(#)\\1{3}\\s*(.*)"), r_h5("(#)\\1{4}\\s*(.*)"), r_h6("(#)\\1{5}\\s*(.*)"), r_h7("(#)\\1{6}\\s*(.*)");
                s = regex_replace(v[i], r_h7, "<h7>$2</h7>");
                s = regex_replace(s, r_h6, "<h6>$2</h6>");
                s = regex_replace(s, r_h5, "<h5>$2</h5>");
                s = regex_replace(s, r_h4, "<h4>$2</h4>");
                s = regex_replace(s, r_h3, "<h3>$2</h3>");
                s = regex_replace(s, r_h2, "<h2>$2</h2>");
                s = regex_replace(s, r_h1, "<h1>$1</h1>");
                v[i] = s;
            }
            else if (v[i][0] == '*')
            {
                flag_p = false;
                regex r_l("\\*\\s*(.*)");
                v[i] = regex_replace(v[i], r_l, "<li>$1</li>");
                // int k;
                // for (k = 1; k < v[i].size(); k++) //统计 * 后空格个数
                //     if (v[i][k] != ' ')
                //         break;
                // v[i].replace(0, k, "<li>");
                // v[i] += "</li>";
            }
            else
            {
                if (flag_p)
                {
                    v[i - 1].erase(v[i - 1].size() - 4, 4);
                    v[i].append("</p>");
                }
                else
                {
                    flag_p = true;
                    v[i].insert(0, "<p>");
                    v[i].append("</p>");
                }
            }
        }
        else
            flag_p = false;
    }
    for (int i = 0; i < v.size(); i++)
        if (v[i].size() && regex_match(v[i], regex("^<li>.*")))
        {
            v.insert(v.begin() + i, string("<ul>"));
            int j;
            for (j = i + 2; j < v.size(); j++)
                if (!regex_match(v[j], regex("^<li>.*")))
                    break;
            v.insert(v.begin() + j, string("</ul>"));
            i = j;
        }
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].size())
        {
            regex r_em("_(.*?)_");
            v[i] = regex_replace(v[i], r_em, "<em>$1</em>");
        }
    }
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].size())
        {
            regex r_link("\\[(.*?)\\]\\((.*?)\\)");
            v[i] = regex_replace(v[i], r_link, "<a href=\"$2\">$1</a>");
        }
    }

    // for (int i = 0; i < v.size(); i++) //替换强调
    // {
    //     if (v[i].size() != 0)
    //     {
    //         int pos1;
    //         while ((pos1 = v[i].find("_")) != string::npos)
    //         {
    //             v[i].replace(pos1, 1, "<em>");
    //             v[i].replace(v[i].find("_"), 1, "</em>");
    //         }
    //     }
    // }

    // for (int i = 0; i < v.size(); i++) //替换超级链接
    // {
    //     if (v[i].size() != 0)
    //     {
    //         int link_pos, link_pos1, link_pos2;
    //         while ((link_pos = v[i].find("[")) != string::npos)
    //         {
    //             link_pos1 = v[i].find("]");
    //             string tmp_name = v[i].substr(link_pos + 1, link_pos1 - link_pos - 1);
    //             link_pos2 = v[i].find(")");
    //             string tmp_link = v[i].substr(link_pos1 + 2, link_pos2 - link_pos1 - 2);
    //             string link = "<a href=\"" + tmp_link + "\">" + tmp_name + "</a>";
    //             v[i].replace(link_pos, link_pos2 - link_pos + 1, link);
    //         }
    //     }
    // }
    for (int i = 0; i < v.size(); i++)
        if (v[i].length() != 0)
            cout << v[i] << endl;
    return 0;
}