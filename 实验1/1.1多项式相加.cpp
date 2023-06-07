#include <iostream>
using namespace std;
int cnt = 0;
struct QNode {  // 节点结构体
    int coef;
    int expon;
    struct QNode* next;
};
typedef struct QNode* PtrToQNode;

int compare(int e1, int e2) {  // 比较两个节点的指数哪个大
    if (e1 > e2)
        return 1;
    else if (e1 == e2)
        return 0;
    else
        return -1;
}

void attach(int coef, int expon, PtrToQNode* PtrRear) {  // 把coef，expon的节点接在ptrrear后面
    PtrToQNode P;
    P = (PtrToQNode)malloc(sizeof(struct QNode));
    P->coef = coef;
    P->expon = expon;
    P->next = NULL;
    (*PtrRear)->next = P;
    *PtrRear = P;
}

PtrToQNode PolyAdd(PtrToQNode P1, PtrToQNode P2) {  // 把p1和p2相加，返回和的头指针
    PtrToQNode front, rear, temp;
    int sum;
    rear = (PtrToQNode)malloc(sizeof(struct QNode));  // 创建头节点
    front = rear;
    while (P1 && P2) {
        switch (compare(P1->expon, P2->expon)) {  // 比较
        case 1:  // p1大
            attach(P1->coef, P1->expon, &rear);
            P1 = P1->next;
            break;
        case -1:  // p2大
            attach(P2->coef, P2->expon, &rear);
            P2 = P2->next;
            break;
        case 0:  // 一样大
            sum = P1->coef + P2->coef;
            if (sum)
                attach(sum, P1->expon, &rear);
            P1 = P1->next;
            P2 = P2->next;
            break;
        }
    }
    // 结束后把没被清空的那个链表全部接在和链表的后面
    for (; P1; P1 = P1->next)
        attach(P1->coef, P1->expon, &rear);
    for (; P2; P2 = P2->next)
        attach(P2->coef, P2->expon, &rear);
    rear->next = NULL;
    temp = front;
    front = front->next;  // 头节点为无数值的节点，将其删去
    free(temp);
    return front;
}

void print(int coef, int expon) {  // 输出函数
    if (coef == 0)
        return;
    if (expon == 0) {  // 指数是0的判断
        if (cnt && coef > 0)
            cout << "+";
        cout << coef;
        cnt++;
        return;
    }
    if (coef != 1) {
        if (cnt && coef > 0)
            cout << "+";
        cout << coef;
    }
    if (expon == 1) {  // 判断是否需要"^"符号，系数是否为1
        if (coef == 1)
            cout << "+x";
        else
            cout << "x";
    } else
        cout << "x^" << expon;
    cnt++;
}

int main() {
    PtrToQNode P1, P2, P3, P1back, P2back;

    P1 = (PtrToQNode)malloc(sizeof(struct QNode));
    P2 = (PtrToQNode)malloc(sizeof(struct QNode));
    P1back = P1, P2back = P2;

    int coef, expon;
    cin >> coef >> expon;
    while (coef || expon) {  // 输入p1
        attach(coef, expon, &P1back);
        cin >> coef >> expon;
    }
    char tmp;

    cin >> tmp;  // 吸收+号
    cin >> coef >> expon;
    while (coef || expon) {  // 输入p2
        attach(coef, expon, &P2back);
        cin >> coef >> expon;
    }
    P3 = PolyAdd(P1, P2);//相加
    P3 = P3->next;
    while (P3) {//输出
        print(P3->coef, P3->expon);
        P3 = P3->next;
    }

    return 0;
}
