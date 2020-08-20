#include <iostream>

using namespace std;

int n, k;
int ans = 0;
int a[1005];

int main()
{
    cin >> n >> k;
    int tmp_sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        tmp_sum += a[i];
        if (tmp_sum >= k)
        {
            tmp_sum = 0;
            ans++;
        }
    }
    if (tmp_sum != 0)
        ans++;
    cout << ans << endl;
    return 0;
}