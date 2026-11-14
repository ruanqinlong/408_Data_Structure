
/*
基数排序（LSD，最低位优先）
实现方式：链式队列（桶）

适用范围：非负整数

时间复杂度：O(d(n+r))
辅助空间复杂度：O(n+r)
稳定性：稳定

n：元素个数
d：最大关键字的位数
r：基数，这里为10
*/

#include <bits/stdc++.h>
using namespace std;

struct node {
    int data;
    node *next;
};

struct radix {
    node *first;
    node *end;
};

void radix_sort(node a[], int len) {
    if (len <= 1) return;

    // 1. 找到最大值
    int max_num = 0;
    for (int i = 0; i < len; i++) {
        max_num = max(max_num, a[i].data);
    }

    // 2. 初始化当前链表顺序
    for (int i = 0; i < len - 1; i++) {
        a[i].next = &a[i + 1];
    }
    a[len - 1].next = nullptr;

    node *head = &a[0];

    // 3. 从个位开始，逐位分配和收集
    for (long long k = 1; max_num / k > 0; k *= 10) {

        radix buk[10] = {};

        // 分配
        node *p = head;

        while (p != nullptr) {
            node *next = p->next;

            int num = (p->data / k) % 10;

            p->next = nullptr;

            if (buk[num].first == nullptr) {
                buk[num].first = p;
                buk[num].end = p;
            } else {
                buk[num].end->next = p;
                buk[num].end = p;
            }

            p = next;
        }

        // 收集
        head = nullptr;
        node *tail = nullptr;

        for (int i = 0; i < 10; i++) {
            if (buk[i].first == nullptr)
                continue;

            if (head == nullptr) {
                head = buk[i].first;
                tail = buk[i].end;
            } else {
                tail->next = buk[i].first;
                tail = buk[i].end;
            }
        }
    }

    // 4. 将排序结果写回数组
    // 注意：先保存结果，避免覆盖尚未读取的结点
    vector<int> result;
    result.reserve(len);

    for (node *p = head; p != nullptr; p = p->next) {
        result.push_back(p->data);
    }

    for (int i = 0; i < len; i++) {
        a[i].data = result[i];
        a[i].next = (i + 1 < len) ? &a[i + 1] : nullptr;
    }
}

int main() {
    node a[] = {
        {53, nullptr},
        {3, nullptr},
        {542, nullptr},
        {748, nullptr},
        {14, nullptr},
        {214, nullptr}
    };

    int len = sizeof(a) / sizeof(a[0]);

    radix_sort(a, len);

    for (int i = 0; i < len; i++) {
        cout << a[i].data << " ";
    }

    return 0;
}
