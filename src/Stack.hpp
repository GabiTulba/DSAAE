#ifndef _Stack_h
#define _Stack_h

namespace DSAAE {

template <class T>
class Stack {
    private:
        int m_size;

    public:
        Stack();
        ~Stack();
        void push(T &elem);
        void pop();
        T top() const;
};

}

#endif
