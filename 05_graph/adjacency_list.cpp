// 图的邻接表存储
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


int main(){
    
    return 0;
}