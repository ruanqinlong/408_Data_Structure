// 图的十字链表存储（有向图）
#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 100;

// 弧结点
struct ArcNode {
    int tailVertex,headVertex;//从tailVertex结点到headVertex结点
    int weight;//权值
    ArcNode *headLink;  // 下一条具有相同弧头的弧
    ArcNode *tailLink;  // 下一条具有相同弧尾的弧
};

// 顶点结点
struct VertexNode {
    char data;
    ArcNode *firstIn,*firstOut;
};

// 十字链表
struct Graph {
    VertexNode vertices[MAX_SIZE];
    int vertexCount;
    int edgeCount;
};

// 初始化
void init(Graph *g){
    g->edgeCount = 0;
    g->vertexCount = 0;

    for(int i = 0; i < MAX_SIZE; i++){
        g->vertices[i].firstIn = nullptr;
        g->vertices[i].firstOut = nullptr;
    }
}

// 添加顶点
bool addVertex(Graph *g, char v){
    if(g->vertexCount>=MAX_SIZE) return false;
    g->vertices[g->vertexCount++].data = v;

    return true;
}

// 判断是否存在弧 v1 -> v2
bool isAdjacent(Graph *g, int v1, int v2){
    if(v1<0||v1>=g->vertexCount||
        v2<0||v2>=g->vertexCount) 
        return false;
    ArcNode *node = g->vertices[v1].firstOut;
    while(node!=nullptr){
        if(node->headVertex==v2){
            return true;
        }
        node = node->tailLink;
    }
    return false;
}

// 添加弧 v1 -> v2
bool addArc(Graph *g, int v1, int v2, int weight){
    if(v1 < 0 || v1 >= g->vertexCount ||
       v2 < 0 || v2 >= g->vertexCount)
        return false;

    if(isAdjacent(g, v1, v2))
        return false;

    // 创建唯一的弧结点
    ArcNode *node = new ArcNode;

    node->tailVertex = v1;
    node->headVertex = v2;
    node->weight = weight;

    // 插入 v1 的出弧链
    node->tailLink = g->vertices[v1].firstOut;//头插法
    g->vertices[v1].firstOut = node;

    // 同一个结点插入 v2 的入弧链
    node->headLink = g->vertices[v2].firstIn;
    g->vertices[v2].firstIn = node;

    g->edgeCount++;

    return true;
}

// 求顶点的入度
int getInDegree(Graph *g, int v){
    if(v < 0 || v >= g->vertexCount)
        return 0;
    int count = 0;
    ArcNode *n = g->vertices[v].firstIn;
    while(n!=nullptr){
        count++;
        n = n->headLink;
    }
    return count;
}

// 求顶点的出度
int getOutDegree(Graph *g, int v){
    if(v < 0 || v >= g->vertexCount)
        return 0;
    int count = 0;
    ArcNode *n = g->vertices[v].firstOut;
    while(n!=nullptr){
        n = n->tailLink;
        count++;
    }
    return count;
}
int main() {
    Graph g;
    init(&g);

    // 添加顶点
    addVertex(&g, 'A');  // 下标 0
    addVertex(&g, 'B');  // 下标 1
    addVertex(&g, 'C');  // 下标 2
    addVertex(&g, 'D');  // 下标 3

    // 添加弧
    addArc(&g, 0, 1, 10);  // A -> B
    addArc(&g, 0, 2, 20);  // A -> C
    addArc(&g, 2, 1, 30);  // C -> B
    addArc(&g, 2, 3, 40);  // C -> D

    // 基本信息
    cout << "vertexCount: " << g.vertexCount << endl;
    cout << "edgeCount: " << g.edgeCount << endl;

    // 测试相邻关系
    cout << "A -> B: " << isAdjacent(&g, 0, 1) << endl;
    cout << "B -> A: " << isAdjacent(&g, 1, 0) << endl;
    cout << "C -> D: " << isAdjacent(&g, 2, 3) << endl;
    cout << "D -> C: " << isAdjacent(&g, 3, 2) << endl;

    // 测试每个顶点的入度和出度
    for(int i = 0; i < g.vertexCount; i++){
        cout << g.vertices[i].data
             << "  inDegree: " << getInDegree(&g, i)
             << "  outDegree: " << getOutDegree(&g, i)
             << endl;
    }

    return 0;
}