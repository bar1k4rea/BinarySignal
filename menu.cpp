#include "menu.h"

// 1. Пустой конструктор
void emptyConstructor(Prog3A::BinarySignal *ptr) {
    Prog3A::BinarySignal tmp;
    *ptr = tmp;
}

// 2. Первый констурктор
void firstConstructor(Prog3A::BinarySignal *ptr) {
    bool el;
    std::cout << "Enter element of the binary signal: ->";
    getNum(el);
    Prog3A::BinarySignal tmp(el);
    *ptr = tmp;
}

// 3.
void secondConstructor(Prog3A::BinarySignal *ptr) {
    int sz;
    std::cout << "Enter the number of elements in the binary signal: ->";
    getPositiveNum(sz);
    char sq[sz + 1];
    for (int i = 0; i < sz; i++)
        std::cin >> sq[i];
    try {
        Prog3A::BinarySignal tmp(sz + 1, sq);
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
void inputSequence(Prog3A::BinarySignal *ptr)
{
    std::cin >> *ptr;
}

// 5.
void outputSequence(Prog3A::BinarySignal ptr) {
    std::cout << ptr;
}

// 6.
void copyBinarySignal(Prog3A::BinarySignal *ptr) {
    int n;
    std::cout << "Enter n: ->";
    getNum(n);
    try {
        ptr->copy(n);
        //    *ptr *= n;
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

// 7.
void inversionBinarySignal(Prog3A::BinarySignal *ptr) {
    ptr->inversion();
    //    ~*ptr;
}

// 8.
void insertBinarySignal(Prog3A::BinarySignal *ptr) {
    int prd;
    Prog3A::BinarySignal tmp;
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
void removeBinarySignal(Prog3A::BinarySignal *ptr) {
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
void addBinarySignal(Prog3A::BinarySignal *ptr) {
    Prog3A::BinarySignal tmp;
    std::cin >> tmp;
    try {
        ptr->add(tmp);
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