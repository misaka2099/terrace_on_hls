#ifndef MEMORY_POOL
#define MEMORY_POOL

#include <cstddef>
#include <cstring>
#include <ctime>
#include <utility>
#include <iostream>
#include <cstdint>
#include <utility>
#define POOL_SIZE 1048576  // 内存池大小
#define BLOCK_SIZE 1024   // 每个内存块的大小
#include <string.h>


#define mynew(__1) reinterpret_cast<__1>(memory_pool.allocate())
#define myfree(__1) memory_pool.deallocate(__1)
#define mymalloc(...) (memory_pool.allocate())
// #define mynewobj(Type, ...)                         \
// ({                                                       \
//     void* mem = mymalloc(sizeof(Type));                  \
//     Type* arr = reinterpret_cast<Type*>(mem);                        \
//     new (arr) Type(__VA_ARGS__);                         \
//     arr; \
// })

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
template <typename Type, typename... Args>
Type *mynewobj(Args&&... args) {
  void *mem = mymalloc(sizeof(Type));
  Type *arr = reinterpret_cast<Type *>(mem);
  new (arr) Type(std::forward<Args>(args)...);
  return arr;
}
// template<class T>
// class myallocator
// {
//     public:
//     using value_type = T;
//     using pointer = T*;
//     using const_pointer = const T*;
//     using reference = T&;
//     using const_reference = const T&;
//     using size_type = std::size_t;
//     using difference_type = std::ptrdiff_t;

//     pointer allocate(size_type n)
//     {
//         return reinterpret_cast<pointer>(memory_pool.allocate());
//     }

//     void deallocate(pointer ptr, size_type n)
//     {
//         memory_pool.deallocate(ptr);
//     }

//     template <typename... Args>
//     void construct(pointer p, Args&&... args) 
//     {
//         new (p) T(std::forward<Args>(args)...);
//     }
//     void destroy(pointer p) {
//         p->~T();
//     }
//     bool operator==(const myallocator& other)
//     {return true;}
//     bool operator!=(const myallocator& other)
//     {return false;}
// };

// template <class T>
// using custom_vector = std::vector<T, myallocator<T>>;
template <class T>
class custom_vector
{
    public:
    T storage[1024];
    int ptr;
    
    custom_vector()
    { 
        ptr = 0; 
        memset(storage, 0, sizeof(storage));
    }
    void push_back(T val)
    {
        storage[ptr] = val;
        ptr++;
    }
    void pop_back()
    {
        ptr --;
    }
    const T& operator[](int index) const
    {
        return storage[index];
    }
    T& operator[](int index)
    {
        return storage[index];
    }
    const T& front()
    { 
        return storage[0]; 
    }
    const T& back()
    { 
        return storage[ptr - 1];
    }
    bool empty()
    {
        return ptr == 0;
    }
    template<class... Args>
    void emplace_back(Args&&... args) {
        new (&storage[ptr]) T(std::forward<Args>(args)...);
        ptr++;
    }
    int size() const
    { return ptr; }
    // class iterator 
    // {
    //     int pos;
    //     custom_vector* icon;
    //     public:
    //     iterator(custom_vector *a)
    //     {
    //         icon = a;
    //         pos = a->ptr;
    //     }
        
    // };
};
template<class T>
class custom_stack
{
    
    T storage[1024];
    int ptr;
    public:
    custom_stack()
    { 
        ptr = 0; 
        memset(storage, 0, sizeof(storage));
    }
    void push(T val)
    {
        storage[ptr] = val;
        ptr++;
    }
    void pop()
    {
        ptr --;
    }
    T& top()
    {
        return storage[ptr - 1];
    }
    int size() const
    {
        return ptr;
    }
    bool empty()
    {
        return ptr == 0;
    }
    template<class... Args>
    void emplace_back(Args&&... args) {
        new (&storage[ptr]) T(std::forward<Args>(args)...);
        ptr++;
    }
};

namespace std 
{
    template <>
    struct hash<std::pair<unsigned int, unsigned int>> {
        size_t operator()(const std::pair<unsigned int, unsigned int>& p) const {
            return std::hash<unsigned int>()(p.first) ^ std::hash<unsigned int>()(p.second);
        }
    };
}

template<class T>
class custom_set
{
    public:
    T storage[128][16];
    int valid[128];
    size_t capacity = 128;
    int total = 0;
    custom_set()
    {
        memset(storage, 0, sizeof(storage));
        memset(valid, 0, sizeof(valid));
    }
    class iterator 
    {
        public:
        custom_set * icon;
        int first;
        int second;
        
        iterator(const iterator&) = default;
        iterator(custom_set *a): icon(a)
        {
            first = 0;
            second = 0;
        }
        T& operator*()
        { return icon->storage[first][second]; }
        // 前置递增
        iterator operator++() {
            if (second < icon->valid[first] - 1) {
                second++;
            } else {
                first++;
                while (first < icon->capacity && icon->valid[first] == 0) {
                    first++;
                }
                if (first < icon->capacity) {
                    second = 0;
                } else {
                    first = icon->capacity;
                    second = 0;
                }
            }
            return *this;
        }

