#include "swarm.h"
namespace Manju
{
swarm::swarm():lasttime(0)
{
    m_particles= new create_particles[N_PARTICLE];
    //ctor
}

swarm::~swarm()
{
    delete []m_particles;
    //dtor
}
void swarm::update(int elapsed)
{
    int intervel=elapsed - lasttime;
    for(int i=0;i<swarm::N_PARTICLE;i++)
    {
        m_particles[i].update(intervel);
    }
    lasttime=elapsed;
}

}
