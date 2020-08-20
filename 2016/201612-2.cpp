#include <iostream>

using namespace std;

double t, s;

int main()
{
    cin >> s;
    if (0 <= s && s <= 3500)
    {
        t = s;
    }
    else if (3500 < s && s <= 4955)
    {
        t = 3500 + (s - 3500) / 0.97;
    }
    else if (4955 < s && s <= 7655)
    {
        t = 5000 + (s - 4955) / 0.9;
    }
    else if (7655 < s && s <= 11255)
    {
        t = 8000 + (s - 7655) / 0.8;
    }
    else if (11255 < s && s <= 30755)
    {
        t = 12500 + (s - 11255) / 0.75;
    }
    else if (30755 < s && s <= 44755)
    {
        t = 38500 + (s - 30755) / 0.7;
    }
    else if (44755 < s && s <= 61005)
    {
        t = 58500 + (s - 44755) / 0.65;
    }
    else
    {
        t = 83500 + (s - 61005) / 0.55;
    }
    cout << (int)t << endl;
    return 0;
}