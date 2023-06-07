#include <iostream>
#include <queue>
using namespace std;

typedef struct Node {  // 节点结构体
    char data;
    int ltag, rtag;
    Node *left, *right;
    Node(char data)
        : data(data)
        , ltag(0)
        , rtag(0)
        , left(NULL)
        , right(NULL) {};
} ThreadNode;

void addThreadTree(Node* root1, Node* root2)  // 把两个树拼接
{
    if (root1->left == NULL) {
        // 如果A树没有左孩子，那么直接接上并且把B的后驱设置为A就行了
        root1->left = root2;
        root2->right = root1;
        root2->rtag = 1;
        return;
    } else {
        // 否则只要把B接在A左边，把原来A的左接在B右即可
        root2->right = root1->left;
        root1->left = root2;
    }
}

void inOrderThreadTree(Node* root)  // 输出
{
    if (root == NULL)
        return;
    if (root->ltag == 0)
        inOrderThreadTree(root->left);
    cout << root->data;
    if (root->rtag == 0)
        inOrderThreadTree(root->right);
}

int main() {
    Node* root1 = new Node('A');
    Node* root2 = new Node('D');
    root1->left = new Node('B');
    root1->left->right = new Node('C');
    root1->left->right->rtag = 1;
    root1->left->right->right = root1;
    root2->left = new Node('E');
    root2->left->left = new Node('F');
    root2->left->rtag = 1;
    root2->left->right = root2;
    root2->left->left->rtag = 1;
    root2->left->left->right = root2->left;
    // 手动创建好需要相加的两个树
    inOrderThreadTree(root1);
    cout << endl;
    inOrderThreadTree(root2);
    cout << endl;
    //输出两个树
    addThreadTree(root1, root2);
    inOrderThreadTree(root1);
    //输出和树
    cout << endl;
    return 0;
}