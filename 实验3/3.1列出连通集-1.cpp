#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
int dfvis[50], bfvis[50];
priority_queue< int, vector< int >, greater< int > > node[50];

void dfs(int now) {
    priority_queue< int, vector< int >, greater< int > > q = node[now];
    while (!q.empty()) {
        if (!dfvis[q.top()]) {
            dfvis[q.top()] = 1;
            cout << "," << q.top();
            dfs(q.top());
        }
        q.pop();
    }
}

void bfs(int i) {
    queue< int > q;
    q.push(i);
    while (!q.empty()) {
        int tmp = q.front();
        priority_queue< int, vector< int >, greater< int > > tmpq = node[tmp];
        while (!tmpq.empty()) {
            if (!bfvis[tmpq.top()]) {
                bfvis[tmpq.top()] = 1;
                cout << "," << tmpq.top();
                q.push(tmpq.top());
            }
            tmpq.pop();
        }
        q.pop();
    }
}

int main() {
    int nodes, sides, a, b;
    cin >> nodes >> sides;
    for (int i = 0; i < sides; ++i) {
        cin >> a >> b;
        node[a].push(b), node[b].push(a);
    }
    for (int i = 0; i < nodes; ++i) {
        if (!dfvis[i]) {
            dfvis[i] = 1;
            cout << "{" << i;
            dfs(i);
            cout << "}" << endl;
        }
    }
    for (int i = 0; i < nodes; ++i) {
        if (!bfvis[i]) {
            bfvis[i] = 1;
            cout << "{" << i;
            bfs(i);
            cout << "}" << endl;
        }
    }
}