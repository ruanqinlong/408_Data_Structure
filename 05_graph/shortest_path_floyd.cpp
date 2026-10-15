// 用邻接矩阵实现Floyd算法
// 时间复杂度：O(n^3)
// 空间复杂度：O(n^2)

#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100;
const long long INF = LLONG_MAX / 4;

struct Graph {
    char vertices[MAX_SIZE];             // 顶点表
    long long edges[MAX_SIZE][MAX_SIZE];  // 邻接矩阵
    int vertexCount;                      // 顶点数
    int edgeCount;                        // 边数
};

// 初始化
void init(Graph *g) {
    g->vertexCount = 0;
    g->edgeCount = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (i == j)
                g->edges[i][j] = 0;
            else
                g->edges[i][j] = INF;
        }
    }
}

// 增加顶点
bool addVertex(Graph *g, char v) {
    if (g->vertexCount >= MAX_SIZE)
        return false;

    g->vertices[g->vertexCount++] = v;
    return true;
}

// 判断两点是否相邻
bool isAdjacent(Graph *g, int v1, int v2) {
    if (v1 < 0 || v1 >= g->vertexCount ||
        v2 < 0 || v2 >= g->vertexCount)
        return false;

    return v1 != v2 && g->edges[v1][v2] != INF;
}

// 增加边（无向图，非负权）
bool addEdge(Graph *g, int v1, int v2, long long weight) {
    if (v1 < 0 || v1 >= g->vertexCount ||
        v2 < 0 || v2 >= g->vertexCount)
        return false;

    // 本实现不考虑自环和重边
    if (v1 == v2 || weight < 0 || weight >= INF)
        return false;

    if (isAdjacent(g, v1, v2))
        return false;

    g->edges[v1][v2] = weight;
    g->edges[v2][v1] = weight;
    g->edgeCount++;

    return true;
}

// 求某顶点的度
int getDegree(Graph *g, int v) {
    if (v < 0 || v >= g->vertexCount)
        return -1;

    int res = 0;

    for (int i = 0; i < g->vertexCount; i++) {
        if (isAdjacent(g, v, i))
            res++;
    }

    return res;
}

// 记录最短路径的中转点
int path[MAX_SIZE][MAX_SIZE];

// 记录最短距离
long long dis[MAX_SIZE][MAX_SIZE];

// Floyd算法
void floyd(Graph *g) {
    if (g->vertexCount == 0)
        return;

    int size = g->vertexCount;

    // 初始化距离矩阵和中转点矩阵
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dis[i][j] = g->edges[i][j];
            path[i][j] = -1;
        }
    }

    // 逐个考虑顶点k作为中转点
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                // i到k或k到j不可达
                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;

                // 经过k的路径是否更短
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

// 递归输出最短路径的中间顶点
void printMiddle(Graph *g, int i, int j) {
    int k = path[i][j];

    if (k == -1)
        return;

    printMiddle(g, i, k);
    cout << " -> " << g->vertices[k];
    printMiddle(g, k, j);
}

// 输出两个顶点之间的最短路径
void printPath(Graph *g, int i, int j) {
    if (dis[i][j] == INF) {
        cout << "不存在路径" << '\n';
        return;
    }

    cout << g->vertices[i];
    printMiddle(g, i, j);
    if (i != j)
        cout << " -> " << g->vertices[j];

    cout << "  最短距离: " << dis[i][j] << '\n';
}

int main() {
    Graph g;
    init(&g);

    // 添加顶点
    addVertex(&g, 'A');
    addVertex(&g, 'B');
    addVertex(&g, 'C');
    addVertex(&g, 'D');

    // 添加无向带权边
    addEdge(&g, 0, 1, 5);   // A-B，权值5
    addEdge(&g, 0, 2, 10);  // A-C，权值10
    addEdge(&g, 1, 2, 3);   // B-C，权值3
    addEdge(&g, 1, 3, 2);   // B-D，权值2
    addEdge(&g, 2, 3, 1);   // C-D，权值1

    // 执行Floyd算法
    floyd(&g);

    // 输出最短距离矩阵
    cout << "最短距离矩阵：" << '\n';

    for (int i = 0; i < g.vertexCount; i++) {
        for (int j = 0; j < g.vertexCount; j++) {
            if (dis[i][j] == INF)
                cout << "INF ";
            else
                cout << dis[i][j] << " ";
        }
        cout << '\n';
    }

    // 输出任意两个顶点之间的最短路径
    cout << "\n所有顶点之间的最短路径：" << '\n';

    for (int i = 0; i < g.vertexCount; i++) {
        for (int j = i + 1; j < g.vertexCount; j++) {
            printPath(&g, i, j);
        }
    }

    return 0;
}
