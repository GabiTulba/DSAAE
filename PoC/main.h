#ifndef  _MAIN_H_ // include guard
#define _MAIN_H 

class Renderer;
class Node;

class Node
{
    private:
        int value, size;
        Renderer *renderer;

    public:
        SDL_Rect object;
	Node(int v, int x, int y, int s, Renderer *rend);
        ~Node();
};

class Renderer
{
    private:
        SDL_Renderer *renderer = NULL;
        SDL_Window *window = NULL;
        int WINDOW_WIDTH, WINDOW_HEIGHT;
        char *TITLE;
    
        std::set<Node *> entities;

    public:
	Renderer(int width, int height, char *title);
        ~Renderer();
        void redraw();
        void erase(Node *entity);
        void insert(Node *entity);
};

#endif
