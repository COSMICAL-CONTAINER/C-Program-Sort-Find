#include "find.h"

int BinarySearch(Find_InitTypeDef* Find_InitStruct)
{
    size_t Left = 0;
    size_t Right = Find_InitStruct->Find_Size - 1;
    //这里最好不要写 Middle = (Left + Right) / 2
    size_t Middle = Left + ((Right - Left) >> 1);

    void *VP_list[MAXSIZE_FIND];
    
    for(int i = 0; i < Find_InitStruct->Find_Size; i++)
    {
        VP_list[i] = (void *)((long long)Find_InitStruct->Find_Arr + Find_InitStruct->Find_Element_Size* i);
    }

    while(Left <= Right)
    {
        Middle = Left + ((Right - Left) >> 1);

        switch (Find_InitStruct->Find_Compare(VP_list[Middle], Find_InitStruct->WantFind))
        {
            case Find_Result_Equation:
            {
                return Middle;
                break;
            }
            case Find_Result_Bigger:
            {
                Right = Middle - 1;
                break;
            }
            case Find_Result_Smaller:
            {
                Left = Middle + 1;
                break;
            }
            default:
                break;
        }
    }
    return -1;
}