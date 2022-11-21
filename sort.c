/* This file contains a collection of sorting routines */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"


void InsertSort( void *A[ ], int N ,bool (*sort_fun)(void *, void *))
{
    int j, P;
    void * Tmp;
    for( P = 1; P < N; P++ )
    {
        Tmp = A[ P ];
        for( j = P; j > 0 && sort_fun((void *)A[ j - 1 ],(void *)Tmp); j-- )
        {
            A[ j ] = A[ j - 1 ];
        }
        A[ j ] = Tmp;
    }
}


//归并排序
void Merge( void *A[ ], void *TmpArray[ ], int Lpos, int Rpos, int RightEnd, bool (*sort_fun)(void *, void *) )
{
    int i, LeftEnd, NumElements, TmpPos;

    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while( Lpos <= LeftEnd && Rpos <= RightEnd )
        //A[ Lpos ] <= A[ Rpos ]
        if( !sort_fun(A[ Lpos ], A[ Rpos ]) )
            TmpArray[ TmpPos++ ] = A[ Lpos++ ];
        else
            TmpArray[ TmpPos++ ] = A[ Rpos++ ];

    while( Lpos <= LeftEnd )  /* Copy rest of first half */
        TmpArray[ TmpPos++ ] = A[ Lpos++ ];
    while( Rpos <= RightEnd ) /* Copy rest of second half */
        TmpArray[ TmpPos++ ] = A[ Rpos++ ];

    /* Copy TmpArray back */
    for( i = 0; i < NumElements; i++, RightEnd-- )
        A[ RightEnd ] = TmpArray[ RightEnd ];
}

void MSort( void *A[ ], void *TmpArray[ ], int Left, int Right ,bool (*sort_fun)(void *, void *) )
{
    int Center;

    if( Left < Right )
    {
        Center = ( Left + Right ) / 2;
        MSort( A, TmpArray, Left, Center, sort_fun );
        MSort( A, TmpArray, Center + 1, Right, sort_fun );
        Merge( A, TmpArray, Left, Center + 1, Right, sort_fun );
    }
}

void Mergesort(unsigned int Element_Size, void *A[ ], int N , bool (*sort_fun)(void *, void *))
{
    void *TmpArray;

    TmpArray = malloc( N * Element_Size );
    if( TmpArray != NULL )
    {
        //MSort( A, TmpArray, 0, N - 1 );
        
        MSort( A, TmpArray, 0, N - 1, sort_fun);

        free( TmpArray );
    }
    else
        FatalError( "No space for tmp array!!!" );


}
/* END */



//快速排序
#define Cutoff ( 3 )

void Swap( void **Lhs, void **Rhs )
{
    void ** Tmp;
    Tmp = *Lhs;
    *Lhs = *Rhs;
    *Rhs = Tmp;
}

void * Median3( void * A[ ], int Left, int Right, bool (*sort_fun)(void *, void *))
{
    int Center = ( Left + Right ) / 2;

    if( sort_fun(A[ Left ], A[ Center ]) )
        Swap( &A[ Left ], &A[ Center ] );
    if( sort_fun(A[ Left ], A[ Right ]) )
        Swap( &A[ Left ], &A[ Right ] );
    if( sort_fun(A[ Center ], A[ Right ]) )
        Swap( &A[ Center ], &A[ Right ] );

    /* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */

    Swap( &A[ Center ], &A[ Right - 1 ] );  /* Hide pivot */
    return A[ Right - 1 ];                /* Return pivot */
}


void Qsort(void * A[ ], int Left, int Right, bool (*sort_fun)(void *, void *))
{
    int i, j;
    void *Pivot;
    if( Left + Cutoff <= Right )
    {
        Pivot = Median3( A, Left, Right, sort_fun);
        i = Left; j = Right - 1;
        for( ; ; )
        {
            while( !sort_fun(A[ ++i ], Pivot) ){ }
            while( sort_fun(A[ --j ], Pivot) ){ }
            if( i < j )
                Swap( &A[ i ], &A[ j ] );
                else
                break;
        }
        Swap( &A[ i ], &A[ Right - 1 ] );  /* Restore pivot */

        Qsort( A, Left, i - 1, sort_fun);
        Qsort( A, i + 1, Right, sort_fun);
    }
    else  /* Do an insertion sort on the subarray */
    {
        InsertSort( A + Left, Right - Left + 1, sort_fun);
    }
}


void Quicksort(void *A[ ], int N , bool (*sort_fun)(void *, void *))
{
    Qsort( A, 0, N - 1, sort_fun);
}


void copy(char *dest, const void* src, int Element_Size)
{
    for(int i = 0; i < Element_Size; ++i)
    {
        *(dest + i) = *(char *)(&(*(char *)src) + i);
    }
}


void *Sort(Sort_InitTypeDef* Sort_InitStruct)
{
    void *VP_list[MAXSIZE];
    
    for(int i = 0; i < Sort_InitStruct->Sort_Size; i++)
    {
        VP_list[i] = (void *)((long long)Sort_InitStruct->Sort_Arr + Sort_InitStruct->Sort_Element_Size * i);
    }
    
    if( IS_Sort_METHOD(Sort_InitStruct->Sort_Method) )
    {
        switch (Sort_InitStruct->Sort_Method)
        {
            case Sort_Method_Insertionsort:
                InsertSort(VP_list, Sort_InitStruct->Sort_Size, Sort_InitStruct->Sort_Compare);
                break;
            case Sort_Method_Mergesort:
                Mergesort(Sort_InitStruct->Sort_Element_Size, VP_list, Sort_InitStruct->Sort_Size, Sort_InitStruct->Sort_Compare);
                break;
            case Sort_Method_Quicksort:
                Quicksort(VP_list, Sort_InitStruct->Sort_Size, Sort_InitStruct->Sort_Compare);
                break;
            default:
                break;
        }
        if(Sort_InitStruct->Sort_Printf)
            Sort_InitStruct->Sort_Printf(VP_list, Sort_InitStruct->Sort_Size);

        if(Sort_InitStruct->Sort_Way == Sort_Way_Change)
        {
            char *temp = (char *)malloc(Sort_InitStruct->Sort_Size * Sort_InitStruct->Sort_Element_Size);

            //这里确实只能分开写，要不然会出未知bug，奇怪
            for(int i = 0; i < Sort_InitStruct->Sort_Size; ++i)
                copy( (char *)((long long)temp + i * Sort_InitStruct->Sort_Element_Size), VP_list[i], Sort_InitStruct->Sort_Element_Size);

            for(int i = 0; i < Sort_InitStruct->Sort_Size; ++i)
            {
                for(int j = 0; j < Sort_InitStruct->Sort_Element_Size; ++j)
                    *(char *)((long long)Sort_InitStruct->Sort_Arr + (i * Sort_InitStruct->Sort_Element_Size) + (j * sizeof(char))) = *(char *)((long long)temp + (i * Sort_InitStruct->Sort_Element_Size) + (j * sizeof(char)));
            }
            free(temp);
            return NULL;
        }
        else if(Sort_InitStruct->Sort_Way == Sort_Way_UnChange)
        {
            long long *result = (long long *)malloc(MAXSIZE * sizeof(long long *));

            for(int i = 0; i < Sort_InitStruct->Sort_Size; ++i)
                result[i] = (long long)VP_list[i];
            return (void *)result;
        }
    }
    return NULL;
}
