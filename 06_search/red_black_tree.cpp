// 红黑树

#include <bits/stdc++.h>
using namespace std;

// 红黑树：RED表示红色，BLACK表示黑色
// 性质：根为黑；红结点的孩子为黑；任一结点到后代NIL的路径黑结点数相同
// 所有空指针(nullptr)均视为黑色NIL叶结点

enum Color { RED, BLACK };

struct TreeNode {
    int data;
    Color color;
    TreeNode *left, *right, *parent;
};

// 1. 获取结点颜色：空结点视为黑色
// 时间O(1)，空间O(1)
Color get_color(TreeNode *t) {
    return t == nullptr ? BLACK : t->color;
}

// 2. 创建红结点：新插入结点默认为红色
// 时间O(1)，空间O(1)
TreeNode* create_node(int value) {
    TreeNode *p = new TreeNode;
    p->data = value;
    p->color = RED;
    p->left = p->right = p->parent = nullptr;
    return p;
}

// 3. 递归查找：满足BST的大小关系
// 时间O(log n)，空间O(log n)
TreeNode* search_tree_a(TreeNode *t, int key) {
    if (t == nullptr || t->data == key) return t;
    if (key < t->data) return search_tree_a(t->left, key);
    return search_tree_a(t->right, key);
}

// 4. 循环查找
// 时间O(log n)，空间O(1)
TreeNode* search_tree_b(TreeNode *t, int key) {
    while (t != nullptr && t->data != key) {
        if (key < t->data) t = t->left;
        else t = t->right;
    }
    return t;
}

// 5. 左旋：t指向整棵树的根，x是旋转前的局部根
// 时间O(1)，空间O(1)
void rotate_left(TreeNode *&t, TreeNode *x) {
    if (x == nullptr || x->right == nullptr) return;
    TreeNode *p = x->right;
    x->right = p->left;              // p的左子树交给x
    if (p->left != nullptr) p->left->parent = x;
    p->parent = x->parent;
    if (x->parent == nullptr) t = p; // x原来是整棵树的根
    else if (x == x->parent->left) x->parent->left = p;
    else x->parent->right = p;
    p->left = x;
    x->parent = p;
}

// 6. 右旋：与左旋完全对称
// 时间O(1)，空间O(1)
void rotate_right(TreeNode *&t, TreeNode *x) {
    if (x == nullptr || x->left == nullptr) return;
    TreeNode *p = x->left;
    x->left = p->right;
    if (p->right != nullptr) p->right->parent = x;
    p->parent = x->parent;
    if (x->parent == nullptr) t = p;
    else if (x == x->parent->left) x->parent->left = p;
    else x->parent->right = p;
    p->right = x;
    x->parent = p;
}

// 7. 插入后修复红黑树
// 时间O(log n)，空间O(1)
// 红色新结点只有在父结点也为红色时才违反性质
void fix_insert(TreeNode *&t, TreeNode *p) {
    while (p != t && get_color(p->parent) == RED) {
        TreeNode *father = p->parent;
        TreeNode *grand = father->parent; // 父红则祖父必存在

        if (father == grand->left) {
            TreeNode *uncle = grand->right;
            if (get_color(uncle) == RED) {
                // 叔叔红：父、叔变黑，祖父变红，继续向上检查
                father->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                p = grand;
            }
            else {
                if (p == father->right) {
                    // LR：先对父结点左旋，转成LL
                    p = father;
                    rotate_left(t, p);
                    father = p->parent;
                    grand = father->parent;
                }
                // LL：父变黑、祖父变红，对祖父右旋
                father->color = BLACK;
                grand->color = RED;
                rotate_right(t, grand);
            }
        }
        else {
            TreeNode *uncle = grand->left;
            if (get_color(uncle) == RED) {
                father->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                p = grand;
            }
            else {
                if (p == father->left) {
                    // RL：先对父结点右旋，转成RR
                    p = father;
                    rotate_right(t, p);
                    father = p->parent;
                    grand = father->parent;
                }
                // RR：父变黑、祖父变红，对祖父左旋
                father->color = BLACK;
                grand->color = RED;
                rotate_left(t, grand);
            }
        }
    }
    t->color = BLACK; // 根结点必须为黑色
}

