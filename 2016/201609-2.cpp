#include <iostream>
#include <vector>

using namespace std;

int n, p;
// bool f[22][7];
vector<bool> f[22];

int check(int x) //判断是否可以连坐
{
    for (int i = 1; i <= 20; i++)
    {
        if (5 - f[i].size() >= x)
        {
            for (int j = 0; j < x; j++)
            {
                f[i].push_back(true);
            }
            return i;
        }
    }
    return 0;
}

int find_empty()
{
    for (int i = 1; i <= 20; i++)
    {
        if (f[i].size() < 5)
        {
            f[i].push_back(true);
            return (i - 1) * 5 + f[i].size();
        }
    }
    return 0;
}

int main()
{
    cin >> n;
    int f_i, start;
    for (int i = 0; i < n; i++)
    {
        cin >> p;
        if ((f_i = check(p)) != 0)
        {
            start = 5 * (f_i - 1) + f[f_i].size() - p + 1;
            for (int j = 0; j < p; j++)
            {
                cout << start + j << " ";
            }
            cout << endl;
        }
        else
        {
            for (int j = 0; j < p; j++)
            {
                cout << find_empty() << " ";
            }
            cout << endl;
        }
    }
    return 0;
}