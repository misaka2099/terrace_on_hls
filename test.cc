#include "memory_pool.hpp"
#include <iostream>

bool test_memory_pool() {
    std::cout << "Testing Memory Pool:" << std::endl;

    // 测试分配和释放
    int* a = reinterpret_cast<int*>(mymalloc(sizeof(int)));
    *a = 10;
    // std::cout << "Allocated value: " << *a << " (Expected: 10)" << std::endl;
    myfree(a);

    // 测试批量分配和释放
    int* arr = mymulnew(int, 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    for (int i = 0; i < 5; i++) {
        // std::cout << "Array[" << i << "]: " << arr[i] << " (Expected: " << i * 10 << ")" << std::endl;
        if (arr[i] != i * 10) {
            // std::cout << "Test failed: Memory Pool multi allocation and deallocation" << std::endl;
            mymuldel(arr, 5);
            return false;
        }
    }
    mymuldel(arr, 5);
    return true;
}

bool test_custom_vector() {
    // std::cout << "\nTesting Custom Vector:" << std::endl;

    custom_vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    // std::cout << "Vector size: " << vec.size() << " (Expected: 3)" << std::endl;
    if (vec.size() != 3) {
        // std::cout << "Test failed: Custom Vector size after push_back" << std::endl;
        return false;
    }
    // std::cout << "Vector[0]: " << vec[0] << " (Expected: 10)" << std::endl;
    if (vec[0] != 10) {
        // std::cout << "Test failed: Custom Vector element access" << std::endl;
        return false;
    }
    // std::cout << "Vector[1]: " << vec[1] << " (Expected: 20)" << std::endl;
    if (vec[1] != 20) {
        // std::cout << "Test failed: Custom Vector element access" << std::endl;
        return false;
    }
    // std::cout << "Vector[2]: " << vec[2] << " (Expected: 30)" << std::endl;
    if (vec[2] != 30) {
        // std::cout << "Test failed: Custom Vector element access" << std::endl;
        return false;
    }
    vec.pop_back();
    // std::cout << "Vector size after pop: " << vec.size() << " (Expected: 2)" << std::endl;
    if (vec.size() != 2) {
        // std::cout << "Test failed: Custom Vector size after pop_back" << std::endl;
        return false;
    }
    return true;
}

bool test_custom_stack() {
    // std::cout << "\nTesting Custom Stack:" << std::endl;

    custom_stack<int> stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    // std::cout << "Stack top: " << stk.top() << " (Expected: 30)" << std::endl;
    if (stk.top() != 30) {
        // std::cout << "Test failed: Custom Stack top element" << std::endl;
        return false;
    }
    stk.pop();
    // std::cout << "Stack top after pop: " << stk.top() << " (Expected: 20)" << std::endl;
    if (stk.top() != 20) {
        // std::cout << "Test failed: Custom Stack top element after pop" << std::endl;
        return false;
    }
    return true;
}

bool test_custom_set() {
    // std::cout << "\nTesting Custom Set:" << std::endl;

    custom_set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    // std::cout << "Set contains 20: " << s.count(20) << " (Expected: 1)" << std::endl;
    if (s.count(20) != 1) {
        // std::cout << "Test failed: Custom Set contains element" << std::endl;
        return false;
    }
    // std::cout << "Set contains 40: " << s.count(40) << " (Expected: 0)" << std::endl;
    if (s.count(40) != 0) {
        // std::cout << "Test failed: Custom Set contains non-existing element" << std::endl;
        return false;
    }
    s.erase(20);
    // std::cout << "Set contains 20 after erase: " << s.count(20) << " (Expected: 0)" << std::endl;
    if (s.count(20) != 0) {
        // std::cout << "Test failed: Custom Set erase element" << std::endl;
        return false;
    }
    return true;
}

bool test_custom_map() {
    // std::cout << "\nTesting Custom Map:" << std::endl;

    custom_map<int, int> m;
    m.insert(std::make_pair(1, 10));
    m.insert(std::make_pair(2, 20));
    m.insert(std::make_pair(3, 30));
    // std::cout << "Map contains key 2: " << m.count(2) << " (Expected: 1)" << std::endl;
    if (m.count(2) != 1) {
        // std::cout << "Test failed: Custom Map contains key" << std::endl;
        return false;
    }
    // std::cout << "Map contains key 4: " << m.count(4) << " (Expected: 0)" << std::endl;
    if (m.count(4) != 0) {
        // std::cout << "Test failed: Custom Map contains non-existing key" << std::endl;
        return false;
    }
    return true;
}
bool test()
{
    return test_memory_pool() && test_custom_vector() &&test_custom_set() &&test_custom_stack() &&test_custom_map();
}
// #include <cstdint>
// #include <iostream>
// class block 
// {
//     public:
//     int storage = 0;
//     int index = 1;
// }Block;
// block* trans(void* ptr)
// {
//     auto* to_deallocate = reinterpret_cast<block*>(
//         reinterpret_cast<int8_t*>(ptr) - offsetof(block, index)
//     );
//     return to_deallocate;;
// }
// bool test()
// {
    
//     auto *ptr = &Block.index;
//     auto* to_deallocate = trans(ptr);
//     if (to_deallocate->index == 1 && to_deallocate->storage == 0)
//     {
//         return true;
//     }
//     return false;
// }
