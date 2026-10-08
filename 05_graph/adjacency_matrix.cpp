// 图的邻接矩阵存储(代码使用无向图)
#include<bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100;

struct Graph {
    char vertices[MAX_SIZE];        // 顶点表
    int edges[MAX_SIZE][MAX_SIZE];  // 邻接矩阵
    int vertexCount;                // 顶点数
    int edgeCount;                  // 边数
};

//初始化
void init(Graph *g){
    g->vertexCount = 0;
    g->edgeCount = 0;

    for(int i=0;i<MAX_SIZE;i++){
        for(int j=0;j<MAX_SIZE;j++){
            g->edges[i][j] = 0;
        }
    }
}

//增加顶点
bool addVertex(Graph *g,char v){
    if(g->vertexCount>=MAX_SIZE) return false;
    g->vertices[g->vertexCount++] = v;
    return true;
}

//判断两点是否相邻
bool isAdjacent(Graph *g,int v1,int v2){
    return g->edges[v1][v2];
}

//增加边
bool addEdge(Graph *g,int v1,int v2,int weight){
    if(v1 < 0 || v1 >= g->vertexCount ||
        v2 < 0 || v2 >= g->vertexCount){
        return false;
    }
    if(isAdjacent(g,v1,v2)) return false;
    g->edges[v1][v2] = weight;
    g->edges[v2][v1] = weight;
    g->edgeCount++;
    return true;
}

//求某顶点的度
int getDegree(Graph *g,int v){
    int res = 0;
    for(int i=0;i<g->vertexCount;i++){
        if(g->edges[v][i]){
            res++;
        }
    }
    return res;    
}



int main(){
    Graph g;

    // 初始化图
    init(&g);

    // 添加顶点
    addVertex(&g, 'A');
    addVertex(&g, 'B');
    addVertex(&g, 'C');
    addVertex(&g, 'D');

    // 添加边
    addEdge(&g, 0, 1,0);  // A-B
    addEdge(&g, 0, 2,0);  // A-C
    addEdge(&g, 1, 2,0);  // B-C
    addEdge(&g, 1, 3,0);  // B-D
    addEdge(&g, 2, 3,0);  // C-D

    // 输出基本信息
    cout << "顶点数：" << g.vertexCount << endl;
    cout << "边数：" << g.edgeCount << endl;

    // 输出顶点
    cout << "顶点：";
    for(int i = 0; i < g.vertexCount; i++){
        cout << g.vertices[i] << " ";
    }
    cout << endl;

    // 输出邻接矩阵
    cout << "\n邻接矩阵：" << endl;

    cout << "  ";
    for(int i = 0; i < g.vertexCount; i++){
        cout << g.vertices[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < g.vertexCount; i++){
        cout << g.vertices[i] << " ";

        for(int j = 0; j < g.vertexCount; j++){
            cout << g.edges[i][j] << " ";
        }

        cout << endl;
    }

    // 测试相邻关系
    cout << "\nA和B是否相邻："
         << isAdjacent(&g, 0, 1) << endl;

    cout << "A和D是否相邻："
         << isAdjacent(&g, 0, 3) << endl;

    // 测试顶点的度
    for(int i = 0; i < g.vertexCount; i++){
        cout << "顶点 " << g.vertices[i]
             << " 的度：" << getDegree(&g, i) << endl;
    }

    return 0;
}