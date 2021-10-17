#include "binarySignal.h"

int main() {
    char str1[10] = "000111011";
    char str2[5] = "0010";
    //::BinarySignal tmp1(10, str1);
    Prog3A::BinarySignal tmp2(5, str2);

    tmp2.copy(4);

    return 0;
}
