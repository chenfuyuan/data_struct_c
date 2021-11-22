/**
 * 使用顺序存储结构 来实现完全二叉树
 */
#include<stdio.h>
#include<queue>

#define MAX_SIZE 9
#define ROOT_INDEX 1
typedef char ElemType;
//树节点
typedef struct TreeNode {
    ElemType data;
    bool isEmpty;
} TreeNode;

//树
typedef struct Tree {
    TreeNode array[MAX_SIZE];
    int length;
} Tree;


bool Init(Tree &tree);    //初始化
bool CreateTree(Tree &tree);    //构建一个树
void Visit(TreeNode node);    //访问节点
void PreOrder(Tree tree, int index);    //前序遍历
void InfixOrder(Tree tree, int index);    //中序遍历
void PostOrder(Tree tree, int index);    //后序遍历
void LevelOrder(Tree tree);    //层次遍历

/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    Tree tree;
    //构建二叉树
    CreateTree(tree);

    //前序遍历
    //PreOrder
    printf("前序遍历:");
    PreOrder(tree, ROOT_INDEX);

    //中序遍历
    //InfixOrder
    printf("\n中序遍历:");
    InfixOrder(tree, ROOT_INDEX);

    //后序遍历
    //PostOrder
    printf("\n后序遍历:");
    PostOrder(tree, ROOT_INDEX);

    //层次遍历
    //LevelOrder
    printf("\n层次遍历:");
    LevelOrder(tree);
}

int main() {
    test_all_function();
    return 0;
}

/**
 * 层次遍历
 * @param tree
 */
void LevelOrder(Tree tree) {
    int i = 1;
    TreeNode *array = tree.array;
    std::queue<int> q;
    q.push(i);    //将首元素入队
    while (!q.empty()) {    //当队列为空时，结束循环
        //从队列中，弹出访问节点索引
        int index = q.front();
        q.pop();

        //访问该节点
        Visit(array[index]);

        //寻找该节点的左孩子，如果存在，则将左孩子索引入队
        if (index * 2 < MAX_SIZE && !array[index * 2].isEmpty) {
            q.push(index * 2);
        }
        //寻找该节点的右孩子，如果存在，则将右孩子索引入队
        if (index * 2 + 1 < MAX_SIZE && !array[index * 2 + 1].isEmpty) {
            q.push(index * 2+1);
        }
    }


}

/**
 * 后序遍历
 * 左子树、右子树、根
 * @param tree
 * @param index
 */
void PostOrder(Tree tree, int index) {
    if (tree.array[index].isEmpty || index >= MAX_SIZE) {
        return;
    }

    PostOrder(tree, index * 2);    //访问左子树
    PostOrder(tree, index * 2 + 1);    //访问右子树
    Visit(tree.array[index]);    //访问根节点
}

/**
 * 中序遍历
 * 左子树、根、右子树
 * @param tree
 * @param index
 */
void InfixOrder(Tree tree, int index) {
    if (tree.array[index].isEmpty || index >= MAX_SIZE) {
        return;
    }

    InfixOrder(tree, index * 2);    //访问左子树
    Visit(tree.array[index]);    //访问根节点
    InfixOrder(tree, index * 2 + 1);    //访问右子树
}

void Visit(TreeNode node) {
    printf("%c ", node.data);
}

/**
 * 前序遍历
 * 根据 根，左子树，右子树的顺序对树进行遍历
 * @param tree 需要遍历的树
 */
void PreOrder(Tree tree, int index) {
    if (tree.array[index].isEmpty || index >= MAX_SIZE) {
        return;
    }

    Visit(tree.array[index]);    //访问根节点
    PreOrder(tree, index * 2);    //访问左子树
    PreOrder(tree, index * 2 + 1);    //访问右子树
}

/**
 * 创建一棵树
 * @param tree 树
 * @return 是否创建成功
 */
bool CreateTree(Tree &tree) {
    Init(tree);    //初始化
    char data;
    printf("请输入数据:");
    fflush(stdout);
    scanf("%c", &data);
    int i = 1;
    while (data != '!') {
        if (i >= MAX_SIZE) {    //当超过树的最大容量时，返回
            printf("输入超过最大容量。\n");
            break;
        }
        //录入数据
        tree.array[i].data = data;
        tree.array[i].isEmpty = false;
        scanf("%c", &data);
        i++;
    }
    tree.length = i - 1;

    return true;
}

/**
 * 初始化树
 * @param tree 树
 * @return
 */
bool Init(Tree &tree) {
    TreeNode *array = tree.array;
    for (int i = 0; i < MAX_SIZE; ++i) {
        array[i].isEmpty = true;
        array[i].data = '\0';
    }
    tree.length = 0;
}