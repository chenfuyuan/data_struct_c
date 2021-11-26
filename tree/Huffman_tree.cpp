#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVALUE  100000        //输入文本最大字符个数
#define MAXLEAF   256           //最大叶结点个数，即最大不同字符个数
#define MAXBIT    MAXLEAF-1     //编码最大长度
#define MAXNODE   MAXLEAF*2-1   //最大结点个数

typedef struct{        //Huffman树结点结构体
    float weight;      //结点权值，这里是字符出现的频率，及频次/字符种类数
    int parent;        //父结点位置索引，初始-1
    int lchild;        //左孩子位置索引，初始-1
    int rchild;        //右孩子位置索引，初始-1
} HNodeType;

typedef struct{        //Huffman编码结构体
    int bit[MAXBIT];   //字符的哈夫曼编码
    int start;         //该编码在数组bit中的开始位置
} HCodeType;

/**
 * 输入可包含空格的字符串，输入字符串存放在str中
 * @param str
 */
void str_input(char str[]) {
    gets(str);
}


/**
 * 统计每种字符的出现频次，返回出现的不同字符的个数
 * 出现的字符存放在ch中，对应字符的出现频次存放在weight中
 * @param text
 * @param ch
 * @param weight
 * @return
 */
int TextStatistics(char text[], char ch[], float weight[]) {
    int text_index = 0;  //text字符串索引
    int ch_index = 0;	 //统计字符数组索引，仅用于出现不同字符时，将该字符加入到ch[]中。仅自增

    int weight_index = 0;//频数更新索引。用于指定weight[]要更新频数的位置

    while(text[text_index]!='\0'){
        //查找ch中，是否存在字符text[text_index]，返回查到的第一个字符的位置
        char* pos = strchr(ch,text[text_index]);

        //如果ch中无该字符。或者ch为空。就将text[text_index]加入到ch中
        if(ch[0]==NULL  || pos == NULL ){

            //加入到统计字符数组中
            ch[ch_index] = text[text_index];

            //新增一个字符的频数，当所有字符都统计完之后再计算频率
            weight[ch_index] += 1;
            ch_index++;

        }else{//如果字符串中有该
            //找到该字符的索引位置，更新其频数
            weight_index = pos - ch ;
            weight[weight_index] += 1;

        }

        text_index++;
    }
    ch[ch_index] = '\0';//添加结束符
    //根据频数计算频率
    int index=0;
    while(weight[index]!=0){
        weight[index]/=text_index;
        index++;
    }
    //最终 ch_index的值即为text字符串中不同字符的个数
    return ch_index;
}


/**
 * 从 HuffNodes[0..range]中，找到最小的结点索引赋给s1,s2 。已经找到过的结点，其parent不为-1（重点！因为构造哈夫曼树的时候，两叶子结点会合并出一个新的结点作为他们俩的父结点）
 * @param HuffNodes
 * @param range
 * @param s1
 * @param s2
 */
void select(HNodeType HuffNodes[],int range,int *s1,int *s2){
    //先找第一个最小值 。
    float min1 = 5;

    for(int index1=0;index1<=range;index1++){

        if(HuffNodes[index1].weight < min1 && HuffNodes[index1].parent ==-1){
            //判断该结点是否被选过。如果该结点parent为-1，则其为没有选过的叶结点。否则，说明其被选过
            min1 = HuffNodes[index1].weight;
            *s1 = index1 ;
        }
    }


    //找第2个最小值
    float min2 = 5;
    for(int index2=0;index2<=range ;index2++){
        if(HuffNodes[index2].weight < min2 && HuffNodes[index2].parent ==-1 && index2!=*s1){
            //判断该结点是否被选过。还要判断其是否被s1选了
            min2 = HuffNodes[index2].weight;
            *s2 = index2 ;
        }
    }

}


/**
 * 构造一棵Huffman树，树结点存放在HuffNodes中，n为t输入字符串中字符种类数（即叶子结点个数）
 * @param HuffNodes
 * @param weight
 * @param n
 */
