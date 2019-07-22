#ifndef _StackAnimator_h_
#define _StackAnimator_h_

#include "Base.hpp"
#include "Stack.hpp"

namespace DSAAE {

class StackAnimator {
    private:
        Stack<Node*> m_stack; 

    public:
        StackAnimator();
        ~StackAnimator();
        void push(int m_elem);
        void pop();
        int top() const;
};

}

#endif
