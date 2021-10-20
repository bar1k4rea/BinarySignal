#include "binarySignal.h"

namespace Prog3A {
    BinarySignal::BinarySignal() {
        m_cnt = 0;
        m_lgth = 0;
        for (int i = 0; i < SZ; i++) {
            sq[i].m_lvl = false;
            sq[i].m_val = 0;
        }
    }

    BinarySignal::BinarySignal(bool lvl) {
        m_cnt = 1;
        m_lgth = MAX;
        sq[0].m_lvl = lvl;
        sq[0].m_val = MAX;
    }

    BinarySignal::BinarySignal(int sz, const char *str) {
        int cnt = 0;
        m_cnt = 0;
        if (sz > SZ * MAX)
            throw std::length_error("Illegal size for binary signal!");
        for (int i = 0; i < sz - 1;) {
            if (m_cnt > SZ)
                throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
            if (str[i] == '0') {
                sq[m_cnt].m_lvl = false;
                while (str[i] == '0') {
                    cnt++;
                    i++;
                    if (cnt > MAX)
                        throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
                }
                sq[m_cnt].m_val = cnt;
            } else if (str[i] == '1') {
                sq[m_cnt].m_lvl = true;
                while (str[i] == '1') {
                    cnt++;
                    i++;
                    if (cnt > MAX)
                        throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
                }
                sq[m_cnt].m_val = cnt;
            } else
                throw std::invalid_argument("Illegal value from binary signal!");
            m_cnt++;
            cnt = 0;
        }
        m_lgth = sz - 1;
    }

    void BinarySignal::inversion() {
        for (int i = 0; i < m_cnt; i++) {
            if (sq[i].m_lvl)
                sq[i].m_lvl = false;
            else
                sq[i].m_lvl = true;
        }
    }

    void BinarySignal::add(const BinarySignal &ptr) {
        if (sq[m_cnt - 1].m_lvl == ptr.sq[0].m_lvl) {
            if (m_cnt + ptr.m_cnt - 1 > SZ)
                throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
            if (sq[m_cnt - 1].m_val + ptr.sq[0].m_val > MAX)
                throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
            sq[m_cnt - 1].m_val += ptr.sq[0].m_val;
            for (int i = 0; i < ptr.m_cnt - 1; i++)
                sq[i + m_cnt] = ptr.sq[i + 1];
            m_cnt += ptr.m_cnt - 1;
        } else {
            if (m_cnt + ptr.m_cnt > SZ)
                throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
            for (int i = 0; i < ptr.m_cnt; i++)
                sq[i + m_cnt] = ptr.sq[i];
            m_cnt += ptr.m_cnt;
        }
        m_lgth += ptr.m_lgth;
    }

    void BinarySignal::insert(int prd, const BinarySignal &ptr) {
        if (prd > m_lgth)
            throw std::length_error("Illegal size for binary signal, because prd > m_lght!");
        BinarySignal begin, end, tmp = *this;
        if (prd == 0) {
            begin = ptr;
            begin.add(*this);
            *this = begin;
            return;
        }
        if (prd == m_lgth) {
            add(ptr);
            return;
        }
        int k = 0, i;
        for (i = 0; i < m_cnt; i++) {
            k += sq[i].m_val;
            if (k > prd - 1)
                break;
        }
        tmp.m_cnt = i + 1;
        tmp.m_lgth = prd;
        tmp.sq[i].m_val -= k - prd;
        begin = tmp;
        begin.add(ptr);
        if (k == prd) {
            end.m_cnt = m_cnt - tmp.m_cnt;
            for (i = 0; i < end.m_cnt; i++)
                end.sq[i] = sq[i + tmp.m_cnt];
        } else {
            end.m_cnt = m_cnt - tmp.m_cnt + 1;
            for (i = 0; i < end.m_cnt; i++)
                end.sq[i] = sq[i + tmp.m_cnt - 1];
            end.sq[0].m_val = k - prd;
        }
        end.m_lgth = m_lgth - prd;
        begin.add(end);
        *this = begin;
    }

    void BinarySignal::copy(int n) {
        BinarySignal tmp = *this;
        for (int i = 0; i < n - 1; i++)
            this->add(tmp);
    }

    void BinarySignal::remove(int start, int prd) {
        if (start + prd > m_lgth)
            throw std::length_error("Illegal size for binary signal, because prd > m_lght!");
        int k = 0, q = 0, i;
        BinarySignal begin, end, tmp = *this;
        for (i = 0; i < m_cnt; i++) {
            k += sq[i].m_val;
            if (k > start - 1)
                break;
        }
        tmp.m_cnt = i + 1;
        tmp.m_lgth = start;
        tmp.sq[i].m_val -= k - start;
        begin = tmp;
        std::cout << begin;
        for (i = 0; i < m_cnt; i++) {
            q += sq[i].m_val;
            if (q > start + prd - 1)
                break;
        }
        int s = i;
        if (q == start + prd) {
            end.m_cnt = m_cnt - s - 1;
            for (i = 0; i < end.m_cnt; i++)
                end.sq[i] = sq[i + tmp.m_cnt];
        } else {
            end.m_cnt = m_cnt - i;
            for (i = 0; i < end.m_cnt; i++)
                end.sq[i] = sq[i + s];
            end.sq[0].m_val = q - start - prd;
        }
        end.m_lgth = m_lgth - begin.m_lgth - prd;
        begin.add(end);
        *this = begin;
}

