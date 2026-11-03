//B树
#include <bits/stdc++.h>
using namespace std;

const int T = 3;

// B树结点
struct TreeNode {
    int key[2 * T - 1];       // 最多5个关键字
    TreeNode *child[2 * T];   // 最多6个孩子
    int n;                    // 当前关键字数量
    bool leaf;                // 是否为叶子结点

    TreeNode(bool is_leaf) {
        n = 0;
        leaf = is_leaf;

        for (int i = 0; i < 2 * T; i++) {
            child[i] = nullptr;
        }
    }
};

// 1. 查找关键字
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)，递归栈
bool search_tree(TreeNode *root, int k) {
    if (root == nullptr) {
        return false;
    }

    int i = 0;

    while (i < root->n && k > root->key[i]) {
        i++;
    }

    if (i < root->n && k == root->key[i]) {
        return true;
    }

    if (root->leaf) {
        return false;
    }

    return search_tree(root->child[i], k);
}

// 2. 分裂满结点
// 时间复杂度：O(T)，本实现T为常数
// 空间复杂度：O(T)，创建新结点
void split_child(TreeNode *parent, int i) {
    TreeNode *full = parent->child[i];

    TreeNode *right = new TreeNode(full->leaf);

    right->n = T - 1;

    // 将右半部分关键字移入新结点
    for (int j = 0; j < T - 1; j++) {
        right->key[j] = full->key[j + T];
    }

    // 如果不是叶子结点，还要移动孩子指针
    if (!full->leaf) {
        for (int j = 0; j < T; j++) {
            right->child[j] = full->child[j + T];
            full->child[j + T] = nullptr;
        }
    }

    int middle = full->key[T - 1];

    full->n = T - 1;

    // 为新孩子腾出位置
    for (int j = parent->n; j >= i + 1; j--) {
        parent->child[j + 1] = parent->child[j];
    }

    parent->child[i + 1] = right;

    // 将中间关键字上移到父结点
    for (int j = parent->n - 1; j >= i; j--) {
        parent->key[j + 1] = parent->key[j];
    }

    parent->key[i] = middle;
    parent->n++;
}

// 3. 在非满结点中插入
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)，递归栈
void insert_non_full(TreeNode *root, int k) {
    int i = root->n - 1;

    if (root->leaf) {

        // 从后向前移动，找到插入位置
        while (i >= 0 && k < root->key[i]) {
            root->key[i + 1] = root->key[i];
            i--;
        }

        root->key[i + 1] = k;
        root->n++;
    }
    else {

        // 找到应该进入的孩子
        while (i >= 0 && k < root->key[i]) {
            i--;
        }

        i++;

        // 如果孩子已满，先分裂
        if (root->child[i]->n == 2 * T - 1) {
            split_child(root, i);

            if (k > root->key[i]) {
                i++;
            }
        }

        insert_non_full(root->child[i], k);
    }
}

// 4. 插入关键字
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)
void insert_tree(TreeNode *&root, int k) {

    if (search_tree(root, k)) {
        return;
    }

    // 空树
    if (root == nullptr) {
        root = new TreeNode(true);
        root->key[0] = k;
        root->n = 1;
        return;
    }

    // 根结点已满，需要创建新根
    if (root->n == 2 * T - 1) {

        TreeNode *new_root = new TreeNode(false);

        new_root->child[0] = root;

        split_child(new_root, 0);

        root = new_root;
    }

    insert_non_full(root, k);
}

// 5. 查找关键字在结点中的位置
// 时间复杂度：O(T)
// 空间复杂度：O(1)
int find_key(TreeNode *root, int k) {
    int i = 0;

    while (i < root->n && root->key[i] < k) {
        i++;
    }

    return i;
}

// 6. 从叶子结点删除关键字
// 时间复杂度：O(T)
// 空间复杂度：O(1)
void remove_from_leaf(TreeNode *root, int i) {

    for (int j = i + 1; j < root->n; j++) {
        root->key[j - 1] = root->key[j];
    }

    root->n--;
}

