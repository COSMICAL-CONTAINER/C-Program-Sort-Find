#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

struct StudentInfo
{
    char ID[11];
    char * name;
    double score;
}StuInfo[12]=
{
    {"2000301105", "JACK", 95},
    {"2000201505", "LUN", 85},
    {"2100820115", "MARY", 75.5},
    {"2100850122", "KATE", 78.9},
    {"1900201011", "LILI", 88},
    {"1900401105", "JACK", 96},
    {"2000830105", "JAN", 98.4},
    {"2000520012", "SAM", 75},
    {"1900800045", "OSCAR", 64},
    {"1900301105", "JACK", 97},
    {"2100803312", "ZOE", 68.9},
    {"2100830211", "BOBI", 87.6},
};

typedef struct StudentInfo Student;
typedef Student* P_Student;

/*  排序 int 数组  */
bool sort_int(void *a, void *b)
{
    if( *(int *)a >= *(int *)b )
    {
        return True;
    }
    return False;
}

void Print_int(void *P_Int[], int Size)
{
    for(int i = 0; i < Size; ++i)
    {
        printf("%d ",*(int *)(P_Int[i]));
    }
    putchar('\n');
}

/*  排序 double 数组  */
bool sort_double(void *a, void *b)
{
    if( *(double *)a >= *(double *)b )
    {
        return True;
    }
    return False;
}

void Print_double(void *P_Double[], int Size)
{
    for(int i = 0; i < Size; ++i)
    {
        printf("%lf ",*(double *)(P_Double[i]));
    }
    putchar('\n');
}

/*  排序 结构体 数组  */
bool sort_struct_score(void *a, void *b)
{
    if( ((P_Student)(a))->score >= ((P_Student)(b))->score )
    {
        return True;
    }
    return False;
}

bool sort_struct_ID(void *a, void *b)
{
    if( strcmp( ((P_Student)(a))->ID, ((P_Student)(b))->ID) >= 0)
    {
        return True;
    }
    return False;
}

bool sort_struct_name(void *a, void *b)
{
    if( strcmp( ((P_Student)(a))->name, ((P_Student)(b))->name) >= 0)
    {
        return True;
    }
    return False;
}

void Print_struct(void *P_Student_list[], int Size)
{
    printf("    ID      name  score\n");
    for(int i = 0; i < Size; ++i)
    {
        printf("%s ",((P_Student)(P_Student_list[i]))->ID);
        printf("%5s ",((P_Student)(P_Student_list[i]))->name);
        printf("%6.2lf ",((P_Student)(P_Student_list[i]))->score);
        putchar('\n');
    }
}

//p_int 是指向一个 [指针数组(排好序的元素的地址构成的)]的 指针
void Print_int_1(void *p_int,int N)
{
    for(int i = 0; i < N; ++i)
    {
        printf("%d ", *(int *)(*((long long *)p_int + i)) );
    }
    putchar('\n');
}

void Print_int_2(long long p_int[],int N)
{
    for(int i = 0; i < N; ++i)
    {
        printf("%d ", *(int *)(p_int[i]) );
    }
    putchar('\n');
}

