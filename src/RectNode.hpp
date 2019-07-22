#ifndef _RectNode_h
#define _RectNode_h

#include "Base.hpp"

namespace DSAAE {

class RectNode: INode {
    private:
        SDL_Rect m_object;
    public:
        RectNode(int value, int x, int y, int size, Renderer *rend);
        ~RectNode();
        void draw();
        void destroy();
};

}

#endif
