#include "Spawner.h"
#include <ctime>

Spawner::Spawner()
{

}

Spawner::Spawner(int numberOfObjects, int width, int horizontalPosition, int verticalPosition)
{
    this->position = new int[2];

    this->NUMBER_OF_OBJECTS = numberOfObjects;
    this->objects = new GameObject*[this->NUMBER_OF_OBJECTS];
    this->width = width;
    this->position[0] = horizontalPosition;
    this->position[1] = verticalPosition;

    this->activeObjects = 0;
}

void Spawner::setTemplateParameters(GameObject* templateObject)
{
    this->templateHalfWidth = templateObject->getHalfWidth();
    this->templateHalfHeight = templateObject->getHalfHeight();
    this->templateMass = templateObject->getMass();
}

void Spawner::setTemplateSprite(float r, float g, float b)
{
    this->color.setValue(r, g, b);
}

void Spawner::spawn(btDiscreteDynamicsWorld *dynamicsWorld)
{
  int unactiveObjects = this->NUMBER_OF_OBJECTS - this->activeObjects;

  srand(time(NULL));

  for(int i = 1; i <= unactiveObjects; i++)
  {
    int r = rand();
    int X = r%this->width + this->position[0];
    std::cout << r << " " << r%this->width << " " << X << std::endl;
    this->activeObjects++;

    GameObject *enemy = new GameObject(this->templateHalfWidth, this->templateHalfHeight, X, this->position[1], this->templateMass);
    enemy->setSprite(this->color);

    enemy->setActiveStatus(true);
    dynamicsWorld->addRigidBody(enemy);
  }
}