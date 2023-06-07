#include <iostream>
using namespace std;

void quickSort(int arr[], int left, int right) {
    int i = left, j = right;  // 记录左右范围
    int pivot = arr[i];  // 定义基准数
    if (left >= right) return;  // 如果数组长度<=1就不用排序了
    while (i < j) {  // 不断把比基准小的放在基准左边，比其大的放在右边
        while (i < j && arr[j] > pivot)
            j--;
        if (i < j) swap(arr[i++], arr[j]);
        while (i <= j && arr[i] < pivot)
            i++;
        if (i < j) swap(arr[i], arr[j--]);
    }
    int mid = i;  // 基准元素定义为中间，分开两个数组
    quickSort(arr, left, mid - 1);  // 递归快排前一半
    quickSort(arr, mid + 1, right);  // 递归快排后一半
}

int main() {
    int a[10] = { 6, 1, 2, 7, 9, 3, 4, 5, 10, 8 };
    quickSort(a, 0, 9);
    for (int i = 0; i < 10; i++) {//输出结果
        cout << a[i] << " ";
    }
    return 0;
}