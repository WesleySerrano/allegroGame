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
    btVector3 getPosition();

    void render();

    void setSprite(float, float , float);

    void update();
  private:
    btRigidBody::btRigidBodyConstructionInfo createRigidBody(double, double , double, double, double);

    double halfWidth;
    double halfHeight;
    btVector3 color;
};
