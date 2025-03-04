#ifndef MEMORY_POOL
#define MEMORY_POOL

#include <cstddef>
#include <cstring>
#include <ctime>
#include <stack>
#include <iostream>
#include <cstdint>
#include <utility>
#include <vector>
#include <map>
#include <set>
#define POOL_SIZE 1048576  // 内存池大小
#define BLOCK_SIZE 1024   // 每个内存块的大小
#include <string.h>


#define mynew(__1) reinterpret_cast<__1>(memory_pool.allocate())
#define myfree(__1) memory_pool.deallocate(__1)
#define mymalloc(...) (memory_pool.allocate())
#define mynewobj(Type, ...)                         \
({                                                       \
    void* mem = mymalloc(sizeof(Type));                  \
    Type* arr = reinterpret_cast<Type*>(mem);                        \
    new (arr) Type(__VA_ARGS__);                         \
    arr; \
})
#define mydelete(ptr) \
({ \
    using __ActualType = typename std::remove_pointer<decltype(ptr)>::type; \
    if (ptr) { \
        ptr->~__ActualType(); \
        myfree(ptr); \
        ptr = nullptr; \
    } \
})
#define mymulnew(Type, Size) \
({      \
    void* mem = mymalloc(sizeof(Type)*Size);                  \
    Type* arr = reinterpret_cast<Type*>(mem);                        \
    for (int i = 0 ; i < Size ; i++) {new (&arr[i]) Type(); }\
    arr;\
})      
#define mymuldel(ptr, Size) \
({      \
    using __ActualType = typename std::remove_pointer<decltype(ptr)>::type; \
    for (int i = 0 ; i < Size ; i ++) {ptr[i].~__ActualType();}\
    myfree(ptr);\
    ptr = nullptr;\
})  



// 内存池数组

using Byte = unsigned char;

class _memory_pool 
{
    struct block 
    {
        Byte block_storage[BLOCK_SIZE];
        block *next;
        block()
        {
            next = nullptr;
            memset(block_storage, 0, sizeof(block_storage));
        }
    };
    block storage[POOL_SIZE/BLOCK_SIZE];
    block* cur;
    public:
    _memory_pool ()
    {
        for (int i = 0 ; i < POOL_SIZE/BLOCK_SIZE - 1 ; i++)
        {
            storage[i].next = &storage[i+1];
        }
        cur = storage;
    }
    ~_memory_pool()
    {}
    void* allocate()
    {
        if (cur == nullptr)
        { 
            std::cerr << "no enough space!!!!" << std::endl;
            return nullptr;
        }
        else  
        {
            block* x = cur;
            cur = cur->next;
            return x->block_storage;
        }
    }
    void deallocate(void* bin)
    {
        if (!bin)
        { 
            std::cerr << "bad deallocate!!!!" << std::endl;
            return;
        }
        block* to_deallocate = reinterpret_cast<block*>(
            reinterpret_cast<int8_t*>(bin) - offsetof(block, block_storage)
        );
        memset(bin, 0, sizeof(Byte)*BLOCK_SIZE);
        if (cur == nullptr)
        {
            cur = to_deallocate;
            cur->next = nullptr;
        }
        else  
        {
            to_deallocate->next = cur;
            cur = to_deallocate;
        }
    }
};
extern _memory_pool memory_pool;
template<class T>
class myallocator
{
    public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    pointer allocate(size_type n)
    {
        return reinterpret_cast<pointer>(memory_pool.allocate());
    }

    void deallocate(pointer ptr, size_type n)
    {
        memory_pool.deallocate(ptr);
    }

    template <typename... Args>
    void construct(pointer p, Args&&... args) 
    {
        new (p) T(std::forward<Args>(args)...);
    }
    void destroy(pointer p) {
        p->~T();
    }
    bool operator==(const myallocator& other)
    {return true;}
    bool operator!=(const myallocator& other)
    {return false;}
};

template <class T>
using custom_vector = std::vector<T, myallocator<T>>;
// template <typename T>
// using custom_deque = std::deque<T, myallocator<T>>;
template <typename T>
using custom_stack = std::stack<T, custom_vector<T>>;
template <typename Key, typename T, typename Compare = std::less<Key>>
using custom_map = std::map<Key, T, Compare, myallocator<std::pair<const Key, T>>>;
template <typename T, typename Compare = std::less<T>>
using custom_set = std::set<T, Compare, myallocator<T>>;
#endif