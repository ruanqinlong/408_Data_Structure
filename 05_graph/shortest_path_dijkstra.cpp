// Dijkstra最短路径算法，使用邻接矩阵实现
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

vector<int> dijkstra(Graph *g,int start){
    vector<int> dis;
    if(g==nullptr || g->vertexCount==0 || start<0 || start>=g->vertexCount) return dis;
    dis.resize(g->vertexCount);
    bool flag[MAX_SIZE];
    int parent[MAX_SIZE];

    //初始化
    for(int i=0;i<g->vertexCount;i++){
        if(i==start){
            dis[i] = 0;
            parent[i] = -1;
            flag[i] = true;
            continue;
        }
        flag[i] = false;
        int distance = g->edges[start][i];
        if(distance){
            dis[i] = distance;
            parent[i] = start;
        }else{
            dis[i] = 1e9;
            parent[i] = -1;
        }
    }

    for(int i=0;i<g->vertexCount;i++){
        int index = -1;
        int minP = 1e9;
        //寻找当前最短路径
        for(int j=0;j<g->vertexCount;j++){
            if(minP>dis[j] && !flag[j]){
                minP = dis[j];
                index = j;
            }
        }
        if(index==-1) break;
        //将该路径设为已找到
        flag[index] = true;
        //更新该路径相连的路径长度
        for(int i=0;i<g->vertexCount;i++){
            if(!flag[i] && g->edges[index][i]){
                int distance = g->edges[index][i] + dis[index];
                if(dis[i]>distance){
                    dis[i] = distance;
                    parent[i] = index;
                }
            }
        }
    }

    // 不可达的顶点返回-1
    for(int i=0;i<g->vertexCount;i++){
        if(dis[i]==1e9){
            dis[i] = -1;
        }
    }

    return dis;
}


int main(){
    Graph *g = new Graph;
    init(g);

    // 添加顶点
    for(char v : {'A','B','C','D','E','F','G'}){
        addVertex(g,v);
    }

    // 添加无向带权边
    addEdge(g,0,1,4);   // A-B
    addEdge(g,0,2,2);   // A-C
    addEdge(g,1,2,1);   // B-C
    addEdge(g,1,3,5);   // B-D
    addEdge(g,2,3,8);   // C-D
    addEdge(g,2,4,10);  // C-E
    addEdge(g,3,4,2);   // D-E
    addEdge(g,3,5,6);   // D-F
    addEdge(g,4,5,3);   // E-F

    // G不与其他顶点连接

    // 测试从A出发的最短路径
    vector<int> dis = dijkstra(g,0);

    cout<<"从A出发的最短距离："<<endl;

    for(int i=0;i<g->vertexCount;i++){
        cout<<"A -> "<<g->vertices[i]<<" : "<<dis[i]<<endl;
    }

    delete g;

    return 0;
}
