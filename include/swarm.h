#ifndef SWARM_H
#define SWARM_H
#include "create_particles.h"
namespace Manju
{
class swarm
{
public:
    const static int N_PARTICLE= 5000;
    swarm();
    void update(int elapsed);
    virtual ~swarm();
    const create_particles *const getParticles(){ return m_particles;};

private:
    int lasttime;
    create_particles *m_particles;
};
}
#endif // SWARM_H
