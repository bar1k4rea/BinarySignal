#ifndef PROG3A_BINARYSIGNAL_H
#define PROG3A_BINARYSIGNAL_H



namespace BS {
    struct Status {
        bool m_level;
        unsigned char m_duration;
    };

    class BinarySignal {
    private:
        static const int SZ = 10;
        static const int MAX = 255;
        int m_length;
        int m_number;
        Status m_array[SZ];

        void initialization(int sz, const bool *sgn);

    public:
        BinarySignal() noexcept;

        explicit BinarySignal(bool lvl) noexcept;

        BinarySignal(int sz, const bool *sgn);

        friend std::istream &operator>>(std::istream &in, BinarySignal &bs);

        friend std::ostream &operator<<(std::ostream &out, const BinarySignal &bs) noexcept;

        BinarySignal &inverting() noexcept;

        BinarySignal &addition(const BinarySignal &bs);

        BinarySignal &copying(int n);

        BinarySignal &insert(int start, const BinarySignal &bs);

        void remove(int start, int prd);

        void operator+=(const BinarySignal &ptr);

        void operator*=(int n);

        BinarySignal &operator~();

        void debugging() const;

        static int getSZ();

        int getM_CNT() const;

        int getM_LGHT() const;
    };

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
}

#endif //PROG3A_BINARYSIGNAL_H
