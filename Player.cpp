#include "Player.h"


Player::Player() : GameObject()
{
  this->halfWidth = 0;
  this->halfHeight = 0;
  this->movingDirection = 0;
  this->horizontalMaxSpeed = 10;
}

Player::Player(double halfWidth, double halfHeight, double x, double y, double mass) : GameObject(halfWidth, halfHeight, x, y, mass)
{
   this->halfWidth = halfWidth;
   this->halfHeight = halfHeight;
   this->mass = mass;
  this->movingDirection = 0;
  this->horizontalMaxSpeed = 10;

   this->color.setValue(0, 255, 0);
   this->active = false;
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
         this->movingDirection = 0;
       }
    }
}

void Player::moveLeft()
{
    this->movingDirection = -1;
}

void Player::update()
{
  //if(this->movingDirection) this->setLinearVelocity(btVector3(this->movingDirection * this->horizontalMaxSpeed, 0, 0));
}

void Player::moveRight()  
{
  this->movingDirection = 1;
}