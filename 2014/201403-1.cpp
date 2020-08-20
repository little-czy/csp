#include <iostream>

using namespace std;

int a[505];
int flag[1005];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] < 0)
            a[i] = -a[i];
        flag[a[i]]++;
    }
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        if (flag[a[i]] == 2)
            num++;
    }
    cout << num / 2 << endl;
    return 0;
}