#include<stdio.h>
#include<string.h>

#define MaxSize 6   //定义数组大小
//定义结构体
typedef struct {
    int data[MaxSize];    //静态分配 数组
    int length;    //当前数组长度
} SqList;


/**
 * 初始化线性表
 * @param L 线性表
 */
void InitList(SqList &L) {
    //线性表各个索引位置的内容有"内存残留“,需进行初始化
    for (int i = 0; i < MaxSize; ++i) {
        L.data[i] = 0;
    }
    L.length = 0;
}

void InitListByArray(SqList &L,int array[],int length){
    if(length<0){
        return;
    }
    //复制数组
    //从array中复制(length*元素所占字节)个字节到L.data中
    memcpy(L.data,array,length*sizeof(array[0]));
    L.length = length;
}

void printList(SqList L) {
    for (int i = 0, length = L.length; i < length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

/**
 * 在表L中第i个位置插入数据e
 * 如果i大于MaxSize或大于当前长度+1，抛出错误信息
 * @param L 线性表
 * @param i 位置
 * @param e 数据
 */
bool ListInsertByIndex(SqList &L, int i, int e) {
    //判断i位置是否合法
    int length = L.length;
    if (i > L.length + 1 || i < 1) {
        printf("插入位置非法");
        return false;
    }
    if(length>=MaxSize){
        printf("存储空间已满，不能插入");
        return false;
    }

    //从i-1位置开始，全部往后移动一个单位
    for (int j = length; j >= i; j--) {
        L.data[j] = L.data[j - 1];
    }
    //插入数据
    L.data[i - 1] = e;
    L.length++;
    return true;
}


/**
 * 删除操作:将表L中第i个元素删除，并将删除的元素赋值给e。
 * i的有效位置为 1 - L.length
 * @param L 表L
 * @param i 删除位置
 * @param e 删除元素
 * @return 如果删除成功，返回true
 */
bool ListDelete(SqList &L,int i, int &e){
    int length = L.length;
    //判断删除位置是否合法
    if(i<1 || i>length){
        return false;
    }

    //表为空，无法删除
    if(length<1){
        return false;
    }
    e = L.data[i];

    for (int j = i-1; j <length-1; ++j) {
        L.data[j]=L.data[j+1];
    }
    //对表尾进行初始化
    L.data[length-1]=0;
    L.length--;
    return true;
}

/**
 * 在表L插入数据e
 * @param L 线性表L
 * @param e 元素
 */
void ListInsert(SqList &L, int e) {
    if (L.length == MaxSize) {
        printf("数组已满");
        return;
    }
    L.data[L.length - 1] = e;
    L.length++;
}

/**
 * 根据数据e查找表L，获取该元素在表中的位置
 * 如果找不到返回-1
 * @param L 线性表
 * @param e 数据
 * @return 该元素在表中的位置，如果找不到返回-1
 */
int LocateElem(SqList L, int e) {
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] == e) {
            return i + 1;
        }
    }
    return -1;
}

/**
 * 获取表L的长度
 * @param L 线性表
 * @return 线性表的长度
 */
int Length(SqList L) {
    return L.length;
}

/**
 * 查找表L中位置i的数据
 * @param L 线性表
 * @param i 位置
 * @return 数据
 */
int GetElem(SqList L, int i) {
    if (i > MaxSize) {
        printf("获取位置超过数组最大长度");
        return -1;
    }

    if (i >= L.length + 1) {
        printf("获取位置超过数组当前长度");
        return -1;
    }
    return L.data[i - 1];
}

int main() {
    SqList L;
    int array[MaxSize]= {1,2,3,4,5};
    //sizeof(array)/sizeof(array[0]) 返回的是40 而不是 36
    //因为数组创建时，长度就固定了。上面计算的是数组的容积。而不是长度
    InitListByArray(L,array,5);
    printf("初始化表:");
    printList(L);

    bool isSuccess= ListInsertByIndex(L,3,3);
    printf("是否成功:%d  ",isSuccess);
    printf("插入后:");
    printList(L);
    printf("插入后长度:%d\n", L.length);

    int deleteResult = 0;
    isSuccess = ListDelete(L, 3, deleteResult);
    printf("删除是否成功:%d  ", isSuccess);
    printf("删除后:");
    printList(L);
    printf("删除元素:%d,删除后长度:%d\n", deleteResult,L.length);

    return 0;
}