// 7. 查找前驱
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
int get_predecessor(TreeNode *root, int i) {
    TreeNode *p = root->child[i];

    while (!p->leaf) {
        p = p->child[p->n];
    }

    return p->key[p->n - 1];
}

// 8. 查找后继
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
int get_successor(TreeNode *root, int i) {
    TreeNode *p = root->child[i + 1];

    while (!p->leaf) {
        p = p->child[0];
    }

    return p->key[0];
}

// 9. 向左兄弟借关键字
// 时间复杂度：O(T)
// 空间复杂度：O(1)
void borrow_from_prev(TreeNode *root, int i) {

    TreeNode *child = root->child[i];
    TreeNode *sibling = root->child[i - 1];

    // 孩子的关键字整体右移
    for (int j = child->n - 1; j >= 0; j--) {
        child->key[j + 1] = child->key[j];
    }

    // 如果有孩子指针，也整体右移
    if (!child->leaf) {
        for (int j = child->n; j >= 0; j--) {
            child->child[j + 1] = child->child[j];
        }
    }

    // 父结点的关键字下移
    child->key[0] = root->key[i - 1];

    if (!child->leaf) {
        child->child[0] = sibling->child[sibling->n];
        sibling->child[sibling->n] = nullptr;
    }

    // 左兄弟的最大关键字上移
    root->key[i - 1] = sibling->key[sibling->n - 1];

    child->n++;
    sibling->n--;
}

// 10. 向右兄弟借关键字
// 时间复杂度：O(T)
// 空间复杂度：O(1)
void borrow_from_next(TreeNode *root, int i) {

    TreeNode *child = root->child[i];
    TreeNode *sibling = root->child[i + 1];

    // 父结点关键字下移
    child->key[child->n] = root->key[i];

    if (!child->leaf) {
        child->child[child->n + 1] = sibling->child[0];
    }

    // 右兄弟最小关键字上移
    root->key[i] = sibling->key[0];

    // 右兄弟关键字左移
    for (int j = 1; j < sibling->n; j++) {
        sibling->key[j - 1] = sibling->key[j];
    }

    if (!sibling->leaf) {
        for (int j = 1; j <= sibling->n; j++) {
            sibling->child[j - 1] = sibling->child[j];
        }

        sibling->child[sibling->n] = nullptr;
    }

    child->n++;
    sibling->n--;
}

// 11. 合并两个孩子结点
// 时间复杂度：O(T)
// 空间复杂度：O(1)
void merge_child(TreeNode *root, int i) {

    TreeNode *child = root->child[i];
    TreeNode *sibling = root->child[i + 1];

    // 父结点的分隔关键字下移
    child->key[T - 1] = root->key[i];

    // 合并右兄弟的关键字
    for (int j = 0; j < sibling->n; j++) {
        child->key[j + T] = sibling->key[j];
    }

    // 合并孩子指针
    if (!child->leaf) {
        for (int j = 0; j <= sibling->n; j++) {
            child->child[j + T] = sibling->child[j];
            sibling->child[j] = nullptr;
        }
    }

    child->n += sibling->n + 1;

    // 父结点关键字左移
    for (int j = i + 1; j < root->n; j++) {
        root->key[j - 1] = root->key[j];
    }

    // 父结点孩子指针左移
    for (int j = i + 2; j <= root->n; j++) {
        root->child[j - 1] = root->child[j];
    }

    root->child[root->n] = nullptr;
    root->n--;

    delete sibling;
}

// 12. 确保孩子至少有T个关键字
// 时间复杂度：O(T)
// 空间复杂度：O(1)
void fill_child(TreeNode *root, int i) {

    // 优先向左兄弟借
    if (i != 0 && root->child[i - 1]->n >= T) {
        borrow_from_prev(root, i);
    }
    // 向右兄弟借
    else if (i != root->n && root->child[i + 1]->n >= T) {
        borrow_from_next(root, i);
    }
    // 都不能借，则合并
    else {
        if (i != root->n) {
            merge_child(root, i);
        }
        else {
            merge_child(root, i - 1);
        }
    }
}

