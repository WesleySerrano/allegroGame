#include "GameObject.h"

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

   this->color.Set(0, 255, 0);
   this->active = false;
   this->visible = false;

   createRigidBody(halfWidth, halfHeight, x, y, inverseMass, rigidBodyType);

   createShape(halfWidth, halfHeight);
}

void GameObject::render()
{  
  b2Vec2 position = this->getPosition();

  const double X = position.x, Y = -position.y + Allegro::HEIGHT;

  al_draw_rectangle(X - this->halfWidth, Y - this->halfHeight, X + this->halfWidth, Y + this->halfHeight, al_map_rgb(this->color.x, this->color.y, this->color.z), 0);}

void GameObject::setSprite(float r, float g, float b)
{
   this->color.Set(r, g, b);
}

void GameObject::setSprite(b2Vec3 color)
{
   this->color = color;
}

void GameObject::update()
{
}

b2BodyDef* GameObject::createRigidBody(double halfWidth, double halfHeight, double x, double y, double inverseMass, b2BodyType rigidBodyType)
{ 
  this->rigidBodyDefinition = new b2BodyDef();
  this->rigidBodyDefinition->position.Set(x, y);
  this->rigidBodyDefinition->type = rigidBodyType;

  this->halfHeight = halfHeight;

  this->halfWidth = halfWidth;

  return this->rigidBodyDefinition;
}

b2PolygonShape* GameObject::createShape(double halfWidth, double halfHeight)
{
  this->shape = new b2PolygonShape();
  this->shape->SetAsBox(halfWidth, halfHeight);

  return this->shape;
}

b2Vec2 GameObject::getPosition()
{
  return this->getRigidBody()->GetPosition();
}

void GameObject::setPosition(int x, int y)
{
}

b2Vec2* GameObject::getCorners()
{
  b2Vec2 position = this->getPosition();
  double X = position.x, Y = position.y;

  b2Vec2* results = new b2Vec2[4];
  //std::cout << X << ", " << Y <<  ", " << position.getZ() << ", " << halfWidth << ", " << halfHeight << std::endl;
  /*
  3 - 2
  |   |
  0 - 1
  */
  results[0] = b2Vec2(X - halfWidth, Y - halfHeight);
  results[1] = b2Vec2(X + halfWidth, Y - halfHeight);
  results[2] = b2Vec2(X + halfWidth, Y + halfHeight); 
  results[3] = b2Vec2(X - halfWidth, Y + halfHeight);

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

b2Body* GameObject::getRigidBody()
{
  return this->rigidBody;
}

void GameObject::setRigidBody(b2Body* body)
{  
  b2FixtureDef* objectFixtureDef = new b2FixtureDef();
  objectFixtureDef->density = this->inverseMass;
  objectFixtureDef->shape = this->shape;

  this->rigidBody = body;
  this->rigidBody->CreateFixture(objectFixtureDef);
}