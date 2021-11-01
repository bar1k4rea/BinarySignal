#ifndef PROG3A_MENU_H
#define PROG3A_MENU_H

#include <iostream>
#include "../lib/binarySignal.h"

template <class T>
int getNum(T &a)
{
    while (true) {
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR! Invalid data! Try again please: ->";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
    }
}

int getPositiveNum(int &a);

void emptyConstructor(BS::BinarySignal *ptr);
void firstConstructor(BS::BinarySignal *ptr);
void secondConstructor(BS::BinarySignal *ptr);
void inputSequence(BS::BinarySignal *ptr);
void outputSequence(BS::BinarySignal ptr);
void copyBinarySignal(BS::BinarySignal *ptr);
void inversionBinarySignal(BS::BinarySignal *ptr);
void insertBinarySignal(BS::BinarySignal *ptr);
void removeBinarySignal(BS::BinarySignal *ptr);
void addBinarySignal(BS::BinarySignal *ptr);

#endif //PROG3A_MENU_H
