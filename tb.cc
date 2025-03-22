#include "test.h"
#include <iostream>
int main() {
    bool all_tests_passed = test();

    

    if (all_tests_passed) {
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } else {
        std::cout << "\nSome tests failed. Please check the error messages above." << std::endl;
        return 1;
    }

    return 0;
}