/**
 * no_direction_adjacent_matrix 无向图邻接矩阵
 * adjacent 邻接的
 * matrix 矩阵
 *
 * 使用邻接矩阵表示无向图
 */
#include<stdio.h>
#include<queue>
using namespace std;
#define MAX_SIZE 10
#define array_size(array) (sizeof(array)/sizeof(array[0]))

typedef char ElemType;    //定义元素类型
typedef int InfoType;    //权值

typedef struct VertexNode{
    ElemType data;    //数据域
    bool isEmpty;    //该节点是否为空
};

typedef struct Graph{
    VertexNode vex[MAX_SIZE];    //邻接矩阵，顶点表
    InfoType edge[MAX_SIZE][MAX_SIZE];    //邻接矩阵，边表
    int vertex_num, edge_num;    //顶点数，边数
    int emptyIndex;    //可插入位置
}Graph;

//method
bool Init(Graph &graph);    //初始化图
VertexNode GetNode();    //获取一个顶点节点
void BFS_Traverse(Graph graph);    //进行广度优先遍历
void BFS(Graph graph,int v_index);    //进行广度优先遍历
bool InsertVertx(Graph &graph, ElemType data);    //插入顶点
bool AddEdge(Graph &graph, int x, int y);    //若无向边(x,y)或有向边<x,y>不存在，则向图graph中添加该边
//param
bool visited[MAX_SIZE];    //辅助数组，用于保存已访问过的顶点


/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    //初始化图
    Graph graph;
    Init(graph);
    //输入数据
    int vertex_data[] = {'a','b','c','d','e','f'};
    for (int i = 0,length= array_size(vertex_data); i < length; ++i) {
        InsertVertx(graph, vertex_data[i]);
    }
    //添加边
    AddEdge(graph, 0, 1);
    AddEdge(graph,0,3);
    AddEdge(graph,1,3);
    AddEdge(graph,1,2);
    AddEdge(graph,3,4);
    AddEdge(graph,2,4);
    AddEdge(graph,2,5);

    //进行广度优先遍历
    BFS_Traverse(graph);
}

int main() {
    test_all_function();
    return 0;
}


void Visit(VertexNode node){
    printf("%c ", node.data);
}

void BFS(Graph graph, int v_index){
    queue<int> queue;
    //将遍历的顶点入队
    queue.push(v_index);
    visited[v_index] = true;
    while (!queue.empty()) {
        int front = queue.front();    //获取下一个需要遍历的顶点索引
        queue.pop();    //出队
        Visit(graph.vex[front]);    //访问该结点

        for (int i = 0; i < MAX_SIZE; ++i){    //遍历边表，找出相邻的边
            if (graph.edge[front][i] != 0&&visited[i]!= true) {    //将与该顶点相邻且未被访问的边对应顶点索引入队
                queue.push(i);    //入队
                visited[i] = true;    //将该顶点标为已访问
            }
        }
    }
}

void BFS_Traverse(Graph graph){
    //初始辅助数组
    for (int i = 0; i < MAX_SIZE; ++i){
        visited[i] = false;
    }

    //遍历
    for (int i = 0; i < MAX_SIZE; ++i){
        //遍历所有未被访问过的顶点
        if (visited[i] == true) {
            //被访问过，跳过
            continue;
        }

        //当该顶点索引位置为空时，跳过
        if(graph.vex[i].isEmpty){
            continue;
        }

        //访问未被访问过的点
        BFS(graph, i);
    }
}



/**
 * 添加边
 * @param graph
 * @param x
 * @param y
 * @return
 */
bool AddEdge(Graph &graph, int x, int y){
    graph.edge[x][y] = 1;
    graph.edge[y][x] = 1;
}

/**
 * 判断图是否满
 * @param graph
 * @return
 */
bool Full(Graph graph){
    return graph.vertex_num >= MAX_SIZE;
}

/**
 * 将数据data 插入图中
 * @param graph
 * @param data
 * @return
 */
bool InsertVertx(Graph &graph, ElemType data){
    //判断该顶点是否已经在图中
    for (int i = 0,j = 1; j <= graph.vertex_num; ++i) {
        if (graph.vex[i].isEmpty) {
            continue;
        }

        //判断顶点是否已在图中
        if (graph.vex[i].data == data) {
            printf("顶点{%c}已在图中。\n", data);
            return false;
        }

        j++;
    }


    if (Full(graph)) {
        printf("图已满。\n");
        return false;
    }

    VertexNode node = GetNode();
    node.data = data;
    node.isEmpty = false;

    graph.vex[graph.emptyIndex] = node;
    graph.vertex_num++;

    //获取下一个可插入的位置
    for (int i = graph.emptyIndex+1; i < MAX_SIZE; ++i){
        if (graph.vex[i].isEmpty) {
            graph.emptyIndex = i;
            break;
        }
    }

    return true;
}

/**
 * 获取一个空的顶点
 * @return
 */
VertexNode GetNode(){
    VertexNode result;
    result.data = 0;
    result.isEmpty = true;
    return result;
}

/**
 * 初始化
 * @param graph
 * @return
 */
bool Init(Graph &graph){
    for (int i = 0; i < MAX_SIZE; ++i){
        //初始化顶点
        graph.vex[i] = GetNode();
        //初始化边
        for (int j = 0; j < MAX_SIZE; ++j) {
            graph.edge[i][j] = 0;
        }
    }

    graph.edge_num = 0;
    graph.vertex_num = 0;
    graph.emptyIndex = 0;
}