    void operator>>(std::istream &in, BinarySignal &ptr) {
        int sz;
        in >> sz;
        char sq[sz + 1];
        for (int i = 0; i < sz; i++)
            in >> sq[i];
        Prog3A::BinarySignal tmp(sz + 1, sq);
        ptr = tmp;
    }

    void operator<<(std::ostream &out, const BinarySignal &ptr) {
        out << "Binary Signal: -> ";
        for (int i = 0; i < ptr.m_cnt; i++) {
            for (int j = 0; j < ptr.sq[i].m_val; j++)
                out << ptr.sq[i].m_lvl;
        }
        out << std::endl;
    }

    void BinarySignal::operator+=(const BinarySignal &ptr) {
        add(ptr);
    }

    void BinarySignal::operator*=(int n) {
        copy(n);
    }

    BinarySignal& BinarySignal::operator~() {
        inversion();
    }

    void BinarySignal::printDebug() const {
        for (int i = 0; i < m_cnt; i++)
            std::cout << "#" << i << ": " << sq[i].m_lvl << " -> " << static_cast<int>(sq[i].m_val) << std::endl;
        std::cout << std::endl;
    }

    int BinarySignal::getSZ() {
        return SZ;
    }

    int BinarySignal::getM_CNT() const {
        return m_cnt;
    }

    int BinarySignal::getM_LGHT() const {
        return m_lgth;
    }
}


/*    Дополнение сигнала другим сигналом с помощью строки */
//    void BinarySignal::add(const BinarySignal &ptr) {
//        int sz = MAX * (m_cnt + ptr.m_cnt), k = 0;
//        char str[sz];
//
//        for (int i = 0; i < m_cnt; i++) {
//            if (sq[i].m_lvl)
//                for (int j = 0; j < sq[i].m_val; j++)
//                    str[j + k] = '1';
//            else
//                for (int j = 0; j < sq[i].m_val; j++)
//                    str[j + k] = '0';
//            k += sq[i].m_val;
//        }
//        for (int i = 0; i < ptr.m_cnt; i++) {
//            if (ptr.sq[i].m_lvl)
//                for (int j = 0; j < ptr.sq[i].m_val; j++)
//                    str[j + k] = '1';
//            else
//                for (int j = 0; j < ptr.sq[i].m_val; j++)
//                    str[j + k] = '0';
//            k += ptr.sq[i].m_val;
//        }
//        BinarySignal tmp(k + 1, str);
//        *this = tmp;
//    }


/*    Копирование двоичного сигнала (усложнённое) */
//        if (m_cnt < 2) {
//            if (n * m_cnt > SZ)
//                throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
//            sq[0].m_val *= n;
//        } else if (sq[0].m_lvl == sq[m_cnt - 1].m_lvl) {
//            if (m_cnt + (m_cnt - 1) * (n - 1)  > SZ)
//                throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
//            if (sq[0].m_val + sq[m_cnt - 1].m_val > MAX)
//                throw std::length_error("Illegal size for binary signal, because m_val > MAX!");
//            BinarySignal tmp = *this;
//            for (int i = 0; i < n - 1; i++)
//                this->add(tmp);
//        } else {
//            for (int i = 1; i < n; i++)
//                for (int j = 0; j < m_cnt; j++)
//                    sq[j + m_cnt * i] = sq[j];
//            m_cnt *= n;
//        }

/*    Копирование двоичного сигнала (очень простое) */
//            if (n * m_cnt > SZ)
//            throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
//        for (int i = 1; i < n; i++)
//            for (int j = 0; j < m_cnt; j++)
//                sq[j + m_cnt * i] = sq[j];
//        m_cnt *= n;

/*  Простая вставка */
//        if (prd > m_cnt)
//            throw std::length_error("Illegal size for binary signal, because prd > m_cnt!");
//        if (m_cnt + ptr.m_cnt > SZ)
//            throw std::length_error("Illegal size for binary signal, because m_cnt > SZ!");
//        int j = 0;
//        for (int i = m_cnt - 1; i > prd - 1; i--, j++)
//            sq[i + ptr.m_cnt] = sq[i];
//        for (int i = 0; i < ptr.m_cnt; i++)
//            sq[i + prd] = ptr.sq[i];
//        m_cnt += ptr.m_cnt;