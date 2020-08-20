#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a[1005];
int maxs;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int temp_max = 0;
    for (int i = 0; i < n; i++)
    {
        int flag_height = a[i];
        for (int j = 0; j < n;)
        {
            if (a[j] >= flag_height)
            {
                int k;
                for (k = j + 1; k < n && a[k] >= flag_height; k++)
                    ;
                temp_max = flag_height * (k - j);
                if (temp_max > maxs)
                    maxs = temp_max;
                j = k;
            }
            else
                j++;
        }
    }
    cout << maxs << endl;
    return 0;
}