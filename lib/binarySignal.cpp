#include <iostream>
#include "binarySignal.h"

namespace BS {
    // Пустой конструктор.
    BinarySignal::BinarySignal() noexcept: m_size(0), m_length(0), m_array{} {

    }

    // Первый конструктор.
    BinarySignal::BinarySignal(bool lvl) noexcept: m_size(SZ), m_length(MAX), m_array{lvl, MAX} {

    }

    // Второй конструктор.
    BinarySignal::BinarySignal(int sz, const bool *sgn) : m_size(0), m_length(sz), m_array{} {
        initialization(sz, sgn);
    }

    //  Инициализация.
    void BinarySignal::initialization(int sz, const bool *sgn) {
        int cnt = 0;
        for (int i = 0; i < sz;) {
            if (m_size > SZ - 1)
                throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
            if (!sgn[i]) {
                m_array[m_size].m_level = false;
                while (!sgn[i] && i < sz) {
                    cnt++;
                    i++;
                    if (cnt > MAX)
                        throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
                }
                m_array[m_size].m_duration = cnt;
            } else {
                m_array[m_size].m_level = true;
                while (sgn[i] && i < sz) {
                    cnt++;
                    i++;
                    if (cnt > MAX)
                        throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
                }
                m_array[m_size].m_duration = cnt;
            }
            m_size++;
            cnt = 0;
        }
    }

    // Ввод.
    std::istream &operator>>(std::istream &in, BinarySignal &bs) {
        int sz;
        getNum(in, sz);
        bool sgn[sz];
        for (int i = 0; i < sz; i++)
            getNum(in, sgn[i]);
        bs.initialization(sz, sgn);
        return in;
    }

    // Вывод.
    std::ostream &operator<<(std::ostream &out, const BinarySignal &bs) noexcept {
        if (!bs.m_size)
            out << "Binary Signal is empty!";
        else {
            for (int i = 0; i < bs.m_size; i++)
                for (int j = 0; j < bs.m_array[i].m_duration; j++)
                    out << bs.m_array[i].m_level;
        }
        return out;
    }

    // Инвертирование.
    BinarySignal &BinarySignal::inverting() noexcept {
        for (int i = 0; i < m_size; i++)
            m_array[i].m_level = !m_array[i].m_level;
        return *this;
    }

    // Дополнение.
    BinarySignal &BinarySignal::addition(const BinarySignal &bs) {
        if (!bs.m_size);
        else if (!m_size)
            *this = bs;
        else {
            if (m_array[m_size - 1].m_level == bs.m_array[0].m_level) {
                if (m_size + bs.m_size - 1 > SZ)
                    throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
                if (m_array[m_size - 1].m_duration + bs.m_array[0].m_duration > MAX)
                    throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
                m_array[m_size - 1].m_duration += bs.m_array[0].m_duration;
                for (int i = 0; i < bs.m_size - 1; i++)
                    m_array[i + m_size] = bs.m_array[i + 1];
                m_size += bs.m_size - 1;
            } else {
                if (m_size + bs.m_size > SZ)
                    throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
                for (int i = 0; i < bs.m_size; i++)
                    m_array[i + m_size] = bs.m_array[i];
                m_size += bs.m_size;
            }
            m_length += bs.m_length;
        }
        return *this;
    }

    // Копирование.
    BinarySignal &BinarySignal::copying(int n) {
        BinarySignal bs = *this;
        for (int i = 1; i < n; i++)
            this->addition(bs);
        return *this;
    }

    // Отладка.
    void BinarySignal::debugging() const {
        for (int i = 0; i < m_size; i++)
            std::cout << "#" << i << ": " << m_array[i].m_level << " -> " << static_cast<int>(m_array[i].m_duration) << std::endl;
    }

