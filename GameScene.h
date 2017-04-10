#ifndef GAMESCENE_H
#define GAMESCENE_H

#define BIT(x) (1<<(x))

#include "Player.h"
#include "Spawner.h"

using namespace std; 

class GameScene
{
    public:
        GameScene();
        void loop();
        
        btDiscreteDynamicsWorld* getDynamicsWorld() {return this->dynamicsWorld;}
    private:
        void createGameObjects();
        void createDynamicsWorld();
        void processEvent(ALLEGRO_EVENT&);
        void render();
        void setGravity(btVector3);
        void tick(btScalar timeStep);
        void update();


        btDiscreteDynamicsWorld *dynamicsWorld;
        float TIME_STEP;
        Player *player;
        Spawner *enemySpawner;

        enum  collisionTypes {COLLIDES_WITH_WALL = 0, COLLIDES_WITH_OBJECTS = BIT(0)};
};
#endif