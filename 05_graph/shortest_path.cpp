
#include <bits/stdc++.h>
using namespace std;

// 最短路径：BFS、Dijkstra、Floyd

const int MAX_SIZE = 100;

struct EdgeNode{
    int adjVertex;    // 当前边结点对应的邻接顶点下标
    EdgeNode *next;   // 指向下一个边结点
};

struct VertexNode{
    char data;
    EdgeNode *firstEdge;
};

struct Graph{
    VertexNode vertices[MAX_SIZE];
    int vertexCount;  // 顶点数
    int edgeCount;    // 边数
};

bool visited[MAX_SIZE] = {false};

// 初始化
void init(Graph *g){
    g->edgeCount = 0;
    g->vertexCount = 0;

    for(int i=0;i<MAX_SIZE;i++){
        g->vertices[i].firstEdge = nullptr;
    }
}

// 添加顶点
bool addVertex(Graph *g,char v){
    if(g->vertexCount>=MAX_SIZE) return false;

    g->vertices[g->vertexCount++].data = v;
    return true;
}

// 判断是否相邻
bool isAdjacent(Graph *g,int v1,int v2){
    if(v1<0 || v1>=g->vertexCount ||
       v2<0 || v2>=g->vertexCount)
        return false;

    EdgeNode *e = g->vertices[v1].firstEdge;

    while(e!=nullptr){
        if(e->adjVertex==v2){
            return true;
        }
        e = e->next;
    }

    return false;
}

// 添加无向边
bool addEdge(Graph *g,int v1,int v2){
    if(v1<0 || v1>=g->vertexCount ||
       v2<0 || v2>=g->vertexCount)
        return false;

    if(v1==v2 || isAdjacent(g,v1,v2))
        return false;

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

// 获取顶点的度
int getDegree(Graph *g,int v){
    if(v<0 || v>=g->vertexCount) return -1;

    int res = 0;
    EdgeNode *e = g->vertices[v].firstEdge;

    while(e!=nullptr){
        res++;
        e = e->next;
    }

    return res;
}

// 销毁图
void destroy(Graph *g){
    if(g==nullptr) return;

    for(int i=0;i<g->vertexCount;i++){
        EdgeNode *p = g->vertices[i].firstEdge;

        while(p!=nullptr){
            EdgeNode *t = p;
            p = p->next;
            delete t;
        }

        g->vertices[i].firstEdge = nullptr;
    }

    delete g;
}

// BFS求无权图两点间的最短距离
int BFSMinDistance(Graph *g,int start,int end){
    if(g==nullptr || g->vertexCount==0 ||
       start<0 || start>=g->vertexCount ||
       end<0 || end>=g->vertexCount) return -1;

    int dis[MAX_SIZE];

    for(int i=0;i<g->vertexCount;i++){
        dis[i] = -1;
        visited[i] = false;
    }

    queue<int> q;
    q.push(start);
    dis[start] = 0;
    visited[start] = true;

    while(!q.empty()){
        int v = q.front();

        EdgeNode *n = g->vertices[v].firstEdge;

        while(n!=nullptr){
            if(!visited[n->adjVertex]){
                q.push(n->adjVertex);
                dis[n->adjVertex] = dis[v]+1;
                visited[n->adjVertex] = true;
            }

            n = n->next;
        }

        q.pop();
    }

    return dis[end];
}

int main(){
    Graph *g = new Graph;
    init(g);

    // 添加顶点
    addVertex(g,'A');  // 0
    addVertex(g,'B');  // 1
    addVertex(g,'C');  // 2
    addVertex(g,'D');  // 3
    addVertex(g,'E');  // 4
    addVertex(g,'F');  // 5
    addVertex(g,'G');  // 6

    // 添加无向边
    addEdge(g,0,1);  // A-B
    addEdge(g,0,2);  // A-C
    addEdge(g,1,3);  // B-D
    addEdge(g,2,3);  // C-D
    addEdge(g,2,4);  // C-E
    addEdge(g,3,5);  // D-F
    addEdge(g,4,5);  // E-F

    // G不与任何顶点连接

    cout<<"A到F的最短距离: "
        <<BFSMinDistance(g,0,5)<<endl;

    cout<<"A到G的最短距离: "
        <<BFSMinDistance(g,0,6)<<endl;

    cout<<"A到A的最短距离: "
        <<BFSMinDistance(g,0,0)<<endl;

    cout<<"B到E的最短距离: "
        <<BFSMinDistance(g,1,4)<<endl;

    destroy(g);

    return 0;
}
