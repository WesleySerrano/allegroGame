#include "GameObject.h"
#include <iostream>

using namespace std; 

class GameScene
{
    public:
        GameScene();
        btDiscreteDynamicsWorld* getDynamicsWorld() {return this->dynamicsWorld;}
    private:
        void createGameObjects();
        void createDynamicsWorld();
        btDiscreteDynamicsWorld *dynamicsWorld;
        void tick(btScalar timeStep);
        void setGravity(btVector3);
};