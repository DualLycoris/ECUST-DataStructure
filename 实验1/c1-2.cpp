#include <bits/stdc++.h>
using namespace std;
int n;
char tmp[1000], pre[30], aft[30];  // 用数组模拟栈
int vis[30];
string s;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)  // 输入进栈顺序
        cin >> pre[i];
    for (int i = 0; i < n; i++)  // 输入出栈顺序
        cin >> aft[i];
    int cnt = 0, que = 0, afcnt = 0;  // 记录输入的位置、栈内数量、出栈到第几个
    while (afcnt != n) {
        if (vis[aft[afcnt] - 'A']) {  // 如果需要出栈的已经入栈，则看能够出栈
            if (tmp[que - 1] != aft[afcnt]) {  // 如果不能出栈，说明不能达成
                cout << "0" << endl;
                return 0;
            } else {  // 否则出栈
                s += tmp[que - 1];
                s += "_out ";
                que--;
                afcnt++;
                continue;
            }
        }
        // 如果下一个元素没被入栈，则不断入栈直到下一个出栈的元素被入栈
        while (pre[cnt] != aft[afcnt]) {
            tmp[que++] = pre[cnt++];
            vis[tmp[que - 1] - 'A']++;
            s += tmp[que - 1];
            s += "_in ";
        }
        s += pre[cnt];
        s += "_in ";
        s += pre[cnt];
        s += "_out ";
        cnt++, afcnt++;
    }
    // cout << afcnt << endl;
    if (afcnt != n) {//判断是否真的完成出栈
        cout << 0 << endl;
        return 0;
    }
    cout << 1 << endl;//输出1，和储存的出入栈记录s
    cout << s << endl;
    return 0;
}