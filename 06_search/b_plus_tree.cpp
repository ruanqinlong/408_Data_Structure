// B+ 树

#include <bits/stdc++.h>
using namespace std;

// B+树结点
struct TreeNode {
    bool leaf;                    // 是否为叶子结点
    vector<int> key;              // 关键字
    vector<TreeNode*> child;      // 孩子指针
    TreeNode *next;               // 叶子结点的后继

    TreeNode(bool is_leaf) {
        leaf = is_leaf;
        next = nullptr;
    }
};

const int M = 4;                  // B+树的阶数
const int MAX_KEY = M - 1;        // 最多3个关键字
const int MIN_KEY = 2;            // 非根叶子结点最少2个关键字

// 1. 查找子树中的最小关键字
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
int find_min(TreeNode *root) {

    while (!root->leaf) {
        root = root->child[0];
    }

    return root->key[0];
}

// 2. 更新内部结点的索引关键字
// 时间复杂度：O(M log n)，沿树高更新
// 空间复杂度：O(1)
void update_key(TreeNode *root) {

    if (root == nullptr || root->leaf) {
        return;
    }

    root->key.clear();

    // 每个右孩子的最小关键字作为分隔关键字
    for (int i = 1; i < root->child.size(); i++) {
        root->key.push_back(find_min(root->child[i]));
    }
}

// 3. 查找关键字
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
bool search_tree(TreeNode *root, int k) {

    while (root != nullptr && !root->leaf) {

        int i = 0;

        // 找到应该进入的孩子
        while (i < root->key.size() && k >= root->key[i]) {
            i++;
        }

        root = root->child[i];
    }

    if (root == nullptr) {
        return false;
    }

    return binary_search(root->key.begin(),
                         root->key.end(), k);
}

// 4. 插入辅助函数
// 时间复杂度：O(log n)，不包含结点内移动的常数代价
// 空间复杂度：O(log n)，递归栈
TreeNode* insert_helper(TreeNode *root, int k) {

    // 到达叶子结点
    if (root->leaf) {

        auto it = lower_bound(
            root->key.begin(), root->key.end(), k
        );

        root->key.insert(it, k);

        // 没有超过容量
        if (root->key.size() <= MAX_KEY) {
            return nullptr;
        }

        // 叶子结点分裂
        TreeNode *right = new TreeNode(true);

        int mid = root->key.size() / 2;

        right->key.assign(
            root->key.begin() + mid,
            root->key.end()
        );

        root->key.erase(
            root->key.begin() + mid,
            root->key.end()
        );

        // 维护叶子结点链表
        right->next = root->next;
        root->next = right;

        return right;
    }

    // 找到应该进入的孩子
    int i = 0;

    while (i < root->key.size() && k >= root->key[i]) {
        i++;
    }

    // 递归插入
    TreeNode *right = insert_helper(root->child[i], k);

    // 孩子没有分裂
    if (right == nullptr) {
        update_key(root);
        return nullptr;
    }

    // 孩子分裂，将新孩子插入当前结点
    root->child.insert(root->child.begin() + i + 1, right);

    update_key(root);

    // 当前结点没有超过容量
    if (root->child.size() <= M) {
        return nullptr;
    }

    // 内部结点分裂
    TreeNode *new_right = new TreeNode(false);

    int mid = root->child.size() / 2;

    new_right->child.assign(
        root->child.begin() + mid,
        root->child.end()
    );

    root->child.erase(
        root->child.begin() + mid,
        root->child.end()
    );

    update_key(root);
    update_key(new_right);

    return new_right;
}

// 5. 插入关键字
// 时间复杂度：O(log n)
// 空间复杂度：O(log n)，递归栈及分裂结点
void insert_tree(TreeNode *&root, int k) {

    // 不允许重复关键字
    if (search_tree(root, k)) {
        return;
    }

    // 空树
    if (root == nullptr) {

        root = new TreeNode(true);
        root->key.push_back(k);

        return;
    }

    TreeNode *right = insert_helper(root, k);

    // 根结点发生分裂
    if (right != nullptr) {

        TreeNode *new_root = new TreeNode(false);

        new_root->child.push_back(root);
        new_root->child.push_back(right);

        update_key(new_root);

        root = new_root;
    }
}

// 6. 重新调整内部结点的索引
// 时间复杂度：O(M log n)，用于沿路径更新
// 空间复杂度：O(1)
void refresh_tree(TreeNode *root) {

    while (root != nullptr) {
        update_key(root);
        root = nullptr;
    }
}

// 7. 删除叶子结点中的关键字
// 时间复杂度：O(M)
// 空间复杂度：O(1)
void erase_leaf(TreeNode *root, int k) {

    auto it = lower_bound(
        root->key.begin(), root->key.end(), k
    );

    if (it != root->key.end() && *it == k) {
        root->key.erase(it);
    }
}

