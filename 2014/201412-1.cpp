#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 1005
using namespace std;

int _count[MAXN], n;
int visitor;
int num[MAXN];

int main()
{
    cin >> n;
    memset(_count, 0, sizeof(_count));
    for (int i = 0; i < n; i++)
    {
        cin >> visitor;
        _count[visitor]++;
        num[i] = _count[visitor];
    }
    for (int i = 0; i < n; i++)
    {
        cout << num[i] << " ";
    }

    return 0;
}