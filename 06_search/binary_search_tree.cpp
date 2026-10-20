// 二叉排序树 / 二叉搜索树（BST）
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
};

// 1. 递归查找
// 时间复杂度：O(h)，空间复杂度：O(h)（递归栈）
// 平衡时 O(log n)，最坏退化为链表时 O(n)
TreeNode* search_tree_a(TreeNode *t, int key) {
    if (t == nullptr) return nullptr;
    else if (key == t->data)
        return t;
    else if (key > t->data)
        return search_tree_a(t->right, key);
    else if (key < t->data)
        return search_tree_a(t->left, key);

    return nullptr;
}

// 2. 循环查找
// 时间复杂度：O(h)，空间复杂度：O(1)
// 平衡时 O(log n)，最坏退化为链表时 O(n)
TreeNode* search_tree_b(TreeNode *t, int key) {
    while (t != nullptr && t->data != key) {
        if (key > t->data)
            t = t->right;
        else if (key < t->data)
            t = t->left;
    }
    return t;
}

// 3. 插入函数
// 时间复杂度：O(h)，空间复杂度：O(h)（递归栈）
// 平衡时 O(log n)，最坏退化为链表时 O(n)
// BST不插入重复关键字
bool insert_tree(TreeNode *&t, int value) {
    if (t == nullptr) {
        TreeNode *p = new TreeNode;
        p->data = value;
        p->left = p->right = nullptr;
        t = p;
        return true;
    }
    else if (t->data == value) {
        return false;
    }
    else if (value < t->data) {
        return insert_tree(t->left, value);
    }
    else if (value > t->data) {
        return insert_tree(t->right, value);
    }

    return false;
}

// 4. 构建二叉排序树
// 时间复杂度：平均 O(nlog n)，最坏 O(n²)
// 辅助空间复杂度：平均 O(log n)，最坏 O(n)（插入时的递归栈）
// 依次插入n个结点，最终树形取决于插入顺序
TreeNode* create_tree(int arr[], int n) {
    if (n <= 0) return nullptr;

    TreeNode *root = nullptr;

    for (int i = 0; i < n; i++) {
        insert_tree(root, arr[i]);
    }

    return root;
}

// 提前声明，供删除函数调用
TreeNode* find_min(TreeNode *t);

// 5. 删除指定结点
// 时间复杂度：O(h)，空间复杂度：O(h)（递归栈）
// 平衡时 O(log n)，最坏退化为链表时 O(n)
// 删除分为三种情况：没有孩子、一个孩子、两个孩子
bool delete_tree(TreeNode *&t, int key) {
    if (t == nullptr)
        return false;

    if (key < t->data)
        return delete_tree(t->left, key);
    else if (key > t->data)
        return delete_tree(t->right, key);

    // 找到了该结点
    else if (key == t->data) {

        // 统计当前结点的孩子数量
        int son = (t->left != nullptr) + (t->right != nullptr);

        // 情况1：没有孩子，直接删除
        if (son == 0) {
            delete t;
            t = nullptr;
        }

        // 情况2：只有一个孩子，让孩子接替当前结点
        else if (son == 1) {
            TreeNode *p = t;

            if (t->left != nullptr) {
                t = t->left;
            }
            else {
                t = t->right;
            }

            delete p;
        }

        // 情况3：有两个孩子
        else if (son == 2) {

            // 可以用左子树的最大结点（中序前驱）替代
            // 也可以用右子树的最小结点（中序后继）替代

            // 找到右子树的最小结点
            TreeNode *minNode = find_min(t->right);

            // 将当前结点的数据替换为中序后继的数据
            t->data = minNode->data;

            // 再删除右子树中原来的中序后继结点
            // 中序后继没有左孩子，因此删除时至多只有一个孩子
            return delete_tree(t->right, minNode->data);
        }

        return true;
    }

    return false;
}

