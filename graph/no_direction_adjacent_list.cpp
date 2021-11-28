/**
 * no_direction_adjacent_table 无向图邻接表
 *
 * 使用邻接表结构存储无向图
 */
#include<stdio.h>
#include<queue>
#include<stdlib.h>

#define MAX_SIZE 10
#define NOT_FOUND -1
#define array_size(array) (sizeof(array)/sizeof(array[0]))

using namespace std;

typedef char ElemType;    //定义元素类型

typedef struct EdgeNode {
    int adjvex_index;    //边指向的顶点在顺序存储中的索引
    EdgeNode *next;    //下一条边
} EdgeNode;

//顶点
typedef struct VertexNode {
    ElemType data;    //数据域
    EdgeNode *first;    //与该节点相邻的第一条边
    bool isEmpty;    //该顶点是否为空
} VertexNode;

//邻接表
typedef struct Graph {
    VertexNode vex[MAX_SIZE];    //顶点数组
    int vertex_num, edge_num;    //顶点数，边数
    int insertIndex;    //插入位置
} Graph;

//method
bool Init(Graph &graph);    //初始化图
VertexNode GetVertexNode();    //获取一个顶点节点
void BFS_Traverse(Graph graph);    //进行广度优先遍历
void BFS(Graph graph, int v_index);    //进行广度优先遍历
bool InsertVertx(Graph &graph, ElemType data);    //插入顶点
bool AddEdge(Graph &graph, ElemType data_01, ElemType data_02);    //若无向边(x,y)或有向边<x,y>不存在，则向图graph中添加该边
int GetIndex(Graph graph, ElemType data);    //寻找顶点data的索引，不存在返回-1
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
    int vertex_data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    for (int i = 0, length = array_size(vertex_data); i < length; ++i) {
        InsertVertx(graph, vertex_data[i]);
    }
    //添加边
    AddEdge(graph, 'a', 'b');
    AddEdge(graph, 'a', 'd');
    AddEdge(graph, 'b', 'd');
    AddEdge(graph, 'b', 'c');
    AddEdge(graph, 'd', 'e');
    AddEdge(graph, 'c', 'e');
    AddEdge(graph, 'c', 'f');

    //进行广度优先遍历
    printf("广度优先遍历:");
    BFS_Traverse(graph);

}

int main() {
    test_all_function();
    return 0;
}

/**
 * 对图进行广度优先遍历
 * @param graph
 */
void BFS_Traverse(Graph graph){
    //初始化辅助数组
    for (int i = 0; i < MAX_SIZE; ++i){
        visited[i] = false;
    }

    //遍历辅助数组，找寻未访问数组，并对其进行遍历
    for (int i = 0; i < MAX_SIZE; i++) {
        if (visited[i] == true) {    //跳过已访问过的节点
            continue;
        }

        if (graph.vex[i].isEmpty) {    //当该索引位置为空，则跳过
            continue;
        }
        BFS(graph, i);    //访问索引为i的顶点
    }
}

/**
 * 获取第v_index个顶点的第一个相邻的边
 * @param graph
 * @param v_index
 * @return
 */
EdgeNode* GetFirstEdge(Graph graph,int v_index){
    return graph.vex[v_index].first;
}

/**
 * 获取当前边的下一条边
 * @param edgeNode
 * @return
 */
EdgeNode *GetNextEdge(EdgeNode *edgeNode){
    return edgeNode->next;
}


void Visit(VertexNode vertex){
    printf("%c ", vertex.data);
}

/**
 * 从图的第i个顶点进行广度优先遍历
 * @param graph
 * @param v_index
 */
void BFS(Graph graph, int v_index){
    queue<int> queue;

    //首先将要遍历的顶点入队
    queue.push(v_index);
    visited[v_index] = true;

    while (!queue.empty()) {
        int index = queue.front();    //从队列中取出要访问的顶点
        queue.pop();
        Visit(graph.vex[index]);
        //遍历该顶点的边
        for (EdgeNode *edge = GetFirstEdge(graph, index); edge != NULL; edge = GetNextEdge(edge)) {
            if (!visited[edge->adjvex_index]) {    //如果该边对应的相邻顶点没有被访问过
                queue.push(edge->adjvex_index);
                visited[edge->adjvex_index] = true;
            }
        }
    }
}

