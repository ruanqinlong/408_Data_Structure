// 图的邻接多重表存储（无向图）
#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 100;

// 边结点
struct EdgeNode {
    int iVertex, jVertex;      // 边的两个端点
    int weight;                // 权值
    EdgeNode *iLink;           // 下一条依附于 iVertex 的边
    EdgeNode *jLink;           // 下一条依附于 jVertex 的边
};

// 顶点结点
struct VertexNode {
    char data;
    EdgeNode *firstEdge;
};

// 邻接多重表
struct Graph {
    VertexNode vertices[MAX_SIZE];
    int vertexCount;
    int edgeCount;
};


// 初始化
void init(Graph *g){
    g->vertexCount = 0;
    g->edgeCount = 0;
    for(int i=0;i<MAX_SIZE;i++){
        g->vertices[i].firstEdge = nullptr;
    }
}

// 添加顶点
bool addVertex(Graph *g, char v){
    if(g->vertexCount>=MAX_SIZE) return false;
    g->vertices[g->vertexCount++].data = v;
    return true;
}

// 判断两顶点是否相邻
bool isAdjacent(Graph *g, int v1, int v2){
    if(v1<0||v1>=g->vertexCount||
        v2<0||v2>=g->vertexCount||
        g->vertices[v1].firstEdge==nullptr) return false;
    EdgeNode *edge = g->vertices[v1].firstEdge;
    while (edge!=nullptr)
    {
        if(edge->iVertex == v2 || edge->jVertex == v2) return true;
        if(edge->iVertex==v1){
            edge = edge->iLink;
        }else if(edge->jVertex==v1){
            edge = edge->jLink;
        }
    }
    return false;
}

// 添加边
bool addEdge(Graph *g, int v1, int v2, int weight){
    if(v1<0||v1>=g->vertexCount|| v2<0||v2>=g->vertexCount) return false;
    if(isAdjacent(g, v1, v2)) return false;
    EdgeNode *edge = new EdgeNode;
    edge->iVertex = v1;
    edge->jVertex = v2;
    edge->weight = weight;
    edge->iLink = g->vertices[v1].firstEdge;
    g->vertices[v1].firstEdge = edge;
    edge->jLink = g->vertices[v2].firstEdge;
    g->vertices[v2].firstEdge = edge;
    g->edgeCount++;
    return true;
}

// 求顶点的度
int getDegree(Graph *g, int v){
    if(v<0||v>=g->vertexCount) return 0;
    int count = 0;
    EdgeNode *node = g->vertices[v].firstEdge;
    while(node!=nullptr){
        if(node->iVertex == v){
            node = node->iLink;
        }else{
            node = node->jLink;
        }
        count++;
    }
    return count;
}
int main(){
    Graph g;
    init(&g);

    // 添加顶点
    addVertex(&g, 'A');  // 0
    addVertex(&g, 'B');  // 1
    addVertex(&g, 'C');  // 2
    addVertex(&g, 'D');  // 3
    addVertex(&g, 'E');  // 4

    // 添加边
    addEdge(&g, 0, 1, 10);  // A-B
    addEdge(&g, 0, 2, 20);  // A-C
    addEdge(&g, 1, 3, 30);  // B-D
    addEdge(&g, 2, 3, 40);  // C-D
    addEdge(&g, 2, 4, 50);  // C-E
    addEdge(&g, 3, 4, 60);  // D-E

    // 测试顶点数和边数
    cout << "vertexCount: " << g.vertexCount << endl;
    cout << "edgeCount: " << g.edgeCount << endl;

    // 测试相邻关系
    cout << "A-B: " << isAdjacent(&g, 0, 1) << endl;
    cout << "B-A: " << isAdjacent(&g, 1, 0) << endl;
    cout << "A-D: " << isAdjacent(&g, 0, 3) << endl;
    cout << "C-E: " << isAdjacent(&g, 2, 4) << endl;

    // 测试各顶点的度
    for(int i = 0; i < g.vertexCount; i++){
        cout << g.vertices[i].data
             << " degree: "
             << getDegree(&g, i)
             << endl;
    }

    return 0;
}