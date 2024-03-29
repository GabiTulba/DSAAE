#ifndef _StackAnimator_h_
#define _StackAnimator_h_

#include "RectNode.hpp"
#include "Stack.hpp"

namespace DSAAE {

class StackAnimator {
    private:
        Stack<RectNode*> m_stack; 

    public:
        StackAnimator();
        ~StackAnimator();
        void push(int m_elem);
        void pop();
        int top() const;
};

}

#endif