        // 前置递减
        iterator operator--() {
            if (second > 0) {
                second--;
            } else {
                first--;
                while (first >= 0 && icon->valid[first] == 0) {
                    first--;
                }
                if (first >= 0) {
                    second = icon->valid[first] - 1;
                } else {
                    first = -1;
                    second = 0;
                }
            }
            return *this;
        }

        // 后置递增
        iterator operator++(int) {
            iterator old = *this;
            operator++();
            return old;
        }

        // 后置递减
        iterator operator--(int) {
            iterator old = *this;
            operator--();
            return old;
        }


        bool operator==(const iterator& other)
        {
            return icon == other.icon && first == other.first && second == other.second;
        }

        bool operator!=(const iterator& other)
        {
            return !(*this == other);
        }
    };
    bool erase(const T& value) 
    {
        size_t hash = std::hash<T>{}(value) % capacity;
        for (int it = storage[hash][0]; it < valid[hash]; ++it) {
            if (storage[hash][it] == value) {
                for (int i = it ; i < valid[hash] - 1; i++)
                {
                    storage[hash][i] = storage[hash][i+1];
                }
                --valid[hash];
                return true;
            }
        }
        return false;
    }
    void insert(const T& value)
    {
        size_t hash = std::hash<T>{}(value) % capacity;
        storage[hash][valid[hash]] = value;
        valid[hash]++;
    }
    int count(const T& value)
    {
        size_t hash = std::hash<T>{}(value) % capacity;
        for (int i = 0 ; i < valid[hash] ; i++)
        {
            if (storage[hash][i] == value)
            {
                return 1;
            }
        }
        return 0;
    }
    iterator begin()
    {
        int first = -1;
        for (int i = 0 ; i < capacity ; i++)
        {
            if (valid[i] != 0)
            {
                first = i;
                break;
            }
        }
        if (first == -1)
        {
            return end();
        }
        iterator res = iterator(this);
        res.first = first;
        res.second = 0;
        return res;
    }
    iterator end() 
    {
        iterator res = iterator(this);
        res.first = capacity;
        res.second = 0;
        return res;
    }
};
template <typename Key, typename T>
class custom_map 
{
    using Hash = std::hash<Key>;
    using pair=std::pair<Key, T>;
    
    pair storage[128][16];
    int capacity = 128;
    int valid[128];
    public:
    class iterator 
    {
        public:
        custom_map * icon;
        int first;
        int second;
        iterator(const iterator&) = default;
        iterator(custom_map *a): icon(a)
        {
            first = 0;
            second = 0;
        }
        pair& operator*()
        { return icon->storage[first][second]; }
        // 前置递增
        iterator operator++() {
            if (second < icon->valid[first] - 1) {
                second++;
            } else {
                first++;
                while (first < icon->capacity && icon->valid[first] == 0) {
                    first++;
                }
                if (first < icon->capacity) {
                    second = 0;
                } else {
                    first = icon->capacity;
                    second = 0;
                }
            }
            return *this;
        }

        // 前置递减
        iterator operator--() {
            if (second > 0) {
                second--;
            } else {
                first--;
                while (first >= 0 && icon->valid[first] == 0) {
                    first--;
                }
                if (first >= 0) {
                    second = icon->valid[first] - 1;
                } else {
                    first = -1;
                    second = 0;
                }
            }
            return *this;
        }

        // 后置递增
        iterator operator++(int) {
            iterator old = *this;
            operator++();
            return old;
        }

        // 后置递减
        iterator operator--(int) {
            iterator old = *this;
            operator--();
            return old;
        }

        bool operator==(const iterator& other)
        {
            return icon == other.icon && first == other.first && second == other.second;
        }

        bool operator!=(const iterator& other)
        {
            return !(*this == other);
        }
    };
    custom_map()
    {
        memset(storage, 0, sizeof(storage));
        memset(valid, 0, sizeof(valid));
    }
    int count(Key key)
    { 
        Hash process;
        int hash = process(key)%capacity;
        for (int i = 0 ; i < valid[hash] ; i++)
        {
            if (storage[hash][i].first == key)
            {
                return 1;
            }
        }
        return 0;
    }
    void insert (pair x)
    {
        Hash process;
        int hash = process(x.first)%capacity;
        storage[hash][valid[hash]] = x;
        valid[hash]++;
    }
    iterator begin()
    {
        int first = -1;
        for (int i = 0 ; i < capacity ; i++)
        {
            if (valid[i] != 0)
            {
                first = i;
                break;
            }
        }
        if (first == -1)
        {
            return end();
        }
        iterator res = iterator(this);
        res.first = first;
        res.second = 0;
        return res;
    }
    iterator end() 
    {
        iterator res = iterator(this);
        res.first = capacity;
        res.second = 0;
        return res;
    }
};

// template <typename T>
// using custom_deque = std::deque<T, myallocator<T>>;
// template <typename T>
// using custom_stack = std::stack<T, custom_vector<T>>;
// template <typename Key, typename T, typename Compare = std::less<Key>>
// using custom_map = std::map<Key, T, Compare, myallocator<std::pair<const Key, T>>>;
// template <typename T, typename Compare = std::less<T>>
// using custom_set = std::set<T, Compare, myallocator<T>>;
#endif