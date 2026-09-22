/*
 * 408 考研数据结构：二叉树
 *
 * 本程序用于学习和练习二叉树的基本操作，当前包括：
 * 1. 二叉树结点结构
 * 2. 前序遍历
 * 3. 中序遍历
 * 4. 后序遍历
 * 5. 层序遍历
 *
 * 后续可以继续在本文件中补充：
 * 求二叉树高度、统计总结点数、统计叶子结点、
 * 统计度为 1 和度为 2 的结点、交换左右子树等递归操作。
 */

#include<bits/stdc++.h>

using namespace std;

//结点结构体
struct Node{
    int data;
    Node *left,*right;

    Node(int value){
        data = value;
        left = NULL;
        right = NULL;
    }
};

//访问函数
void visit(Node *root){
    cout<<root->data<<" ";
}

//前中后序遍历
void preorder(Node *root){
    if(root==NULL) return;
    visit(root);
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node *root){
    if(root==NULL) return;
    inorder(root->left);
    visit(root);
    inorder(root->right);
}
void postorder(Node *root){
    if(root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    visit(root);
}

//层序遍历
void levelorder(Node *root){
    if(root==NULL) return;
    queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        Node *p = q.front();
        q.pop();

        visit(p);
        if(p->left != NULL){
            q.push(p->left);
        }
        if(p->right != NULL){
            q.push(p->right);
        }
    }
}

//求二叉树高度

//统计总结点数

//统计叶子结点

//统计度为1的结点数

//统计度为2的结点数

int main(){

    /*
                 1
               /   \
              2     3
             / \     \
            4   5     6
               /
              7
    */

    Node *root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->right = new Node(6);

    root->left->right->left = new Node(7);

    cout << "前序遍历：";
    preorder(root);
    cout << endl;

    cout << "中序遍历：";
    inorder(root);
    cout << endl;

    cout << "后序遍历：";
    postorder(root);
    cout << endl;

    cout << "层序遍历：";
    levelorder(root);
    cout << endl;

    return 0;
}
