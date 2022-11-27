#ifndef __sort_H
#define __sort_H

#define bool char
#define True 1
#define False 0

#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
#define GetVarName(var) (#var)

#define MAXSIZE 50

typedef enum
{
    Sort_Way_Change   = 0x00,             // 改变原来的数组
    Sort_Way_UnChange = 0x02,             // 不改变原来的数组返回一个指针数组供给用户
}SortWay_TypeDef;

typedef enum
{
    Sort_Method_Insertionsort = 0x00,             // 插入排序
    Sort_Method_Mergesort     = 0x02,             // 归并排序
    Sort_Method_Quicksort     = 0x04,             // 快速排序  
}SortMethod_TypeDef;

typedef struct
{
    unsigned int Sort_Element_Size;               //排序数组中每个元素占用的空间
    void *Sort_Arr;                               //需要排序的数组
    unsigned int Sort_Size;                       //排序数组的元素个数
    SortMethod_TypeDef Sort_Method;               //排序方法-插入排序、归并排序、快速排序
    bool (*Sort_Compare)(void *, void *);         //用户自定义比较函数 默认bool返回值，True表示需要交换
    SortWay_TypeDef Sort_Way;                     //排序是否会改变用户数组
    void (*Sort_Printf)(void *[], int);           //最终打印函数
}Sort_InitTypeDef;

#define IS_Sort_METHOD(METHOD) ((METHOD) == Sort_Method_Insertionsort) || \
                                ((METHOD) == Sort_Method_Mergesort) || \
                                ((METHOD) == Sort_Method_Quicksort)

//插入排序
void InsertSort( void *A[ ], int N ,bool (*sort_fun)(void *, void *));

//归并排序
void Merge( void *A[ ], void *TmpArray[ ], int Lpos, int Rpos, int RightEnd, bool (*sort_fun)(void *, void *));
void MSort( void *A[ ], void *TmpArray[ ], int Left, int Right ,bool (*sort_fun)(void *, void *));
void Mergesort(unsigned int Element_Size, void *A[ ], int N , bool (*sort_fun)(void *, void *));

//快速排序
void Swap( void **Lhs, void **Rhs );
void * Median3( void * A[ ], int Left, int Right, bool (*sort_fun)(void *, void *));

void Qsort(void * A[ ], int Left, int Right, bool (*sort_fun)(void *, void *));
void Quicksort(void *A[ ], int N , bool (*sort_fun)(void *, void *));
void copy(char *dest, const void* src, int Element_Size);
void *Sort(Sort_InitTypeDef* Sort_InitStruct);

#endif