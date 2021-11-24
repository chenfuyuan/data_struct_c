/**
 * 使用链式存储结构，来存储二叉树
 */
#include<stdio.h>
#include<stdlib.h>
#include<queue>

typedef char ElemType;
typedef struct TreeNode{
    ElemType data;    //数据域
    TreeNode *left,*right;    //左子树，右子树指针
}TreeNode,*Tree;


bool Init(Tree &tree);    //初始化
bool CreateTree(Tree &tree);    //构建一个树
void Visit(TreeNode node);    //访问节点
void PreOrder(Tree tree);    //前序遍历
void InfixOrder(Tree tree);    //中序遍历
void PostOrder(Tree tree);    //后序遍历
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
    PreOrder(tree);

    //中序遍历
    //InfixOrder
    printf("\n中序遍历:");
    InfixOrder(tree);

    //后序遍历
    //PostOrder
    printf("\n后序遍历:");
    PostOrder(tree);

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
 * 访问节点
 * @param node
 */
void Visit(TreeNode *node){
    printf("%c ", node->data);
}

/**
 * 层次遍历
 * @param tree
 */
void LevelOrder(Tree tree){
    std::queue<TreeNode*> nodeQueue;
    nodeQueue.push(tree);    //将根节点入队
    while (!nodeQueue.empty()) {
        //取出队头元素
        TreeNode *node = nodeQueue.front();
        nodeQueue.pop();    //出队
        //访问该节点
        Visit(node);
        //如果左右孩子不为空，则将左右孩子入队
        if (node->left != NULL) {
            nodeQueue.push(node->left);
        }
        if (node->right != NULL) {
            nodeQueue.push(node->right);
        }
    }

}



/**
 * 后序遍历
 * @param tree
 */
void PostOrder(Tree tree){
    if (tree == NULL) {
        return;
    }

    PostOrder(tree->left);
    PostOrder(tree->right);
    Visit(tree);
}


/**
 * 中序遍历
 * @param tree
 */
void InfixOrder(Tree tree){
    if (tree == NULL) {
        return;
    }

    InfixOrder(tree->left);
    Visit(tree);
    InfixOrder(tree->right);
}
/**
 * 前序遍历
 * @param tree
 */
void PreOrder(Tree tree){
    if (tree == NULL) {
        return;
    }

    Visit(tree);
    PreOrder(tree->left);
    PreOrder(tree->right);
}

/**
 * 根据data构建一个新节点
 * @param data
 * @return
 */
TreeNode* GetNode(ElemType data){
    //申请内存空间
    TreeNode *result = (TreeNode *) malloc(sizeof(TreeNode));

    //判断是否分配成功
    if (result == NULL) {
        return result;
    }

    //插入数据
    result->data = data;
    result->left = NULL;
    result->right = NULL;
    return result;
}

/**
 * 将节点insertNode插入root节点
 * 当左孩子为空时，插入左孩子，否则插入右孩子
 * @param root
 * @param insertNode
 * @return 插入失败返回-1,插入左子树返回1，插入右子树返回2
 */
int InsertNode(TreeNode* root,TreeNode *insertNode){
    if (root == NULL || insertNode == NULL) {
        printf("插入失败，节点为空。\n");
        return -1;
    }

    if (root->left == NULL) {
        root->left = insertNode;
        return 1;
    }

    if (root->right == NULL) {
        root->right = insertNode;
        return 2;
    }
    printf("插入失败，无可插入位置。\n");
    return -1;

}


/**
 * 创建树
 * @param tree
 * @return
 */
bool CreateTree(Tree &tree){
    Init(tree);

    //从控制台获取输入
    ElemType input;

    //获取第一个输入
    printf("输入数据:");
    fflush(stdout);
    scanf("%c", &input);

    std::queue<TreeNode*> nodeQueue;    //记录插入位置

    while(input!='!'){    //当输入为!时结束输入

        //插入数据，插入顺序为，左子树，右子树

        //根据data新建一个节点
        TreeNode *node = GetNode(input);
        if (node == NULL) {
            printf("创建新节点失败，内存空间不足。\n");
            return false;
        }
        if (tree == NULL) {
            //如果插入的是根节点时，需要将根节点地址 赋值给tree
            tree = node;
        }else{
            //判断插入左子树，还是右子树
            TreeNode *insertPos = nodeQueue.front();
            int sign = InsertNode(insertPos, node);
            if (sign == -1) {    //插入失败
                return false;
            }
            if (sign == 2) {    //返回值为2,代表插入的位置是右子树，代表该插入位置，已经插入完毕，进行出队
                nodeQueue.pop();
            }
        }

        //将新增的节点入队，规定插入顺序
        nodeQueue.push(node);

        scanf("%c", &input);    //获取新输入
    }


    return true;
}


/**
 * 初始化树
 * @param tree
 * @return
 */
bool Init(Tree &tree){
    tree = NULL;
    return true;
}