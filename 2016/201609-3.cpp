#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct suicong
{
    int health;
    int attack;
    suicong(int _h, int _a) : health(_h), attack(_a){};
};

int n;
vector<suicong> s1, s2;
string op;
bool huihe = 1; //当前处于谁的回合 1：先手，0：后手

int main()
{
    cin >> n;
    int sui_pos, sui_att, sui_hea;
    int attacker, defender;
    s1.push_back(suicong(30, 0));
    s2.push_back(suicong(30, 0));
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        if (op == "summon") //召唤随从
        {
            cin >> sui_pos >> sui_att >> sui_hea;
            if (huihe) //先手回合
            {
                s1.insert(s1.begin() + sui_pos, suicong(sui_hea, sui_att));
            }
            else //后手回合
            {
                s2.insert(s2.begin() + sui_pos, suicong(sui_hea, sui_att));
            }
        }
        else if (op == "attack") //随从攻击
        {
            cin >> attacker >> defender;
            if (huihe) //先手回合
            {
                s1[attacker].health -= s2[defender].attack;
                s2[defender].health -= s1[attacker].attack;
                if (attacker != 0 && s1[attacker].health <= 0)
                    s1.erase(s1.begin() + attacker);
                if (defender != 0 && s2[defender].health <= 0)
                    s2.erase(s2.begin() + defender);
            }
            else //后手回合
            {
                s2[attacker].health -= s1[defender].attack;
                s1[defender].health -= s2[attacker].attack;
                if (attacker != 0 && s2[attacker].health <= 0)
                    s2.erase(s2.begin() + attacker);
                if (defender != 0 && s1[defender].health <= 0)
                    s1.erase(s1.begin() + defender);
            }
        }
        else if (op == "end") //结束回合
        {
            huihe = !huihe;
        }
    }
    if (s1[0].health > 0 && s2[0].health > 0)
    {
        cout << 0 << endl;
    }
    else if (s1[0].health > 0)
    {
        cout << 1 << endl;
    }
    else if (s2[0].health > 0)
    {
        cout << -1 << endl;
    }
    cout << s1[0].health << endl;
    cout << s1.size() - 1;
    for (vector<suicong>::iterator it = s1.begin() + 1; it != s1.end(); it++)
        cout << " " << it->health;
    cout << endl;
    cout << s2[0].health << endl;
    cout << s2.size() - 1;
    for (vector<suicong>::iterator it = s2.begin() + 1; it != s2.end(); it++)
        cout << " " << it->health;
    cout << endl;
    return 0;
}