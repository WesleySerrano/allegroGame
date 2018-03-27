#include "GameScene.h"
#define REAL double
#include "triangle.h"

void tickCallback(btDynamicsWorld *world, btScalar timeStep)
{
    long numManifolds = world->getDispatcher()->getNumManifolds();
    if(numManifolds)
    {
    }
}

void printTriangleIO(triangulateio data)
{
  std::cout << "Number of points: " << data.numberofpoints << std::endl;
  std::cout << "Number of holes: " << data.numberofholes << std::endl;
  std::cout << "Number of segments: " << data.numberofsegments << std::endl;
  std::cout << "Number of regions: " << data.numberofregions << std::endl;
  std::cout << "Number of points attributes: " << data.numberofpointattributes << std::endl;
}

void GameScene::addObjectToTriangulation(btVector3 position, btVector3* corners)
{
  const short NUMBER_OF_COORDINATES = 3;
  const short NUMBER_OF_NEW_OBJECTS = 4;
  //const long PREVIOUS_NUMBER_OF_POINTS = this->verticesOnScene->numberofpoints;
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
      this->triangulateObjects();
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
    this->player->setVisibleStatus(true);

    Enemy *enemy = new Enemy(5, 5, -100, -100, 1);
    this->enemySpawner->setTemplateParameters(enemy);
    this->enemySpawner->setTemplateSprite(255, 0, 0);

    const int NUM_CHAIN_NODES = 30;
    float startX = 100, startY = 400, halfWidth = 4, halfHeight = 4, mass = 1;
    
    const float DISTANCE_CONSTRAINT = 4;
    const float OFFSET = 8;

    //this->sb = new SoftBody(NUM_CHAIN_NODES,startX,startY,OFFSET,DISTANCE_CONSTRAINT, 1, this->dynamicsWorld, false);

    GameObject *ground = new GameObject(400, 4, 400, 10, 0);
    ground->setActiveStatus(true);
    ground->setVisibleStatus(true);

    btVector3* playerCorners = player->getCorners();    
    btVector3* groundCorners = ground->getCorners();

    this->addObjectToTriangulation(this->player->getPosition(),playerCorners);
    this->addObjectToTriangulation(ground->getPosition(),groundCorners);
    /* for(short i = 0; i < 8; i++)
    {
      cout << "(x,y,z) = (" << this->verticesOnScene->pointlist[3*i] << " "<< this->verticesOnScene->pointlist[3*i + 1] << " "<< this->verticesOnScene->pointlist[3*i + 2] << ")\n";
    } */

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
  //this->sb->render();
  for (int j = this->getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; --j)
  {
    GameObject *obj = (GameObject*)this->getDynamicsWorld()->getCollisionObjectArray()[j];
    if(obj->isVisible())obj->render();
  } 
}

