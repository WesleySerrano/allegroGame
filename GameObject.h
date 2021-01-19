#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "Allegro.h"

class GameObject
{
  public:
    GameObject();
    GameObject(double, double , double, double, double, b2BodyType);

    bool isActive();
    bool isVisible();
    b2Vec2 getPosition();
    b2Vec2* getCorners();
    b2Body* getRigidBody();
    b2BodyDef* getRigidBodyDefinition();
    double getHalfWidth();
    double getHalfHeight();
    double getInverseMass();    

    void render();

    void setActiveStatus(bool);
    void setPosition(int, int);
    void setSprite(b2Vec3);
    void setSprite(float, float , float);
    void setVisibleStatus(bool);
    void setRigidBody(b2Body*);

    void update();
  protected:
    b2BodyDef* createRigidBody(double, double , double, double, double, b2BodyType);
    b2PolygonShape* createShape(double, double);

    double halfWidth;
    double halfHeight;
    double inverseMass;
    b2Vec3 color;
    bool active;
    bool visible;

    b2BodyDef *rigidBodyDefinition;
    b2PolygonShape* shape;
    b2Body *rigidBody;
};
#endif
