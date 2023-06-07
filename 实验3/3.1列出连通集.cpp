#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
int vis[150];
typedef struct AdjNode {  // 边的结构体
    int data;
    struct AdjNode* next = NULL;
    AdjNode(int a)
        : data(a)
        , next(NULL) {};
} AdjNode;

typedef struct Gnode {  // 图的结构体
    int Nodes;
    int sides;
    AdjNode* mp[100];
    Gnode(int a, int b)
        : Nodes(a)
        , sides(b) {};
} Gnode;

Gnode* Gn;  // 图的指针

Gnode* CreateGraph(int nodes, int sides) {  // 创建nodes,sizes数量的图
    Gnode* temp = new Gnode(nodes, sides);
    for (int i = 0; i < nodes; ++i) {  // 初始化边为-1，便于排序
        temp->mp[i] = new AdjNode(-1);
    }
    return temp;
};

void input(int a, int b) {  // 构建a与b的边
    AdjNode *tmp1 = new AdjNode(b), *tmp2 = new AdjNode(a);  // 创建临时节点
    AdjNode *ahead = Gn->mp[a], *bhead = Gn->mp[b];
    while (ahead->next != NULL && ahead->next->data < b)  // 找到b应该放的位置，满足联通的节点编号递增排序
        ahead = ahead->next;
    tmp1->next = ahead->next, ahead->next = tmp1;

    while (bhead->next != NULL && bhead->next->data < a)  // 找到a应该放的位置，满足联通的节点编号递增排序
        bhead = bhead->next;
    tmp2->next = bhead->next, bhead->next = tmp2;
    return;
}

void dfs(int now) {  // 深搜
    AdjNode* tmp = Gn->mp[now]->next;  // 去掉空的头节点
    while (tmp != NULL) {
        if (!vis[tmp->data]) {  // 判断是否搜索过
            vis[tmp->data] = 1;
            cout << "," << tmp->data;
            dfs(tmp->data);
        }
        tmp = tmp->next;
    }
}

void bfs(int key) {  // 广搜，用队列
    queue< int > q;
    q.push(key);
    while (!q.empty()) {
        int tdata = q.front();
        AdjNode* tmp = Gn->mp[tdata]->next;
        q.pop();
        while (tmp != NULL) {
            if (!vis[tmp->data]) {  // 判断是否已经搜索过
                vis[tmp->data] = 1;
                cout << "," << tmp->data;
                q.push(tmp->data);
            }
            tmp = tmp->next;
        }
    }
}

int main() {
    int nodes, sides, a, b;
    cin >> nodes >> sides;
    Gn = CreateGraph(nodes, sides);
    for (int i = 0; i < sides; ++i) {  // 输入边
        cin >> a >> b;
        input(a, b);
    }
    for (int i = 0; i < nodes; ++i) {  // 深搜，搜完一个联通分量后找下一个没被搜到的点
        if (!vis[i]) {
            vis[i] = 1;
            cout << "{" << i;
            dfs(i);
            cout << "}" << endl;
        }
    }
    memset(vis, 0, sizeof(vis));  // 再次初始化vis数组
    for (int i = 0; i < nodes; ++i) {  // 广搜，搜完一个联通分量后找下一个没被搜到的点
        if (!vis[i]) {
            vis[i] = 1;
            cout << "{" << i;
            bfs(i);
            cout << "}" << endl;
        }
    }
    return 0;
}