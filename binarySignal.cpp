#include "binarySignal.h"
#define DEBUG

namespace Prog3A
{
    BinarySignal::BinarySignal()
    {
        m_cnt = 0;
        for (int i = 0; i < SZ; i++)
        {
            sq[i].m_lvl = false;
            sq[i].m_val = 0;
        }
    }

    BinarySignal::BinarySignal(bool lvl)
    {
        m_cnt = 1;
        sq[0].m_lvl = lvl;
        sq[0].m_val = MAX;
    }

    BinarySignal::BinarySignal(int sz, const char *str)
    {
        int cnt = 0;
        m_cnt = 0;
        if (sz > SZ * MAX)
                    throw std::length_error("Illegal size for binary signal!");
#ifdef DEBUG
        std::cout << "Entered string: ";
        for (int i = 0; i < sz; i++)
            std::cout << str[i] << " ";
        std::cout << std::endl;
#endif //DEBUG
        for (int i = 0; i < sz - 1;)
        {
            if (m_cnt > SZ)
                throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
            if (str[i] == '0')
            {
                sq[m_cnt].m_lvl = false;
                while (str[i] == '0')
                {
                    cnt++;
                    i++;
                    if (cnt > MAX)
                        throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
                }
                sq[m_cnt].m_val = cnt;
            }
            else if (str[i] == '1')
            {
                sq[m_cnt].m_lvl = true;
                while (str[i] == '1')
                {
                    cnt++;
                    i++;
                    if (cnt > MAX)
                        throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
                }
                sq[m_cnt].m_val = cnt;
            }
            else
                throw std::invalid_argument("Illegal value from binary signal!");
            m_cnt++;
            cnt = 0;
        }
    }

    void BinarySignal::inversion()
    {
        for (int i = 0; i < m_cnt; i++)
        {
            if (sq[i].m_lvl)
                sq[i].m_lvl = false;
            else
                sq[i].m_lvl = true;
        }
    }

    void BinarySignal::add(const BinarySignal &ptr)
    {
        if (m_cnt + ptr.m_cnt > SZ)
            throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
        for (int i = 0; i < ptr.m_cnt; i++)
            sq[i + m_cnt] = ptr.sq[i];
        m_cnt += ptr.m_cnt;
    }

    void BinarySignal::insert(int prd, const BinarySignal &ptr)
    {
        if (prd > m_cnt)
            throw std::length_error("Illegal size for binary signal, because prd > m_cnt!");
        if (m_cnt + ptr.m_cnt > SZ)
            throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
        int j = 0;
        for (int i = m_cnt - 1; i > prd - 1; i--, j++)
            sq[i + ptr.m_cnt] = sq[i];
        for (int i = 0; i < ptr.m_cnt; i++)
            sq[i + prd] = ptr.sq[i];
        m_cnt += ptr.m_cnt;
    }

    void BinarySignal::copy(int n)
    {
        if (n * m_cnt > SZ)
            throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m_cnt; j++)
                sq[j + m_cnt * i] = sq[j];
        m_cnt *= n;
    }

    void BinarySignal::remove(int prd)
    {
        
    }

    void BinarySignal::printDebug() const
    {
        for (int i = 0; i < m_cnt; i++)
            std::cout << "#" << i << ": " << sq[i].m_lvl << " -> " << static_cast<int>(sq[i].m_val) << std::endl;
        std::cout << std::endl;
    }


    int BinarySignal::getSZ()
    {
        return SZ;
    }
}