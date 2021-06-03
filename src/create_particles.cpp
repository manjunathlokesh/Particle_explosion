#include "create_particles.h"
#include<math.h>
#include <stdlib.h>
namespace Manju
{
create_particles::create_particles(): m_x(0),m_y(0)
{
    init();
    //ctor
}

create_particles::~create_particles()
{
    //dtor
}
void create_particles::init()
{
    m_x=0;
    m_y=0;
    m_direction= (2 * M_PI * rand())/RAND_MAX;
    m_speed = (0.04 * rand())/RAND_MAX;
    m_speed *= m_speed;
}
void create_particles::update(int intervel)
{
    m_direction+=intervel*0.0003;
    double xspeed= m_speed * cos(m_direction);
    double yspeed= m_speed * sin(m_direction);
    m_x+=xspeed * intervel;
    m_y+=yspeed * intervel;
    if( m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
       init();
    if(rand() < RAND_MAX/100)
    {
        init();
    }


}
}
