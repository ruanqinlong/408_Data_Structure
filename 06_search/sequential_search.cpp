/*
 * 顺序查找（Sequential Search）
 *
 * 存储结构：顺序表（数组）
 * 适用条件：有序表、无序表均可
 *
 * 时间复杂度：
 *   最好情况：O(1)
 *   最坏情况：O(n)
 *   平均情况：O(n)
 *
 * 空间复杂度：O(1)（查找算法的辅助空间）
 *
 * 平均查找长度 ASL：
 *
 * 1. 查找成功
 *    假设每个元素被查找的概率相等：
 *
 *    ASL成功 = (1+2+...+n)/n
 *            = (n+1)/2
 *
 * 2. 查找失败
 *    需要比较全部 n 个元素：
 *
 *    ASL失败 = n
 *
 * 特点：
 *   1. 算法简单，适用于有序表和无序表
 *   2. 不要求元素连续存储，但本实现使用数组
 *   3. 查找效率较低，数据量大时不适合
 *   4. 不带哨兵，查找失败返回 -1
 *
 * 注意：
 *   ASL统计的是关键字比较次数，不是时间复杂度。
 */

#include<bits/stdc++.h>

using namespace std;

#define MAX_SIZE 50

struct STable{
    int data[MAX_SIZE];
    int len;
};

int Search_Seq(STable *s,int key){
    for(int i=0;i<s->len;i++){
        if(s->data[i] == key) return i;
    }
    return -1;
}

int main() {
    STable s = {{12, 35, 8, 46, 23, 71, 19, 54, 30, 67}, 10};

    // 输出序号
    cout << "序号：";
    for (int i = 0; i < s.len; i++) {
        cout << setw(5) << i;
    }
    cout << endl;

    // 输出数据
    cout << "数据：";
    for (int i = 0; i < s.len; i++) {
        cout << setw(5) << s.data[i];
    }
    cout << endl;

    // 输入待查找的值
    int key;
    cout << "请输入待查找的值：";
    cin >> key;

    // 顺序查找
    int pos = Search_Seq(&s, key);

    if (pos == -1) {
        cout << "查找失败，元素不存在！" << endl;
    } else {
        cout << "查找成功，序号为：" << pos << endl;
    }

    return 0;
}
