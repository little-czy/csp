#include <iostream>
#include <math.h>

using namespace std;

int n;

int main()
{
    cin >> n;
    int x, y, ans = 0;
    cin >> x;
    for (int i = 1; i < n; i++)
    {
        cin >> y;
        if (abs(y - x) > ans)
            ans = abs(y - x);
        x = y;
    }
    cout << ans << endl;
    return 0;
}