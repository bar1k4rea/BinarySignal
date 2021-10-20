#include "binarySignal.h"

int main()
{
    char str1[10] = "000111001";
    char str2[4] = "010";
    int sz;
    Prog3A::BinarySignal tmp1(10, str1);
    Prog3A::BinarySignal tmp2(4, str2);
    Prog3A::BinarySignal tmp3(3);

    std::cout << tmp1;
    tmp1.remove(4, 3);
    std::cout << tmp1;

//    std::cin >> sz;
//    char sq[sz];
//    std::cin >> sq[sz];
//    for (int i = 0; i < sz; i++)
//        std::cout << sq[i];

//    std::cin >> tmp3;
//    std::cout << tmp3;

//    tmp1.printDebug();
//    std::cout << "CNT: -> " << tmp1.getM_CNT() << std::endl  << "LGTH: -> "<< tmp1.getM_LGHT()<< std::endl;
//    tmp2.printDebug();
//    std::cout << "CNT: -> " << tmp2.getM_CNT() << std::endl  << "LGTH: -> "<< tmp2.getM_LGHT()<< std::endl;
//
//    tmp1.insert(0, tmp2);
//    tmp1.printDebug();
//    std::cout << tmp1;


//    tmp1.printDebug();
//    std::cout << "CNT: -> " << tmp1.getM_CNT() << std::endl << std::endl;
//    tmp2.printDebug();
//    std::cout << "CNT: -> " << tmp2.getM_CNT() << std::endl  << "LGTH: -> "<< tmp2.getM_LGHT()<< std::endl;
//
//    tmp2.copy(10);
//
//    tmp2.printDebug();
//    std::cout << "CNT: -> " << tmp2.getM_CNT() << std::endl  << "LGTH: -> "<< tmp2.getM_LGHT()<< std::endl;
//    tmp1.add(tmp2);
//    tmp1.printDebug();
//    std::cout << "CNT: -> " << tmp1.getM_CNT() << std::endl << std::endl;

    return 0;
}
