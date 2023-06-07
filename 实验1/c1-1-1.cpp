#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
queue<pii> q1;
queue<pii> q2;
int cnt = 0;

int main()
{
    int n, m;
    cin >> n >> m;
    while (n | m) {
        q1.push(make_pair(n, m));
        cin >> n >> m;
    }
    cin >> n >> m;
    while (n | m) {
        q2.push(make_pair(n, m));
        cin >> n >> m;
    }
    q1.push(make_pair(0, -1));
    q2.push(make_pair(0, -1));
    while (!q1.empty() || !q2.empty()) {
        int a = q1.front().first;
        int b = q1.front().second;
        int c = q2.front().first;
        int d = q2.front().second;
        if (b == -1 && d == -1)
            break;
        if (b == d) {
            int tmp = a + c;
            if (tmp == 0) {
                q1.pop(), q2.pop();
                continue;
            }
            if (b == 0) {
                q1.pop(), q2.pop();
                if (cnt && tmp > 0)
                    cout << "+";
                cout << tmp;
                cnt++;
                continue;
            }
            if (tmp != 1) {
                if (cnt && tmp > 0)
                    cout << "+";
                cout << tmp;
            }
            if (b == 1)
                cout << "x";
            else
                cout << "x^" << b;
            q1.pop(), q2.pop();
            cnt++;
            continue;
        }
        if (b > d)
            q1.pop();
        else {
            q2.pop();
            b = d, a = c;
        }
        if (a == 0)
            continue;
        if (b == 0) {
            if (cnt && a > 0)
                cout << "+";
            cout << a;
            cnt++;
            continue;
        }
        if (a != 1) {
            if (cnt && a > 0)
                cout << "+";
            cout << a;
        }
        if (b == 1)
            cout << "x";
        else
            cout << "x^" << b;
        cnt++;
    }
    return 0;
}
