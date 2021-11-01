#include "menu.h"

// 1. Пустой конструктор
void emptyConstructor(BS::BinarySignal *ptr) {
    BS::BinarySignal tmp;
    *ptr = tmp;
}

// 2. Первый констурктор
void firstConstructor(BS::BinarySignal *ptr) {
    bool el;
    std::cout << "Enter element of the binary signal: ->";
    getNum(el);
    BS::BinarySignal tmp(el);
    *ptr = tmp;
}

// 3.
void secondConstructor(BS::BinarySignal *ptr) {
    int sz;
    std::cout << "Enter the number of elements in the binary signal: ->";
//    getPositiveNum(sz);
    std::cin >> sz;
    bool sq[sz];
    for (int i = 0; i < sz; i++)
        std::cin >> sq[i];
    try {
        BS::BinarySignal tmp(sz + 1, sq);
        *ptr = tmp;
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
    catch (std::invalid_argument &ia) {
        std::cout << ia.what() << std::endl;
    }
}

// 4.
void inputSequence(BS::BinarySignal *ptr)
{
    std::cin >> *ptr;
}

// 5.
void outputSequence(BS::BinarySignal ptr) {
    std::cout << ptr << std::endl;
}

// 6.
void copyBinarySignal(BS::BinarySignal *ptr) {
    int n;
    std::cout << "Enter n: ->";
    getNum(n);
    try {
        ptr->copying(n);
        //    *ptr *= n;
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

// 7.
void inversionBinarySignal(BS::BinarySignal *ptr) {
    ptr->inverting();
    //    ~*ptr;
}

// 8.
void insertBinarySignal(BS::BinarySignal *ptr) {
    int prd;
    BS::BinarySignal tmp;
    std::cin >> tmp;
    std::cout << "Enter the period: ->";
    getPositiveNum(prd);
    try {
        ptr->insert(prd, tmp);
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

// 9.
void removeBinarySignal(BS::BinarySignal *ptr) {
    int start, prd;
    std::cout << "Enter the start: ->";
    getPositiveNum(start);
    std::cout << "Enter the period: ->";
    getPositiveNum(prd);
    try {
        ptr->remove(start, prd);
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

// 10.
void addBinarySignal(BS::BinarySignal *ptr) {
    BS::BinarySignal tmp;
    std::cin >> tmp;
    try {
        ptr->addition(tmp);
        //    *ptr += tmp;
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

int getPositiveNum(int &a) {
    const char *pr = "";
    do {
        std::cout << pr << std::endl;
        pr = "You are wrong! Repeat again please!";
        if (getNum(a) < 1)
            return 1;
    } while (a < 1);
}