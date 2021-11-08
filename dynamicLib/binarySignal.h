#ifndef COLLECTION_BINARYSIGNAL_H
#define COLLECTION_BINARYSIGNAL_H

namespace Signal {

    template<class T>
    void getNum(std::istream &in, T &num) {
        while (true) {
            in >> num;
            if (!in.good()) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
    }

    struct Status {
        bool m_level;
        unsigned char m_duration;
    };

    class BinarySignal {
    private:
        static const int BLOCK = 5;
        static const int MAX = 255;
        int m_length;
        int m_size;
        Status *m_array;

        void initialization(int size, int length, const char *string);

    public:
        BinarySignal();

        BinarySignal(bool level);

        BinarySignal(int length, const char *string);

        BinarySignal(const BinarySignal &bs);

        BinarySignal(BinarySignal &&bs) noexcept;

        ~BinarySignal();

        BinarySignal &operator=(const BinarySignal &bs);

        BinarySignal &operator=(BinarySignal &&bs) noexcept;

        friend std::istream &operator>>(std::istream &in, BinarySignal &bs);

        friend std::ostream &operator<<(std::ostream &out, const BinarySignal &bs);
    };
}

#endif //COLLECTION_BINARYSIGNAL_H
