#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int get_mon_num(int y, int m);
int get_week(int y, int m, int d);

enum MON
{
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

enum WEEK
{
    Sun = 0,
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat
};

struct _command
{
    bool min[60];
    bool h[24];
    bool dm[32];
    bool mon[13];
    bool week[7];
    string command;

    void all_min()
    {
        for (int i = 0; i < 60; i++)
            min[i] = true;
    }
    void all_min(int x)
    {
        min[x] = true;
    }
    void all_min(int x, int y)
    {
        for (int i = x; i <= y; i++)
            min[i] = true;
    }

    void all_hour()
    {
        for (int i = 0; i < 24; i++)
            h[i] = true;
    }
    void all_hour(int x)
    {
        h[x] = true;
    }
    void all_hour(int x, int y)
    {
        for (int i = x; i <= y; i++)
            h[i] = true;
    }

    void all_dm()
    {
        for (int i = 0; i < 32; i++)
            dm[i] = true;
    }
    void all_dm(int x)
    {
        dm[x] = true;
    }
    void all_dm(int x, int y)
    {
        for (int i = x; i <= y; i++)
            dm[i] = true;
    }

    void all_mon()
    {
        for (int i = 0; i < 13; i++)
            mon[i] = true;
    }
    void all_mon(int x)
    {
        mon[x] = true;
    }
    void all_mon(int x, int y)
    {
        for (int i = x; i <= y; i++)
            mon[i] = true;
    }

    void all_week()
    {
        for (int i = 0; i < 7; i++)
            week[i] = true;
    }
    void all_week(int x)
    {
        week[x] = true;
    }
    void all_week(int x, int y)
    {
        for (int i = x; i <= y; i++)
            week[i] = true;
    }

    bool shouldDoCommand(int _min, int _h, int _dm, int _mon, int _week) //判断某个时间是否需要执行该命令
    {
        return min[_min] && h[_h] && dm[_dm] && mon[_mon] && week[_week];
    }
} com[25];

struct _time
{
    int year, month, day, hour, minute;
    int week;

    void increace()
    {
        if (minute < 59)
            minute++;
        else
        {
            minute = 0;
            if (hour < 23)
                hour++;
            else
            {
                hour = 0;
                week = (week + 1) % 7;
                if (day < get_mon_num(year, month))
                    day++;
                else
                {
                    day = 1;
                    if (month < 12)
                        month++;
                    else
                    {
                        month = 1;
                        year++;
                    }
                }
            }
        }
    }

    bool operator==(_time &x)
    {
        return x.year == year && x.month == month && x.day == day && x.hour == hour && minute == x.minute && x.week == week;
    }
} start, ter;

int n;
string s, t;
map<string, int> mon, week;
int mon_num[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get_mon_num(int y, int m)
{
    if (m == 2 && (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))) //2月且闰年
        return 29;
    return mon_num[m];
}

bool runnian(int y) //闰年
{
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int get_week(int y, int m, int d)
{
    int sum_day = 0;
    for (int i = 1970; i < y; i++)
    {
        if (runnian(i))
            sum_day += 366;
        else
            sum_day += 365;
    }
    for (int i = 1; i < m; i++)
    {
        sum_day += get_mon_num(y, i);
    }
    sum_day += d;
    return (sum_day + 3) % 7;
}

void init_mon_week()
{
    mon["jan"] = Jan, mon["feb"] = Feb, mon["mar"] = Mar, mon["apr"] = Apr;
    mon["may"] = May, mon["jun"] = Jun, mon["jul"] = Jul, mon["aug"] = Aug;
    mon["sep"] = Sep, mon["oct"] = Oct, mon["nov"] = Nov, mon["dec"] = Dec;
    week["sun"] = Sun, week["mon"] = Mon, week["tue"] = Tue, week["wed"] = Wed;
    week["thu"] = Thu, week["fri"] = Fri, week["sat"] = Sat;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            com[i].min[j] = false;
        }
        for (int j = 0; j < 24; j++)
        {
            com[i].h[j] = false;
        }
        for (int j = 0; j < 32; j++)
        {
            com[i].dm[j] = false;
        }
        for (int j = 0; j < 13; j++)
        {
            com[i].mon[j] = false;
        }
        for (int j = 0; j < 7; j++)
        {
            com[i].week[j] = false;
        }
    }
}

