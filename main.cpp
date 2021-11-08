#include <iostream>
#include "dynamicLib/binarySignal.h"

int main() {
    Signal::BinarySignal bs1;
    std::cout << bs1 << std::endl;

    Signal::BinarySignal bs2(false);
    std::cout << bs2 << std::endl;

    char str1[]{'0', '1', '1', '0'};
    Signal::BinarySignal bs3(4, str1);
    std::cout << bs3 << std::endl;

    std::cin >> bs2;
    std::cout << bs2 << std::endl;

    return 0;
}
