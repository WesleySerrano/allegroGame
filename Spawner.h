#ifndef SPAWNER_H
#define SPAWNER_H

#include "GameObject.h"
#include <ctime>

class Spawner
{
  public:
    Spawner();
    Spawner(int, int, int, int, int , double);

    void setTemplateParameters(GameObject*);
    void setTemplateSprite(float, float, float);
    void spawn(btDiscreteDynamicsWorld*);
  private:
    GameObject** objects;
    int NUMBER_OF_OBJECTS;
    int objectsPerRound;
    int activeObjects;

    int width;
    int* position;
    
    double timeInterval;
    time_t timeElapsed;
    double templateHalfWidth;
    double templateHalfHeight;
    double templateMass;

    btVector3 color;
};
#endif