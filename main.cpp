#include "SDL.h"
#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include "graphical_object.h"
#include "swarm.h"
using namespace std;
using namespace Manju;
int main(int argc, char* argv[])
{
    graphical_object Graphics;
    swarm Swarm;

    if(Graphics.init() == false)
    {
        cout << "initalization failed" << endl;
    }

    while(true)
    {
        int elapsed=SDL_GetTicks();
        Swarm.update(elapsed);
        unsigned char red=(unsigned char)((1+sin(elapsed* 0.0001))*128);
        unsigned char green=(unsigned char)((1+sin(elapsed* 0.0002))*128);
        unsigned char blue=(unsigned char)((1+sin(elapsed* 0.0003))*128);
        const create_particles *const particles=Swarm.getParticles();
        for(int i=0;i<swarm::N_PARTICLE;i++)
        {
            create_particles pparticle= particles[i];
            int x=(pparticle.m_x + 1 ) * graphical_object::SCREEN_WIDTH/2;
            int y=pparticle.m_y * graphical_object::SCREEN_WIDTH/2 + graphical_object::SCREEN_HEIGHT/2;
            Graphics.setPixel(x,y,red,green,blue);
        }

        Graphics.blur();
        Graphics.update();
        if(Graphics.ProcessEvent() == false)
            break;
    }
    Graphics.close();
    return 0;
}
