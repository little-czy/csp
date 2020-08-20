#include <cstdio>

using namespace std;

int main()
{
    int a1, a2, a3, a4, a5, a6, a7, a8, a9, x;
    a1 = getchar() - '0';
    getchar();
    a2 = getchar() - '0';
    a3 = getchar() - '0';
    a4 = getchar() - '0';
    getchar();
    a5 = getchar() - '0';
    a6 = getchar() - '0';
    a7 = getchar() - '0';
    a8 = getchar() - '0';
    a9 = getchar() - '0';
    getchar();
    x = getchar() - '0';
    getchar();
    int x_r = (a1 + a2 * 2 + a3 * 3 + a4 * 4 + a5 * 5 + a6 * 6 + a7 * 7 + a8 * 8 + a9 * 9) % 11;
    if (x == 'X' - '0')
    {
        if (x_r == 10)
            printf("Right\n");
        else
            printf("%d-%d%d%d-%d%d%d%d%d-%d\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, x_r);
    }
    else
    {
        if (x == x_r)
            printf("Right\n");
        else
        {
            if (x_r == 10)
                printf("%d-%d%d%d-%d%d%d%d%d-X\n", a1, a2, a3, a4, a5, a6, a7, a8, a9);
            else
                printf("%d-%d%d%d-%d%d%d%d%d-%d\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, x_r);
        }
    }

    return 0;
}