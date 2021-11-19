#include<stdio.h>
#include<stdlib.h>

#define MaxSize 255
typedef struct {
    char *data;    //静态数组，存放字符串
    int length;    //串的长度
} AString;

bool Init(AString &string);    //初始化
bool StrAssign(AString &string, char *chars);    //赋值操作，把串string赋值为chars
bool StrCopy(AString &string, AString source);    //复制操作，把串source复制到串string中
bool StrEmpty(AString string);    //判空
int StrLength(AString string);    //获取串长
bool Concat(AString &string, AString source_01, AString source_02);    //拼接操作，将串source_01和串source_02拼接成新串，返回给string
bool SubString(AString &sub, AString main, int pos, int len);    //求子串
int StrCompare(AString source_01, AString source_02);    //比较操作
int index(AString string, AString source);    //定位操作
int index_kmp(AString string, AString source, int next[]);    //定位操作-kmp算法
bool getNextArray(AString source,int *next);   //构造辅助数组 next
/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    AString string;
    Init(string);

    //=======StrAssign
    char *str = " googlooogoogle";
    StrAssign(string, str);
    printf("%s length=%d\n", string.data, string.length);

    //=======StrCopy
    printf("copy:");
    AString copyString;
    Init(copyString);
    StrCopy(copyString, string);
    printf("%s length=%d\n", copyString.data, string.length);


    //======SubString
    AString sub;
    Init(sub);
    SubString(sub, string, 2, 4);
    printf("subString:%s length=%d\n", sub.data, sub.length);

    //======index
    int pos = index(string, sub);
    printf("index:%d\n", pos);

    //======index_kmp
    sub.data = " google";
    sub.length = 6;
    int next[sub.length + 1];
    getNextArray(sub,next);

    printf("next:[");
    for (int i = 1; i < (sub.length+1); ++i){
        printf("%d", next[i]);
        if((i+1)<sub.length+1) {
            printf(" ,");
        }
    }
    printf("]\n");

    pos = index_kmp(string, sub, next);
    printf("index(kmp):%d\n", pos);


}


/**
 * 构建kmp-next数组
 * @param source
 * @return
 */
bool getNextArray(AString source,int *next) {
    int length = source.length;
    next[1] = 0;
    next[2] = 1;
    for (int i = 3; i <= length; ++i) {
        //i代表 第i位置，匹配失败
        //source 的前i-1个字符 已知
        int j = i - 1;   //最后一个匹配成功的位置
        int k = i - 2;
        while (k > 0) {
            if (source.data[k] == source.data[j]) {
                j--;
                k--;
            } else {
                //向右移动一格
                //j-k 代表 平移位数
                //-2 代表距离 i 2位
                k = i - (j - k) - 2;
                j = i - 1;
            }
        }
        if (k == 0) {
            next[i] = i - j;
        } else {
            next[i] = 1;
        }

    }
    return true;
}

/**
 * 定位 使用kmp算法
 * @param string
 * @param source
 * @param next
 * @return
 */
int index_kmp(AString string, AString source, int next[]) {
    int m_length = string.length;    //主串长度
    int s_length = source.length;    //模式串长度
    int s_size = m_length - s_length + 1;    //比主串指针遍历的最后位置(最后一个子串的起始位置)
    if (m_length < s_length) {    //判断传入参数是否合法
        return -1;
    }

    int i = 1;    //从位置1遍历到s_size
    while (i <= s_size) {
        int j = 1;    //指向模式串第一个位置
        while (j <= s_length) {
            //当 next[1]时  或者当前字符不匹配时，指针进行后移
            if (j==0 || string.data[i] == source.data[j]) {
                i++;
                j++;
            }else{
                //从next数组读取偏移量
                j = next[j];
            }
        }
        //当j==s_length+1 表示匹配成功
        if (j == s_length + 1) {
            //计算出匹配位置
            return i-s_length;
        }
    }

}


/**
 * 定位(朴素模式匹配)
 * 根据source匹配串string的子串
 * 如果定位成功，返回定位位置，否者返回-1
 * @param string 串
 * @param source 匹配资源
 * @return 定位位置
 */
int index(AString string, AString source) {
    int m_length = string.length;
    int s_length = source.length;
    int s_size = m_length - s_length + 1;


    int i = 1;
    while (i <= s_size) {
/*        AString sub;
        Init(sub);
        SubString(sub, string, i, s_length);
        if (StrCompare(sub, source) == 0) {
            return i;
        }
        i++;*/

        int j = 1;
        while (j <= s_length) {
            if (source.data[j] != string.data[i]) {
                break;
            }
            i++;
            j++;
        }

        if (j == s_length + 1) {
            return i - j + 1;
        }
        i = i - j + 2;
        j = 1;

    }

    return -1;

}

int main() {
    test_all_function();
    return 0;
}

/**
 * 从主串main中的第pos位置开始，分割大小为len的子串
 * @param sub 子串
 * @param main 主串
 * @param pos 分割位置
 * @param len 子串长度
 * @return 是否分割成功
 */
bool SubString(AString &sub, AString main, int pos, int len) {
    if (pos + len - main.length - 1 > 0) {
        return false;
    }

    int i = 1;

    for (int j = pos; j < pos + len; ++j, ++i) {
        sub.data[i] = main.data[j];
    }
    sub.length = len;
    sub.data[sub.length + 1] = '\0';
    return true;
}

/**
 * 比较操作
 * 遍历source_01和source_02，当字符不相等时，返回 字符的差值。差值大于0时，表示大于，差值小于0时，表示小于。当两个串相等时，返回true
 * 其中一个串遍历结束时，另一个串还存在其他字符，则返回两个串的长度差值source_01.length - source_02.length
 * @param source_01 串1
 * @param source_02 串2
 * @return 比较字符串大小
 */
int StrCompare(AString source_01, AString source_02) {
    int minLength = source_01.length > source_02.length ? source_02.length : source_01.length;
    for (int i = 1; i <= minLength; ++i) {
        if (source_01.data[i] != source_02.data[i]) {
            return source_01.data[i] - source_02.data[i];
        }
    }
    return source_01.length - source_02.length;
}

/**
 * 返回串string的长度
 * @param string 串
 * @return 串string的长度
 */
int StrLength(AString string) {
    return string.length;
}

/**
 * 判断串string是否为空
 * @param string 字符串
 * @return 串是否为空
 */
bool StrEmpty(AString string) {
    return string.length == 0;
}

/**
 * 复制操作
 * 将串source复制到串string上
 * @param string 串
 * @param source 串
 * @return 如果复制成功，则返回true
 */
bool StrCopy(AString &string, AString source) {
    for (int i = 1; i <= source.length; ++i) {
        string.data[i] = source.data[i];
    }
    string.length = source.length;

    string.data[string.length + 1] = '\0';    //添加终止符

    return true;
}

/**
 * 初始化串
 * @param string 串
 * @return 初始化结果
 */
bool Init(AString &string) {
    string.data = (char *) malloc(MaxSize * sizeof(char));
    string.length = 0;
    string.data[0] = ' ';
    return string.data != NULL;
}

/**
 * 赋值操作，将chars赋值给串string
 * @param string 串
 * @param chars 赋值内容
 * @return 赋值结果
 */
bool StrAssign(AString &string, char *chars) {
    if (chars == NULL) {
        return false;
    }

    int len = 0;
    int pos = 1;
    chars = chars + 1;    //char数组，索引0位置放空，从索引1开始
    while (*(chars) != '\0') {
        string.data[pos++] = *chars;
        len++;
        chars++;
    }
    string.data[pos] = '\0';

    string.length = len;
    return true;
}