#ifndef SPAWNER_H
#define SPAWNER_H

#include "GameObject.h"

class Spawner
{
  public:
    Spawner();
    Spawner(int, int, int, int);

    void setTemplateParameters(GameObject*);
    void setTemplateSprite(float, float, float);
    void spawn(btDiscreteDynamicsWorld*);
  private:
    GameObject** objects;
    int NUMBER_OF_OBJECTS;
    int activeObjects;

    int width;
    int* position;
    
    double templateHalfWidth;
    double templateHalfHeight;
    double templateMass;

    btVector3 color;
};
#endif