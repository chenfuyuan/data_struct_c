/**
 * 平衡二叉树
 */
#include<stdio.h>
#include<stdlib.h>
//定义平衡因子取值
#define EH 0
#define LH 1
#define RH -1

//定义结构体
typedef int ElemType;
typedef struct Node {
    ElemType data;    //数据域
    int balance;    //平衡因子
    Node *left, *right;    //左指针，右指针
} Node,*Tree;

bool Init(Tree &tree);    //初始化
bool Create(Tree &tree,int input[],int length);    //创建一个平衡二叉树
Node* GetNode();    //获取一个节点
bool InsertNode(Tree &tree, ElemType elem,bool &taller);    //插入一个元素
void R_Rotate(Tree &tree);    //右旋
void L_Rotate(Tree &tree);    //左旋
void Left_Balance(Tree &tree);    //左平衡
void Right_Balance(Tree &tree);    //右平衡
void InfixPrint(Tree tree);    //中序遍历
/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    int inputArray[10]={3,2,1,4,5,6,7,10,9,8};
    Tree tree;
    Init(tree);
    Create(tree, inputArray, 10);

    InfixPrint(tree);

}

void InfixPrint(Tree tree){
    if (tree != NULL) {
        InfixPrint(tree->left);
        printf("%d ", tree->data);
        InfixPrint(tree->right);
    }
}

int main() {
    test_all_function();
    return 0;
}

/**
 * 进行左平衡
 * @param tree
 */
void Left_Balance(Tree &tree){
    Node *left = tree->left;
    switch (left->balance) {
        case LH:    //新节点插入在 tree的左子树的左子树上，作单右旋操作
            //单右旋操作
            R_Rotate(tree);
            //操作后平衡因子 变为平衡
            tree->balance = left->balance = EH;
            break;
        case RH:    //新节点插入在tree的左子树的右子树上，要作双旋操作达到平衡
            Node *left_right = left->right;
            //针对插入位置的双亲节点的平衡情况，更改 tree节点和tree节点的左子树的平衡情况
            switch (left_right->balance) {
                case LH:
                    tree->balance = RH;
                    left->balance = EH;
                    break;
                case EH:
                    tree->balance = left->balance = EH;
                    break;
                case RH:
                    tree->balance = EH;
                    left->balance = LH;
                    break;
            }
            left_right->balance = EH;
            //对tree的左子树进行一次左旋
            L_Rotate(tree->left);
            //对tree进行一次右旋
            R_Rotate(tree);
    }

}

void Right_Balance(Tree &tree){
    Node *right = tree->right;
    switch (right->balance) {
        case RH:    //当插入位置为 tree的右子树的右子树，要做一次单左旋操作
            tree->balance = right->balance = EH;
            L_Rotate(tree);
            break;
        case LH:    //当插入位置为tree的右子树的左子树，要做双旋操作，进行平衡
            Node *right_left = right->left;
            //针对插入位置的双亲节点的平衡情况，更改 tree节点和tree节点的左子树的平衡情况
            switch (right_left->balance) {
                case LH:
                    tree->balance = EH;
                    right->balance = RH;
                    break;
                case EH:
                    tree->balance = right->balance = EH;
                    break;
                case RH:
                    tree->balance = LH;
                    right->balance = EH;
                    break;
            }
            right_left->balance = EH;
            R_Rotate(tree->right);
            L_Rotate(tree);

    }
}

/**
 * 右旋
 * @param tree
 */
void R_Rotate(Tree &root){
    Node *left = root->left;    //暂存左孩子
    root->left = left->right;    //root.左 = root.左.右
    left->right = root;    //左.右 = root
    root = left;    //将root指向left
}

/**
 * 左旋
 * @param tree
 */
void L_Rotate(Tree &root){
    Node *right = root->right;
    root->right = right->left;
    right->left = root;
    root = right;
}

bool InsertNode(Tree &tree,ElemType elem,bool &taller){
    //寻找插入位置
    if (tree == NULL) {    //当树为空时，直接插入
        tree = GetNode();
        tree->data = elem;
        tree->balance = 0;
        taller = true;    //树长高
        return true;
    }

    //当elem已存在在当前树中，则返回false,不进行插入
    if (tree->data == elem) {
        return false;
    }

    if (tree->data > elem) {    //当插入数据，小于当前节点时，寻找左子树
        if (!InsertNode(tree->left, elem, taller)) {
            return false;
        }
        //有变高
        if (taller) {    //已插入到tree的左子树中，且子树长高
            switch (tree->balance) {
                case LH:    //原本左子树高于右子树，需要进行左平衡
                    Left_Balance(tree);
                    taller = false;    //平衡后,不再长高
                    break;
                case EH:    //原本左子树高度等于右子树高度，现因插入左子树，导致左子树长高
                    tree->balance = LH;
                    taller = true;
                    break;
                case RH:    //原本左子树低于右子树，现在达到平衡
                    tree->balance = EH;
                    taller = false;
                    break;
            }
        }
    } else{
        //寻找右子树
        if (!InsertNode(tree->right, elem, taller)) {
            return false;
        }

        if(taller){    //已插入tree的右子树，且子树长高
            switch (tree->balance) {
                case LH:    //原本的左子树高于右子树，插入节点后，达到平衡
                    tree->balance = EH;
                    taller = false;
                    break;
                case EH:    //原本的左子树高度等于右子树高度，插入节点后，导致右子树高度大于左子树高度
                    tree->balance = RH;
                    taller = true;
                    break;
                case RH:    //原本右子树高于左子树，插入节点后导致不平衡，需要进行右平衡
                    Right_Balance(tree);
                    taller = false;
                    break;
            }

        }

    }
    return true;

}

bool Create(Tree &tree,ElemType input[],int length){
    for (int i = 0; i < length; ++i){
        //提取数据
        ElemType data = input[i];
        //插入数据
        bool taller = false;
        InsertNode(tree, data,taller);
    }
}

/**
 * 获得一个新的节点
 * @return
 */
Node* GetNode(){
    Node *result = (Node *) malloc(sizeof(Node));    //申请内存空间
    if(result==NULL){    //内存空间申请失败
        return result;
    }

    //初始化信息
    result->data = 0;
    result->left=NULL;
    result->right = NULL;
    result->balance = EH;
}

/**
 * 初始化
 * @param tree
 * @return
 */
bool Init(Tree &tree){
    tree = NULL;
}
