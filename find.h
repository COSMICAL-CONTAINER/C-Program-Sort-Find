#ifndef __find_H
#define __find_H

#define bool char
#define MAXSIZE_FIND 50

typedef enum
{
    Find_Result_Equation   = 0x00,             // 查找相等
    Find_Result_Bigger     = 0x02,             // 查找大于
    Find_Result_Smaller    = 0x04,             // 查找小于  
}FindResult_TypeDef;

typedef struct
{
    unsigned int Find_Element_Size;               //查找数组中每个元素占用的空间
    void *Find_Arr;                               //需要进行查找操作的数组
    unsigned int Find_Size;                       //查找数组的元素个数
    bool (*Find_Compare)(void *, void *);         //用户自定义查找函数 默认bool返回值使用枚举类型FindResult_TypeDef作为返回值
    void * WantFind;                              //想要查找的元素
}Find_InitTypeDef;

int BinarySearch(Find_InitTypeDef* Find_InitStruct);

#endif