#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
vector<string> v;

int main()
{
    string line;
    bool p = 0;
    while (getline(cin, line))
    {
        v.push_back(line);
    }
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i][0] == '#')
        {
            int j, k;
            for (j = 1; j < v[i].size(); j++) //统计 # 个数
            {
                if (v[i][j] != '#')
                    break;
            }
            for (k = j; k < v[i].size(); k++) //统计#后空格个数
            {
                if (v[i][k] != ' ')
                    break;
            }
            string tmp_begin = "<h";
            tmp_begin += (j + '0');
            tmp_begin += ">";
            string tmp_end = "</h";
            tmp_end += (j + '0');
            tmp_end += ">";
            v[i].replace(0, k, tmp_begin);
            v[i] += tmp_end;
        }
        else if (v[i][0] == '*')
        {
            int k;
            for (k = 1; k < v[i].size(); k++) //统计 * 后空格个数
            {
                if (v[i][k] != ' ')
                    break;
            }
            string tmp_begin = "<li>";
            string tmp_end = "</li>";
            v[i].replace(0, k, tmp_begin);
            v[i] += tmp_end;
        }
        else if (v[i].size() != 0)
        {
            int end_pos;
            if (i > 0 && (end_pos = v[i - 1].find("</p>")) != string::npos) //前面已有段落开始符
            {
                v[i - 1].erase(end_pos, 4);
                string tmp_end = "</p>";
                v[i] += tmp_end;
            }
            else //本行为段落开始
            {
                string tmp_begin = "<p>";
                string tmp_end = "</p>";
                v[i].insert(0, tmp_begin);
                v[i] += tmp_end;
            }
        }
    }

    for (int i = 0; i < v.size(); i++) //完善列表
    {
        if (v[i].size() != 0)
        {
            if (v[i].find("<li>") != string::npos)
            {
                v.insert(v.begin() + i, "<ul>");
                int j;
                for (j = i + 2; j < v.size(); j++)
                {
                    if (v[j].find("<li>") == string::npos)
                    {
                        break;
                    }
                }
                v.insert(v.begin() + j, "</ul>");
                i = j;
            }
        }
    }

    for (int i = 0; i < v.size(); i++) //替换强调
    {
        if (v[i].size() != 0)
        {
            int pos1;
            while ((pos1 = v[i].find("_")) != string::npos)
            {
                v[i].replace(pos1, 1, "<em>");
                v[i].replace(v[i].find("_"), 1, "</em>");
            }
        }
    }

    for (int i = 0; i < v.size(); i++) //替换超级链接
    {
        if (v[i].size() != 0)
        {
            int link_pos, link_pos1, link_pos2;
            while ((link_pos = v[i].find("[")) != string::npos)
            {
                link_pos1 = v[i].find("]");
                string tmp_name = v[i].substr(link_pos + 1, link_pos1 - link_pos - 1);
                link_pos2 = v[i].find(")");
                string tmp_link = v[i].substr(link_pos1 + 2, link_pos2 - link_pos1 - 2);
                string link = "<a href=\"" + tmp_link + "\">" + tmp_name + "</a>";
                v[i].replace(link_pos, link_pos2 - link_pos + 1, link);
            }
        }
    }

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].length() != 0)
        {
            cout << v[i] << endl;
        }
    }
    return 0;
}