// 并查集
#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 50;

int parent[MAX_SIZE];

// 初始化并查集
void initSet(int set[]){
    for(int i = 0; i < MAX_SIZE; i++){
        set[i] = -1;
    }
}

// 查找结点x所在集合的根结点
int findRoot(int set[], int x){
    int root = x;
    while(set[root] >= 0) root = set[root];
    while(x!=root){
        int t = set[x];//获取父结点下标
        set[x] = root;//直接将x结点挂在根结点下
        x = t;
    }
    
    return x;
}

// 合并两个集合
// root1和root2必须是两个集合的根结点
bool unionSet(int set[], int root1, int root2){
    if(root1 == root2){
        return false;
    }

    // 将root2所在的树合并到root1下面
    set[root2] = root1;

    return true;
}

int main(){

    initSet(parent);

    // 0、1最初都是根结点
    unionSet(parent, 0, 1);

    // 此时0是根结点，2也是根结点
    unionSet(parent, 0, 2);

    // 3、4都是根结点
    unionSet(parent, 3, 4);

    cout << "0的根结点：" << findRoot(parent, 0) << endl;
    cout << "1的根结点：" << findRoot(parent, 1) << endl;
    cout << "2的根结点：" << findRoot(parent, 2) << endl;
    cout << "3的根结点：" << findRoot(parent, 3) << endl;
    cout << "4的根结点：" << findRoot(parent, 4) << endl;

    return 0;
}