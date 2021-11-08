#include <iostream>
#include "binarySignal.h"

namespace Signal {
    // Empty constructor.
    BinarySignal::BinarySignal() : m_size(0), m_length(0), m_array(nullptr) {
        std::cout << "Empty Constructor: " << this << std::endl;
    }

    // First constructor.
    BinarySignal::BinarySignal(bool level) : m_size(1), m_length(MAX) {
        m_array = new Status[BLOCK];
        m_array[0] = {level, MAX};
        std::cout << "First Constructor: " << this << std::endl;
    }

    // Second Constructor.
    BinarySignal::BinarySignal(int length, const char *string) : m_size(0), m_length(length) {
        int size = 0;
        for (int i = 0; i < m_length;) {
            if (string[i] == '0') {
                size += 1;
                while (string[i] == '0' && i < m_length)
                    i++;
            } else if (string[i] == '1') {
                size += 1;
                while (string[i] == '1' && i < m_length)
                    i++;
            } else
                throw std::invalid_argument("ERROR! Illegal value from binary signal!");
        }
        initialization(size, length, string);
        std::cout << "Second Constructor: " << this << std::endl;
    }

    // Binary signal initialization.
    void BinarySignal::initialization(int size, int length, const char *string) {
        m_size = size;
        m_length = length;
        if (m_size == 0)
            m_array = nullptr;
        else {
            int counter = 0, duration = 0;
            m_array = new Status[BLOCK * ((m_size - 1) * BLOCK + 1)];
            for (int i = 0; i < m_length;) {
                if (string[i] == '0') {
                    m_array[counter].m_level = false;
                    while (string[i] == '0' && i < m_length) {
                        duration += 1;
                        i++;
                        if (duration > MAX)
                            throw std::length_error("ERROR! Illegal size for binary signal, because m_duration > MAX!");
                    }
                    m_array[counter].m_duration = duration;
                } else if (string[i] == '1') {
                    m_array[counter].m_level = true;
                    while (string[i] == '1' && i < m_length) {
                        duration += 1;
                        i++;
                        if (duration > MAX)
                            throw std::length_error("ERROR! Illegal size for binary signal, because m_duration > MAX!");
                    }
                    m_array[counter].m_duration = duration;
                } else
                    throw std::invalid_argument("ERROR! Illegal value from binary signal!");
                duration = 0;
                counter += 1;
            }
        }
    }

    // Copy constructor.
    BinarySignal::BinarySignal(const BinarySignal &bs) : m_length(bs.m_length), m_size(bs.m_size) {
        if (m_size == 0)
            m_array = nullptr;
        else {
            m_array = new Status[BLOCK * ((m_size - 1) * BLOCK + 1)];
            for (int i = 0; i < m_size; i++)
                m_array[i] = bs.m_array[i];
        }
        std::cout << "Copy Constructor: " << this << std::endl;
    }

    // Move constructor.
    BinarySignal::BinarySignal(BinarySignal &&bs) noexcept: m_length(bs.m_length), m_size(bs.m_size),
                                                            m_array(bs.m_array) {
        bs.m_length = 0;
        bs.m_size = 0;
        bs.m_array = nullptr;
        std::cout << "Move Constructor: " << this << std::endl;
    }

    // Destructor.
    BinarySignal::~BinarySignal() {
        m_length = 0;
        m_size = 0;
        delete[] m_array;
        std::cout << "Destructor: " << this << std::endl;
    }

    // Copy assignment operator.
    BinarySignal &BinarySignal::operator=(const BinarySignal &bs) {
        if (this != &bs) {
            delete[] m_array;
            m_length = bs.m_length;
            m_size = bs.m_size;
            if (m_size == 0)
                m_array = nullptr;
            else {
                m_array = new Status[BLOCK * ((m_size - 1) * BLOCK + 1)];
                for (int i = 0; i < m_size; i++)
                    m_array[i] = bs.m_array[i];
            }
        }
        std::cout << "Copy Assignment Operator: " << this << " = " << &bs << std::endl;
        return *this;
    }

    // Move assignment operator.
    BinarySignal &BinarySignal::operator=(BinarySignal &&bs) noexcept {
        if (this != &bs) {
            delete[] m_array;
            m_length = bs.m_length;
            m_size = bs.m_size;
            m_array = bs.m_array;
            bs.m_length = 0;
            bs.m_size = 0;
            bs.m_array = nullptr;
        }
        std::cout << "Move Assignment Operator: " << this << " = " << &bs << std::endl;
        return *this;
    }

    // Input.
    std::istream &operator>>(std::istream &in, BinarySignal &bs) {
        if (bs.m_size != 0)
            delete[] bs.m_array;
        int length;
        getNum(in, length);
        if (length > 0) {
            int size = 1;
            char string[length + 1];
            getNum(in, string[0]);
            for (int i = 1; i < length; i++) {
                getNum(in, string[i]);
                if (string[i - 1] != string[i])
                    size += 1;
            }
            bs.initialization(size, length, string);
        }
        return in;
    }

    // Output.
    std::ostream &operator<<(std::ostream &out, const BinarySignal &bs) {
        if (bs.m_size == 0)
            out << "Binary Signal is empty!";
        else {
            for (int i = 0; i < bs.m_size; i++)
                for (int j = 0; j < bs.m_array[i].m_duration; j++)
                    out << bs.m_array[i].m_level;
        }
        return out;
    }
}
