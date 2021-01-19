#ifndef GAMESCENE_H
#define GAMESCENE_H

#define BIT(x) (1<<(x))

#include <cstdio>
#include <vector>
#include <box2d/b2_world.h>
#include "Player.h"
#include "Spawner.h"

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
        
    private:
        void createGameObjects();
        void createWorld();
        void processEvent(ALLEGRO_EVENT&);
        void render();
        void setGravity(b2Vec2);
        void tick(double timeStep);
        void update();

        float TIME_STEP;
        Player *player;
        Spawner *enemySpawner;
        b2World *world;
        b2Vec2 gravity;

        std::vector<GameObject*> objects;
        std::vector<b2Body*> bodies;

        enum  collisionTypes {COLLIDES_WITH_WALL = 0, COLLIDES_WITH_OBJECTS = BIT(0)};
};
#endif