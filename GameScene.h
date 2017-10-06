#ifndef GAMESCENE_H
#define GAMESCENE_H

#define BIT(x) (1<<(x))

#include "Player.h"
#include "Spawner.h"
#include "SoftBody.h"

using namespace std; 

class GameScene
{
    public:
        /**
        * Constructor. Initializes Allegro directives, the simulation step, 
        * the Physics world and the objects on scene
        */
        GameScene();
        
        /**
        * The game/scene's main loop. Updates each object's properties 
        * each frame and the event queue.
        */
         void loop();
        
        /**
        * Gets the variable describing the physics world
        * @return The informations about the physics world
        */
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
        SoftBody* sb;

        enum  collisionTypes {COLLIDES_WITH_WALL = 0, COLLIDES_WITH_OBJECTS = BIT(0)};
};
#endif