    // Вставка.
    BinarySignal &BinarySignal::insert(int start, const BinarySignal &bs) {
        if (start < 0 || start > m_length)
            throw std::invalid_argument("Illegal value for start!");

        if (!bs.m_size); // вставляемый сигнал - пустой
        else if (!m_size) // исходный сигнал - пустой
            *this = bs;
        else if (!start) { // вставляем в начало
            if (m_size + bs.m_size > SZ)
                throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
            for (int i = m_size - 1; i > -1; i--)
                m_array[i + bs.m_size] = m_array[i];
            for (int i = 0; i < bs.m_size; i++)
                m_array[i] = bs.m_array[i];
            m_length += bs.m_length;
        }
        else if (start == m_length) // вставляем в конец
            addition(bs);
        else { // вставяем в середину
            int counter = 0, length = 0;
            for (int i = 0; i < m_size; i++) {
                length += m_array[i].m_duration;
                if (length > start) {
                    counter = i;
                    break;
                }
            }
            if (m_array[counter].m_duration == length - start)  {
                if (m_size + bs.m_size > SZ)
                    throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
                for (int i = m_size - 1; i > counter - 1; i--)
                    m_array[i + bs.m_size] = m_array[i];
                for (int i = 0; i < bs.m_size; i++)
                    m_array[i + counter] = bs.m_array[i];
                m_size += bs.m_size;
            }
            else {
                if (m_size + bs.m_size + 1 > SZ)
                    throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
                m_array[counter].m_duration = m_array[counter].m_duration - length + start;
                for (int i = m_size - 1; i > counter - 1; i--)
                    m_array[i + bs.m_size + 1] = m_array[i];
                m_array[counter + bs.m_size + 1].m_duration = length - start;
                for (int i = 0; i < bs.m_size; i++)
                    m_array[i + counter + 1] = bs.m_array[i];
                m_size += bs.m_size + 1;
            }
            m_length += bs.m_length;
        }
        return *this;
    }

    // Удаление
    void BinarySignal::remove(int start, int duration) {
        if (start < 0 || duration < 0 || start + duration > m_length)
            throw std::invalid_argument("Illegal value for start or duration!");

        if (!duration); // длительность равна нулю, ничего не удаляем
        else if (start + duration == m_length && !start) { // удаляем весь бинарный сигнал
            m_size = 0;
            m_length = 0;
            *m_array = {};
        }
        else if (start + duration == m_length) { // удаление с конца.
            int counter = 0, length = 0;
            for (int i = 0; i < m_size; i++) {
                length += m_array[i].m_duration;
                if (length > start) {
                    counter = i;
                    break;
                }
            }
            if (m_array[counter].m_duration == length - start) {
                for (int i = counter; i < m_size; i++)
                    m_array[i] = {};
                m_size = counter;
                m_length = start;
            }
            else {
                m_array[counter].m_duration = length - start;
                for (int i = counter + 1; i < m_size; i++)
                    m_array[i] = {};
                m_size = counter + 1;
                m_length = start;
            }
        }







        if (start + duration > m_length)
            throw std::length_error("Illegal size for binary signal, because duration > m_lght!");
        int k = 0, q = 0, i;
        BinarySignal begin, end, tmp = *this;
        for (i = 0; i < m_size; i++) {
            k += m_array[i].m_duration;
            if (k > start - 1)
                break;
        }
        tmp.m_size = i + 1;
        tmp.m_length = start;
        tmp.m_array[i].m_duration -= k - start;
        begin = tmp;
        std::cout << begin;
        for (i = 0; i < m_size; i++) {
            q += m_array[i].m_duration;
            if (q > start + duration - 1)
                break;
        }
        int s = i;
        if (q == start + duration) {
            end.m_size = m_size - s - 1;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + tmp.m_size];
        } else {
            end.m_size = m_size - i;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + s];
            end.m_array[0].m_duration = q - start - duration;
        }
        end.m_length = m_length - begin.m_length - duration;
        begin.addition(end);
        *this = begin;
    }



//        int sz;
//        getNum(in, sz);
//        char sq[sz + 1];
//        for (int i = 0; i < sz; i++)
//            getNum(in, sq[i]);
//        BS::BinarySignal tmp(sz + 1, sq);
//        bs = tmp;

    void BinarySignal::operator+=(const BinarySignal &ptr) {
        addition(ptr);
    }

    void BinarySignal::operator*=(int n) {
        copying(n);
    }

    BinarySignal &BinarySignal::operator~() {
        inverting();
    }

    int BinarySignal::getSZ() {
        return SZ;
    }

    int BinarySignal::getM_CNT() const {
        return m_size;
    }

    int BinarySignal::getM_LGHT() const {
        return m_length;
    }
}