// 8. 插入结点：先按BST规则插入，再修复颜色
// 时间O(log n)，空间O(1)
// 不允许重复关键字
bool insert_tree(TreeNode *&t, int value) {
    TreeNode *father = nullptr;
    TreeNode *p = t;
    while (p != nullptr) {
        father = p;
        if (value < p->data) p = p->left;
        else if (value > p->data) p = p->right;
        else return false;
    }

    TreeNode *node = create_node(value);
    node->parent = father;
    if (father == nullptr) t = node;
    else if (value < father->data) father->left = node;
    else father->right = node;

    fix_insert(t, node);
    return true;
}

// 9. 创建红黑树：依次插入数组元素
// 时间O(n log n)，额外空间O(1)（不计树结点）
TreeNode* create_tree(int arr[], int n) {
    TreeNode *root = nullptr;
    for (int i = 0; i < n; i++) insert_tree(root, arr[i]);
    return root;
}

// 10. 查找最小值：沿左指针一直走
// 时间O(log n)，空间O(1)
TreeNode* find_min(TreeNode *t) {
    if (t == nullptr) return nullptr;
    while (t->left != nullptr) t = t->left;
    return t;
}

// 11. 查找最大值：沿右指针一直走
// 时间O(log n)，空间O(1)
TreeNode* find_max(TreeNode *t) {
    if (t == nullptr) return nullptr;
    while (t->right != nullptr) t = t->right;
    return t;
}

// 12. 用v替换u在父结点中的位置
// 时间O(1)，空间O(1)
// 注意：只改变连接关系，不释放u，也不修改颜色
void transplant(TreeNode *&t, TreeNode *u, TreeNode *v) {
    if (u->parent == nullptr) t = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v != nullptr) v->parent = u->parent;
}

// 13. 删除黑结点后的修复
// 时间O(log n)，空间O(1)
// x可能为空，因此额外传入father和x是否是左孩子
// 将空结点视为黑色NIL；当x为空时，不能访问x->parent
void fix_delete(TreeNode *&t, TreeNode *x, TreeNode *father, bool x_is_left) {
    while (x != t && get_color(x) == BLACK) {
        if (father == nullptr) break;

        bool is_left = (x != nullptr) ? (x == father->left) : x_is_left;
        if (is_left) {
            TreeNode *brother = father->right;

            if (get_color(brother) == RED) {
                // 情况1：兄弟红，旋转后转化为兄弟黑的情况
                brother->color = BLACK;
                father->color = RED;
                rotate_left(t, father);
                brother = father->right;
            }

            if (get_color(brother ? brother->left : nullptr) == BLACK &&
                get_color(brother ? brother->right : nullptr) == BLACK) {
                // 情况2：兄弟黑，兄弟的两个孩子也黑
                if (brother != nullptr) brother->color = RED;
                x = father;               // 缺少的黑高向上转移
                father = x->parent;
                if (father != nullptr) x_is_left = (x == father->left);
            }
            else {
                if (get_color(brother->right) == BLACK) {
                    // 情况3：兄弟黑，近侄红、远侄黑
                    if (brother->left != nullptr) brother->left->color = BLACK;
                    brother->color = RED;
                    rotate_right(t, brother);
                    brother = father->right;
                }
                // 情况4：远侄红，调整后可以结束修复
                brother->color = father->color;
                father->color = BLACK;
                if (brother->right != nullptr) brother->right->color = BLACK;
                rotate_left(t, father);
                x = t;
            }
        }
        else {
            // 右孩子情况与左孩子完全对称
            TreeNode *brother = father->left;

            if (get_color(brother) == RED) {
                brother->color = BLACK;
                father->color = RED;
                rotate_right(t, father);
                brother = father->left;
            }

            if (get_color(brother ? brother->left : nullptr) == BLACK &&
                get_color(brother ? brother->right : nullptr) == BLACK) {
                if (brother != nullptr) brother->color = RED;
                x = father;
                father = x->parent;
                if (father != nullptr) x_is_left = (x == father->left);
            }
            else {
                if (get_color(brother->left) == BLACK) {
                    if (brother->right != nullptr) brother->right->color = BLACK;
                    brother->color = RED;
                    rotate_left(t, brother);
                    brother = father->left;
                }
                brother->color = father->color;
                father->color = BLACK;
                if (brother->left != nullptr) brother->left->color = BLACK;
                rotate_right(t, father);
                x = t;
            }
        }
    }
    if (x != nullptr) x->color = BLACK;
}

