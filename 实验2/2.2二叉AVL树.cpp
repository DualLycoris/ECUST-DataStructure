#include <iostream>
using namespace std;

typedef struct BitNode {  // 树的节点
    int data, height;
    struct BitNode *l, *r;
    BitNode(int d)
        : data(d)
        , height(0)
        , l(NULL)
        , r(NULL) {
    }
} BitNode, *BitTree;

int GetHeight(BitNode* Node);
BitNode* LL(BitNode* Node);
BitNode* RR(BitNode* Node);
BitNode* LR(BitNode* Node);
BitNode* RL(BitNode* Node);

void Print(BitTree T) {  // 先序输出
    // T = (BitTree)malloc(sizeof(BitNode));
    if (T == NULL) {
        cout << "# ";
        return;
    } else {
        cout << T->data << ' ';
        Print(T->l);
        Print(T->r);
    }
    return;
}

BitNode* Insert(BitNode* Node, int key) {  // 插入并平衡树
    if (Node == NULL) {  // 如果本节点为空，直接创建
        Node = new BitNode(key);
        Node->height = 0;
    } else if (key < Node->data) {  // 如果比本节点小放左边，递归插入
        Node->l = Insert(Node->l, key);
        if (GetHeight(Node->l) - GetHeight(Node->r) == 2) {
            // 判断是否还是平衡的，因为插入左边左边更容易失衡
            if (key < Node->l->data) {
                Node = LL(Node);  // LL旋转
            } else {
                Node = LR(Node);  // LR旋转
            }
        }
    } else {  // 如果比本节点大放右边，递归插入
        Node->r = Insert(Node->r, key);
        if (GetHeight(Node->r) - GetHeight(Node->l) == 2) {
            // 判断是否还是平衡的
            if (key > Node->r->data) {
                Node = RR(Node);  // RR旋转
            } else {
                Node = RL(Node);  // RL旋转
            }
        }
    }
    Node->height = max(GetHeight(Node->l), GetHeight(Node->r)) + 1;  // 更新高度
    return Node;
}

int GetHeight(BitNode* node) {
    return node != NULL ? node->height : 0;
}

BitNode* LL(BitNode* Node) {  // LL旋转
    BitNode* tmp = Node->l;
    Node->l = tmp->r;
    tmp->r = Node;
    Node->height = max(GetHeight(Node->l), GetHeight(Node->r)) + 1;
    tmp->height = max(GetHeight(tmp->l), Node->height) + 1;
    return tmp;
}

BitNode* RR(BitNode* Node) {  // RR旋转
    BitNode* tmp = Node->r;
    Node->r = tmp->l;
    tmp->l = Node;
    Node->height = max(GetHeight(Node->l), GetHeight(Node->r)) + 1;
    tmp->height = max(GetHeight(tmp->r), Node->height) + 1;
    return tmp;
}

BitNode* LR(BitNode* Node) {  // LR旋转，只要先对其左节点右旋，后对其左旋
    Node->l = RR(Node->l);
    return LL(Node);
}

BitNode* RL(BitNode* Node) {  // RL旋转，只要先对其右节点左旋，后对其右旋
    Node->r = LL(Node->r);
    return RR(Node);
}

int main() {
    int n, tmp;
    cin >> n;
    BitTree T = NULL;
    for (int i = 0; i < n; i++) {//输入并插入
        cin >> tmp;
        T = Insert(T, tmp);
    }
    Print(T);
    return 0;
}