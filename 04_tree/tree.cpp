// 一般树：双亲表示法、孩子表示法、孩子兄弟表示法
#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 100;


// 双亲表示法
struct ParentNode{
    int data;
    int parent;
};

struct ParentTree{
    ParentNode nodes[MAX_SIZE];
    int len;
};


// 孩子表示法

// 孩子链表结点
struct ChildNode{
    int child;              // 孩子在数组中的下标
    ChildNode *nextChild;
};

// 真正的树结点
struct ChildBox{
    int data;
    ChildNode *firstChild;
};

// 整棵树
struct ChildTree{
    int len;
    int index;              // 根结点的数组下标
    ChildBox nodes[MAX_SIZE];
};


// 孩子兄弟表示法
struct ChildSiblingNode{
    int data;
    ChildSiblingNode *firstChild;
    ChildSiblingNode *nextSibling;
};


int main(){

    return 0;
}