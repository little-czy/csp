#include <iostream>

using namespace std;

int n;

int main()
{
    cin >> n;
    int ans = 1, t, last_t;
    cin >> t;
    last_t = t;
    for (int i = 1; i < n; i++)
    {
        cin >> t;
        if (last_t != t)
        {
            last_t = t;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}