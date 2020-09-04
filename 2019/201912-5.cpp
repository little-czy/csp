#include <iostream>

#define ll __int128

using namespace std;
// typedef long long ll;
const int inf = 0x3f3f3f3f;
const int maxn = 1e6 + 5;

struct node
{
    int l, r;
    ll mlz, plz, sum;
} tree[maxn << 2];

int n, q;
ll a[maxn], p = 2009731336725594113;
ll u[5] = {314882150829468584,
           427197303358170108,
           1022292690726729920,
           1698479428772363217,
           2006101093849356424};

inline ll f(ll x)
{
    return (x % p) % 2019;
}

void build_tree(int i, int l, int r)
{
    tree[i].l = l, tree[i].r = r;
    tree[i].mlz = 1;
    if (l == r)
        tree[i].sum = l % p;
    else
    {
        int mid = (l + r) >> 1;
        build_tree(i << 1, l, mid);
        build_tree(i << 1 | 1, mid + 1, r);
        tree[i].sum = (tree[i << 1].sum + tree[i << 1 | 1].sum) % p;
    }
}

void push_down(int i)
{
    ll mlz = tree[i].mlz, plz = tree[i].plz;
    tree[i << 1].sum = (tree[i << 1].sum * mlz + plz * (tree[i << 1].r - tree[i << 1].l + 1)) % p;
    tree[i << 1 | 1].sum = (tree[i << 1 | 1].sum * mlz + plz * (tree[i << 1 | 1].r - tree[i << 1 | 1].l + 1)) % p;
    tree[i << 1].mlz = (tree[i << 1].mlz * mlz) % p;
    tree[i << 1 | 1].mlz = (tree[i << 1 | 1].mlz * mlz) % p;
    tree[i << 1].plz = (tree[i << 1].plz * mlz + plz) % p;
    tree[i << 1 | 1].plz = (tree[i << 1 | 1].plz * mlz + plz) % p;
    tree[i].plz = 0;
    tree[i].mlz = 1;
}

void add(int i, int l, int r, ll k)
{
    if (tree[i].r < l || tree[i].l > r)
        return;
    if (l <= tree[i].l && tree[i].r <= r)
    {
        tree[i].sum += (k * (tree[i].r - tree[i].l + 1)) % p;
        tree[i].plz = (tree[i].plz + k) % p;
    }
    else
    {
        push_down(i);
        if (l <= tree[i << 1].r)
            add(i << 1, l, r, k);
        if (tree[i << 1].r < r)
            add(i << 1 | 1, l, r, k);
        tree[i].sum = (tree[i << 1].sum + tree[i << 1 | 1].sum) % p;
    }
}

void mul(int i, int l, int r, ll k)
{
    if (tree[i].r < l || tree[i].l > r)
        return;
    if (l <= tree[i].l && tree[i].r <= r)
    {
        tree[i].sum = (tree[i].sum * k) % p;
        tree[i].plz = (tree[i].plz * k) % p;
        tree[i].mlz = (tree[i].mlz * k) % p;
    }
    else
    {
        push_down(i);
        if (l <= tree[i << 1].r)
            mul(i << 1, l, r, k);
        if (tree[i << 1].r < r)
            mul(i << 1 | 1, l, r, k);
        tree[i].sum = (tree[i << 1].sum + tree[i << 1 | 1].sum) % p;
    }
}

ll search(int i, int l, int r)
{
    if (tree[i].r < l || tree[i].l > r)
        return 0;
    if (l <= tree[i].l && tree[i].r <= r)
        return tree[i].sum;
    else
    {
        push_down(i);
        ll ans = 0;
        if (l <= tree[i << 1].r)
            ans += search(i << 1, l, r) % p;
        if (tree[i << 1].r < r)
            ans += search(i << 1 | 1, l, r) % p;
        return ans % p;
    }
}

inline void write(ll x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int main()
{
    int l, r, t;
    ll s;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    build_tree(1, 1, n);
    for (int i = 0; i < q; i++)
    {
        cin >> l >> r;
        s = search(1, l, r) % 2019;
        // cout << s << endl;
        // printf("%d\n", s);
        write(s);
        printf("\n");
        t = s % 5;
        mul(1, l, r, u[t]);
    }
    return 0;
}
