#pragma once
#include <utility>
template <typename T>
inline void mysort(T arr[], int n, bool (*compare)(const T&, const T&)) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - 1 - i; j++) 
        {
            if (compare(arr[j + 1], arr[j])) { // 使用传入的比较函数
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
