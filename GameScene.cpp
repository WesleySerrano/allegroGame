#include "GameScene.h"
#define REAL double
#include "triangle.h"

GameScene::GameScene()
{
   this->TIME_STEP = 1.0/Allegro::FPS;
    const int NUMBER_OF_ENEMIES = 100;
    const int OBJECTS_PER_ROUND = 5;
    const int WIDTH = 400;
    const int HORIZONTAL_POSITION = 50;
    const int VERTICAL_POSITION = 400;
    const double TIME_INTERVAL = 1.0;
   this->enemySpawner = new Spawner(NUMBER_OF_ENEMIES, OBJECTS_PER_ROUND, WIDTH, HORIZONTAL_POSITION, VERTICAL_POSITION, TIME_INTERVAL);

   Allegro::initialize(Allegro::WIDTH, Allegro::HEIGHT, "AllegroApp");

  this->setGravity(b2Vec2(0.0f, -9.8f));
   this->createGameObjects();
   this->createWorld();
}

void GameScene::loop()
{ 
  bool refresh = true;

  ALLEGRO_EVENT event;

  const int POSITION_ITERATIONS = 2, VELOCITY_ITERATIONS = 6;

  while(42)
  {
    al_wait_for_event(Allegro::eventQueue, &event);


    if(event.type == ALLEGRO_EVENT_TIMER)
    {
      this->world->Step(this->TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
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

    this->player = new Player(10.0f, 10.0f, 140, 300, 1);
    this->player->setActiveStatus(true);
    this->player->setVisibleStatus(true);

    Enemy *enemy = new Enemy(5, 5, -100, -100, 1);
    this->enemySpawner->setTemplateParameters(enemy);
    this->enemySpawner->setTemplateSprite(255, 0, 0);

    GameObject *ground = new GameObject(360.0f, 4.0f, 400, 10, 0, b2_staticBody);
    ground->setActiveStatus(true);
    ground->setVisibleStatus(true);

    this->objects.emplace_back(ground);
    this->objects.emplace_back(player);

}

void GameScene::createWorld()
{
  this->world = new b2World(b2Vec2(this->gravity.x, this->gravity.y));

  for(GameObject *object : this->objects)
  {
    if(object->isActive())
    {
      b2Body* objectRigidBody = this->world->CreateBody(object->getRigidBodyDefinition());

      object->setRigidBody(objectRigidBody);

      this->bodies.emplace_back(objectRigidBody);
    }
  }
}

void GameScene::setGravity(b2Vec2 _gravity)
{
  this->gravity = b2Vec2(_gravity.x, _gravity.y);
}

void GameScene::render()
{
  for(GameObject *object : this->objects)
  {
    if(object->isVisible())
    {
      object->render();
    }
  }
}

void GameScene::update()
{
  //std::cout << "X: " << this->world->GetGravity().x << " Y: " << this->world->GetGravity().y << std::endl;

  /*for(b2Body *body : this->bodies)
  {
    std::cout << "X: " <<body->GetPosition().x << " Y: " << body->GetPosition().y<< std::endl;
  }*/

  for(GameObject *object : this->objects)
  {
    double X = object->getRigidBody()->GetPosition().x, Y = object->getRigidBody()->GetPosition().y;
    std::cout << "X: " << X << " Y: " << Y << std::endl;
  }
}