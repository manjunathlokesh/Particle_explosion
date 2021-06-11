#ifndef GRAPHICAL_OBJECT_H
#define GRAPHICAL_OBJECT_H
#include "SDL.h"
#include <cstring>
namespace Manju
{
class graphical_object
{
public:
    const static int SCREEN_WIDTH=800;
    const static int SCREEN_HEIGHT=600;
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer;
    Uint32 *m_buffer1;
public:
    graphical_object();
    bool init();
    void update();
    void setPixel(int x,int y,Uint8 red,Uint8 green,Uint8 blue);
    bool ProcessEvent();
    void blur();
    bool close();
    virtual ~graphical_object();
};
}
#endif // GRAPHICAL_OBJECT_H
