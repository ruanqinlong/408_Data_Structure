
#include <bits/stdc++.h>
using namespace std;

// 平衡二叉树（AVL）
// 在二叉排序树（BST）的基础上增加平衡因子和旋转操作
// 平衡因子 BF = 左子树高度 - 右子树高度
// AVL树要求每个结点的BF只能为 -1、0、1

struct TreeNode {
    int data;
    int bf;                    // 平衡因子
    TreeNode *left, *right;
};

// 1. 递归查找
// 时间复杂度：O(log n)，空间复杂度：O(log n)（递归栈）
// AVL树始终保持平衡，不会退化为链表
TreeNode* search_tree_a(TreeNode *t, int key) {
    if (t == nullptr) return nullptr;

    if (key == t->data)
        return t;
    else if (key > t->data)
        return search_tree_a(t->right, key);
    else
        return search_tree_a(t->left, key);
}

// 2. 循环查找
// 时间复杂度：O(log n)，空间复杂度：O(1)
TreeNode* search_tree_b(TreeNode *t, int key) {
    while (t != nullptr && t->data != key) {
        if (key > t->data)
            t = t->right;
        else
            t = t->left;
    }

    return t;
}

// 3. 右旋
// 时间复杂度：O(1)，空间复杂度：O(1)
// 用于LL型调整，也用于LR型的第二次旋转
// 这里只修改指针，不负责更新BF
void rotate_right(TreeNode *&t) {
    TreeNode *p = t->left;

    // 将p的右子树交给原根结点作为左子树
    t->left = p->right;

    // 原根结点成为p的右孩子
    p->right = t;

    // p成为新的子树根结点
    t = p;
}

// 4. 左旋
// 时间复杂度：O(1)，空间复杂度：O(1)
// 用于RR型调整，也用于RL型的第二次旋转
void rotate_left(TreeNode *&t) {
    TreeNode *p = t->right;

    // 将p的左子树交给原根结点作为右子树
    t->right = p->left;

    // 原根结点成为p的左孩子
    p->left = t;

    // p成为新的子树根结点
    t = p;
}

// 5. 左子树过高时进行平衡调整
// 调用条件：当前结点的BF即将由+1变为+2
// 时间复杂度：O(1)，空间复杂度：O(1)
void balance_left(TreeNode *&t) {
    TreeNode *p = t->left;

    // 情况1：LL型，右单旋
    // 删除时p->bf也可能为0
    if (p->bf >= 0) {
        int old_bf = p->bf;

        rotate_right(t);

        if (old_bf == 0) {
            // 删除时的特殊情况
            t->bf = -1;
            t->right->bf = 1;
        }
        else {
            // 插入导致的LL型失衡
            t->bf = 0;
            t->right->bf = 0;
        }
    }

    // 情况2：LR型，先左旋再右旋
    else if (p->bf == -1) {
        // 保存孙子结点旋转前的BF
        int middle_bf = p->right->bf;

        rotate_left(t->left);
        rotate_right(t);

        // 双旋后，新的子树根BF为0
        t->bf = 0;

        // 根据孙子结点原来的BF更新两个孩子
        if (middle_bf == 1) {
            t->left->bf = 0;
            t->right->bf = -1;
        }
        else if (middle_bf == -1) {
            t->left->bf = 1;
            t->right->bf = 0;
        }
        else {
            t->left->bf = 0;
            t->right->bf = 0;
        }
    }
}

// 6. 右子树过高时进行平衡调整
// 调用条件：当前结点的BF即将由-1变为-2
// 时间复杂度：O(1)，空间复杂度：O(1)
void balance_right(TreeNode *&t) {
    TreeNode *p = t->right;

    // 情况1：RR型，左单旋
    // 删除时p->bf也可能为0
    if (p->bf <= 0) {
        int old_bf = p->bf;

        rotate_left(t);

        if (old_bf == 0) {
            // 删除时的特殊情况
            t->bf = 1;
            t->left->bf = -1;
        }
        else {
            // 插入导致的RR型失衡
            t->bf = 0;
            t->left->bf = 0;
        }
    }

    // 情况2：RL型，先右旋再左旋
    else if (p->bf == 1) {
        int middle_bf = p->left->bf;

        rotate_right(t->right);
        rotate_left(t);

        t->bf = 0;

        if (middle_bf == 1) {
            t->left->bf = 0;
            t->right->bf = -1;
        }
        else if (middle_bf == -1) {
            t->left->bf = 1;
            t->right->bf = 0;
        }
        else {
            t->left->bf = 0;
            t->right->bf = 0;
        }
    }
}

