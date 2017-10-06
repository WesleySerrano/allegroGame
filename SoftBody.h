#ifndef SOFTBODY_H
#define SOFTBODY_H

#include "GameObject.h"

class SoftBody : public GameObject
{
    public:
        SoftBody();
        SoftBody(int, double, double , double, double, double, btDiscreteDynamicsWorld*, bool fixed = false);
        void render();

    private:
        GameObject** nodes;
        int numberOfNodes;
};

#endif