void GameScene::triangulateObjects()
{
  char* triswitches;
  struct triangulateio in, out, vorout;
  const long NUMBER_OF_OBJECTS = this->getDynamicsWorld()->getNumCollisionObjects();
  long pointsCount = 0;
  
  in.numberofpoints = 4*(NUMBER_OF_OBJECTS + 1);
  in.numberofpointattributes = 0;
  in.numberofsegments = 4*(NUMBER_OF_OBJECTS + 1);
  in.numberofholes = NUMBER_OF_OBJECTS;
  in.numberofregions = 0;
  in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
  in.segmentlist = (int *) malloc(in.numberofsegments*2*sizeof(int));
  in.holelist = (REAL *) malloc(in.numberofholes*2*sizeof(REAL));
  in.pointattributelist = (REAL *) malloc(in.numberofpoints *
                                          in.numberofpointattributes *
                                          sizeof(REAL));
  in.pointmarkerlist = (int *) NULL;
  
  for (int j = NUMBER_OF_OBJECTS - 1; j >= 0; --j)
  {
    GameObject *obj = (GameObject*)this->getDynamicsWorld()->getCollisionObjectArray()[j];
    
    btVector3 objPosition = obj->getPosition();
    const double X = objPosition.getX();
    const double Y = objPosition.getY();
    const double halfHeight = obj->getHalfHeight();
    const double halfWidth = obj->getHalfWidth();
    
    if(in.numberofsegments > 0)
    {
     const long BASE_INDEX = pointsCount/2;
     in.segmentlist[BASE_INDEX] = BASE_INDEX;
     in.segmentlist[BASE_INDEX+1] = BASE_INDEX+1;
     in.segmentlist[BASE_INDEX+2] = BASE_INDEX+1;
     in.segmentlist[BASE_INDEX+3] = BASE_INDEX+2;
     in.segmentlist[BASE_INDEX+4] = BASE_INDEX+2;
     in.segmentlist[BASE_INDEX+5] = BASE_INDEX+3;
     in.segmentlist[BASE_INDEX+6] = BASE_INDEX+3;
     in.segmentlist[BASE_INDEX+7] = BASE_INDEX;
    }

    in.pointlist[pointsCount++] = X - halfWidth;
    in.pointlist[pointsCount++] = Y - halfHeight;
    in.pointlist[pointsCount++] = X + halfWidth;
    in.pointlist[pointsCount++] = Y - halfHeight;
    in.pointlist[pointsCount++] = X + halfWidth;
    in.pointlist[pointsCount++] = Y + halfHeight;
    in.pointlist[pointsCount++] = X - halfWidth;
    in.pointlist[pointsCount++] = Y + halfHeight;  

    if(in.numberofholes > 0)
    {
     in.holelist[2 * j] = X;
     in.holelist[2 * j + 1] = Y;
    }
  } 

  if(in.numberofsegments > 0)
  {
    const long BASE_INDEX = pointsCount/2;
    in.segmentlist[BASE_INDEX] = BASE_INDEX;
    in.segmentlist[BASE_INDEX+1] = BASE_INDEX+1;
    in.segmentlist[BASE_INDEX+2] = BASE_INDEX+1;
    in.segmentlist[BASE_INDEX+3] = BASE_INDEX+2;
    in.segmentlist[BASE_INDEX+4] = BASE_INDEX+2;
    in.segmentlist[BASE_INDEX+5] = BASE_INDEX+3;
    in.segmentlist[BASE_INDEX+6] = BASE_INDEX+3;
    in.segmentlist[BASE_INDEX+7] = BASE_INDEX;
  }
  in.pointlist[pointsCount++] = 0.0;
  in.pointlist[pointsCount++] = 0.0;
  in.pointlist[pointsCount++] = Allegro::WIDTH;
  in.pointlist[pointsCount++] = 0.0;
  in.pointlist[pointsCount++] = Allegro::WIDTH;
  in.pointlist[pointsCount++] = Allegro::HEIGHT;
  in.pointlist[pointsCount++] = 0.0;
  in.pointlist[pointsCount++] = Allegro::HEIGHT;
  
  out.pointlist = (REAL *) NULL;
  
  out.pointattributelist = (REAL *) NULL;
  out.pointmarkerlist = (int *) NULL;
  out.trianglelist = (int *) NULL;
  
  out.triangleattributelist = (REAL *) NULL;
  out.neighborlist = (int *) NULL;
  
  out.segmentlist = (int *) NULL;
  
  out.segmentmarkerlist = (int *) NULL;
  out.edgelist = (int *) NULL;
  out.edgemarkerlist = (int *) NULL;

  vorout.pointlist = (REAL *) NULL;
  
  vorout.pointattributelist = (REAL *) NULL;
  vorout.edgelist = (int *) NULL;
  vorout.normlist = (REAL *) NULL; 

  std::string switchesStr = "pBz";
  char *switches = new char[switchesStr.length() + 1];
  strcpy(switches,switchesStr.c_str());
  
  triangulate(switches, &in, &out, &vorout);  

  for(int i = 0; i < out.numberoftriangles; i++)
  {
    const long P0 = out.trianglelist[3*i];
    const long P1 = out.trianglelist[3*i+1];
    const long P2 = out.trianglelist[3*i+2];
    std::cout << P0<< " "<< P1<< " "<< P2<< " "<< out.numberofsegments<< " "<< out.numberofedges<< " "<< out.numberofpoints<<std::endl;
    std::cout << 2*P0 - 2 << " - " << 2*P0 - 1 << std::endl;
    std::cout << 2*P1 - 2 << " - " << 2*P1 - 1 << std::endl;
    std::cout << 2*P2 - 2 << " - " << 2*P2 - 1 << std::endl;
    std::cout << out.pointlist[2*out.numberofpoints-1] << std::endl;
    std::cout << out.numberoftriangles << " " << out.numberofpoints << std::endl;
    const double X0 = out.pointlist[2*P0-2], Y0 = out.pointlist[2*P0 - 1];
    const double X1 = out.pointlist[2*P1-2], Y1 = out.pointlist[2*P1 - 1];

    //std::cout << X0<< " "<< Y0<< " "<< X1<< " "<< Y1<< " "<< X2<< " "<< Y2<<std::endl;

    al_draw_triangle(out.pointlist[2*P0 - 2], out.pointlist[2*P0 - 1], out.pointlist[2*P1 - 2], out.pointlist[2*P1 - 1], out.pointlist[2*P2 - 2], out.pointlist[2*P2 - 1], al_map_rgb(255, 255, 255),1);
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