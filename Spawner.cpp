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

void Spawner::setTemplate(GameObject* templateObject)
{
    this->templateHalfWidth = templateObject->getHalfWidth();
    this->templateHalfHeight = templateObject->getHalfHeight();
    this->templateMass = templateObject->getMass();
}

void Spawner::spawn(btDiscreteDynamicsWorld *dynamicsWorld)
{
  int unactiveObjects = this->NUMBER_OF_OBJECTS - this->activeObjects;

  for(int i = 1; i <= unactiveObjects; i++)
  {
    int X = rand()%this->width + this->position[0];
    this->activeObjects++;

    GameObject *enemy = new GameObject(this->templateHalfWidth, this->templateHalfHeight, X, this->position[1], this->templateMass);

    enemy->setActiveStatus(true);
    dynamicsWorld->addRigidBody(enemy);
  }
}