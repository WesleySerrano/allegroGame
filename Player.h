#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
    public:
        Player();
        Player(double, double , double, double, double);

        void processEvent(ALLEGRO_EVENT&);
    private:
        void moveLeft();
        void moveRight();
};

#endif