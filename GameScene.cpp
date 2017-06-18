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

   this->enemySpawner = new Spawner(100, 5, 400, 50, 400, 1.0);

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

void GameScene::processEvent(ALLEGRO_EVENT& event)
{
   this->player->processEvent(event);
}

void GameScene::createGameObjects()
{
    const int PLAYER_COLLIDES_WITH = COLLIDES_WITH_WALL | COLLIDES_WITH_OBJECTS;
    const int WALL_COLLIDES_WITH = COLLIDES_WITH_OBJECTS;

    this->player = new Player(10, 10, 140, 300, 0);
    this->player->setActiveStatus(true);

    Enemy *enemy = new Enemy(5, 5, -100, -100, 1);
    this->enemySpawner->setTemplateParameters(enemy);
    this->enemySpawner->setTemplateSprite(255, 0, 0);

    GameObject *chainA = new GameObject(20, 2, 100, 400, 1);
    chainA->setActiveStatus(true);
    GameObject *chainB = new GameObject(20, 2, 139, 400, 1);
    chainB->setActiveStatus(true);
    GameObject *chainC = new GameObject(20, 2, 179, 400, 1);
    chainC->setActiveStatus(true);
    
    btPoint2PointConstraint* c0 = new btPoint2PointConstraint(*chainA, btVector3(0, 0, 0));
    btPoint2PointConstraint* c1 = new btPoint2PointConstraint(*chainA, *chainB, btVector3(10, 2, 0), btVector3(0.5, 2, 0));

    this->dynamicsWorld->addConstraint(c0);
    //this->dynamicsWorld->addConstraint(c1);

    this->dynamicsWorld->addRigidBody(chainA);
    this->dynamicsWorld->addRigidBody(chainB);
    this->dynamicsWorld->addRigidBody(chainC);

    GameObject *ground = new GameObject(400, 4, 400, 10, 0);
    ground->setActiveStatus(true);

    this->dynamicsWorld->addRigidBody(player);
    this->dynamicsWorld->addRigidBody(ground);
}

void GameScene::createDynamicsWorld()
{
  const double GRAVITY = -98.0f;

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
    if(obj->isActive())obj->render();
  } 
}

void GameScene::update()
{
      this->getDynamicsWorld()->stepSimulation(TIME_STEP, 10);
      this->enemySpawner->spawn(this->dynamicsWorld);
      for (int j = this->getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; --j) 
      {
            if(dynamic_cast<Player*>(this->getDynamicsWorld()->getCollisionObjectArray()[j]))
            {
             Player* obj =  dynamic_cast<Player*>(this->getDynamicsWorld()->getCollisionObjectArray()[j]);
             if(obj->isActive())obj->update();
            }
            else if(dynamic_cast<Enemy*>(this->getDynamicsWorld()->getCollisionObjectArray()[j]))
            {
             Enemy *obj = dynamic_cast<Enemy*>(this->getDynamicsWorld()->getCollisionObjectArray()[j]);
             if(obj->isActive())obj->update();
            }
      }
}