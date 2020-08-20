#include <iostream>

using namespace std;

struct s{
    int a, b;
    bool flag;
}h[2001];

struct t{
    int c, d;
    bool flag;
}w[2001];


int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        h[i].flag = true;
        cin >> h[i].a >> h[i].b;
    }
    for (int i = 0; i < n; i++){
        w[i].flag = true;
        cin >> w[i].c >> w[i].d;
    }
    int i, j;
    i = j = 0;
    int total_time = 0;
    while (i < n && j < n){
        if (h[i].a <= w[j].c && h[i].b >= w[j].d) {
            total_time = total_time + (w[j].d - w[j].c);
            j++;
        } else if (h[i].b <= w[j].c) {
            i++;
        } else if (h[i].a <= w[j].c && h[i].b >= w[j].c && h[i].b <= w[j].d) {
            total_time = total_time + (h[i].b - w[j].c);
            i++;
        } else if (h[i].a >= w[j].c && h[i].b <= w[j].d) {
            total_time = total_time + (h[i].b - h[i].a);
            i++;
        } else if (h[i].a >= w[j].c && h[i].a <= w[j].d && h[i].b >= w[j].d) {
            total_time = total_time + (w[j].d - h[i].a);
            j++;
        } else if ( h[i].a >= w[j].d) {
            j++;
        }
    }
    cout << total_time << endl;
    //system("pause");
    return 0;
}