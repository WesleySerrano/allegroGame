#include "GameScene.h"

void tickCallback(btDynamicsWorld *world, btScalar timeStep)
{
    long numManifolds = world->getDispatcher()->getNumManifolds();
    std::cout << "numManifolds = " << numManifolds << "\n";
}

GameScene::GameScene()
{
   this->createDynamicsWorld();
   this->createGameObjects();
}

void GameScene::createGameObjects()
{
    GameObject *player = new GameObject(0.5, 0.5, 40, 30, 1);
    GameObject *ground = new GameObject(400, 0.05, 400, 10, 0);

    this->dynamicsWorld->addRigidBody(player);
    this->dynamicsWorld->addRigidBody(ground);
}

void GameScene::createDynamicsWorld()
{
  const double GRAVITY = -10.0f;

   btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
   btCollisionDispatcher *dispatcher = new	btCollisionDispatcher(collisionConfiguration);
   btDbvtBroadphase *broadphase = new btDbvtBroadphase();
   btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;
   
   this->dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
   this->dynamicsWorld->setGravity(btVector3(0, -10, 0));
   this->dynamicsWorld->setInternalTickCallback(tickCallback);
   this->setGravity(btVector3(0, GRAVITY, 0));
}


void GameScene::tick(btScalar timeStep)
{
  this->dynamicsWorld->stepSimulation(timeStep);
}

void GameScene::setGravity(btVector3 gravity)
{
  this->dynamicsWorld->setGravity(gravity);
}