void HuffmanTree(HNodeType HuffNodes[], float weight[], int n){

    if(n>MAXLEAF) {
        printf("超出叶结点最大数量!\n");
        return;
    }
    if(n<=1) return;

    int m = 2*n-1;//哈夫曼树中结点总个数 	=叶子结点个数*2-1

    int node_index = 0;
    //初始化各叶节点(共n个）
    for(;node_index < n;node_index++){
        /*
            HuffNodes[node_index]->weight
            HuffNodes[node_index]->parent
            HuffNodes[node_index]->lchild
            HuffNodes[node_index]->rchild
        */
        HuffNodes[node_index].weight = weight[node_index];
        HuffNodes[node_index].parent = -1;
        HuffNodes[node_index].lchild = -1;
        HuffNodes[node_index].rchild = -1;
    }
    //初始化非叶节点（共m-n个）
    for(;node_index<m;node_index++){
        HuffNodes[node_index].weight = 0;
        HuffNodes[node_index].parent = -1;
        HuffNodes[node_index].lchild = -1;
        HuffNodes[node_index].rchild = -1;
    }

    //构建Huffmantree

    int s1,s2;//最小值索引

    for(int i = n;i < m;i++) {
        select(HuffNodes,i-1,&s1,&s2);
        HuffNodes[s1].parent = i;
        HuffNodes[s2].parent = i;
        HuffNodes[i].lchild = s1;
        HuffNodes[i].rchild = s2;
        HuffNodes[i].weight = HuffNodes[s1].weight + HuffNodes[s2].weight;

    }

}

/**
 * 生成Huffman编码，所有结点的Huffman编码存放在HuffCodes中（一个位置存储一个节点的哈夫曼编码，单个结点的哈夫曼编码在bit数组中
 * @param HuffNodes
 * @param HuffCodes
 * @param n
 */
void HuffmanCode(HNodeType HuffNodes[], HCodeType HuffCodes[], int n) {
    int start;
    for(int i =0 ;i<n;i++){
        start = n-2;//每个结点的哈夫曼编码的长度不超过（叶子结点个数n-1），因此bit数组只需要使用(n-1)的长度。
        //而哈夫曼编码是从哈夫曼树的叶子结点开始一直追溯到根结点按照左右赋予0/1值的，所以倒着编码，bit数组起始下标应该是(n-2)，每编码一位就减一
        for(int c = i , f=HuffNodes[i].parent ; f!=-1; c =f,f=HuffNodes[f].parent){
            if(c == HuffNodes[f].lchild) HuffCodes[i].bit[start--]=0;
            else HuffCodes[i].bit[start--]=1;
        }
        HuffCodes[i].start = start+1;//记录第i个结点的哈夫曼编码在其对应bit数组中的起始位置
    }
}


/**
 * Huffman树的中序遍历，遍历结果存放在result中，返回下一个result位置索引
 * @param HuffNodes
 * @param result
 * @param root
 * @param resultIndex
 * @return
 */
int MidOrderTraverse(HNodeType HuffNodes[], float result[], int root, int resultIndex) {
    //根节点 为root
    if (root!=-1){
        resultIndex = MidOrderTraverse( HuffNodes,result,HuffNodes[root].lchild,resultIndex);
        result[resultIndex++] = HuffNodes[root].weight;
        resultIndex = MidOrderTraverse( HuffNodes,result,HuffNodes[root].rchild,resultIndex);
    }

    return resultIndex;
}
/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    HNodeType HuffNodes[MAXNODE];   // 定义一个结点结构体数组
    HCodeType HuffCodes[MAXLEAF];   // 定义一个编码结构体数组
    char text[MAXVALUE+1], ch[MAXLEAF];
    float weight[MAXLEAF], result[MAXNODE];
    int i, j, n, resultIndex;

    //1.接收输入
    str_input(text);

    //2.计算字符总数n，以计算频率
    n = TextStatistics(text, ch, weight);


    // 3.建立哈夫曼树，并进行哈夫曼编码
    HuffmanTree(HuffNodes, weight, n);
    HuffmanCode(HuffNodes, HuffCodes, n);

    //4.打印哈夫曼编码
    for (i=0; i<n; i++) {
        printf("%c的Huffman编码是：", ch[i]);

        for(j=HuffCodes[i].start; j<n-1; j++)
            printf("%d", HuffCodes[i].bit[j]);

        printf("\n");
    }


    // 5.输出Huffman树的中序遍历结果
    resultIndex = MidOrderTraverse(HuffNodes, result, 2*n-2, 0);
    printf("\nHuffman树的中序遍历结果是：");

    for (i=0; i<resultIndex; i++)
        if (i < resultIndex-1)
            printf("%.4f, ", result[i]);
        else
            printf("%.4f\n\n", result[i]);
}

int main() {
    test_all_function();
    return 0;
}

