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
void visitCreate(Node *root){
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

void visit(Node *root){
    cout<<root->data<<" ";
}



//前中后序遍历的形式构建对应的线索二叉树
void preOrder(Node *root){
    if(root==NULL) return;

    visitCreate(root);
    if(root->ltag == 0)
        preOrder(root->left);
    if(root->rtag == 0)
        preOrder(root->right);
}
void inOrder(Node *root){
    if(root==NULL) return;

    inOrder(root->left);
    visitCreate(root);
    inOrder(root->right);
}
void postOrder(Node *root){
    if(root==NULL) return;

    postOrder(root->left);
    postOrder(root->right);
    visitCreate(root);
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

//使用前序线索二叉树，来寻找结点的前驱
Node *prePred(Node *root){
    // 使用前序线索二叉树寻找结点 p 的前驱
    // 1. 若 p->ltag == 1，则 p->left 直接指向其前序前驱
    //
    // 2. 若 p->ltag == 0，则无法通过 p 自身直接得到前驱，
    //    需要找到 p 的父结点 parent：
    //    ① p 是 parent 的左孩子：
    //       p 的前驱为 parent
    //
    //    ② p 是 parent 的右孩子，且 parent 没有左子树：
    //       p 的前驱为 parent
    //
    //    ③ p 是 parent 的右孩子，且 parent 有左子树：
    //       p 的前驱为 parent 左子树中最后一个被前序遍历的结点
    //
    // 3. 若 p 是整棵树的根结点，则 p 没有前序前驱
    //
    // 注意：当前 Node 结构体没有 parent 父指针，
    // 因此在 ltag == 0 时不能仅凭 p 直接找到其父结点。
    // 若要完整实现，需要增加父指针，或从根结点重新查找父结点。
    // 本代码暂不实现 prePred()。
}
Node *preSucc(Node *root){

    // 如果 rtag == 0，right 仍然是右孩子指针
    if(root->rtag == 0){
        // 有左孩子：前序遍历下，左孩子就是后继
        if(root->ltag == 0)
            return root->left;
        // 没有左孩子：进入右孩子
        else
            return root->right;
    }else{
        // rtag == 1，right 已经是后继线索
        return root->right;
    }
}

Node *inPred(Node *root){

}
Node *inSucc(Node *root){
    
}

Node *postPred(Node *root){
    if(root->ltag) return root->left;
    if(root->rtag==0) return root->right;
    else return root->left;
}
Node *postSucc(Node *root){
    // 使用后序线索二叉树寻找结点 p 的后继
    //
    // 1. 若 p->rtag == 1，则 p->right 直接指向其后序后继
    //
    // 2. 若 p->rtag == 0，则无法仅通过 p 自身直接得到后继，
    //    需要找到 p 的父结点 parent：
    //
    //    ① p 是 parent 的右孩子：
    //       p 的后继为 parent
    //
    //    ② p 是 parent 的左孩子，且 parent 没有右子树：
    //       p 的后继为 parent
    //
    //    ③ p 是 parent 的左孩子，且 parent 有右子树：
    //       p 的后继为 parent 右子树中第一个被后序遍历的结点
    //
    // 3. 若 p 是整棵树的根结点，则 p 没有后序后继
    //
    // 注意：当前 Node 结构体没有 parent 父指针，
    // 因此某些情况下无法仅凭 p 找到其后序后继。
    // 若要完整实现，需要增加父指针，或从根结点重新寻找父结点。
    // 本代码暂不实现 postSucc()。
}


int main(){

    return 0;
}