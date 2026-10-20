/*
 * 折半查找（二分查找，Binary Search）
 * 前提条件：顺序存储，关键字有序（这里按升序）
 *
 * 时间复杂度：
 *   最好：O(1)
 *   最坏：O(log₂n)
 *   平均：O(log₂n)
 *
 * 空间复杂度：O(1)（非递归实现）
 *
 * 返回值：
 *   查找成功：返回元素下标
 *   查找失败：返回 -1
 */
#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 50

// 顺序表
struct STable {
    int data[MAX_SIZE];
    int len;
};

int Binary_Search(STable *s, int key) {
    int left = 0;
    int right = s->len-1;

    int mid; 

    while(left<=right){
        mid = (right-left)/2+left;
        if(s->data[mid]>key){
            right = mid -1;
        }else if(s->data[mid]<key){
            left = mid + 1;
        }else{
            return mid;
        }
    }
    return -1;
}

// 测试
int main() {
    STable s = {{3, 8, 12, 19, 23, 30, 35, 46, 54, 67}, 10};

    cout << "序号：";
    for (int i = 0; i < s.len; i++)
        cout << setw(5) << i;
    cout << endl;

    cout << "数据：";
    for (int i = 0; i < s.len; i++)
        cout << setw(5) << s.data[i];
    cout << endl;

    int key;
    cout << "请输入待查找的值：";
    cin >> key;

    int pos = Binary_Search(&s, key);

    if (pos == -1)
        cout << "查找失败，元素不存在！" << endl;
    else
        cout << "查找成功，序号为：" << pos << endl;

    return 0;
}