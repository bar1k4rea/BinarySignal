#include <iostream>
#include "lib/binarySignal.h"
#include "menu\menu.h"


int main() {
    bool num1[]{0, 0, 0};
    BS::BinarySignal bs1(3, num1);
    std::cout << "BS1: -> " << bs1 << std::endl;
    bs1.debugging();

    bool num4[]{0, 0, 1, 0, 1, 1};
    BS::BinarySignal bs4(6, num4);
    std::cout << std::endl << "BS4: -> " << bs4 << std::endl;
    bs4.debugging();

//    bs4.insert(3, bs1);
//    bool num1[]{1, 1, 1, 0, 0, 0, 1, 0, 1, 1};
//    BS::BinarySignal bs1(10, num1);
//    BS::BinarySignal bs2;
//    int a;
//    std::cin >> bs1 >> bs2 >> a;
//    std::cout << bs1 << std::endl;
//    bs1.debugging();

    bs4.insert(2, bs1);
    std::cout << bs4 << std::endl;
    bs4.debugging();
    return 0;
}

//    int command;
//    BS::BinarySignal tmp;
//
//    std::cout << "0. Exit" << std::endl;
//    std::cout << "1. Empty constructor" << std::endl;
//    std::cout << "2. Creating a binary signal with a single element" << std::endl;
//    std::cout << "3. Creating a binary signal with multiple elements" << std::endl;
//    std::cout << "4. Input a binary signal" << std::endl;
//    std::cout << "5. Output a binary signal" << std::endl;
//    std::cout << "6. Combining two binary signal" << std::endl;
//    std::cout << "7. Inversion a binary signal" << std::endl;
//    std::cout << "8. Insert binary signal" << std::endl;
//    std::cout << "9. Remove binary signal" << std::endl;
//    std::cout << "10. Add binary signal" << std::endl;
//    do {
//        std::cout << "Enter the command: ->";
//        getNum(command);
//        switch(command)
//        {
//            case 0:
//                std::cout << "EXIT!" << std::endl;
//                break;
//            case 1:
//                emptyConstructor(&tmp);
//                break;
//            case 2:
//                firstConstructor(&tmp);
//                break;
//            case 3:
//                secondConstructor(&tmp);
//                break;
//            case 4:
//                inputSequence(&tmp);
//                break;
//            case 5:
//                outputSequence(tmp);
//                break;
//            case 6:
//                copyBinarySignal(&tmp);;
//                break;
//            case 7:
//                inversionBinarySignal(&tmp);
//                break;
//            case 8:
//                insertBinarySignal(&tmp);
//                break;
//            case 9:
//                removeBinarySignal(&tmp);
//                break;
//            case 10:
//                addBinarySignal(&tmp);
//                break;
//            case 11:
//                tmp.debugging();
//                break;
//            default:
//                std::cout << "ERROR! There is no such command." << std::endl;
//        }
//    } while (command != 0);