// 13. 从内部结点删除关键字
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)
void remove_from_internal(TreeNode *root, int i) {

    int k = root->key[i];

    // 左孩子有足够关键字，用前驱替换
    if (root->child[i]->n >= T) {

        int pre = get_predecessor(root, i);

        root->key[i] = pre;

        delete_tree(root->child[i], pre);
    }
    // 右孩子有足够关键字，用后继替换
    else if (root->child[i + 1]->n >= T) {

        int suc = get_successor(root, i);

        root->key[i] = suc;

        delete_tree(root->child[i + 1], suc);
    }
    // 两边都不够，合并后删除
    else {

        merge_child(root, i);

        delete_tree(root->child[i], k);
    }
}

// 14. 删除辅助函数
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)，递归栈
void delete_tree(TreeNode *root, int k) {

    if (root == nullptr) {
        return;
    }

    int i = find_key(root, k);

    // 找到了关键字
    if (i < root->n && root->key[i] == k) {

        if (root->leaf) {
            remove_from_leaf(root, i);
        }
        else {
            remove_from_internal(root, i);
        }
    }
    else {

        // 叶子结点中不存在该关键字
        if (root->leaf) {
            return;
        }

        bool last_child = (i == root->n);

        // 如果孩子关键字不足，先调整
        if (root->child[i]->n < T) {
            fill_child(root, i);
        }

        // 合并可能改变孩子的位置
        if (last_child && i > root->n) {
            delete_tree(root->child[i - 1], k);
        }
        else {
            delete_tree(root->child[i], k);
        }
    }
}

// 15. 删除入口，调整根结点
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)
void delete_key(TreeNode *&root, int k) {

    if (root == nullptr) {
        return;
    }

    delete_tree(root, k);

    // 根结点没有关键字时，降低树高
    if (root->n == 0) {

        TreeNode *old_root = root;

        if (root->leaf) {
            root = nullptr;
        }
        else {
            root = root->child[0];
            old_root->child[0] = nullptr;
        }

        delete old_root;
    }
}

// 16. 中序遍历
// 时间复杂度：O(n)
// 空间复杂度：O(log n)，递归栈
void inorder(TreeNode *root) {

    if (root == nullptr) {
        return;
    }

    int i;

    for (i = 0; i < root->n; i++) {

        if (!root->leaf) {
            inorder(root->child[i]);
        }

        cout << root->key[i] << " ";
    }

    if (!root->leaf) {
        inorder(root->child[i]);
    }
}

// 17. 查找最小值
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
int find_min(TreeNode *root) {

    if (root == nullptr) {
        return -1;
    }

    while (!root->leaf) {
        root = root->child[0];
    }

    return root->key[0];
}

// 18. 查找最大值
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
int find_max(TreeNode *root) {

    if (root == nullptr) {
        return -1;
    }

    while (!root->leaf) {
        root = root->child[root->n];
    }

    return root->key[root->n - 1];
}

// 19. 销毁整棵树
// 时间复杂度：O(n)
// 空间复杂度：O(log n)，递归栈
void destroy_tree(TreeNode *&root) {

    if (root == nullptr) {
        return;
    }

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++) {
            destroy_tree(root->child[i]);
        }
    }

    delete root;
    root = nullptr;
}

// 20. 测试
int main() {

    TreeNode *root = nullptr;

    int a[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    // 插入
    for (int x : a) {
        insert_tree(root, x);
    }

    cout << "中序遍历：";
    inorder(root);
    cout << endl;

    cout << "查找50：" << search_tree(root, 50) << endl;

    cout << "最小值：" << find_min(root) << endl;
    cout << "最大值：" << find_max(root) << endl;

    // 删除
    delete_key(root, 40);
    delete_key(root, 50);

    cout << "删除后：";
    inorder(root);
    cout << endl;

    destroy_tree(root);

    return 0;
}
