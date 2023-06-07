#include <cstdlib>
#include <iostream>
#include <math.h>
#include <queue>
using namespace std;

typedef struct BitNode {  // 节点结构体
    char data;
    struct BitNode *l, *r;
} BitNode, *BitTree;

BitTree CreateBiTree()  // 先序创建树
{
    char ch;
    cin >> ch;
    BitNode* T;
    if (ch == '#')
        T = NULL;
    else {
        T = (BitTree)malloc(sizeof(BitNode));
        T->data = ch;
        T->l = CreateBiTree();
        T->r = CreateBiTree();
    }
    return T;
}

int Width(BitTree bt)  // 求宽度
{
    if (bt == NULL)  // 空树直接返回
        return 0;
    else {
        int w = 1;  // 第一层有1个
        queue< BitNode* > q, tmp;  // 两个队列，一个记录本层一个记录下一层
        q.push(bt);
        while (!q.empty()) {
            BitNode* t = q.front();
            q.pop();
            if (t->l != NULL)
                tmp.push(t->l);
            if (t->r != NULL)
                tmp.push(t->r);
            if (q.empty()) {  // 如果本层空，把下一层复制给本层，清空下一层
                w = max(w, (int)tmp.size());
                q = tmp;
                while (!tmp.empty())
                    tmp.pop();
            }
        }
        return w;
    }
}

int main()
{
    BitTree T;
    T = CreateBiTree();
    cout << Width(T) << endl;
    return 0;
}