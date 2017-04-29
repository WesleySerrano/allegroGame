#include "Player.h"


Player::Player() : GameObject()
{
  this->halfWidth = 0;
  this->halfHeight = 0;
}

Player::Player(double halfWidth, double halfHeight, double x, double y, double mass) : GameObject(halfWidth, halfHeight, x, y, mass)
{
  this->speed = btVector3(0, 0, 0);
   /*this->halfWidth = halfWidth;
   this->halfHeight = halfHeight;
   this->mass = mass;

   this->color.setValue(0, 255, 0);
   this->active = false;*/
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
         this->speed = btVector3(0, 0, 0);
       }
    }
}

void Player::moveLeft()
{
    this->speed = btVector3(-10, 0, 0);
}

void Player::update()
{
  if(this->speed.getX() != 0) this->setLinearVelocity(this->speed);
}

void Player::moveRight()  
{
    this->speed = btVector3(10, 0, 0);
    this->setLinearVelocity(this->speed);
}