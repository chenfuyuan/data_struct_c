#include<stdio.h>

#define MaxSize 10    //定义数组大小

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

void printList(SqList L) {
    for (int i = 0, length = L.length; i < length; i++) {
        printf("%d\n", L.data[i]);
    }
}

/**
 * 在表L中第i个位置插入数据e
 * 如果i大于MaxSize或大于当前长度+1，抛出错误信息
 * @param L 线性表
 * @param i 位置
 * @param e 数据
 */
void ListInsertByIndex(SqList &L, int i, int e) {
    if (i > MaxSize) {
        printf("位置%d超过数组长度", i);
        return;
    }
    if (i >= L.length + 1) {
        printf("插入位置非法");
        return;
    }
    L.data[i - 1] = e;
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
int LocateElem(SqList L,int e){
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] == e) {
            return i+1;
        }
    }
    return -1;
}

/**
 * 获取表L的长度
 * @param L 线性表
 * @return 线性表的长度
 */
int Length(SqList L){
    return L.length;
}

/**
 * 查找表L中位置i的数据
 * @param L 线性表
 * @param i 位置
 * @return 数据
 */
int GetElem(SqList L,int i){
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
    InitList(L);
    return 0;
}