#include <iostream>
#include <queue>
using namespace std;
typedef struct Node {  // 节点结构体
    int data;
    int childs;
    int now = 0;
    struct Node *child, *sibling;
    Node(int d, int ch)
        : data(d)
        , childs(ch)
        , child(NULL)
        , sibling(NULL) {};
} Node;

queue< Node* > Q;
Node* root;  // 根节点

void Insert() {  // 输入
    while (!Q.empty()) {
        Node* t = Q.front();
        Q.pop();
        for (int i = 0; i < t->childs; i++) {  // 输入所有的孩子
            int key, child;
            cin >> key >> child;
            Node* temp = new Node(key, child);
            if (i == 0) {  // 如果是第一个 那就是孩子节点
                t->child = temp;
            } else {  // 否则是孩子的兄弟
                Node* tp = t->child;
                for (int j = 1; j < i; j++) {
                    tp = tp->sibling;
                }
                tp->sibling = temp;
            }
            if (child)  // 如果这个节点有孩子就推如队列
                Q.push(temp);
        }
    }
}

void PreOrder(Node* t, string s) {  // 先序输出，字符串记录目前需要输出的内容
    if (t->child == NULL && t->sibling == NULL) {  // 如果孩子和兄弟都为空则输出
        cout << s + (char)(t->data + 48) << endl;
        return;
    }
    if (t->child != NULL)  // 如果孩子不为空就递归孩子
        PreOrder(t->child, s + (char)(t->data + 48) + ' ');
    if (t->sibling != NULL)  // 如果兄弟不为空就递归兄弟
        PreOrder(t->sibling, s + (char)(t->data + 48) + ' ');
};

int main() {
    int n;
    cin >> n;
    int key, child;
    cin >> key >> child;//输入第一个孩子并创建节点，推入队列
    root = new Node(key, child);
    Q.push(root);
    Insert();
    PreOrder(root, "");//输出
    return 0;
}