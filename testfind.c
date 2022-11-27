#include <stdio.h>
#include <string.h>
#include "sort.h"
#include "find.h"

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
typedef Student ElementType;
typedef Student* P_Student;

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


void Print_struct1(Student s1)
{
    printf("    ID      name  score\n");
    printf("%s ",s1.ID);
    printf("%5s ",s1.name);
    printf("%6.2lf ",s1.score);
    putchar('\n');
}


/****************/
bool Find_ID(void *Ele, void *WantFind)
{
    int result = strcmp(((P_Student)(Ele))->ID, (char *)WantFind);
    if( result == 0 )
    {
        return Find_Result_Equation;
    }
    else if( result >= 0)
    {
        return Find_Result_Bigger;
    }
    else
    {
        return Find_Result_Smaller;
    }
}

bool Find_Name(void *Ele, void *WantFind)
{
    int result = strcmp(((P_Student)(Ele))->name, (char *)WantFind);
    if( result == 0 )
    {
        return Find_Result_Equation;
    }
    else if( result >= 0)
    {
        return Find_Result_Bigger;
    }
    else
    {
        return Find_Result_Smaller;
    }
}

bool Find_Score(void *Ele, void *WantFind)
{
    if( ((P_Student)(Ele))->score == *(double *)WantFind)
    {
        return Find_Result_Equation;
    }
    else if( ((P_Student)(Ele))->score > *(double *)WantFind)
    {
        return Find_Result_Bigger;
    }
    else
    {
        return Find_Result_Smaller;
    }
}



int main()
{
    Sort_InitTypeDef Sort_InitStructure;
    int student = 0;
    char ID[11];
    char name[20];
    double score;

    printf("\n按 ID 排序结构体:\n");
    //欲排序的数组中每个元素所占用的大小
    Sort_InitStructure.Sort_Element_Size = sizeof(StuInfo[0]);
    //欲排序的数组的首地址
    Sort_InitStructure.Sort_Arr = StuInfo;
    //欲排序数组的长短，也就是排序元素的多少
    Sort_InitStructure.Sort_Size = sizeof(StuInfo) / sizeof(StuInfo[0]);
    //欲使用的排序方法 [插入排序、归并排序、快速排序](目前写了的方法，后面可能会加入别的排序方法)
    Sort_InitStructure.Sort_Method = Sort_Method_Quicksort;
    //用户自定义的比较函数，用于确认两个元素的排序的先后顺序，默认bool Sort_Comapre(void *a, void *b),返回 True 表示需要交换
    Sort_InitStructure.Sort_Compare = sort_struct_ID;
    //排序的时候是否需要改变原来的数组的顺序，如果不改变就会返回一个指针数组用来表示排序的结果
    Sort_InitStructure.Sort_Way = Sort_Way_Change;
    //排序完成后的打印函数，用于排好序之后直接输出排序结果，默认void Sort_Print(void *P_Ele[], int Size),传入NULL可以选择不打印
    Sort_InitStructure.Sort_Printf = Print_struct;
    Sort(&Sort_InitStructure);
    printf("请输入要查找的学生的ID:");
    gets(ID);
    
    //初始化查找结构体
    Find_InitTypeDef Find_InitStruct;
    //欲进行查找的数组中每个元素所占用的大小
    Find_InitStruct.Find_Element_Size = sizeof(StuInfo[0]);
    //欲进行查找的数组
    Find_InitStruct.Find_Arr = StuInfo;
    //欲进行查找的数组的长度
    Find_InitStruct.Find_Size = sizeof(StuInfo) / sizeof(StuInfo[0]);
    //欲进行的查找函数
    Find_InitStruct.Find_Compare = Find_ID;
    //欲查找的元素
    Find_InitStruct.WantFind = ID;
    student = BinarySearch(&Find_InitStruct);
    if( student >= 0)
    {
        printf("查找到 ID 为 %s 的学生\n", ID);
        Print_struct1(StuInfo[student]);
    }
    else
    {
        printf("没有找到该学生\n");
    }


    //在上面初始化好之后，我们要改变结构体排序的具体内容的时候只需要改变Sort_Compare
    printf("\n按 name 排序结构体:\n");
    Sort_InitStructure.Sort_Compare = sort_struct_name;
    Sort(&Sort_InitStructure);
    printf("请输入要查找的学生的姓名:");
    gets(name);
    //同理，查找我们也只需要进行Find_Compare的改变以及要查找的元素的
    Find_InitStruct.Find_Compare = Find_Name;
    Find_InitStruct.WantFind = name;
    student = BinarySearch(&Find_InitStruct);
    if( student >= 0)
    {
        printf("查找到 name 为 %s 的学生\n", name);
        Print_struct1(StuInfo[student]);
    }
    else
    {
        printf("没有找到该学生\n");
    }

    printf("\n按 score 排序结构体:\n");
    Sort_InitStructure.Sort_Compare = sort_struct_score;
    Sort(&Sort_InitStructure);
    printf("请输入要查找的学生的分数:");
    scanf("%lf",&score);
    Find_InitStruct.Find_Compare = Find_Score;
    Find_InitStruct.WantFind = &score;
    student = BinarySearch(&Find_InitStruct);
    if( student >= 0)
    {
        printf("查找到 score 为 %lf 的学生\n", score);
        Print_struct1(StuInfo[student]);
    }
    else
    {
        printf("没有找到该学生\n");
    }
    return 0;
}