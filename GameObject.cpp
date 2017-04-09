#include "GameObject.h"

GameObject::GameObject() : btRigidBody(btScalar(0), NULL, NULL, btVector3(0,0,0))
{
  this->halfWidth = 0;
  this->halfHeight = 0;
}

GameObject::GameObject(double halfWidth, double halfHeight, double x, double y, double mass) : btRigidBody(createRigidBody(halfWidth, halfHeight, x, y, mass))
{
   //this->setUserIndex(-1);
   this->halfWidth = halfWidth;
   this->halfHeight = halfHeight;

   this->color.setValue(0, 255, 0);
}

void GameObject::render()
{  
  btVector3 position = this->getPosition();

  const double X = position.getX(), Y = -position.getY() + Allegro::HEIGHT;

  al_draw_rectangle(X - this->halfWidth, Y - this->halfHeight, X + this->halfWidth, Y + this->halfHeight, al_map_rgb(this->color.getX(), this->color.getY(), this->color.getZ()), 0);
}

void GameObject::setSprite(float r, float g, float b)
{
   this->color.setValue(r, g, b);
}

void GameObject::update()
{
}

btRigidBody::btRigidBodyConstructionInfo GameObject::createRigidBody(double halfWidth, double halfHeight, double x, double y, double mass)
{ 
  btBoxShape* shape = new btBoxShape(btVector3(halfWidth, halfHeight, 10));
  
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(x, y, 0));

  this->setWorldTransform(transform);

  btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if(isDynamic)
  {
    shape->calculateLocalInertia(mass, localInertia);
  }

  btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, 0)));
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
  //btRigidBody* body = new btRigidBody(constructionInfo); 

   return constructionInfo;
}

btVector3 GameObject::getPosition()
{
  btTransform trans;
  this->getMotionState()->getWorldTransform(trans);
  
  return trans.getOrigin();
}