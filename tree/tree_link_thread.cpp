/**
 * 使用链式存储结构，来存储线索二叉树
 */
#include<stdio.h>
#include<stdlib.h>
#include<queue>

typedef char ElemType;
typedef struct TreeNode {
    ElemType data;    //数据域
    TreeNode *left, *right;    //左孩子，右孩子指针
    TreeNode *parent;    //双亲指针(用于后序线索遍历)
    int ltag, rtag;    //用于表示孩子节点是否为线索  0为孩子，1为线索
} TreeNode, *Tree;


bool Init(Tree &tree);    //初始化
bool CreateTree(Tree &tree);    //构建一个树

void CreatePreThread(Tree tree);    //创建先序线索
void PreVisit(TreeNode *node);    //访问节点，构建前序线索
void PreThread(Tree tree);    //前序遍历
void PrePrint(Tree tree);    //遍历(前序)

void CreateInfixThread(Tree tree);    //创建中序线索
void InfixThread(Tree tree);    //中序遍历
void InfixVisit(TreeNode *node);    //访问结点，构建中序线索
void InfixPrint(Tree tree);    //遍历(中序)

void CreatePostThread(Tree tree);    //创建后续线索
void PostThread(Tree tree);    //后序遍历
void PostVisit(TreeNode* node);    //访问节点，构建后序线索
void PostPrint(Tree tree);    //遍历(后序)



//定义全局辅助指针 用于记录前驱节点
TreeNode *pre = NULL;

/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    Tree tree;
    //构建二叉树
    CreateTree(tree);

    //线索化
    //前序线索化(报错未解决)
    //CreatePreThread(tree);
    //PrePrint(tree);

    //中序线索化
    //CreateInfixThread(tree);
    //InfixPrint(tree);

    //后序线索化
    CreatePostThread(tree);
    PostPrint(tree);
}

int main() {
    test_all_function();
    return 0;
}


void PostPrint(Tree tree){
    if(tree==NULL){
        return;
    }

    TreeNode *temp = tree;
    TreeNode *preNode = NULL;
    while (temp!=NULL){
        //遍历到最左节点
        while (temp->ltag != 1) {
            temp = temp->left;
        }

        //遍历后继节点
        while (temp->right != NULL && temp->rtag == 1) {
            printf("%c ", temp->data);
            fflush(stdout);
            preNode = temp;
            temp = temp->right;
        }

        if (temp == tree) {    //当当前节点为 树的根节点时，遍历完成
            printf("%c ", temp->data);
            fflush(stdout);
            return;
        }

        //遍历双亲节点
        while (temp!=NULL && temp->right == preNode) {    //当前节点为双亲
            printf("%c ",temp->data);
            fflush(stdout);
            preNode = temp;
            temp = temp->parent;    //指向父节点
        }

        if (temp != NULL && temp->rtag == 0) {
            temp = temp->right;
        }

    }

}

/**
 * 创建后序线索
 * @param tree
 */
void CreatePostThread(Tree tree){
    pre = NULL;
    if(tree!=NULL){
        PostThread(tree);    //构建后序线索
    }
}

/**
 * 访问节点，构建后序线索
 * @param node
 */
void PostVisit(TreeNode* node){
    //如果左子树为空，则将左子树跟前驱关联
    if(node->left==NULL){
        node->left = pre;
        node->ltag = 1;
    }

    //如果前驱节点的右孩子为空，当前节点为前驱节点的后继，将前驱节点的右孩子与当前节点关联
    if (pre != NULL && pre->right == NULL) {
        pre->right = node;
        pre->rtag = 1;
    }
    //前驱节点指针移动
    pre = node;
}

/**
 * 后序线索
 * @param tree
 */
void PostThread(Tree tree){
    if(tree!=NULL){
        PostThread(tree->left);    //左子树
        PostThread(tree->right);    //右子树
        PostVisit(tree);
    }
}
/**
 * 创建中序线索
 * @param tree
 */
void CreateInfixThread(Tree tree) {
    pre = NULL;
    if (tree != NULL) {
        //进行线索化
        InfixThread(tree);
        //对最后一个后继进行处理
        pre->right == NULL;
        pre->rtag = 1;

    }
}

