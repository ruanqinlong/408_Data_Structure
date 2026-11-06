
#include <bits/stdc++.h>
using namespace std;

/*
直接插入排序：
最好 O(n)，    平均 O(n^2)，最坏 O(n^2)

折半插入排序：
最好 O(nlogn)，平均 O(n^2)，最坏 O(n^2)

两者空间复杂度均为 O(1)，均为稳定排序。
*/

// 直接插入排序
void insert_sort(int a[], int len) {
    if (len <= 1) return;

    for (int i = 1; i < len; i++) {
        int temp = a[i];
        int pos = i - 1;

        // 查找插入位置
        while (pos >= 0 && a[pos] > temp) {
            pos--;
        }

        // 元素后移
        for (int j = i; j > pos + 1; j--) {
            a[j] = a[j - 1];
        }

        a[pos + 1] = temp;
    }
}

// 折半插入排序
void binary_insert_sort(int a[], int len) {
    if (len <= 1) return;

    for (int i = 1; i < len; i++) {
        int pos, temp = a[i];
        int left = 0, right = i - 1;

        // 折半查找插入位置
        while (left <= right) {
            pos = (left + right) / 2;

            if (a[pos] > temp) {
                right = pos - 1;
            } else {
                left = pos + 1;
            }
        }

        // 元素后移
        for (int j = i; j > left; j--) {
            a[j] = a[j - 1];
        }

        a[left] = temp;
    }
}

// 输出数组
void print_array(int a[], int len) {
    for (int i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int a[] = {8, 3, 5, 1, 9, 2, 5, 7};
    int len = sizeof(a) / sizeof(a[0]);

    int b[8];
    copy(a, a + len, b);

    cout << "原始数组：";
    print_array(a, len);

    insert_sort(a, len);
    cout << "直接插入排序：";
    print_array(a, len);

    binary_insert_sort(b, len);
    cout << "折半插入排序：";
    print_array(b, len);

    return 0;
}
