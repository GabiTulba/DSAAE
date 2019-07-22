#ifndef _Renderer_h_
#define _Renderer_h_

#include <SDL2/SDL.h>
#include <string>
#include <set>

namespace DSAAE {

class INode;

class Renderer {
    private:
        SDL_Renderer *m_renderer = nullptr;
        SDL_Window *m_window     = nullptr;
        int m_window_width, m_window_height;
        std::string m_title;
        std::set<INode*> m_entities;

    public:
        Renderer(int width, int height, std::string &title);
        ~Renderer();
        void redraw() const;
        void erase(INode *entity);
        void insert(INode *entity);
};

class INode {
    friend class Renderer;
    private:
        int m_value, m_size;
        Renderer *m_renderer;

    public:
        INode(int value, int x, int y, int size, Renderer *rend);
        ~INode();
        virtual void draw() = 0;
        virtual void destroy() = 0;
};


}

#endif
