#include <iostream>
#include <stack>

using namespace std;

int n;
stack<char> sign;
stack<int> num;

int main()
{
    int a;
    char c;
    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        num.push(a);
        for (int j = 0; j < 3; j++)
        {
            cin >> c >> a;
            if (c == '+' || c == '-')
            {
                if (!sign.empty())
                {
                    int tmp1 = num.top();
                    num.pop();
                    int tmp2 = num.top();
                    if (sign.top() == '+')
                        num.push(tmp1 + tmp2);
                    else
                        num.push(tmp2 - tmp1);
                    sign.pop();
                }
                sign.push(c), num.push(a);
            }
            else if (c == 'x')
            {
                int tmp = num.top();
                num.pop();
                num.push(tmp * a);
            }
            else if (c == '/')
            {
                int tmp = num.top();
                num.pop();
                num.push(tmp / a);
            }
        }
        if (!sign.empty())
        {
            int tmp1 = num.top();
            num.pop();
            int tmp2 = num.top();
            if (sign.top() == '+')
                num.push(tmp1 + tmp2);
            else
                num.push(tmp2 - tmp1);
            sign.pop();
        }
        if (num.top() == 24)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        num.pop();
    }
    return 0;
}