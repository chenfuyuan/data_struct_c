#include<stdio.h>
#define MaxSize 3
#define array_size(array) (sizeof(array)/sizeof(array[0]))
typedef int ElemType;

/**
 * 使用size，辅助判断队列空和满的 循环数列
 */
typedef struct {
    ElemType data[MaxSize];
    int front;    //队头指针
    int rear;    //队尾指针
    int size;    //当前元素个数
}Queue;

bool Init(Queue &queue);    //初始化
bool Empty(Queue queue);    //判断队列是否为空
bool Full(Queue queue);    //判断队列是否满
bool EnQueue(Queue &queue, ElemType elem);    //入队
bool DeQueue(Queue &queue, ElemType &elem);    //出队
int Size(Queue queue);    //获取队列长度
bool Print(Queue queue);    //遍历队列
int GetNextIndex(int index);    //获取下一个位置
/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    printf("%d\n", (1 % MaxSize));
    Queue queue;
    Init(queue);
    EnQueue(queue, 1);
    EnQueue(queue, 2);
    printf("入队结果:");
    Print(queue);
    printf("当前队列元素个数为:%d\n", Size(queue));
    int deQueueResult = 0;
    DeQueue(queue, deQueueResult);
    printf("出队元素:%d\n", deQueueResult);
    DeQueue(queue, deQueueResult);
    printf("出队元素:%d\n", deQueueResult);
    DeQueue(queue, deQueueResult);
    printf("出队元素:%d\n", deQueueResult);

    printf("出队结果:");
    Print(queue);
}

int main() {
    test_all_function();
    return 0;
}


/**
 * 判断队列大小
 * @param queue 队列
 * @return 队列大小
 */
int Size(Queue queue){
    return queue.size;
}
/**
 * 出队
 * 将队列queue的队头元素赋值给elem，然后删除
 * @param queue 队列
 * @param elem 元素
 * @return 出队是否成功
 */
bool DeQueue(Queue &queue, ElemType &elem){
    //判断队列是否为空
    if (Empty(queue)) {
        printf("队列为空。\n");
        return false;
    }

    //获取队头元素
    elem = queue.data[queue.front];
    queue.data[queue.front] = 0;
    queue.front = GetNextIndex(queue.front);
    queue.size--;
    return true;
}

/**
 * 判断队列是否满
 * @param queue 队列
 * @return 队列满则返回true
 */
bool Full(Queue queue){
    return queue.rear == queue.front && queue.size != 0;
}

/**
 * 入队操作
 * 将元素elem 添加到队列queue的队尾
 * @param queue 队列
 * @param elem 元素
 * @return 入队是否成功
 */
bool EnQueue(Queue &queue,ElemType elem){
    //判断队列是否满
    if (Full(queue)) {
        printf("队列已满，元素{%d}无法添加。\n", elem);
        return false;
    }

    //将元素添加到队尾
    queue.data[queue.rear] = elem;
    queue.rear = GetNextIndex(queue.rear);
    queue.size++;

    return true;
}
/**
 * 获取循环队列下一个索引位置
 * @param index 当前索引
 * @return 下一个索引位置
 */
int GetNextIndex(int index){
    return (index + 1) % MaxSize;
}
/**
 * 判断队列是否为空
 * @param queue 队列
 * @return 队列为空,返回true
 */
bool Empty(Queue queue){
    return queue.rear == queue.front && queue.size == 0;
}

/**
 * 遍历队列，遍历顺序:队头->队尾
 * @param queue 遍历队列
 * @return 遍历是否成功
 */
bool Print(Queue queue){
    if (Empty(queue)) {
        printf("[]\n");
        return true;
    }

    //从队头开始遍历
    int front = queue.front;
    int size = queue.size;
    ElemType *data = queue.data;
    printf("[");
    while (size!=0) {    //遍历到数列为空
        printf("%d", data[front]);
        if (size-1!=0) {
            printf(", ");
        }
        front = GetNextIndex(front);
        size--;
    }
    printf("]\n");

}

/**
 * 初始化队列
 * @param queue 队列
 * @return
 */
bool Init(Queue &queue){
    queue.front = queue.rear = 0;
    queue.size = 0;
    for (int i = 0, length = array_size(queue.data); i < length; ++i) {
        queue.data[i] = 0;
    }
    return true;
}