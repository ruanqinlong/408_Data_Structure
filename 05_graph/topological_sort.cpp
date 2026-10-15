
#include <bits/stdc++.h>
using namespace std;

// 拓扑排序：使用邻接表实现
// 每次将入度为0的结点纳入序列，并删除其相关的出边
// 时间复杂度 O(V+E)，空间复杂度 O(V+E)

const int MAX_SIZE = 100;

struct EdgeNode {
    int adjVertex;       // 当前边结点对应的邻接顶点下标
    EdgeNode *next;      // 指向下一个边结点
};

struct VertexNode {
    char data;
    EdgeNode *firstEdge;
};

struct Graph {
    VertexNode vertices[MAX_SIZE];
    int vertexCount;     // 点数量
    int edgeCount;       // 边数量
};

// 初始化
void init(Graph *g) {
    g->edgeCount = 0;
    g->vertexCount = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        g->vertices[i].firstEdge = nullptr;
    }
}

// 添加顶点
bool addVertex(Graph *g, char v) {
    if (g->vertexCount >= MAX_SIZE)
        return false;

    g->vertices[g->vertexCount++].data = v;
    return true;
}

// 判断是否相邻（是否存在v1指向v2的弧）
bool isAdjacent(Graph *g, int v1, int v2) {
    if (v1 < 0 || v1 >= g->vertexCount ||
        v2 < 0 || v2 >= g->vertexCount ||
        g->vertices[v1].firstEdge == nullptr)
        return false;

    EdgeNode *e = g->vertices[v1].firstEdge;

    while (e != nullptr) {
        if (e->adjVertex == v2) {
            return true;
        }
        e = e->next;
    }

    return false;
}

// 添加有向边 v1 -> v2
bool addEdge(Graph *g, int v1, int v2) {
    if (v1 < 0 || v1 >= g->vertexCount ||
        v2 < 0 || v2 >= g->vertexCount)
        return false;

    // 不允许自环和重复边
    if (v1 == v2 || isAdjacent(g, v1, v2))
        return false;

    EdgeNode *e = new EdgeNode;
    e->adjVertex = v2;
    e->next = g->vertices[v1].firstEdge;
    g->vertices[v1].firstEdge = e;

    g->edgeCount++;

    return true;
}

// 获取某顶点的出度
int getDegree(Graph *g, int v) {
    if (v < 0 || v >= g->vertexCount)
        return -1;

    int res = 0;
    EdgeNode *e = g->vertices[v].firstEdge;

    while (e != nullptr) {
        res++;
        e = e->next;
    }

    return res;
}

// 摧毁图，释放动态分配的边表结点
void destroy(Graph *g) {
    for (int i = 0; i < g->vertexCount; i++) {
        EdgeNode *e = g->vertices[i].firstEdge;

        while (e != nullptr) {
            EdgeNode *temp = e;
            e = e->next;
            delete temp;
        }

        g->vertices[i].firstEdge = nullptr;
    }

    g->vertexCount = 0;
    g->edgeCount = 0;
}

// 记录各个顶点的入度
int indegree[MAX_SIZE];

// 拓扑排序
void topologicalSort(Graph *g) {
    if (g->vertexCount == 0)
        return;

    queue<int> q;

    // 初始化入度数组
    for (int i = 0; i < g->vertexCount; i++) {
        indegree[i] = 0;
    }

    // 统计入度
    for (int i = 0; i < g->vertexCount; i++) {
        EdgeNode *e = g->vertices[i].firstEdge;

        while (e != nullptr) {
            indegree[e->adjVertex]++;
            e = e->next;
        }
    }

    // 获取入度为0的结点
    for (int i = 0; i < g->vertexCount; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int count = 0;

    // 按队列中的顺序出队
    // 出队时逻辑删除其出边，将对应弧头的入度减1
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << g->vertices[u].data << " ";
        count++;

        EdgeNode *e = g->vertices[u].firstEdge;

        while (e != nullptr) {
            indegree[e->adjVertex]--;

            if (indegree[e->adjVertex] == 0) {
                q.push(e->adjVertex);
            }

            e = e->next;
        }
    }

    cout << endl;

    // 判断是否存在有向环
    if (count < g->vertexCount) {
        cout << "图中存在有向环，无法完成拓扑排序" << endl;
    }
}

int main() {
    Graph g;
    init(&g);

    // 添加顶点
    addVertex(&g, 'A');  // 0
    addVertex(&g, 'B');  // 1
    addVertex(&g, 'C');  // 2
    addVertex(&g, 'D');  // 3
    addVertex(&g, 'E');  // 4
    addVertex(&g, 'F');  // 5

    // 添加有向边
    addEdge(&g, 0, 1);   // A -> B
    addEdge(&g, 0, 2);   // A -> C
    addEdge(&g, 1, 3);   // B -> D
    addEdge(&g, 2, 3);   // C -> D
    addEdge(&g, 2, 4);   // C -> E
    addEdge(&g, 3, 5);   // D -> F
    addEdge(&g, 4, 5);   // E -> F

    // 输出图的基本信息
    cout << "顶点数：" << g.vertexCount << endl;
    cout << "边数：" << g.edgeCount << endl;

    // 输出各顶点的出度
    cout << "各顶点出度：" << endl;
    for (int i = 0; i < g.vertexCount; i++) {
        cout << g.vertices[i].data << ": "
             << getDegree(&g, i) << endl;
    }

    // 拓扑排序
    cout << "拓扑排序结果：" << endl;
    topologicalSort(&g);

    // 释放内存
    destroy(&g);

    return 0;
}
