#include <iostream>
#include <algorithm>

using namespace std;

int n;
int a[1005];
int s[1005];

int main()
{
    cin >> n;
    int x, sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        a[x]++;
    }
    for (int i = 0; i < 1002; i++)
    {
        sum += a[i];
        s[i] = sum;
    }
    for (int i = 1; i < 1002; i++)
    {
        if (a[i] != 0 && s[i - 1] == s[1001] - s[i])
        {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}