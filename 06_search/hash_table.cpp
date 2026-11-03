
#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 47;

// 链表结点
struct HashNode {
    int data;
    HashNode *next;
};

// 散列表
struct HashTable {
    HashNode *items[MAX_SIZE];
};

// 散列函数：除留余数法（关键字为非负整数）
int hashFunction(int value) {
    return value % MAX_SIZE;
}

// 初始化
void init(HashTable *t) {
    for (int i = 0; i < MAX_SIZE; i++) {
        t->items[i] = nullptr;
    }
}

// 查找：成功返回结点指针，失败返回 nullptr
HashNode* find(HashTable *t, int key) {
    int k = hashFunction(key);
    HashNode *node = t->items[k];

    while (node) {
        if (node->data == key)
            return node;

        node = node->next;
    }

    return nullptr;
}

// 插入：采用头插法，不允许重复
bool insert(HashTable *t, int value) {
    int k = hashFunction(value);

    // 检查是否重复
    HashNode *node = t->items[k];
    while (node) {
        if (node->data == value)
            return false;

        node = node->next;
    }

    // 创建新结点并头插
    HashNode *newNode = new HashNode;
    newNode->data = value;
    newNode->next = t->items[k];
    t->items[k] = newNode;

    return true;
}

// 删除：成功返回 true，失败返回 false
bool deleteItem(HashTable *t, int key) {
    int k = hashFunction(key);

    HashNode *node = t->items[k];
    HashNode *last = nullptr;

    // 查找目标结点及其前驱
    while (node && node->data != key) {
        last = node;
        node = node->next;
    }

    if (node == nullptr)
        return false;

    // 修改链表连接
    if (last == nullptr)
        t->items[k] = node->next;
    else
        last->next = node->next;

    delete node;
    return true;
}

// 输出散列表
void printHash(HashTable *t) {
    for (int i = 0; i < MAX_SIZE; i++) {
        HashNode *node = t->items[i];

        if (node == nullptr)
            continue;

        cout << i << ": ";

        while (node) {
            cout << node->data << " -> ";
            node = node->next;
        }

        cout << "NULL" << endl;
    }
}

// 销毁散列表
void destroy(HashTable *t) {
    for (int i = 0; i < MAX_SIZE; i++) {
        HashNode *node = t->items[i];

        while (node) {
            HashNode *next = node->next;
            delete node;
            node = next;
        }

        t->items[i] = nullptr;
    }
}

int main() {
    HashTable t;
    init(&t);

    // 插入
    insert(&t, 3);
    insert(&t, 50);
    insert(&t, 97);
    insert(&t, 12);
    insert(&t, 59);

    cout << "初始散列表：" << endl;
    printHash(&t);

    // 重复插入
    cout << "\n重复插入50：" << insert(&t, 50) << endl;

    // 查找
    HashNode *p = find(&t, 50);
    if (p)
        cout << "查找成功：" << p->data << endl;
    else
        cout << "查找失败" << endl;

    // 删除
    cout << "\n删除50：" << deleteItem(&t, 50) << endl;
    cout << "删除97：" << deleteItem(&t, 97) << endl;
    cout << "删除100：" << deleteItem(&t, 100) << endl;

    cout << "\n删除后的散列表：" << endl;
    printHash(&t);

    // 释放内存
    destroy(&t);

    return 0;
}
