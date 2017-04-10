#include "Player.h"


Player::Player() : GameObject()
{
  this->halfWidth = 0;
  this->halfHeight = 0;
}

Player::Player(double halfWidth, double halfHeight, double x, double y, double mass) : GameObject(halfWidth, halfHeight, x, y, mass)
{
   this->halfWidth = halfWidth;
   this->halfHeight = halfHeight;
   this->mass = mass;

   this->color.setValue(0, 255, 0);
   this->active = false;
}

void Player::processEvent(ALLEGRO_EVENT& event)
{
    if(event.type==ALLEGRO_EVENT_KEY_DOWN)
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
}

void Player::moveLeft()
{
    std::cout << "To the left\n";
}

void Player::moveRight()
{
    std::cout << "To the right\n";
}