#include <iostream>

using namespace std;

int n;

int main()
{
    cin >> n;
    cout << (n / 50 * 7 + n % 50 / 30 * 4 + n % 50 % 30 / 10) << endl;
    return 0;
}