#include "GameScene.h"

void tickCallback(btDynamicsWorld *world, btScalar timeStep)
{
    long numManifolds = world->getDispatcher()->getNumManifolds();
    if(numManifolds)
    {
    }
}

GameScene::GameScene()
{
   this->TIME_STEP = 1.0/Allegro::FPS;

   Allegro::initialize(Allegro::WIDTH, Allegro::HEIGHT, "AirMeshApplication");
   this->createDynamicsWorld();
   this->createGameObjects();
}

void GameScene::loop()
{ 
  bool refresh = true;

  ALLEGRO_EVENT event;

  while(42)
  {
    al_wait_for_event(Allegro::eventQueue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER)
    {
      refresh = true;
      this->update();
    }

    else if(event.type != ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      this->processEvent(event);
    }

    else
    {
      break;
    }

    if(refresh && al_is_event_queue_empty(Allegro::eventQueue))
    {
      refresh = false;
      this->render();

      al_flip_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
    }
  }
}

void GameScene::processEvent(ALLEGRO_EVENT event)
{

}

void GameScene::createGameObjects()
{
    const int PLAYER_COLLIDES_WITH = COLLIDES_WITH_WALL | COLLIDES_WITH_OBJECTS;
    const int WALL_COLLIDES_WITH = COLLIDES_WITH_OBJECTS;

    this->player = new GameObject(10, 10, 40, 300, 1);

    for (int i = 1; i <= 5; i++)
    {
      GameObject *enemy = new GameObject(5, 5, 50 + 20 * i, 400, 0);
      enemy->setSprite(255, 0, 0);

      this->dynamicsWorld->addRigidBody(enemy);
    }

    GameObject *ground = new GameObject(400, 0.1, 400, 10, 0);

    this->dynamicsWorld->addRigidBody(player);
    this->dynamicsWorld->addRigidBody(ground);
}

void GameScene::createDynamicsWorld()
{
  const double GRAVITY = -100.0f;

   btDbvtBroadphase *broadphase = new btDbvtBroadphase();
   btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
   btCollisionDispatcher *dispatcher = new	btCollisionDispatcher(collisionConfiguration);
   btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;
   
   this->dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
   //this->dynamicsWorld->setInternalTickCallback(tickCallback);
    this->setGravity(btVector3(0, GRAVITY, 0));
}

void GameScene::setGravity(btVector3 gravity)
{
  this->dynamicsWorld->setGravity(gravity);
}

void GameScene::render()
{
  for (int j = this->getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; --j)
  {
    GameObject *obj = (GameObject*)this->getDynamicsWorld()->getCollisionObjectArray()[j];
    obj->render();
  } 
}

void GameScene::update()
{
      this->getDynamicsWorld()->stepSimulation(TIME_STEP, 10);
      for (int j = this->getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; --j) 
      {
            GameObject *obj = (GameObject*)this->getDynamicsWorld()->getCollisionObjectArray()[j];
            obj->update();
      }
}