// 7. 插入函数
// 时间复杂度：O(log n)，空间复杂度：O(log n)（递归栈）
// BST不插入重复关键字
// grew表示本次插入后，当前子树的高度是否增加
bool insert_tree(TreeNode *&t, int value, bool &grew) {
    if (t == nullptr) {
        TreeNode *p = new TreeNode;

        p->data = value;
        p->bf = 0;
        p->left = p->right = nullptr;

        t = p;
        grew = true;             // 新建结点，子树高度增加
        return true;
    }

    else if (t->data == value) {
        grew = false;            // 重复关键字，不插入
        return false;
    }

    // 情况1：插入左子树
    else if (value < t->data) {
        bool success = insert_tree(t->left, value, grew);

        if (!success)
            return false;

        // 左子树高度没变，当前结点无需调整
        if (!grew)
            return true;

        // 左子树高度增加1
        if (t->bf == -1) {
            // 原来右高，现在左右等高
            t->bf = 0;
            grew = false;
        }
        else if (t->bf == 0) {
            // 原来等高，现在左高1
            t->bf = 1;
            grew = true;
        }
        else if (t->bf == 1) {
            // 原来左高1，现在左高2，发生失衡
            balance_left(t);

            // 旋转后恢复插入前的子树高度
            grew = false;
        }
    }

    // 情况2：插入右子树
    else if (value > t->data) {
        bool success = insert_tree(t->right, value, grew);

        if (!success)
            return false;

        if (!grew)
            return true;

        // 右子树高度增加1
        if (t->bf == 1) {
            // 原来左高，现在左右等高
            t->bf = 0;
            grew = false;
        }
        else if (t->bf == 0) {
            // 原来等高，现在右高1
            t->bf = -1;
            grew = true;
        }
        else if (t->bf == -1) {
            // 原来右高1，现在右高2，发生失衡
            balance_right(t);

            grew = false;
        }
    }

    return true;
}

// 插入函数的简化调用
// 对外只需要传入根结点和关键字
bool insert_tree(TreeNode *&t, int value) {
    bool grew = false;
    return insert_tree(t, value, grew);
}

// 8. 构建平衡二叉树
// 时间复杂度：O(nlog n)
// 空间复杂度：O(log n)（不计树结点本身）
// 依次插入n个结点，插入过程中自动维持平衡
TreeNode* create_tree(int arr[], int n) {
    if (n <= 0) return nullptr;

    TreeNode *root = nullptr;

    for (int i = 0; i < n; i++) {
        insert_tree(root, arr[i]);
    }

    return root;
}

// 9. 查找最小值结点
// 时间复杂度：O(log n)，空间复杂度：O(log n)
// 最小值位于最左侧，不一定是叶结点
TreeNode* find_min(TreeNode *t) {
    if (t == nullptr) return nullptr;
    if (t->left == nullptr) return t;

    return find_min(t->left);
}

// 10. 查找最大值结点
// 时间复杂度：O(log n)，空间复杂度：O(log n)
// 最大值位于最右侧，不一定是叶结点
TreeNode* find_max(TreeNode *t) {
    if (t == nullptr) return nullptr;
    if (t->right == nullptr) return t;

    return find_max(t->right);
}

// 11. 删除后左子树高度减少的调整
// 时间复杂度：O(1)，空间复杂度：O(1)
// 左子树变矮，相当于当前结点BF减少1
void after_left_shrunk(TreeNode *&t, bool &shrunk) {
    if (t->bf == 1) {
        // 原来左高1，现在左右等高
        t->bf = 0;
        shrunk = true;
    }
    else if (t->bf == 0) {
        // 原来等高，现在右高1
        t->bf = -1;

        // 当前整棵子树高度不变
        shrunk = false;
    }
    else if (t->bf == -1) {
        // 原来右高1，现在右高2
        int child_bf = t->right->bf;

        balance_right(t);

        // 孩子BF为0时，旋转后高度不再减少
        shrunk = (child_bf != 0);
    }
}

// 12. 删除后右子树高度减少的调整
// 时间复杂度：O(1)，空间复杂度：O(1)
// 右子树变矮，相当于当前结点BF增加1
void after_right_shrunk(TreeNode *&t, bool &shrunk) {
    if (t->bf == -1) {
        // 原来右高1，现在左右等高
        t->bf = 0;
        shrunk = true;
    }
    else if (t->bf == 0) {
        // 原来等高，现在左高1
        t->bf = 1;
        shrunk = false;
    }
    else if (t->bf == 1) {
        // 原来左高1，现在左高2
        int child_bf = t->left->bf;

        balance_left(t);

        shrunk = (child_bf != 0);
    }
}

