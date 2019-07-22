#ifndef _Renderer_h_
#define _Renderer_h_

#include <SDL2/SDL.h>
#include <string>
#include <set>

namespace DSAAE {

class Node;

class Renderer {
    private:
        SDL_Renderer *m_renderer = nullptr;
        SDL_Window *m_window     = nullptr;
        int m_window_width, m_window_height;
        std::string m_title;
        std::set<Node*> m_entities;

    public:
        Renderer(int width, int height, std::string &title);
        ~Renderer();
        void redraw() const;
        void erase(Node *entity);
        void insert(Node *entity);
};

class Node {
    friend class Renderer;
    private:
        int m_value, m_size;
        Renderer *m_renderer;
        SDL_Rect m_object;

    public:
        Node(int value, int x, int y, int size, Renderer *rend);
        ~Node();
};


}

#endif
