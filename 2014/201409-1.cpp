#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, num = 0;
int a[1010];

// bool cmp(int x, int y)
// {
//     return x < y;
// }

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++)
    {
        // cout << a[i] << " ";
        if (a[i + 1] - a[i] == 1)
            num++;
    }
    cout << num << endl;
    return 0;
}