#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int n;
long long m;
vector<string> s;

int main()
{
    cin >> n >> m;
    string tmp_s;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp_s;
        s.push_back(tmp_s);
    }

    return 0;
}