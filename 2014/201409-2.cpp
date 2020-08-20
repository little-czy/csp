#include <iostream>
#include <cstdio>

using namespace std;

int n, num = 0;
bool flag[110][110] = {0};

int main()
{
    cin >> n;
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for (int j = x1; j < x2; j++)
            for (int k = y1; k < y2; k++)
                flag[j][k] = 1;
    }
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++)
            if (flag[i][j])
                num++;
    cout << num << endl;
    return 0;
}