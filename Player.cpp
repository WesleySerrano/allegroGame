#include "Player.h"
#include "Utils.hpp"


Player::Player() : GameObject()
{
  this->halfWidth = 0;
  this->halfHeight = 0;
}

Player::Player(double halfWidth, double halfHeight, double x, double y, double mass) : GameObject(halfWidth, halfHeight, x, y, mass, b2_dynamicBody)
{
  this->speed = makeVec2(0.0f, 0.0f);
   this->halfWidth = halfWidth;
   this->halfHeight = halfHeight;

   this->color = Vec3(0, 255, 0);
   this->active = false;
   this->label = "Player";
}

void Player::processEvent(ALLEGRO_EVENT& event)
{ 
    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
       if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
       {
         this->moveLeft();  
       }
       else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
       {
         this->moveRight();
       }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
       if(event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
       { 
         this->speed = makeVec2(0, 0);
       }
    }
}

void Player::moveLeft()
{
    this->speed = makeVec2(-50, 0);
}

void Player::moveRight()  
{
    this->speed = makeVec2(50, 0);
}

void Player::update() {
  GameObject::update();
  if(this->speed.x != 0){}
  b2Vec2 position = this->getPosition();
  position.x += this->speed.x;
  position.y += this->speed.y;
  this->getRigidBodyDefinition()->position = position;
}