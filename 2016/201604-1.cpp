#include <iostream>

using namespace std;

int n, ans = 0;
int a[4];

int main()
{
    cin >> n;
    if (n == 1)
    {
        cin >> a[0];
    }
    else if (n == 2)
    {
        cin >> a[0] >> a[1];
    }
    else
    {
        cin >> a[0] >> a[1];
        for (int i = 2; i < n; i++)
        {
            cin >> a[2];
            if ((a[0] < a[1] && a[2] < a[1]) || (a[0] > a[1] && a[2] > a[1]))
                ans++;
            a[0] = a[1], a[1] = a[2];
        }
    }
    cout << ans << endl;
    return 0;
}