// 14. 删除指定结点
// 时间O(log n)，空间O(1)
// 先按BST规则删除；如果实际移走黑结点，则修复红黑性质
bool delete_tree(TreeNode *&t, int key) {
    TreeNode *z = search_tree_b(t, key);
    if (z == nullptr) return false;

    TreeNode *y = z;               // y是实际被移走原位置的结点
    Color old_color = y->color;
    TreeNode *x = nullptr;         // x是接替y原位置的孩子（可能为空）
    TreeNode *father = nullptr;    // x的父结点
    bool x_is_left = false;        // x为空时记录其原本的位置

    if (z->left == nullptr) {
        x = z->right;
        father = z->parent;
        if (father != nullptr) x_is_left = (z == father->left);
        transplant(t, z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        father = z->parent;
        if (father != nullptr) x_is_left = (z == father->left);
        transplant(t, z, z->left);
    }
    else {
        // 两个孩子：用右子树最小结点（中序后继）接替z
        y = find_min(z->right);
        old_color = y->color;
        x = y->right;              // y没有左孩子

        if (y->parent == z) {
            // 后继就是z的右孩子
            father = y;
            x_is_left = false;     // x位于y的右侧
            if (x != nullptr) x->parent = y;
        }
        else {
            // 先将y从原位置摘下
            father = y->parent;
            x_is_left = true;      // y是其父结点的左孩子
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        // 将y放到z原来的位置，并继承z的颜色
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;
    if (old_color == BLACK) fix_delete(t, x, father, x_is_left);
    if (t != nullptr) t->color = BLACK;
    return true;
}

// 15. 中序遍历：输出关键字（应当严格递增）
// 时间O(n)，空间O(log n)
void inorder(TreeNode *t) {
    if (t == nullptr) return;
    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}

// 16. 先序遍历：R红、B黑，方便观察调整结果
// 时间O(n)，空间O(log n)
void preorder(TreeNode *t) {
    if (t == nullptr) return;
    cout << t->data << "(" << (t->color == RED ? "R" : "B") << ") ";
    preorder(t->left);
    preorder(t->right);
}

// 17. 检查红黑树性质，返回当前子树的黑高
// 时间O(n)，空间O(log n)
// 空NIL的黑高记为1；只要各路径口径一致即可
int check_black_height(TreeNode *t, TreeNode *father,
                       long long low, long long high, bool &ok) {
    if (t == nullptr) return 1;

    if (t->parent != father || t->data <= low || t->data >= high)
        ok = false;                // 父指针和BST大小关系
    if (t->color == RED &&
        (get_color(t->left) == RED || get_color(t->right) == RED))
        ok = false;                // 红结点不能有红孩子

    int lh = check_black_height(t->left, t, low, t->data, ok);
    int rh = check_black_height(t->right, t, t->data, high, ok);
    if (lh != rh) ok = false;      // 左右黑高必须相同
    return lh + (t->color == BLACK ? 1 : 0);
}

bool check_red_black(TreeNode *t) {
    bool ok = true;
    if (t != nullptr && (t->color != BLACK || t->parent != nullptr))
        ok = false;
    check_black_height(t, nullptr, LLONG_MIN, LLONG_MAX, ok);
    return ok;
}

// 18. 销毁红黑树：后序释放结点
// 时间O(n)，空间O(log n)
void destroy_tree(TreeNode *&t) {
    if (t == nullptr) return;
    destroy_tree(t->left);
    destroy_tree(t->right);
    delete t;
    t = nullptr;
}

// 19. 主函数：测试插入、查找、删除及红黑树性质
int main() {
    int arr[] = {30, 10, 20, 40, 50, 25, 5, 35, 45, 60, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    TreeNode *root = create_tree(arr, n);

    cout << "初始中序遍历：";
    inorder(root);
    cout << "\n初始先序遍历：";
    preorder(root);
    cout << "\n红黑树检查：" << (check_red_black(root) ? "通过" : "失败") << "\n";

    cout << "递归查找25：" << (search_tree_a(root, 25) ? "找到" : "未找到") << "\n";
    cout << "循环查找99：" << (search_tree_b(root, 99) ? "找到" : "未找到") << "\n";
    if (root != nullptr)
        cout << "最小值：" << find_min(root)->data
             << "，最大值：" << find_max(root)->data << "\n";

    int del[] = {10, 30, 40, 25, 5, 60, 20, 35, 45, 15, 50};
    for (int key : del) {
        cout << "\n删除 " << key << "：" << (delete_tree(root, key) ? "成功" : "失败");
        cout << "\n中序遍历：";
        inorder(root);
        cout << "\n红黑树检查：" << (check_red_black(root) ? "通过" : "失败") << "\n";
    }
    destroy_tree(root);
    return 0;
}
