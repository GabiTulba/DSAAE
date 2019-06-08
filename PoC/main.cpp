#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <set>
#include "main.h"

#define UNUSED __attribute__((unused))

Node::Node(int v, int x, int y, int s, Renderer *rend)
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
	SDL_Delay(50);
    }
}

Node::~Node()
{
    for(int frame = 10; frame > 0; frame--)
    {
        object.w = object.h = frame * size / 10;
        renderer->redraw();
	SDL_Delay(50);
    }
    renderer->erase(this);
    renderer = NULL;
}

Renderer::Renderer(int width, int height, char *title)
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

Renderer::~Renderer()
{
    entities.clear();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Renderer::redraw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(std::set<Node *>::iterator entity = entities.begin(); entity != entities.end(); entity++)
    {
        SDL_RenderDrawRect(renderer, &((*entity)->object));
    }

    SDL_RenderPresent(renderer);
}

void Renderer::erase(Node *entity)
{
    entities.erase(entity);
    redraw();
}

void Renderer::insert(Node *entity)
{
    entities.insert(entity);
    redraw();
}

//Declaration of Data Structures and Animators
class Stack
{
    private:
        Renderer *renderer;
        int start_x, start_y;
        int nodeSize;

        std::vector<Node *> object;

    public:
        Stack(int x, int y, int size, Renderer *rend)
        {
            start_x = x;
            start_y = y;
            nodeSize = size;
	    renderer = rend;
        }

        ~Stack()
        {
	    while(!object.empty())
	    {
		Node *aux = object[object.size()-1];
		object.pop_back();
		delete aux;
	    }
	    renderer = NULL;
        }

        void push(int a)
        {
            Node *aux = new Node(a, start_x + (nodeSize + 2) * object.size(), start_y , nodeSize, renderer);
            renderer->insert(aux);
            object.push_back(aux);
        }

        void pop()
        {
	    Node *aux = object[object.size() -1];
            object.pop_back();
	    delete aux;
        }
};

int main(UNUSED int argc, UNUSED char * argv[])
{
    char title[] = "Proof of Concept";
    Renderer renderer(640, 480, title);
    Stack S(50, 50, 25, &renderer);
    S.push(4);
    S.push(3);
    S.push(1);
    S.push(2);
    S.pop();
    S.pop();
    S.push(2);
    S.push(1);

    return 0;
}
