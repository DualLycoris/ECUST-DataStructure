#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

typedef struct AdjNode {  // 联通节点
    int data;
    struct AdjNode* next = NULL;
    AdjNode(int a)
        : data(a)
        , next(NULL) {};
} AdjNode;

typedef struct Gnode {  // 图
    int Nodes;
    int sides;
    AdjNode* mp[10010];
    Gnode(int a, int b)
        : Nodes(a)
        , sides(b) {};
} Gnode;

Gnode* Gn;

Gnode* CreateGraph(int nodes, int sides) {  // 初始化图和边
    Gnode* temp = new Gnode(nodes, sides);
    for (int i = 0; i < nodes + 1; ++i) {
        temp->mp[i] = new AdjNode(-1);
    }
    return temp;
};

void input(int a, int b) {  // 输入边
    AdjNode *tmp1 = new AdjNode(b), *tmp2 = new AdjNode(a);
    AdjNode *ahead = Gn->mp[a], *bhead = Gn->mp[b];
    while (ahead->next != NULL && ahead->next->data < b)
        ahead = ahead->next;
    tmp1->next = ahead->next, ahead->next = tmp1;

    while (bhead->next != NULL && bhead->next->data < a)
        bhead = bhead->next;
    tmp2->next = bhead->next, bhead->next = tmp2;
    return;
}

double bfs(int key) {  // 使用广搜搜索所有联通的节点
    queue< int > q;
    int vis[10010] = { 0 }, now = 1, cnt = 0, ans = 0;
    /*
    初始化访问数组，now目前搜到最少需要now条边与所求点联通
    cnt为联通点的计数器，ans为计算∑d(i,j)
    */
    vis[key] = 1;  // 把本体排除，避免被计入
    if (Gn->mp[key]->next == NULL) return 0;  // 判断是否是孤立的点

    q.push(key);  // 使用队列搜索
    queue< int > q1;  // 需要now+1次到达key的点的队列
    while (!q.empty()) {
        int tdata = q.front();
        AdjNode* tmp = Gn->mp[tdata]->next;
        q.pop();
        while (tmp != NULL) {
            if (!vis[tmp->data]) {  // 未被搜索过就把它输入下一个搜索的队列
                vis[tmp->data] = now;
                q1.push(tmp->data);
                cnt++;
                ans += now;
            }
            tmp = tmp->next;
        }
        if (q.empty()) {
            // 如果队列是空，把now+1的队列给now，清空now+1队列，now自增
            q = q1;
            q1 = queue< int >();
            now++;
        }
    }
    return (double)cnt / 1.0 / ans;  // 返回结果
}

int main() {
    int nodes, sides, a, b;
    cin >> nodes >> sides;
    Gn = CreateGraph(nodes, sides);  // 创建图
    for (int i = 0; i < sides; ++i) {  // 输入边
        cin >> a >> b;
        input(a, b);
    }
    int num;
    cin >> num;
    for (int i = 0; i < num; ++i) {//输入需要求的节点
        cin >> a;
        printf("Cc(%d)=%.2lf\n", a, bfs(a));
    }
    return 0;
}