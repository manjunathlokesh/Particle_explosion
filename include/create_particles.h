#ifndef CREATE_PARTICLES_H
#define CREATE_PARTICLES_H

namespace Manju
{
class create_particles
{
public:
    double m_x;
    double m_y;
    double m_speed;
    double m_direction;
public:
    void update(int intervel);
    create_particles();
    virtual ~create_particles();
private:
    void init();

};
}
#endif // CREATE PARTICLES_H
