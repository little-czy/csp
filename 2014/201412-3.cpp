#include <iostream>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

double price[5005];
long long price_num[5005];
bool buy_or_sell[5005];
map<double, long long> buy, sell;
// map<long long, double> bu, se;
map<double, long long> bu, se;
set<double> price_set;

int main()
{
    char tmp_buf[64], type[32];
    int i = 1;
    long long num, count = 0;
    double ans = 0.0;
    while (fgets(tmp_buf, 64, stdin) != NULL)
    {
        if (sscanf(tmp_buf, "%s%lf%lld", type, &price[i], &price_num[i]) == 2)
        {
            if (buy_or_sell[(int)price[i]]) //buy map
            {
                map<double, long long>::iterator it = buy.find(price[(int)price[i]]);
                it->second -= price_num[(int)price[i]];
                if (it->second == 0)
                    buy.erase(it);
            }
            else //sell map
            {
                map<double, long long>::iterator it = sell.find(price[(int)price[i]]);
                it->second -= price_num[(int)price[i]];
                if (it->second == 0)
                    sell.erase(it);
            }
        }
        else
        {
            if (type[0] == 'b')
            {
                buy_or_sell[i] = 1;
                if (buy.find(price[i]) != buy.end())
                {
                    buy[price[i]] += price_num[i];
                }
                else
                {
                    buy[price[i]] = price_num[i];
                }
            }
            else
            {
                buy_or_sell[i] = 0;
                if (sell.find(price[i]) != sell.end())
                {
                    sell[price[i]] += price_num[i];
                }
                else
                {
                    sell[price[i]] = price_num[i];
                }
            }
        }
        i++;
    }
    long long buy_sum = 0, sell_sum = 0;
    for (map<double, long long>::reverse_iterator buy_it = buy.rbegin(); buy_it != buy.rend(); buy_it++)
    {
        // cout << buy_it->first << "  " << buy_it->second << endl;
        buy_sum += buy_it->second;
        // bu[buy_sum] = buy_it->first;
        bu[buy_it->first] = buy_sum;
        price_set.insert(buy_it->first);
    }
    for (map<double, long long>::iterator sell_it = sell.begin(); sell_it != sell.end(); sell_it++)
    {
        // cout << sell_it->first << "  " << sell_it->second << endl;
        sell_sum += sell_it->second;
        // se[sell_sum] = sell_it->first;
        se[sell_it->first] = sell_sum;
        price_set.insert(sell_it->first);
    }

    // for (map<double, long long>::iterator bu_it = bu.begin(); bu_it != bu.end(); bu_it++)
    // {
    //     cout << bu_it->first << "  " << bu_it->second << endl;
    // }
    long long tmp_count, sum_buy, sum_sell;
    for (set<double>::iterator pr_it = price_set.begin(); pr_it != price_set.end(); pr_it++)
    {
        sum_buy = 0;
        for (map<double, long long>::iterator bu_it = bu.begin(); bu_it != bu.end(); bu_it++)
        {
            if (bu_it->first >= *pr_it)
            {
                sum_buy = bu_it->second;
                break;
            }
        }
        sum_sell = 0;
        for (map<double, long long>::iterator se_it = se.begin(); se_it != se.end(); se_it++)
        {

            if (se_it->first <= *pr_it)
            {
                sum_sell = se_it->second;
            }
            else
            {
                break;
            }
        }
        tmp_count = sum_buy < sum_sell ? sum_buy : sum_sell;
        if (count <= tmp_count)
        {
            count = tmp_count;
            ans = *pr_it;
        }
    }
    printf("%.2lf %lld\n", ans, count);
    return 0;
}