// 8. 删除递归辅助函数
// 时间复杂度：O(log n)，不计固定阶数的结点调整
// 空间复杂度：O(log n)，递归栈
void delete_helper(TreeNode *root, int k) {

    if (root->leaf) {
        erase_leaf(root, k);
        return;
    }

    int i = 0;

    while (i < root->key.size() && k >= root->key[i]) {
        i++;
    }

    delete_helper(root->child[i], k);

    TreeNode *child = root->child[i];

    // 叶子结点发生下溢
    if (child->leaf && child->key.size() < MIN_KEY) {

        // 向左兄弟借
        if (i > 0 &&
            root->child[i - 1]->key.size() > MIN_KEY) {

            TreeNode *left = root->child[i - 1];

            child->key.insert(
                child->key.begin(),
                left->key.back()
            );

            left->key.pop_back();
        }

        // 向右兄弟借
        else if (i + 1 < root->child.size() &&
                 root->child[i + 1]->key.size() > MIN_KEY) {

            TreeNode *right = root->child[i + 1];

            child->key.push_back(right->key.front());

            right->key.erase(right->key.begin());
        }

        // 合并
        else if (i > 0) {

            TreeNode *left = root->child[i - 1];

            left->key.insert(
                left->key.end(),
                child->key.begin(),
                child->key.end()
            );

            left->next = child->next;

            delete child;

            root->child.erase(root->child.begin() + i);
        }

        else if (i + 1 < root->child.size()) {

            TreeNode *right = root->child[i + 1];

            child->key.insert(
                child->key.end(),
                right->key.begin(),
                right->key.end()
            );

            child->next = right->next;

            delete right;

            root->child.erase(root->child.begin() + i + 1);
        }
    }

    // 内部结点的孩子数量下溢
    else if (!child->leaf &&
             child->child.size() < 2) {

        // 向左兄弟借孩子
        if (i > 0 &&
            root->child[i - 1]->child.size() > 2) {

            TreeNode *left = root->child[i - 1];

            child->child.insert(
                child->child.begin(),
                left->child.back()
            );

            left->child.pop_back();

            update_key(left);
            update_key(child);
        }

        // 向右兄弟借孩子
        else if (i + 1 < root->child.size() &&
                 root->child[i + 1]->child.size() > 2) {

            TreeNode *right = root->child[i + 1];

            child->child.push_back(right->child.front());

            right->child.erase(right->child.begin());

            update_key(right);
            update_key(child);
        }

        // 与左兄弟合并
        else if (i > 0) {

            TreeNode *left = root->child[i - 1];

            left->child.insert(
                left->child.end(),
                child->child.begin(),
                child->child.end()
            );

            child->child.clear();

            delete child;

            root->child.erase(root->child.begin() + i);

            update_key(left);
        }

        // 与右兄弟合并
        else if (i + 1 < root->child.size()) {

            TreeNode *right = root->child[i + 1];

            child->child.insert(
                child->child.end(),
                right->child.begin(),
                right->child.end()
            );

            right->child.clear();

            delete right;

            root->child.erase(root->child.begin() + i + 1);

            update_key(child);
        }
    }

    update_key(root);
}

// 9. 删除关键字
// 时间复杂度：O(log n)，不计固定阶数的结点调整
// 空间复杂度：O(log n)，递归栈
void delete_tree(TreeNode *&root, int k) {

    if (root == nullptr || !search_tree(root, k)) {
        return;
    }

    delete_helper(root, k);

    // 根结点只有一个孩子时，降低树高
    while (root != nullptr && !root->leaf &&
           root->child.size() == 1) {

        TreeNode *old_root = root;

        root = root->child[0];

        old_root->child.clear();

        delete old_root;
    }

    // 根结点为空
    if (root != nullptr && root->leaf &&
        root->key.empty()) {

        delete root;
        root = nullptr;
    }
}

// 10. 查找叶子结点
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
TreeNode* find_leaf(TreeNode *root, int k) {

    while (root != nullptr && !root->leaf) {

        int i = 0;

        while (i < root->key.size() && k >= root->key[i]) {
            i++;
        }

        root = root->child[i];
    }

    return root;
}

// 11. 范围查询
// 时间复杂度：O(log n + r)，r为输出关键字数量
// 空间复杂度：O(1)，不计输出空间
void range_search(TreeNode *root, int low, int high) {

    TreeNode *p = find_leaf(root, low);

    if (p == nullptr) {
        return;
    }

    // 利用叶子结点链表顺序查找
    while (p != nullptr) {

        for (int k : p->key) {

            if (k > high) {
                return;
            }

            if (k >= low) {
                cout << k << " ";
            }
        }

        p = p->next;
    }
}

// 12. 查找最小值
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

// 13. 查找最大值
// 时间复杂度：O(log n)
// 空间复杂度：O(1)
int find_max(TreeNode *root) {

    if (root == nullptr) {
        return -1;
    }

    while (!root->leaf) {
        root = root->child.back();
    }

    return root->key.back();
}

// 14. 遍历叶子结点
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void inorder(TreeNode *root) {

    if (root == nullptr) {
        return;
    }

    // 找到最左侧叶子结点
    while (!root->leaf) {
        root = root->child[0];
    }

    // 沿叶子链表遍历
    while (root != nullptr) {

        for (int k : root->key) {
            cout << k << " ";
        }

        root = root->next;
    }
}

// 15. 销毁整棵树
// 时间复杂度：O(n)
// 空间复杂度：O(log n)，递归栈
void destroy_tree(TreeNode *&root) {

    if (root == nullptr) {
        return;
    }

    if (!root->leaf) {

        for (TreeNode *p : root->child) {
            destroy_tree(p);
        }
    }

    delete root;
    root = nullptr;
}

// 16. 测试
int main() {

    TreeNode *root = nullptr;

    int a[] = {
        10, 20, 30, 40, 50,
        60, 70, 80, 90, 100
    };

    // 插入
    for (int x : a) {
        insert_tree(root, x);
    }

    cout << "叶子结点遍历：";
    inorder(root);
    cout << endl;

    cout << "查找50："
         << search_tree(root, 50) << endl;

    cout << "最小值："
         << find_min(root) << endl;

    cout << "最大值："
         << find_max(root) << endl;

    cout << "范围查询30~80：";
    range_search(root, 30, 80);
    cout << endl;

    // 删除
    delete_tree(root, 40);
    delete_tree(root, 50);

    cout << "删除后：";
    inorder(root);
    cout << endl;

    destroy_tree(root);

    return 0;
}
