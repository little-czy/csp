#include <iostream>

using namespace std;

int now, last = 1, ans = 0;

int main()
{
    cin >> now;
    while (now != 0)
    {
        if (now == 2 && last == 1)
        {
            ans += 2;
            last = 2;
        }
        else if (now == 2 && last != 1)
        {
            last += 2;
            ans += last;
        }
        else
        {
            ans += 1;
            last = 1;
        }
        cin >> now;
    }
    cout << ans << endl;
    return 0;
}