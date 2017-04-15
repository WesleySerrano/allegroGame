#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
    public:
        Player();
        Player(double, double , double, double, double);

        void processEvent(ALLEGRO_EVENT&);
        void update();
    private:
        void moveLeft();
        void moveRight();

        int movingDirection;
        double horizontalMaxSpeed;
};

#endif