/**
 * 中序线索树遍历
 * @param tree
 */
void InfixPrint(Tree tree) {
    TreeNode *temp = tree;
    while (temp!=NULL){

        while (temp->ltag == 0) {    //移动到最左边的结点
            temp = temp->left;
        }

        printf("%c ", temp->data);    //打印
        while (temp->rtag == 1 && temp->right!=NULL) {    //如果该结点的右孩子为线索，且不为NULL就打印
            temp = temp->right;
            printf("%c ", temp->data);
        }

        temp = temp->right;    //指向右子树
    }

}

/**
 * 访问结点，建立中序线索
 * @param node
 */
void InfixVisit(TreeNode *node) {
    //当孩子节点为空时，需要建立线索
    //左子树为空，关联前驱节点
    if (node->left == NULL) {
        node->left = pre;
        node->ltag = 1;
    }
    //如果前一个结点的右孩子为空，则建立后继关联，pre.right=node
    if (pre != NULL && pre->right == NULL) {
        pre->right = node;
        pre->rtag = 1;
    }
    pre = node;
}

/**
 * 中序线索化
 * @param tree
 */
void InfixThread(Tree tree) {
    if (tree != NULL) {
        InfixThread(tree->left);    //左子树
        InfixVisit(tree);    //根
        InfixThread(tree->right);    //右子树
    }
}

/**
 * 前序遍历
 * @param tree
 */
void PrePrint(Tree tree) {
    TreeNode *p = tree;
    while (p != NULL) {
        printf("%c ", p->data);
        if (p->left != NULL && p->ltag == 0) {
            p = p->left;
            continue;
        }

        p = p->right;
    }
}

/**
 * 创建先序线索
 * @param tree
 */
void CreatePreThread(Tree tree) {
    pre = NULL;
    if (tree != NULL) {
        //线索化
        PreThread(tree);
        //处理最后一个结点
        pre->right = NULL;
        pre->rtag = 1;
    }
}

/**
 * 构建线索
 * @param node
 */
void PreVisit(TreeNode *node) {
    //判断左孩子和右孩子是否为NULL,如果为NULL才需要构造线索
    if (node->left == NULL) {
        node->left = pre;
        node->ltag = 1;
    }

    if (pre != NULL && pre->right == NULL) {
        pre->right = node;
        pre->rtag = 1;
    }
    pre = node;
}

/**
 * 前序线索化
 * @param tree
 */
void PreThread(Tree tree) {
    if (tree != NULL) {
        PreVisit(tree);    //根
        if (tree->ltag == 0) {    //因为已将pre指针指向当前结点，如果当前结点的左孩子已经线索化了，则会出现循环递归的问题
            PreThread(tree->left);    //左
        }
        if(tree-> rtag == 0){
            PreThread(tree->right);    //右
        }
    }
}


/**
 * 根据data构建一个新节点
 * @param data
 * @return
 */
TreeNode *GetNode(ElemType data) {
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
    result->parent = NULL;
    //线索flg标识，0为孩子，1为线索
    result->ltag = 0;
    result->rtag = 0;
    return result;
}

/**
 * 将节点insertNode插入root节点
 * 当左孩子为空时，插入左孩子，否则插入右孩子
 * @param root
 * @param insertNode
 * @return 插入失败返回-1,插入左子树返回1，插入右子树返回2
 */
int InsertNode(TreeNode *root, TreeNode *insertNode) {
    if (root == NULL || insertNode == NULL) {
        printf("插入失败，节点为空。\n");
        return -1;
    }
    insertNode->parent = root;
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
bool CreateTree(Tree &tree) {
    Init(tree);

    //从控制台获取输入
    ElemType input;

    //获取第一个输入
    printf("输入数据:");
    fflush(stdout);
    scanf("%c", &input);

    std::queue<TreeNode *> nodeQueue;    //记录插入位置

    while (input != '!') {    //当输入为!时结束输入

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
        } else {
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
bool Init(Tree &tree) {
    tree = NULL;
    return true;
}