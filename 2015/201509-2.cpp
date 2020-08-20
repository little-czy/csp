#include <iostream>

using namespace std;

int y, d;
int mon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

inline bool check(int y)
{
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int main()
{
    cin >> y >> d;
    if (check(y)) //ÈòÄê
        mon[2] = 29;
    int i, count = 0;
    for (i = 1; i < 13; i++)
    {
        if (count + mon[i] >= d)
            break;
        count += mon[i];
    }
    cout << i << endl;
    cout << d - count << endl;
    return 0;
}