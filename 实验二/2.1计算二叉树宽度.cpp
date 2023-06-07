#include <cstdlib>
#include <iostream>
using namespace std;
int cnt[15];
void Count(int depth) {
    char ch;
    cin >> ch;
    if (ch == '#')
        return;
    else {
        cnt[depth]++;
        Count(depth + 1);
        Count(depth + 1);
    }
}
int main() {
    Count(1);
    int ans = 0;
    for (int i = 0; i < 15; ++i) {
        if (ans < cnt[i]) ans = cnt[i];
    }
    cout << ans << endl;
}