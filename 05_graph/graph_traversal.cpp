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

//添加无向边
bool addEdge(Graph *g,int v1,int v2){
    if(v1<0 || v1>=g->vertexCount ||
       v2<0 || v2>=g->vertexCount) return false;

    EdgeNode *e1 = new EdgeNode;
    e1->adjVertex = v2;
    e1->next = g->vertices[v1].firstEdge;
    g->vertices[v1].firstEdge = e1;

    EdgeNode *e2 = new EdgeNode;
    e2->adjVertex = v1;
    e2->next = g->vertices[v2].firstEdge;
    g->vertices[v2].firstEdge = e2;

    g->edgeCount++;

    return true;
}

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

void DFS(Graph *g,int v){
    visit(g,v);
    visited[v] = true;
    EdgeNode *n = g->vertices[v].firstEdge;
    while(n!=nullptr){
        if(!visited[n->adjVertex])
            DFS(g,n->adjVertex);
        n = n->next;
    }
}

void DFSTraverse(Graph *g){
    if(g->vertexCount==0) return;
    for(int i=0;i<g->vertexCount;i++){
        visited[i] = false;
    }
    for(int i=0;i<g->vertexCount;i++){
        if(!visited[i]){
            DFS(g,i);
        }
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
    Graph g;
    init(&g);

    // 添加顶点
    addVertex(&g,'A');   // 0
    addVertex(&g,'B');   // 1
    addVertex(&g,'C');   // 2
    addVertex(&g,'D');   // 3
    addVertex(&g,'E');   // 4
    addVertex(&g,'F');   // 5
    addVertex(&g,'G');   // 6

    // 添加边
    addEdge(&g,0,1);     // A-B
    addEdge(&g,0,2);     // A-C
    addEdge(&g,1,3);     // B-D
    addEdge(&g,1,4);     // B-E
    addEdge(&g,2,4);     // C-E

    // F-G单独构成另一个连通分量
    addEdge(&g,5,6);     // F-G

    cout<<"BFS: ";
    BFSTraverse(&g);
    cout<<endl;

    cout<<"DFS: ";
    DFSTraverse(&g);
    cout<<endl;

    return 0;
}