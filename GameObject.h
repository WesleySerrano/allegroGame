#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <string>
#include <box2d/box2d.h>
#include <box2d/math_functions.h>
#include <box2d/base.h>
#include <box2d/types.h>
#include "Allegro.h"
#include "Vec3.hpp"

class GameObject
{
  public:
    GameObject();
    GameObject(double, double , double, double, double, b2BodyType);

    bool isActive();
    bool isVisible();
    b2Vec2 getPosition();
    b2Vec2* getCorners();
    b2BodyId* getRigidBody();
    b2BodyDef* getRigidBodyDefinition();
    b2ShapeDef* getShapeDefinition();
    double getHalfWidth();
    double getHalfHeight();
    double getInverseMass();
    std::string getLabel();    
    void createShape(b2BodyId, double, double);

    void render();

    void setActiveStatus(bool);
    void setPosition(int, int);
    void setSprite(Vec3);
    void setSprite(double, double, double);
    void setVisibleStatus(bool);
    void setRigidBody(b2BodyId*);
    void setLabel(std::string);

    virtual void update();
  protected:
    void createRigidBody(double, double , double, double, double, b2BodyType);

    double halfWidth;
    double halfHeight;
    double inverseMass;
    Vec3 color;
    bool active;
    bool visible;

    std::string label;

    b2BodyDef *rigidBodyDefinition;
    b2Polygon* shape;
    b2BodyId *rigidBody;
    b2ShapeDef *shapeDef;
};
#endif
