#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> v;

bool should_skip(int num)
{
    if (num % k == 0 || num % 10 == k)
        return true;
    return false;
}

int main()
{
    cin >> n >> k;
    int num = 1, v_i = 0;
    for (int i = 1; i <= n; i++)
    {
        v.push_back(i);
    }
    while (v.size() != 1)
    {
        if (should_skip(num))
        {
            v.erase(v.begin() + v_i);
            if (v_i == v.size())
                v_i = 0;
        }
        else
        {
            v_i = (v_i + 1) % v.size();
        }
        num++;
    }
    cout << v[0] << endl;
    return 0;
}