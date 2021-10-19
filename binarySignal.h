#ifndef PROG3A_BINARYSIGNAL_H
#define PROG3A_BINARYSIGNAL_H

#include <iostream>
#include <stdexcept>

namespace Prog3A
{
    struct Status
    {
        bool m_lvl;
        unsigned char m_val;
    };

    class BinarySignal
    {
    private:
        static const int SZ = 100;
        static const int MAX = 255;
        int m_lgth;
        int m_cnt;
        Status sq[SZ];
    public:
        BinarySignal();
        explicit BinarySignal(bool lvl);
        BinarySignal(int sz, const char* str);

        void inversion();
        void add(const BinarySignal &ptr);
        void insert(int prd, const BinarySignal &ptr);
        void copy(int n);
        void remove(int prd);

        friend void operator>>(std::istream &in, BinarySignal &ptr);
        friend void operator<<(std::ostream &out, const BinarySignal &ptr);

        void printDebug() const;
        static int getSZ();
        int getM_CNT() const;
        int getM_LGHT() const;
    };

}



#endif //PROG3A_BINARYSIGNAL_H
