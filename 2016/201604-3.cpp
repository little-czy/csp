#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int p;
string cur_path; //当前路径
string tmp;      //需要正规化的路径

void erase1() //删除多余的 /
{
    for (int i = 0; i < tmp.size(); i++)
        if (tmp[i] == '/')
            while (i + 1 < tmp.size() && tmp[i + 1] == '/')
                tmp.erase(i + 1, 1);
    if (tmp.empty()) //空路径保存为当前路径
        tmp = cur_path;
    if (tmp[tmp.size() - 1] != '/') //确保以斜杠结尾
        tmp.append("/");
    if (tmp[0] != '/') //相对路径接在当前路径后
        tmp.insert(0, cur_path + "/");
    // cout << tmp << endl;
}

void del_point() //去除 .. 和 .
{
    int pos1 = 0;
    while ((pos1 = tmp.find("/./")) != string::npos) //去除 .
    {
        tmp.replace(pos1, 3, "/");
    }
    while ((pos1 = tmp.find("/../")) != string::npos) //去除 ..
    {
        if (pos1 == 0) //上一级为根节点
        {
            tmp.replace(pos1, 4, "/");
        }
        else
        {
            int i;
            for (i = pos1 - 1; tmp[i] != '/'; i--)
                ;
            // cout << pos1 << "  " << i << endl;
            tmp.erase(i, pos1 + 3 - i);
        }
    }
    if (tmp.size() != 1)
        tmp.erase(tmp.size() - 1, 1);
}

int main()
{
    cin >> p >> cur_path;
    getchar();
    for (int i = 0; i < p; i++)
    {
        getline(cin, tmp);
        erase1();
        del_point();
        cout << tmp << endl;
    }

    return 0;
}