#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "Allegro.h"
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btAlignedObjectArray.h> 

class GameObject : public btRigidBody
{
  public:
    GameObject();
    GameObject(double, double , double, double, double);


    bool isActive();
    btVector3 getPosition();
    double getHalfWidth();
    double getHalfHeight();
    double getMass();    

    void render();

    void setActiveStatus(bool);
    void setPosition(int, int);
    void setSprite(float, float , float);

    void update();
  private:
    btRigidBody::btRigidBodyConstructionInfo createRigidBody(double, double , double, double, double);

    double halfWidth;
    double halfHeight;
    double mass;
    btVector3 color;
    bool active;
};
#endif
