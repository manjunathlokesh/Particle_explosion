#include "graphical_object.h"
namespace Manju
{
graphical_object::graphical_object():m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer(NULL), m_buffer1(NULL) {}

bool graphical_object::init()
{
    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    m_window = SDL_CreateWindow(
                   "Graphical window",                  // window title
                   SDL_WINDOWPOS_UNDEFINED,           // initial x position
                   SDL_WINDOWPOS_UNDEFINED,           // initial y position
                   800,                               // width, in pixels
                   600,                               // height, in pixels
                   SDL_WINDOW_SHOWN                  // flags - see below
               );

    // Check that the window was successfully created
    if (m_window == NULL)
    {
        // In the case that the window could not be made...
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer,SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_STATIC,SCREEN_WIDTH,SCREEN_HEIGHT);

    if(m_renderer == NULL)
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    if(m_texture == NULL)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    m_buffer= new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
    m_buffer1= new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
    memset(m_buffer,0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    memset(m_buffer1,0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    return true;
}
bool graphical_object::ProcessEvent()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}
void graphical_object::update()
{
    SDL_UpdateTexture(m_texture,NULL,m_buffer,SCREEN_WIDTH*sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    SDL_RenderPresent(m_renderer);

}
void graphical_object::setPixel(int x,int y,Uint8 red,Uint8 green,Uint8 blue)
{
    if( x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT )
        return;
    Uint32 color=0;
    color +=red;
    color <<=8;
    color +=green;
    color <<=8;
    color +=blue;
    color <<=8;
    color +=0xFF;
    m_buffer[(y*SCREEN_WIDTH)+ x] = color;
}
bool graphical_object::close()
{
    delete [] m_buffer;
    delete [] m_buffer1;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return true;
}
void graphical_object::blur()
{
    Uint32 *temp=m_buffer;
    m_buffer=m_buffer1;
    m_buffer1=temp;
    for(int y=0; y<SCREEN_HEIGHT; y++)
    {
        for(int x=0; x<SCREEN_WIDTH; x++)
        {

            int redt=0;
            int greent=0;
            int bluet=0;
            for(int row=-1; row<=1; row++)
            {
                for(int col=-1; col<=1; col++)
                {
                    int currentX=x+col;
                    int currentY=y+row;
                    if(currentX >=0 && currentX <SCREEN_WIDTH && currentY >=0 && currentY <SCREEN_HEIGHT)
                    {
                        Uint32 color = m_buffer1[currentY*SCREEN_WIDTH + currentX];
                        Uint8 red= color >>24;
                        Uint8 green= color >>16;
                        Uint8 blue= color >>8;

                        redt+=red;
                        greent+=green;
                        bluet+=blue;

                    }
                }
            }
            Uint8 red= redt/9;
            Uint8 green= greent/9;
            Uint8 blue= bluet/9;
            setPixel(x,y,red,green,blue);
        }

    }

}
graphical_object::~graphical_object()
{
    //dtor
}
}
