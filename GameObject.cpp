#include "GameObject.h"

GameObject::GameObject() : btRigidBody(btScalar(0), NULL, NULL, btVector3(0,0,0))
{
}

GameObject::GameObject(double halfWidth, double halfHeight, double x, double y, double mass) : btRigidBody(createRigidBody(halfWidth, halfHeight, x, y, mass))
{
   this->setUserIndex(-1);
}

void GameObject::render()
{
}

btRigidBody::btRigidBodyConstructionInfo GameObject::createRigidBody(double halfWidth, double halfHeight, double x, double y, double mass)
{
  btBoxShape* shape = new btBoxShape(btVector3(halfWidth, halfHeight, 0));
  
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(x, y, 0));

  btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if(isDynamic)
  {
    shape->calculateLocalInertia(mass, localInertia);
  }

  btDefaultMotionState *motionState = new btDefaultMotionState(transform);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
  btRigidBody* body = new btRigidBody(constructionInfo); 

   return constructionInfo;
}

btVector3 GameObject::getPosition()
{
  btTransform trans;
  this->getMotionState()->getWorldTransform(trans);
  
  return trans.getOrigin();
}