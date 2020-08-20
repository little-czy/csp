#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct pri
{
    string pname;
    int grade;
    bool haveGrade;
    pri() {}
    pri(string _pname, int _g, bool _hg) : pname(_pname), grade(_g), haveGrade(_hg) {}
};
int p, r, u, q;
map<string, map<string, pri>> role_map, user_map;
map<string, pri> pri_map;

int main()
{
    cin >> p;
    string tmp_privilege;
    int pos;
    for (int i = 0; i < p; i++)
    {
        cin >> tmp_privilege;
        string tmp_pname;
        int tmp_grade;
        if ((pos = tmp_privilege.find(":")) != string::npos)
        {
            tmp_pname = tmp_privilege.substr(0, pos);
            tmp_grade = tmp_privilege[tmp_privilege.size() - 1] - '0';
            pri_map[tmp_pname] = pri(tmp_pname, tmp_grade, 1);
        }
        else
        {
            pri_map[tmp_privilege] = pri(tmp_privilege, 0, 0);
        }
    }
    cin >> r;
    string tmp_role;
    int role_num;
    for (int i = 0; i < r; i++)
    {
        cin >> tmp_role >> role_num;
        map<string, pri> tmp_pri_map;
        for (int j = 0; j < role_num; j++)
        {
            cin >> tmp_privilege;
            string tmp_pname;
            int tmp_grade;
            if ((pos = tmp_privilege.find(":")) != string::npos) //带等级权限
            {
                tmp_pname = tmp_privilege.substr(0, pos);
                // cout << "-" << tmp_pname << "-" << endl;
                tmp_grade = tmp_privilege[tmp_privilege.size() - 1] - '0';
                if (pri_map[tmp_pname].haveGrade)
                {
                    if (tmp_grade > pri_map[tmp_pname].grade)
                    {
                        tmp_grade = pri_map[tmp_pname].grade;
                    }
                    map<string, pri>::iterator it = tmp_pri_map.find(tmp_pname);
                    if (it != tmp_pri_map.end()) //角色中已存在该类权限
                    {
                        if (it->second.haveGrade && it->second.grade < tmp_grade)
                            it->second.grade = tmp_grade;
                    }
                    else //角色中不存在该类权限
                    {
                        tmp_pri_map[tmp_pname] = pri(tmp_pname, tmp_grade, 1);
                    }
                }
                else //不能带等级的权限
                {
                    map<string, pri>::iterator it = tmp_pri_map.find(tmp_pname);
                    if (it == tmp_pri_map.end()) //角色中不存在该类权限
                    {
                        tmp_pri_map[tmp_privilege] = pri(tmp_privilege, 0, 0);
                    }
                }
            }
            else //不带等级权限
            {
                map<string, pri>::iterator it = tmp_pri_map.find(tmp_pname);
                if (it == tmp_pri_map.end()) //角色中不存在该类权限
                {
                    tmp_pri_map[tmp_privilege] = pri(tmp_privilege, 0, 0);
                }
            }
        }
        role_map[tmp_role] = tmp_pri_map;
    }
    cin >> u;
    string tmp_user;
    for (int i = 0; i < u; i++)
    {
        cin >> tmp_user >> role_num;
        for (int j = 0; j < role_num; j++)
        {
            cin >> tmp_role;
            map<string, pri> tmp_role_map = role_map[tmp_role];
            for (map<string, pri>::iterator it = tmp_role_map.begin(); it != tmp_role_map.end(); it++)
            {
                if (user_map.find(tmp_user) != user_map.end()) //用户已创建
                {
                    map<string, pri>::iterator it1 = user_map[tmp_user].find(it->first);
                    if (it1 != user_map[tmp_user].end()) //用户map中已经存在该权限
                    {
                        if (it1->second.haveGrade && it1->second.grade < it->second.grade)
                            it1->second.grade = it->second.grade;
                    }
                    else //用户map中不存在该权限
                    {
                        user_map[tmp_user][it->first] = it->second;
                    }
                }
                else //用户未创建
                {
                    user_map[tmp_user][it->first] = it->second;
                }
            }
        }
    }
    cin >> q;
    int tmp_grade;
    for (int i = 0; i < q; i++)
    {
        cin >> tmp_user >> tmp_privilege;
        if ((pos = tmp_privilege.find(":")) != string::npos)
        {
            tmp_role = tmp_privilege.substr(0, pos);
            // cout << "-" << tmp_role << "-";
            tmp_grade = tmp_privilege[tmp_privilege.size() - 1] - '0';
            // cout << "-" << tmp_grade << "-" << endl;
            if (user_map.find(tmp_user) != user_map.end() && user_map[tmp_user].find(tmp_role) != user_map[tmp_user].end())
            {
                if (user_map[tmp_user][tmp_role].haveGrade && user_map[tmp_user][tmp_role].grade >= tmp_grade)
                    cout << "true" << endl;
                else
                    cout << "false" << endl;
            }
            else
                cout << "false" << endl;
        }
        else
        {
            tmp_role = tmp_privilege;
            if (user_map.find(tmp_user) != user_map.end() && user_map[tmp_user].find(tmp_role) != user_map[tmp_user].end())
            {
                if (user_map[tmp_user][tmp_role].haveGrade)
                    cout << user_map[tmp_user][tmp_role].grade << endl;
                else
                    cout << "true" << endl;
            }
            else
                cout << "false" << endl;
        }
    }
    return 0;
}