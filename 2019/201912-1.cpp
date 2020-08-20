#include <iostream>

using namespace std;

int a[5];
int j = 0, n;

inline bool check(int n)
{
    if (n % 7 == 0)
    {
        return true;
    }
    while (n)
    {
        if (n % 10 == 7)
            return true;
        n /= 10;
    }
    return false;
}

int main()
{
    cin >> n;
    for (int i = 1; j < n; i++)
    {
        if (!check(i))
        {
            j++;
        }
        else
        {
            a[i % 4]++;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        cout << a[i] << endl;
    }
    cout << a[0] << endl;
    return 0;
}