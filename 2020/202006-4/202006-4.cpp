#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;
string s;
map<string, int> mp;

void init()
{
    mp["1"] = 0;
    mp["2"] = 1;
    mp["4"] = 2;
    mp["6"] = 3;
    mp["16"] = 4;
    mp["26"] = 5;
    mp["41"] = 6;
    mp["42"] = 7;
    mp["44"] = 8;
    mp["46"] = 9;
    mp["61"] = 10;
    mp["62"] = 11;
    mp["64"] = 12;
    mp["66"] = 13;
}

const int N = 14;

ll tmp[N][N];

void multi(ll a[][N], ll b[][N], int n)
{
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % 998244353;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = tmp[i][j];
}

ll res[N][N];

void Pow(ll a[][N], int n)
{
    memset(res, 0, sizeof(res)); //n是幂，N是矩阵大小
    for (int i = 0; i < N; i++)
        res[i][i] = 1;
    while (n)
    {
        if (n & 1)
            multi(res, a, N); //res=res*a;复制直接在multi里面实现了；
        multi(a, a, N);       //a=a*a
        n >>= 1;
    }
}

int main()
{
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s;
    init();
    ll a[14][14] = {
        //0 1  2  3  4  5  6  7  8  9 10 11 12 13
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0 1
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1 2
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2 4
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3 6
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4 16
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //5 26
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //6 41
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //7 42
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //8 44
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, //9 46
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //10 61
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //11 62
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //12 64
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}  //13 66
    };
    Pow(a, n);
    cout << res[mp[s]][0] % 998244353 << endl;
    return 0;
}
