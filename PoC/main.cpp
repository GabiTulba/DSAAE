#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <set>


//Renderer singleton to manage talking to the SDL library

class Renderer;

class Node
{
    private:
        int value, size;
        Renderer *renderer;
        SDL_Rect object;

        Node(int v, int x, int y, int s, Renderer *rend)
        {
            value = v;
            object.x = x;
            object.y = y;
            object.w = object.h = 0;
            size = s;
            renderer = rend;

            renderer->insert(this);

            for(int frame = 1; frame <= 10; frame++)
            {
                object.w = object.h = frame * size / 10;
                renderer->redraw();
            }
        }

        ~Node()
        {
            for(int frame = 10; frame > 0; frame--)
            {
                object.w = object.h = frame * size / 10;
                renderer->redraw();
            }
            renderer->erase(this);
            delete object;
            renderer = NULL;
        }

    public:
        bool operator < (const Node &rhs) const
        {
            return value < rhs.value;
        }
};

class Renderer
{
    private:
        SDL_Renderer *renderer = NULL;
        SDL_Window *window = NULL;
        int WINDOW_WIDTH, WINDOW_HEIGHT;
        char *TITLE;
    
        std::set<Node *> entities;

        Renderer(int width, int height, char *title)
        {
            WINDOW_WIDTH = width;
            WINDOW_HEIGHT = height;
            TITLE = title;

            if(SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                printf("Error when initializing SDL!\n SDL ERROR: %s\n", SDL_GetError());
                exit(0);
            }
            else
            {
                window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
                if (window == NULL)
                {
                    printf("Error when initializing window!\n SDL ERROR: %s\n", SDL_GetError());
                    exit(0);
                }
                else
                {
                    renderer = SDL_CreateRenderer(window, -1, 0);
                }
            }
        }
        ~Renderer()
        {
            entities.clear();
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
        }
    public:
        void redraw()
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            for(std::set<Node *>::iterator entity = entities.begin(); entity != entities.end(); entity++)
            {
                SDL_RendereDrawRect(renderer, NULL, (*entity)->object);
            }

            SDL_RenderPresent(renderer);
        }

        void erase(Node *entity)
        {
            entities.erase(entity);
            redraw();
        }
        
        void insert(Node *entity)
        {
            entities.insert(entity);
            redraw();
        }
};

//Declaration of Data Structures and Animators
class Stack
{
    private:
        int start_x, start_y;
        int nodeSize;

        std::vector<Node> object;

        Stack(int x, int y, int size)
        {
            start_x = x;
            start_y = y;
            nodeSize = size;
        }

        ~Stack()
        {
            object.clear();
        }

    public:
        void push(int a)
        {
            Node aux(a, start_x, start_y + nodeSize * object.size(), nodeSize);
            object.push_back(aux);
        }
        void pop()
        {
            object.pop_back();
        }
};

int main(int argc, char * argv[])
{
    if(Init_SDL() == false)
    {
        return 0;
    }
    else
    {
        Stack S;

        S.push(4);
        S.push(3);
        S.push(1);
        S.push(2);
        S.pop();
        S.pop();
        S.push(2);
        S.push(1);
        
        Close_SDL();
    }
    return 0;
}