int main()
{

    cin >> n >> s >> t;
    string tmp, ttmp;
    int point_pos;
    init_mon_week();
    for (int i = 0; i < n; i++) //命令行解析
    {
        //min解析
        cin >> tmp;
        while ((point_pos = tmp.find(",")) != string::npos)
        {
            ttmp = tmp.substr(0, point_pos);
            if (ttmp == "*")
                com[i].all_min();
            else if (ttmp[0] <= '9' && ttmp[0] >= '0') //该项为数字
            {
                int gang_pos = ttmp.find("-");
                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_min(atoi(ttmp.c_str()));
                    cout << atoi(tmp.c_str()) << endl;
                }
                else //是范围
                {
                    int begin = atoi(ttmp.substr(0, gang_pos).c_str());
                    int end = atoi(ttmp.substr(gang_pos + 1).c_str());
                    com[i].all_min(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }
            tmp = tmp.substr(point_pos + 1);
        }
        if (tmp == "*")
            com[i].all_min();
        else if (tmp[0] <= '9' && tmp[0] >= '0') //该项为数字
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_min(atoi(tmp.c_str()));
                // cout << atoi(tmp.c_str()) << endl;
            }
            else //是范围
            {
                int begin = atoi(tmp.substr(0, gang_pos).c_str());
                int end = atoi(tmp.substr(gang_pos + 1).c_str());
                com[i].all_min(begin, end);
                // cout << begin << "  " << end << endl;
            }
        }
        //hour解析
        cin >> tmp;
        while ((point_pos = tmp.find(",")) != string::npos)
        {
            ttmp = tmp.substr(0, point_pos);
            if (ttmp == "*")
                com[i].all_hour();
            else if (ttmp[0] <= '9' && ttmp[0] >= '0') //该项为数字
            {
                int gang_pos = ttmp.find("-");
                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_hour(atoi(ttmp.c_str()));
                    // cout << atoi(tmp.c_str()) << endl;
                }
                else //是范围
                {
                    int begin = atoi(ttmp.substr(0, gang_pos).c_str());
                    int end = atoi(ttmp.substr(gang_pos + 1).c_str());
                    com[i].all_hour(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }
            tmp = tmp.substr(point_pos + 1);
        }
        if (tmp == "*")
            com[i].all_hour();
        else if (tmp[0] <= '9' && tmp[0] >= '0') //该项为数字
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_hour(atoi(tmp.c_str()));
                // cout << atoi(tmp.c_str()) << endl;
            }
            else //是范围
            {
                int begin = atoi(tmp.substr(0, gang_pos).c_str());
                int end = atoi(tmp.substr(gang_pos + 1).c_str());
                com[i].all_hour(begin, end);
                // cout << begin << "  " << end << endl;
            }
        }
        //day of month解析
        cin >> tmp;
        while ((point_pos = tmp.find(",")) != string::npos)
        {
            ttmp = tmp.substr(0, point_pos);
            if (ttmp == "*")
                com[i].all_dm();
            else if (ttmp[0] <= '9' && ttmp[0] >= '0') //该项为数字
            {
                int gang_pos = ttmp.find("-");
                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_dm(atoi(ttmp.c_str()));
                    // cout << atoi(tmp.c_str()) << endl;
                }
                else //是范围
                {
                    int begin = atoi(ttmp.substr(0, gang_pos).c_str());
                    int end = atoi(ttmp.substr(gang_pos + 1).c_str());
                    com[i].all_dm(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }
            tmp = tmp.substr(point_pos + 1);
        }
        if (tmp == "*")
            com[i].all_dm();
        else if (tmp[0] <= '9' && tmp[0] >= '0') //该项为数字
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_dm(atoi(tmp.c_str()));
                // cout << atoi(tmp.c_str()) << endl;
            }
            else //是范围
            {
                int begin = atoi(tmp.substr(0, gang_pos).c_str());
                int end = atoi(tmp.substr(gang_pos + 1).c_str());
                com[i].all_dm(begin, end);
                // cout << begin << "  " << end << endl;
            }
        }
        //month解析
        cin >> tmp;
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower); //转小写
        while ((point_pos = tmp.find(",")) != string::npos)
        {
            ttmp = tmp.substr(0, point_pos);
            if (ttmp == "*")
                com[i].all_mon();
            else if (ttmp[0] <= '9' && ttmp[0] >= '0') //该项为数字
            {
                int gang_pos = ttmp.find("-");
                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_mon(atoi(ttmp.c_str()));
                    // cout << atoi(tmp.c_str()) << endl;
                }
                else //是范围
                {
                    int begin = atoi(ttmp.substr(0, gang_pos).c_str());
                    int end = atoi(ttmp.substr(gang_pos + 1).c_str());
                    com[i].all_mon(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }
            else //英文缩写
            {
                int gang_pos = ttmp.find("-");

                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_mon(mon[ttmp]);
                    // cout << mon[ttmp] << endl;
                }
                else //是范围
                {
                    int begin = mon[ttmp.substr(0, gang_pos)];
                    int end = mon[ttmp.substr(gang_pos + 1)];
                    com[i].all_mon(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }

            tmp = tmp.substr(point_pos + 1);
        }
        // cout << "tmp: " << tmp << endl;
        if (tmp == "*")
            com[i].all_mon();
        else if (tmp[0] <= '9' && tmp[0] >= '0') //该项为数字
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_mon(atoi(tmp.c_str()));
                // cout << "num1" << atoi(tmp.c_str()) << endl;
            }
            else //是范围
            {
                int begin = atoi(tmp.substr(0, gang_pos).c_str());
                int end = atoi(tmp.substr(gang_pos + 1).c_str());
                com[i].all_mon(begin, end);
                // cout << begin << "++" << end << endl;
            }
        }
        else //英文缩写
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_mon(mon[tmp]);
                // cout << "num2" << mon[tmp] << endl;
            }
            else //是范围
            {
                int begin = mon[tmp.substr(0, gang_pos)];
                int end = mon[tmp.substr(gang_pos + 1)];
                com[i].all_mon(begin, end);
                // cout << begin << "--" << end << endl;
            }
        }
        //week解析
        cin >> tmp;
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower); //转小写
        while ((point_pos = tmp.find(",")) != string::npos)
        {
            ttmp = tmp.substr(0, point_pos);
            if (ttmp == "*")
                com[i].all_week();
            else if (ttmp[0] <= '9' && ttmp[0] >= '0') //该项为数字
            {
                int gang_pos = ttmp.find("-");
                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_week(atoi(ttmp.c_str()));
                    // cout << atoi(tmp.c_str()) << endl;
                }
                else //是范围
                {
                    int begin = atoi(ttmp.substr(0, gang_pos).c_str());
                    int end = atoi(ttmp.substr(gang_pos + 1).c_str());
                    com[i].all_week(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }
            else //英文缩写
            {
                int gang_pos = ttmp.find("-");
                if (gang_pos == string::npos) //不是范围
                {
                    com[i].all_week(week[ttmp]);
                    // cout << week[ttmp] << endl;
                }
                else //是范围
                {
                    int begin = week[ttmp.substr(0, gang_pos)];
                    int end = week[ttmp.substr(gang_pos + 1)];
                    com[i].all_week(begin, end);
                    // cout << begin << "  " << end << endl;
                }
            }

            tmp = tmp.substr(point_pos + 1);
        }
        if (tmp == "*")
            com[i].all_week();
        else if (tmp[0] <= '9' && tmp[0] >= '0') //该项为数字
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_week(atoi(tmp.c_str()));
                // cout << atoi(tmp.c_str()) << endl;
            }
            else //是范围
            {
                int begin = atoi(tmp.substr(0, gang_pos).c_str());
                int end = atoi(tmp.substr(gang_pos + 1).c_str());
                com[i].all_week(begin, end);
                // cout << begin << "  " << end << endl;
            }
        }
        else //英文缩写
        {
            int gang_pos = tmp.find("-");
            if (gang_pos == string::npos) //不是范围
            {
                com[i].all_week(week[tmp]);
                // cout << week[tmp] << endl;
            }
            else //是范围
            {
                int begin = week[tmp.substr(0, gang_pos)];
                int end = week[tmp.substr(gang_pos + 1)];
                com[i].all_week(begin, end);
                // cout << begin << "  " << end << endl;
            }
        }
        cin >> com[i].command;
    }

    int y, m, d, h, mint;
    string tmp_s = s.substr(0, 4);
    y = atoi(tmp_s.c_str());
    tmp_s = s.substr(4, 2);
    m = atoi(tmp_s.c_str());
    tmp_s = s.substr(6, 2);
    d = atoi(tmp_s.c_str());
    tmp_s = s.substr(8, 2);
    h = atoi(tmp_s.c_str());
    tmp_s = s.substr(10, 2);
    mint = atoi(tmp_s.c_str());
    start.year = y, start.month = m, start.day = d, start.hour = h, start.minute = mint;
    start.week = get_week(y, m, d);
    // cout << y << " " << m << " " << d << " " << h << " " << mint << " " << start.week << endl;
    tmp_s = t.substr(0, 4);
    y = atoi(tmp_s.c_str());
    tmp_s = t.substr(4, 2);
    m = atoi(tmp_s.c_str());
    tmp_s = t.substr(6, 2);
    d = atoi(tmp_s.c_str());
    tmp_s = t.substr(8, 2);
    h = atoi(tmp_s.c_str());
    tmp_s = t.substr(10, 2);
    mint = atoi(tmp_s.c_str());
    ter.year = y, ter.month = m, ter.day = d, ter.hour = h, ter.minute = mint;
    ter.week = get_week(y, m, d);
    // cout << y << " " << m << " " << d << " " << h << " " << mint << " " << ter.week << endl;
    while (!(start == ter))
    {
        for (int i = 0; i < n; i++)
        {
            if (com[i].shouldDoCommand(start.minute, start.hour, start.day, start.month, start.week))
                printf("%d%02d%02d%02d%02d %s\n", start.year, start.month, start.day, start.hour, start.minute, com[i].command.c_str());
        }
        start.increace();
    }
    // cout << endl
    //      << get_week(y, m, d) << endl;
    // cout << sizeof(bool) << endl;
    return 0;
}