// 13. 删除指定结点
// 时间复杂度：O(log n)，空间复杂度：O(log n)（递归栈）
// shrunk表示本次删除后，当前子树的高度是否减少
// 删除分为三种情况：没有孩子、一个孩子、两个孩子
bool delete_tree(TreeNode *&t, int key, bool &shrunk) {
    if (t == nullptr) {
        shrunk = false;
        return false;
    }

    // 目标在左子树
    if (key < t->data) {
        bool success = delete_tree(t->left, key, shrunk);

        // 左子树高度减少，向上维护平衡
        if (success && shrunk)
            after_left_shrunk(t, shrunk);

        return success;
    }

    // 目标在右子树
    else if (key > t->data) {
        bool success = delete_tree(t->right, key, shrunk);

        if (success && shrunk)
            after_right_shrunk(t, shrunk);

        return success;
    }

    // 找到了该结点
    else if (key == t->data) {

        // 统计当前结点的孩子数量
        int son = (t->left != nullptr) + (t->right != nullptr);

        // 情况1：没有孩子，直接删除
        if (son == 0) {
            delete t;
            t = nullptr;

            shrunk = true;
            return true;
        }

        // 情况2：只有一个孩子，让孩子接替当前结点
        else if (son == 1) {
            TreeNode *p = t;

            if (t->left != nullptr)
                t = t->left;
            else
                t = t->right;

            delete p;

            shrunk = true;
            return true;
        }

        // 情况3：有两个孩子
        else if (son == 2) {

            // 找到右子树最小结点（中序后继）
            TreeNode *minNode = find_min(t->right);

            // 用中序后继的数据替换当前结点
            int value = minNode->data;
            t->data = value;

            // 删除右子树中原来的中序后继
            bool success = delete_tree(t->right, value, shrunk);

            // 右子树可能变矮，需要重新平衡
            if (success && shrunk)
                after_right_shrunk(t, shrunk);

            return success;
        }
    }

    return false;
}

// 删除函数的简化调用
bool delete_tree(TreeNode *&t, int key) {
    bool shrunk = false;
    return delete_tree(t, key, shrunk);
}

// 14. 中序遍历（验证BST是否有序）
// 时间复杂度：O(n)，空间复杂度：O(log n)（递归栈）
// 中序遍历得到递增序列（左、根、右）
void inorder(TreeNode *t) {
    if (t == nullptr) return;

    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}

// 15. 先序遍历（观察AVL旋转后的树形）
// 时间复杂度：O(n)，空间复杂度：O(log n)
// 同时输出结点的平衡因子
void preorder(TreeNode *t) {
    if (t == nullptr) return;

    cout << t->data << "(bf=" << t->bf << ") ";

    preorder(t->left);
    preorder(t->right);
}

// 16. 检查AVL树是否满足平衡条件
// 时间复杂度：O(n)，空间复杂度：O(log n)
// 返回当前子树的实际高度
// low、high用于验证二叉排序树的大小关系
int check_avl_height(TreeNode *t, bool &ok,
                     long long low, long long high) {
    if (t == nullptr) return 0;

    // 检查BST的大小关系
    if (t->data <= low || t->data >= high)
        ok = false;

    // 递归计算左右子树高度
    int left_h = check_avl_height(t->left, ok, low, t->data);
    int right_h = check_avl_height(t->right, ok, t->data, high);

    int actual_bf = left_h - right_h;

    // 检查实际BF与记录BF是否一致
    if (abs(actual_bf) > 1 || actual_bf != t->bf) {
        ok = false;

        cout << "结点 " << t->data
             << " 平衡因子异常，记录BF = " << t->bf
             << "，实际BF = " << actual_bf << endl;
    }

    return max(left_h, right_h) + 1;
}

// 检查函数的简化调用
bool check_avl(TreeNode *t) {
    bool ok = true;

    check_avl_height(t, ok, LLONG_MIN, LLONG_MAX);

    return ok;
}

// 17. 销毁平衡二叉树
// 时间复杂度：O(n)，空间复杂度：O(log n)（递归栈）
// 使用后序遍历，先释放左右子树，再释放根结点
void destroy_tree(TreeNode *&t) {
    if (t == nullptr) return;

    destroy_tree(t->left);
    destroy_tree(t->right);

    delete t;
    t = nullptr;
}

// 18. 主函数：测试AVL树的各项操作
int main() {
    int arr[] = {30, 10, 20, 40, 50, 25, 5, 35, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 构建AVL树
    TreeNode *root = create_tree(arr, n);

    cout << "初始中序遍历：";
    inorder(root);
    cout << endl;

    cout << "初始先序遍历：";
    preorder(root);
    cout << endl;

    cout << "AVL检查："
         << (check_avl(root) ? "通过" : "失败") << endl;

    // 测试查找
    cout << "递归查找25："
         << (search_tree_a(root, 25) ? "找到" : "未找到")
         << endl;

    cout << "循环查找50："
         << (search_tree_b(root, 50) ? "找到" : "未找到")
         << endl;

    // 测试最小值和最大值
    if (root != nullptr) {
        cout << "最小值：" << find_min(root)->data << endl;
        cout << "最大值：" << find_max(root)->data << endl;
    }

    // 测试删除
    int del[] = {10, 30, 40, 25};

    for (int i = 0; i < 4; i++) {
        int key = del[i];

        cout << "\n删除 " << key << "：";

        if (delete_tree(root, key))
            cout << "成功" << endl;
        else
            cout << "失败" << endl;

        cout << "中序遍历：";
        inorder(root);
        cout << endl;

        cout << "AVL检查："
             << (check_avl(root) ? "通过" : "失败")
             << endl;
    }

    // 释放所有结点
    destroy_tree(root);

    return 0;
}