// 6. 查找最小值结点
// 时间复杂度：O(h)，空间复杂度：O(h)（递归栈）
// 平衡时 O(log n)，最坏 O(n)
// BST的最小值结点位于最左侧，不一定是叶结点
TreeNode* find_min(TreeNode *t) {
    if (t == nullptr) return nullptr;
    if (t->left == nullptr) return t;

    return find_min(t->left);
}

// 7. 查找最大值结点
// 时间复杂度：O(h)，空间复杂度：O(h)（递归栈）
// 平衡时 O(log n)，最坏 O(n)
// BST的最大值结点位于最右侧，不一定是叶结点
TreeNode* find_max(TreeNode *t) {
    if (t == nullptr) return nullptr;
    if (t->right == nullptr) return t;

    return find_max(t->right);
}

// 8. 中序遍历（验证BST是否有序）
// 时间复杂度：O(n)，空间复杂度：O(h)（递归栈）
// BST中序遍历得到递增序列（左、根、右）
void inorder(TreeNode *t) {
    if (t == nullptr) return;

    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}

// 9. 销毁二叉排序树
// 时间复杂度：O(n)，空间复杂度：O(h)（递归栈）
// 使用后序遍历，先释放左右子树，再释放根结点
void destroy_tree(TreeNode *&t) {
    if (t == nullptr) return;

    destroy_tree(t->left);
    destroy_tree(t->right);

    delete t;
    t = nullptr;
}

// 10. 主函数：测试BST各项操作
int main() {

    // 1. 创建二叉排序树
    int arr[] = {50, 30, 70, 20, 40, 60, 80, 35, 65};
    int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode *root = create_tree(arr, n);

    cout << "初始BST中序遍历：";
    inorder(root);
    cout << endl;

    // 2. 测试递归查找
    cout << "\n测试递归查找：" << endl;
    TreeNode *p = search_tree_a(root, 40);

    if (p != nullptr)
        cout << "找到结点：" << p->data << endl;
    else
        cout << "未找到结点" << endl;

    // 3. 测试循环查找
    cout << "\n测试循环查找：" << endl;
    p = search_tree_b(root, 100);

    if (p != nullptr)
        cout << "找到结点：" << p->data << endl;
    else
        cout << "未找到结点100" << endl;

    // 4. 测试最大值和最小值
    cout << "\n测试最大值和最小值：" << endl;

    TreeNode *minNode = find_min(root);
    TreeNode *maxNode = find_max(root);

    if (minNode != nullptr)
        cout << "最小值：" << minNode->data << endl;

    if (maxNode != nullptr)
        cout << "最大值：" << maxNode->data << endl;

    // 5. 测试插入
    cout << "\n插入结点55：" << endl;
    insert_tree(root, 55);
    inorder(root);
    cout << endl;

    // 6. 测试删除叶结点
    cout << "\n删除叶结点35：" << endl;
    delete_tree(root, 35);
    inorder(root);
    cout << endl;

    // 7. 测试删除只有一个孩子的结点
    // 此时结点40已经没有左孩子35，也没有右孩子
    // 先插入45，使40只有一个右孩子
    insert_tree(root, 45);

    cout << "\n删除只有一个孩子的结点40：" << endl;
    delete_tree(root, 40);
    inorder(root);
    cout << endl;

    // 8. 测试删除有两个孩子的结点
    // 70的左孩子为60，右孩子为80
    cout << "\n删除有两个孩子的结点70：" << endl;
    delete_tree(root, 70);
    inorder(root);
    cout << endl;

    // 9. 测试删除根结点
    cout << "\n删除根结点50：" << endl;
    delete_tree(root, 50);
    inorder(root);
    cout << endl;

    // 10. 测试删除不存在的结点
    cout << "\n删除不存在的结点100：" << endl;
    bool result = delete_tree(root, 100);
    cout << (result ? "删除成功" : "删除失败") << endl;

    // 11. 销毁二叉排序树
    cout << "\n销毁二叉排序树：" << endl;
    destroy_tree(root);

    if (root == nullptr)
        cout << "二叉排序树已销毁，根指针为nullptr" << endl;

    return 0;
}