// 最小生成树：Prim、Kruskal
#include<bits/stdc++.h>

using namespace std;


/*
    均为邻接矩阵法的程序↓↓↓↓↓↓
*/
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

/*
    均为邻接矩阵法的程序↑↑↑↑↑↑
*/

/*
    均为并查集的程序↓↓↓↓↓↓
*/

int parent[MAX_SIZE];

// 初始化并查集
void initSet(int set[]){
    for(int i = 0; i < MAX_SIZE; i++){
        set[i] = -1;
    }
}

// 查找结点x所在集合的根结点
int findRoot(int set[], int x){
    int root = x;
    while(set[root] >= 0) root = set[root];
    while(x!=root){
        int t = set[x];//获取父结点下标
        set[x] = root;//直接将x结点挂在根结点下
        x = t;
    }
    
    return x;
}

//判断x y是否连通
bool isConnected(int set[],int x,int y){
    return findRoot(set,x)==findRoot(set,y);
}

// 合并两个集合
// root1和root2必须是两个集合的根结点
bool unionSet(int set[], int root1, int root2){
    if(root1 == root2){
        return false;
    }

    // 将root2所在的树合并到root1下面
    set[root2] = root1;

    return true;
}
/*
    均为并查集的程序↑↑↑↑↑↑
*/


struct Edge{
    int u;
    int v;
    int weight;
};
//Prim使用邻接矩阵实现,贪心算法，每次把已加入顶点有的最小权值进行连通
Graph* prim(Graph *g,int start){
    if(g->vertexCount==0 || start<0 || start>=g->vertexCount) return nullptr;
    Graph *res = new Graph;
    init(res);
    
    for(int i=0;i<g->vertexCount;i++){
        addVertex(res,g->vertices[i]);
    }

    bool visited[MAX_SIZE] = {false};
    visited[start] = true;
    int okVertex = 1;

    while(okVertex<g->vertexCount){
        int min=INT_MAX;
        int l=-1,r=-1;
        for(int i=0;i<g->vertexCount;i++){
            if(!visited[i]) continue;

            for(int j=0;j<g->vertexCount;j++){
                if(visited[j]) continue;
                if(g->edges[i][j] && min>g->edges[i][j]){
                    min = g->edges[i][j];
                    l = i;
                    r = j;
                }
            }
        }
        
        if(r==-1){
            delete res;
            return nullptr;
        }
        
        visited[r] = true;
        addEdge(res,l,r,min);
        okVertex++;
    }
    return res;
}


Graph* kruskal(Graph *g,int parent[]){
    if(g==nullptr || g->vertexCount==0) return nullptr;

    Graph *res = new Graph;
    init(res);

    for(int i=0;i<g->vertexCount;i++){
        addVertex(res,g->vertices[i]);
    }

    // 提取邻接矩阵中的所有边
    vector<Edge> edges;

    for(int i=0;i<g->vertexCount;i++){
        for(int j=i+1;j<g->vertexCount;j++){
            if(g->edges[i][j]){
                edges.push_back({i,j,g->edges[i][j]});
            }
        }
    }

    // 按照边的权值从小到大排序
    sort(edges.begin(),edges.end(),[](Edge a,Edge b){
        return a.weight<b.weight;
    });

    // 初始化并查集
    for(int i=0;i<g->vertexCount;i++){
        parent[i] = -1;
    }

    // 依次选择权值最小的边
    for(int i=0;i<(int)edges.size();i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        int root1 = findRoot(parent,u);
        int root2 = findRoot(parent,v);

        // 不属于同一个集合，说明不会形成环
        if(root1!=root2){
            addEdge(res,u,v,weight);
            unionSet(parent,root1,root2);

            // 最小生成树已经有 V-1 条边
            if(res->edgeCount==g->vertexCount-1){
                break;
            }
        }
    }

    // 原图不连通
    if(res->edgeCount!=g->vertexCount-1){
        delete res;
        return nullptr;
    }

    return res;
}



int main(){
    Graph *g = new Graph;
    init(g);

    // 添加顶点
    addVertex(g,'A');
    addVertex(g,'B');
    addVertex(g,'C');
    addVertex(g,'D');
    addVertex(g,'E');
    addVertex(g,'F');

    // 添加无向带权边
    addEdge(g,0,1,6);   // A-B
    addEdge(g,0,2,1);   // A-C
    addEdge(g,0,3,5);   // A-D
    addEdge(g,1,2,5);   // B-C
    addEdge(g,1,4,3);   // B-E
    addEdge(g,2,3,5);   // C-D
    addEdge(g,2,4,6);   // C-E
    addEdge(g,2,5,4);   // C-F
    addEdge(g,3,5,2);   // D-F
    addEdge(g,4,5,6);   // E-F

    // 测试 Prim
    Graph *res1 = prim(g,0);

    cout<<"Prim:"<<endl;

    if(res1==nullptr){
        cout<<"无法生成最小生成树"<<endl;
    }
    else{
        int sum = 0;

        for(int i=0;i<res1->vertexCount;i++){
            for(int j=i+1;j<res1->vertexCount;j++){
                if(res1->edges[i][j]){
                    cout<<res1->vertices[i]<<" - "
                        <<res1->vertices[j]<<" : "
                        <<res1->edges[i][j]<<endl;

                    sum += res1->edges[i][j];
                }
            }
        }

        cout<<"总权值: "<<sum<<endl;
    }

    cout<<endl;

    // 测试 Kruskal
    int parent[MAX_SIZE];
    Graph *res2 = kruskal(g,parent);

    cout<<"Kruskal:"<<endl;

    if(res2==nullptr){
        cout<<"无法生成最小生成树"<<endl;
    }
    else{
        int sum = 0;

        for(int i=0;i<res2->vertexCount;i++){
            for(int j=i+1;j<res2->vertexCount;j++){
                if(res2->edges[i][j]){
                    cout<<res2->vertices[i]<<" - "
                        <<res2->vertices[j]<<" : "
                        <<res2->edges[i][j]<<endl;

                    sum += res2->edges[i][j];
                }
            }
        }

        cout<<"总权值: "<<sum<<endl;
    }

    delete res1;
    delete res2;
    delete g;

    return 0;
}
