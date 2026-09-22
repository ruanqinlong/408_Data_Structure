// 线索二叉树
#include<bits/stdc++.h>

using namespace std;

/*
    线索二叉树，对于原二叉树的一种拓展，对于原二叉树会产生前序、中序、后序遍历，遍历会得到固定的序列
    为解决从结点出发，求该种遍历下的序列的结点前驱和后继问题，提出了线索二叉树
    对于每个不为空的结点，若其左右子结点为空，则按左子结点存储根节点前驱，右子结点存储根节点后继这种辅助数据
*/

struct Node{
    int data;
    Node *left,*right;
    //tag变量为1 表示这个结点存储的是前驱后继信息，而非下一个结点信息
    int ltag,rtag;

    Node(int value){
        data = value;
        left = NULL;
        right = NULL;
        ltag = 0;
        rtag = 0;
    }
};

//实时存储当前访问结点的前驱结点
Node *pre = NULL;

//对结点进行遍历，在符合条件的情况下修改其前驱和前驱结点的后继信息（是前驱结点的后继，不是当前结点的后继）
void visit(Node *root){
    if(root->left==NULL){
        root->ltag = 1;
        root->left = pre;
    }
    if(pre!=NULL && pre->right==NULL){
        pre->rtag  = 1;
        pre->right = root;
    }
    pre = root;
}



//前中后序遍历的形式构建对应的线索二叉树
void preOrder(Node *root){
    if(root==NULL) return;

    visit(root);
    if(root->ltag == 0)
        preOrder(root->left);
    if(root->rtag == 0)
        preOrder(root->right);
}
void inOrder(Node *root){
    if(root==NULL) return;

    inOrder(root->left);
    visit(root);
    inOrder(root->right);
}
void postOrder(Node *root){
    if(root==NULL) return;

    postOrder(root->left);
    postOrder(root->right);
    visit(root);
}

//构造线索二叉树的主函数,并在此处处理最后一个元素的后继结点
void createPreThread(Node *root){
    pre = NULL;

    if(root!=NULL){
        preOrder(root);

        if(pre->right==NULL){
            pre->rtag  = 1;
            pre->right = NULL;
        }
    }
}
void createInThread(Node *root){
    pre = NULL;

    if(root!=NULL){
        inOrder(root);

        if(pre->right==NULL){
            pre->rtag  = 1;
            pre->right = NULL;
        }
    }
}
void createPostThread(Node *root){
    pre = NULL;

    if(root!=NULL){
        postOrder(root);

        if(pre->right==NULL){
            pre->rtag  = 1;
            pre->right = NULL;
        }
    }
}

int main(){

    return 0;
}