int main()
{
    Sort_InitTypeDef Sort_InitStructure;
    int array_int[10] = {9,8,7,6,5,4,3,2,1,0};
    double array_double[10] = {9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1,10.10};

    printf("排序 int 型数组:\n");
    
    //欲排序的数组中每个元素所占用的大小
    Sort_InitStructure.Sort_Element_Size = sizeof(int);
    //欲排序的数组的首地址
    Sort_InitStructure.Sort_Arr = array_int;
    //欲排序数组的长短，也就是排序元素的多少
    Sort_InitStructure.Sort_Size = sizeof(array_int) / sizeof(array_int[0]);
    //欲使用的排序方法 [插入排序、归并排序、快速排序](目前写了的方法，后面可能会加入别的排序方法)
    Sort_InitStructure.Sort_Method = Sort_Method_Quicksort;
    //用户自定义的比较函数，用于确认两个元素的排序的先后顺序，默认bool Sort_Comapre(void *a, void *b),返回 True 表示需要交换
    Sort_InitStructure.Sort_Compare = sort_int;
    //排序的时候是否需要改变原来的数组的顺序，如果不改变就会返回一个指针数组用来表示排序的结果
    Sort_InitStructure.Sort_Way = Sort_Way_UnChange;
    //排序完成后的打印函数，用于排好序之后直接输出排序结果，默认void Sort_Print(void *P_Ele[], int Size),传入NULL可以选择不打印
    Sort_InitStructure.Sort_Printf = Print_int;
    //Sort函数在上面选择Sort_Way为Sort_Way_UnChange的时候会返回一个指针(地址)数组 [其实是这个数组的首地址]
    //遍历指针所指向的元素就是根据用户传入的排序函数所排序的顺序
    long long *p_int = Sort(&Sort_InitStructure);
    printf("打印返回的 指针数组 \n");
    //下面提供两种方法打印Sort函数返回的数组
    Print_int_1((void *)p_int, sizeof(array_int) / sizeof(array_int[0]));
    Print_int_2(p_int, sizeof(array_int) / sizeof(array_int[0]));
    //最后别忘记了要free掉这片空间
    free(p_int);

    //这样排序就不会打印出结果来
    Sort_InitStructure.Sort_Printf = NULL;
    Sort(&Sort_InitStructure);

    printf("\n排序 double 型数组:\n");
    Sort_InitStructure.Sort_Element_Size = sizeof(double);
    Sort_InitStructure.Sort_Arr = array_double;
    Sort_InitStructure.Sort_Size = sizeof(array_double) / sizeof(array_double[0]);
    Sort_InitStructure.Sort_Method = Sort_Method_Quicksort;
    Sort_InitStructure.Sort_Compare = sort_double;
    Sort_InitStructure.Sort_Way = Sort_Way_Change;
    Sort_InitStructure.Sort_Printf = Print_double;

    Sort(&Sort_InitStructure);

    printf("\n按 ID 排序结构体:\n");
    Sort_InitStructure.Sort_Element_Size = sizeof(StuInfo[0]);
    Sort_InitStructure.Sort_Arr = StuInfo;
    Sort_InitStructure.Sort_Size = sizeof(StuInfo) / sizeof(StuInfo[0]);
    Sort_InitStructure.Sort_Method = Sort_Method_Quicksort;
    Sort_InitStructure.Sort_Compare = sort_struct_ID;
    Sort_InitStructure.Sort_Way = Sort_Way_Change;
    Sort_InitStructure.Sort_Printf = Print_struct;
    Sort(&Sort_InitStructure);

    //在上面初始化好之后，我们要改变结构体排序的具体内容的时候只需要改变Sort_Compare
    printf("\n按 name 排序结构体:\n");
    Sort_InitStructure.Sort_Compare = sort_struct_name;
    Sort(&Sort_InitStructure);

    printf("\n按 score 排序结构体:\n");
    Sort_InitStructure.Sort_Compare = sort_struct_score;
    Sort(&Sort_InitStructure);

    printf("\n原来的int数组:\n");
    for(int i = 0; i < sizeof(array_int) / sizeof(array_int[0]); ++i)
    {
        printf("%d ",array_int[i]);
    }
    putchar('\n');

    printf("\n原来的double数组:\n");
    for(int i = 0; i < sizeof(array_double) / sizeof(array_double[0]); ++i)
    {
        printf("%lf ",array_double[i]);
    }
    putchar('\n');

    printf("\n原来的结构体:\n");
    printf("    ID      name  score\n");
    for(int i = 0; i < sizeof(StuInfo) / sizeof(StuInfo[0]); ++i)
    {
        printf("%s ",(StuInfo[i]).ID);
        printf("%5s ",(StuInfo[i]).name);
        printf("%6.2lf ",(StuInfo[i]).score);
        putchar('\n');
    }

    return 0;
}