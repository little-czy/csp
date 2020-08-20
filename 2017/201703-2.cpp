#include <iostream>

using namespace std;

int n, m;
int v[1005];

inline int find_pos(int id)
{
    for (int i = 1; i <= n; i++)
    {
        if (v[i] == id)
            return i;
    }
    return 0;
}

int main()
{
    cin >> n >> m;
    int pos, id, length, tmp;
    for (int i = 1; i <= n; i++)
    {
        v[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> id >> length;
        int pos = find_pos(id);
        if (length < 0)
        {
            for (int j = 0; j < -length; j++)
            {
                v[pos - j] = v[pos - j - 1];
            }
            v[pos + length] = id;
        }
        else
        {
            for (int j = 0; j < length; j++)
            {
                v[pos + j] = v[pos + j + 1];
            }
            v[pos + length] = id;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}