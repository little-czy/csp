#include <iostream>
#include <vector>
#include <set>
#define MAXS 10105
using namespace std;

int n, k;
set<int> v1[MAXS], v2[MAXS];
int key[1005];

inline void key_back(int num)
{
    for (int i = 1; i <= n; i++)
    {
        if (key[i] == 0)
        {
            key[i] = num;
            break;
        }
    }
}

inline void key_get(int num)
{
    for (int i = 1; i <= n; i++)
    {
        if (key[i] == num)
        {
            key[i] = 0;
            break;
        }
    }
}

int main()
{
    cin >> n >> k;
    int w, s, c;
    for (int i = 0; i < k; i++)
    {
        cin >> w >> s >> c;
        v1[s].insert(w);
        v2[s + c].insert(w);
    }
    for (int i = 1; i <= n; i++)
    {
        key[i] = i;
    }
    for (int i = 0; i < MAXS; i++)
    {
        if (!v2[i].empty())
        {
            for (set<int>::iterator it = v2[i].begin(); it != v2[i].end(); it++)
            {
                key_back(*it);
                // cout << *it << " ";
            }
            // cout << endl;
        }
        if (!v1[i].empty())
        {
            for (set<int>::iterator it = v1[i].begin(); it != v1[i].end(); it++)
            {
                key_get(*it);
                // cout << *it << " ";
            }
            // cout << endl;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << key[i] << " ";
    }
    cout << endl;
    return 0;
}