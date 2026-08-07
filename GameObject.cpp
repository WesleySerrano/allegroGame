#include "GameObject.h"
#include "Utils.hpp"

GameObject::GameObject()
{
  this->halfWidth = 0;
  this->halfHeight = 0;
}

GameObject::GameObject(double halfWidth, double halfHeight, double x, double y, double inverseMass, b2BodyType rigidBodyType)
{
   this->halfWidth = halfWidth;
   this->halfHeight = halfHeight;
   this->inverseMass = inverseMass;

   this->color = Vec3(0.0f, 255.0f, 0.0f);
   this->active = false;
   this->visible = false;

   createRigidBody(halfWidth, halfHeight, x, y, inverseMass, rigidBodyType);
}

void GameObject::render()
{  
  b2Vec2 position = this->getPosition();

  const double X = position.x, Y = -position.y + Allegro::HEIGHT;

  al_draw_rectangle(X - this->halfWidth, Y - this->halfHeight, X + this->halfWidth, Y + this->halfHeight, al_map_rgb(this->color.getX(), this->color.getY(), this->color.getZ()), 0);}

void GameObject::setSprite(double r, double g, double b)
{
   this->color = Vec3(r, g, b);
}

void GameObject::setSprite(Vec3 color)
{
   this->color = color;
}

void GameObject::update()
{
}

void GameObject::createRigidBody(double halfWidth, double halfHeight, double x, double y, double inverseMass, b2BodyType rigidBodyType)
{ 
  b2Vec2 position;
  position.x = x;
  position.y = y;
  this->rigidBodyDefinition = new b2BodyDef(b2DefaultBodyDef());
  this->rigidBodyDefinition->position = position;
  this->rigidBodyDefinition->type = rigidBodyType;

  this->halfHeight = halfHeight;

  this->halfWidth = halfWidth;
}

void GameObject::createShape(b2BodyId bodyId, double halfWidth, double halfHeight)
{
  b2Polygon shape = b2MakeBox(halfWidth, halfHeight);

  this->shape = new b2Polygon(shape);

  this->shapeDef = new b2ShapeDef(b2DefaultShapeDef());
  this->shapeDef->density = this->inverseMass;
  this->shapeDef->material.friction = 0.3f;

  b2CreatePolygonShape(bodyId, this->shapeDef, &shape);
}

b2Vec2 GameObject::getPosition()
{
  return b2Body_GetPosition((*this->rigidBody));
}

void GameObject::setPosition(int x, int y)
{
}

b2Vec2* GameObject::getCorners()
{
  b2Vec2 position = this->getPosition();
  double X = position.x, Y = position.y;

  b2Vec2* results = new b2Vec2[4];
  /*
  3 - 2
  |   |
  0 - 1
  */
  results[0] = makeVec2(X - halfWidth, Y - halfHeight);
  results[1] = makeVec2(X + halfWidth, Y - halfHeight);
  results[2] = makeVec2(X + halfWidth, Y + halfHeight); 
  results[3] = makeVec2(X - halfWidth, Y + halfHeight);

  return results;
}

bool GameObject::isActive()
{
  return this->active;
}

void GameObject::setActiveStatus(bool status)
{
  this->active = status;
}

bool GameObject::isVisible()
{
  return this->visible;
}

void GameObject::setVisibleStatus(bool status)
{
  this->visible = status;
}

std::string GameObject::getLabel()
{
  return this->label;
}

void GameObject::setLabel(std::string label)
{
  this->label = label;
}

double GameObject::getHalfWidth()
{
  return this->halfWidth;
}

double GameObject::getHalfHeight()
{
  return this->halfHeight;
}

double GameObject::getInverseMass()
{
  return this->inverseMass;
}

b2BodyDef* GameObject::getRigidBodyDefinition()
{
  return this->rigidBodyDefinition;
}

b2BodyId* GameObject::getRigidBody()
{
  return this->rigidBody;
}

void GameObject::setRigidBody(b2BodyId* body)
{  
  this->rigidBody = body;
}