/**
 * 在图graph中寻找顶点数据域为data的顶点，并返回其在顶点表中的索引
 * @param graph
 * @param data
 * @return
 */
int GetIndex(Graph graph, ElemType data){
    for (int i = 0, j = 0; j < graph.vertex_num; i++) {
        if (graph.vex[i].isEmpty) {
            continue;
        }

        if (graph.vex[i].data == data) {
            return i;
        }

        j++;
    }

    return NOT_FOUND;
}

EdgeNode *GetEdgeNode() {
    EdgeNode *result = (EdgeNode *) malloc(sizeof(EdgeNode));
    result->next = NULL;
    result->adjvex_index = -1;

    return result;
}

bool InsertEdge(VertexNode &vertexNode, int adjvex_index){
    EdgeNode *edgeNode = GetEdgeNode();
    if (edgeNode == NULL) {
        return false;
    }
    edgeNode->adjvex_index = adjvex_index;
    edgeNode->next = vertexNode.first;
    vertexNode.first = edgeNode;
    return true;
}

/**
 * 插入边关系，插入边(data_01,data_02)
 * @param graph
 * @param data_01
 * @param data_02
 * @return
 */
bool AddEdge(Graph &graph, ElemType data_01, ElemType data_02) {
    //判断顶点是否存在
    int index_01 = GetIndex(graph, data_01);
    if (index_01 == -1) {
        printf("顶点{%c}不存在，请先插入。\n", data_01);
        return false;
    }
    int index_02 = GetIndex(graph, data_02);
    if (index_02 == -1) {
        printf("顶点{%c}不存在，请先插入。\n", data_02);
        return false;
    }

    //使用头插法，插入边
    if(!InsertEdge(graph.vex[index_01], index_02)){
        printf("插入顶点{%c}时失败。\n",data_01);
        return false;
    }

    if (!InsertEdge(graph.vex[index_02], index_01)){
        printf("插入顶点{%c}时失败。\n",data_02);
        return false;
    }

    graph.edge_num++;
    return true;
}

/**
 * 判断图中是否存在数值为data的元素
 * @param graph
 * @param data
 * @return
 */
bool IsExist(Graph graph, ElemType data) {
    return GetIndex(graph, data) != NOT_FOUND;
}

/**
 * 判断图是否已满
 * @param graph
 * @return
 */
bool Full(Graph graph) {
    return graph.vertex_num >= MAX_SIZE;
}

/**
 * 插入一个结点
 * @param graph
 * @param data
 * @return
 */
bool InsertVertx(Graph &graph, ElemType data) {
    //判断该结点是否已经在图中
    if (IsExist(graph, data)) {
        printf("顶点{%c}已存在，无需再添加。\n", data);
        return false;
    }

    if (Full(graph)) {
        printf("图已满。\n");
        return false;
    }

    //插入数据
    VertexNode node = GetVertexNode();
    node.data = data;
    node.isEmpty = false;
    graph.vex[graph.insertIndex] = node;
    graph.vertex_num++;
    //寻找下一个插入点
    for (int i = graph.insertIndex + 1; i < MAX_SIZE; ++i) {
        if (graph.vex[i].isEmpty) {
            graph.insertIndex = i;
            break;
        }
    }

    return true;
}


/**
 * 获取一个空的顶点结点
 * @return 空的顶点结点
 */
VertexNode GetVertexNode() {
    VertexNode result;
    result.data = 0;
    result.isEmpty = true;
    result.first = NULL;
    return result;
}

bool Init(Graph &graph) {
    graph.vertex_num = 0;
    graph.edge_num = 0;
    graph.insertIndex = 0;
    for (int i = 0; i < MAX_SIZE; ++i) {
        graph.vex[i] = GetVertexNode();
    }
    return true;
}