/*    Дополнение сигнала другим сигналом с помощью строки */
//    void BinarySignal::addition(const BinarySignal &ptr) {
//        int sz = MAX * (m_size + ptr.m_size), k = 0;
//        char str[sz];
//
//        for (int i = 0; i < m_size; i++) {
//            if (m_array[i].m_level)
//                for (int j = 0; j < m_array[i].m_duration; j++)
//                    str[j + k] = '1';
//            else
//                for (int j = 0; j < m_array[i].m_duration; j++)
//                    str[j + k] = '0';
//            k += m_array[i].m_duration;
//        }
//        for (int i = 0; i < ptr.m_size; i++) {
//            if (ptr.m_array[i].m_level)
//                for (int j = 0; j < ptr.m_array[i].m_duration; j++)
//                    str[j + k] = '1';
//            else
//                for (int j = 0; j < ptr.m_array[i].m_duration; j++)
//                    str[j + k] = '0';
//            k += ptr.m_array[i].m_duration;
//        }
//        BinarySignal tmp(k + 1, str);
//        *this = tmp;
//    }


/*    Копирование двоичного сигнала (усложнённое) */
//        if (m_size < 2) {
//            if (n * m_size > SZ)
//                throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
//            m_array[0].m_duration *= n;
//        } else if (m_array[0].m_level == m_array[m_size - 1].m_level) {
//            if (m_size + (m_size - 1) * (n - 1)  > SZ)
//                throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
//            if (m_array[0].m_duration + m_array[m_size - 1].m_duration > MAX)
//                throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
//            BinarySignal tmp = *this;
//            for (int i = 0; i < n - 1; i++)
//                this->addition(tmp);
//        } else {
//            for (int i = 1; i < n; i++)
//                for (int j = 0; j < m_size; j++)
//                    m_array[j + m_size * i] = m_array[j];
//            m_size *= n;
//        }

/*    Копирование двоичного сигнала (очень простое) */
//            if (n * m_size > SZ)
//            throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
//        for (int i = 1; i < n; i++)
//            for (int j = 0; j < m_size; j++)
//                m_array[j + m_size * i] = m_array[j];
//        m_size *= n;

/*  Простая вставка */
//        if (prd > m_size)
//            throw std::length_error("Illegal size for binary signal, because prd > m_size!");
//        if (m_size + ptr.m_size > SZ)
//            throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
//        int j = 0;
//        for (int i = m_size - 1; i > prd - 1; i--, j++)
//            m_array[i + ptr.m_size] = m_array[i];
//        for (int i = 0; i < ptr.m_size; i++)
//            m_array[i + prd] = ptr.m_array[i];
//        m_size += ptr.m_size;


/* Раньше это стояло во втором конструкторе */
//        int cnt = 0;
//        for (int i = 0; i < sz;) {
//            if (m_size > SZ - 1)
//                throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
//            if (!sgn[i]) {
//                m_array[m_size].m_level = false;
//                while (!sgn[i] && i < sz) {
//                    cnt++;
//                    i++;
//                    if (cnt > MAX)
//                        throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
//                }
//                m_array[m_size].m_duration = cnt;
//            } else {
//                m_array[m_size].m_level = true;
//                while (sgn[i] && i < sz) {
//                    cnt++;
//                    i++;
//                    if (cnt > MAX)
//                        throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
//                }
//                m_array[m_size].m_duration = cnt;
//            }
//            m_size++;
//            cnt = 0;
//        }


/* оч странная вставка */
//if (!bs.m_size);
//else if (!start) {
//if (!m_size)
//*this = bs;
//else
//if (m_array[0].m_level == bs.m_array[bs.m_size - 1].m_level) {
//if (m_size + bs.m_size - 1 > SZ)
//throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
//if (m_array[0].m_duration + bs.m_array[bs.m_size - 1].m_duration > MAX)
//throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
//
//}
//else {
//
//}
//} else if (start == m_length)
//addition(bs);
//else {
//
//}