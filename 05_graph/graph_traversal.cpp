// 图的 BFS 与 DFS 遍历   使用邻接表法来实现的程序
#include<bits/stdc++.h>

using namespace std;


const int MAX_SIZE = 100;

struct EdgeNode{
    int adjVertex;   // 当前边结点对应的邻接顶点下标
    EdgeNode *next;  // 指向下一个边结点
};

struct VertexNode{
    char data;
    EdgeNode *firstEdge;
};

struct Graph{
    VertexNode vertices[MAX_SIZE];
    int vertexCount;//点数量
    int edgeCount;//边数量
};


bool visited[MAX_SIZE] = {false};

void init(Graph *g){
    g->edgeCount = 0;
    g->vertexCount = 0;
    for(int i=0;i<MAX_SIZE;i++){
        g->vertices[i].firstEdge = nullptr;
    }
}

//添加顶点
bool addVertex(Graph *g, char v){
    if(g->vertexCount>=MAX_SIZE) return false;
    g->vertices[g->vertexCount++].data=v;
    return true;
}

//判断是否相邻
bool isAdjacent(Graph *g, int v1, int v2){
    if(v1<0||v1>=g->vertexCount||
        v2<0||v2>=g->vertexCount||
        g->vertices[v1].firstEdge==nullptr) return false;
    EdgeNode *e = g->vertices[v1].firstEdge;
    while(e != nullptr){
        if(e->adjVertex == v2){
            return true;
        }
        e = e->next;
    }
    return false;
}

//添加边
bool addEdge(Graph *g, int v1, int v2);

//获取度
int getDegree(Graph *g, int v);

//摧毁
void destroy(Graph *g);

//访问函数
void visit(Graph *g,int v){
    cout<<g->vertices[v].data<<" ";
}

//广度优先搜索程序，只能处理连通部分
void BFS(Graph *g,int v){
    queue<int> q;//辅助队列
    q.push(v);
    visited[v] = true;
    while(!q.empty()){
        visit(g,q.front());
        EdgeNode *n = g->vertices[q.front()].firstEdge;
        while(n!=nullptr){
            if(!visited[n->adjVertex]){
                q.push(n->adjVertex);
                visited[n->adjVertex] = true;
            }
            n = n->next;
        }
        q.pop();
    }
}

//整个图的广度优先遍历程序，可以处理非连通图
void BFSTraverse(Graph *g){
    if(g->vertexCount==0) return;
    for(int i=0;i<g->vertexCount;i++){
        visited[i] = false;
    }
    for(int i=0;i<g->vertexCount;i++){
        if(!visited[i]){
            BFS(g,i);
        }
    }
}


int main(){

    return 0;
}