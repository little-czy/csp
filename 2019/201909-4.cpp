#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 3e4 + 5;

struct node
{
    int score, type, id;
    node() {}
    node(int _s, int _t, int _i) : score(_s), type(_t), id(_i) {}
    bool operator<(const node &a) const
    {
        if (a.score < score)
            return true;
        else if (a.score == score)
        {
            if (type < a.type)
                return true;
            else if (type == a.type)
                return id < a.id;
            else
                return false;
        }
        else
            return false;
    }
};

int n, m, kk, k[55], had_select_num[55];
set<node> s;
vector<int> ans[55];
unordered_map<int, int> mp[55];

inline int get_num()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x;
}

inline void select()
{
    int all_num = 0;
    for (int i = 0; i < m; i++)
        ans[i].clear();
    memset(had_select_num, 0, sizeof(had_select_num));
    for (set<node>::iterator it = s.begin(); it != s.end(); it++)
    {
        if (all_num >= kk)
            break;
        if (had_select_num[it->type] < k[it->type])
        {
            had_select_num[it->type]++;
            ans[it->type].push_back(it->id);
            all_num++;
        }
    }
}

int main()
{
    int id, score, type;
    int op_num, op;
    freopen("in", "r", stdin);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cin >> m >> n;
    m = get_num(), n = get_num();
    for (int i = 0; i < n; i++)
    {
        // cin >> id >> score;
        id = get_num(), score = get_num();
        for (int i = 0; i < m; i++)
        {
            mp[i][id] = score;
            s.insert(node(score, i, id));
        }
    }
    // cin >> op_num;
    op_num = get_num();
    for (int i = 0; i < op_num; i++)
    {
        // cin >> op;
        op = get_num();
        if (op == 1)
        {
            // cin >> type >> id >> score;
            type = get_num(), id = get_num(), score = get_num();
            mp[type][id] = score;
            s.insert(node(score, type, id));
        }
        else if (op == 2)
        {
            // cin >> type >> id;
            type = get_num(), id = get_num();
            set<node>::iterator it = s.find(node(mp[type][id], type, id));
            mp[type].erase(id);
            s.erase(it);
        }
        else
        {
            // cin >> kk;
            kk = get_num();
            for (int j = 0; j < m; j++)
                // cin >> k[j];
                k[j] = get_num();
            select();
            for (int j = 0; j < m; j++)
            {
                if (ans[j].size() == 0)
                {
                    // cout << -1 << endl;
                    // puts("-1");
                    printf("-1\n");
                    continue;
                }
                for (vector<int>::iterator it = ans[j].begin(); it != ans[j].end(); it++)
                    // cout << *it << " ";
                    printf("%d ", *it);
                // cout << endl;
                printf("\n");
            }
        }
    }
    return 0;
}