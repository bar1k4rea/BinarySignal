#include "menu.h"


int main()
{
    int command;
    Prog3A::BinarySignal tmp;

    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Empty constructor" << std::endl;
    std::cout << "2. Creating a binary signal with a single element" << std::endl;
    std::cout << "3. Creating a binary signal with multiple elements" << std::endl;
    std::cout << "4. Input a binary signal" << std::endl;
    std::cout << "5. Output a binary signal" << std::endl;
    std::cout << "6. Combining two binary signal" << std::endl;
    std::cout << "7. Inversion a binary signal" << std::endl;
    std::cout << "8. Insert binary signal" << std::endl;
    std::cout << "9. Remove binary signal" << std::endl;
    std::cout << "10. Add binary signal" << std::endl;
    do {
        std::cout << "Enter the command: ->";
        getNum(command);
        switch(command)
        {
            case 0:
                std::cout << "EXIT!" << std::endl;
                break;
            case 1:
                emptyConstructor(&tmp);
                break;
            case 2:
                firstConstructor(&tmp);
                break;
            case 3:
                secondConstructor(&tmp);
                break;
            case 4:
                inputSequence(&tmp);
                break;
            case 5:
                outputSequence(tmp);
                break;
            case 6:
                copyBinarySignal(&tmp);;
                break;
            case 7:
                inversionBinarySignal(&tmp);
                break;
            case 8:
                insertBinarySignal(&tmp);
                break;
            case 9:
                removeBinarySignal(&tmp);
                break;
            case 10:
                addBinarySignal(&tmp);
                break;
            default:
                std::cout << "ERROR! There is no such command." << std::endl;
        }
    } while (command != 0);

    return 0;
}
