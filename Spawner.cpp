#include "Spawner.h"

Spawner::Spawner()
{

}

Spawner::Spawner(int numberOfObjects, int objectsPerRound, int width, int horizontalPosition, int verticalPosition, double timeInterval)
{
    this->position = new int[2];

    this->NUMBER_OF_OBJECTS = numberOfObjects;
    this->objectsPerRound = objectsPerRound;
    this->objects = new GameObject*[this->NUMBER_OF_OBJECTS];
    this->width = width;
    this->position[0] = horizontalPosition;
    this->position[1] = verticalPosition;
    this->timeInterval = timeInterval;
    this->timeElapsed = 0.0;

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
  double secs = (double)(time(NULL) - this->timeElapsed);

  if((this->timeElapsed == 0) || (secs >= this->timeInterval))
  {
    srand(time(NULL));
    const int OBJECTS_TO_SPAWN = (this->objectsPerRound > (this->NUMBER_OF_OBJECTS - this->activeObjects)) ? (this->NUMBER_OF_OBJECTS - this->activeObjects) : this->objectsPerRound ;

    for(int i = 1; i <= OBJECTS_TO_SPAWN; i++)
    {
        int r = rand();
        int X = r%this->width + this->position[0];
        this->activeObjects++;

        GameObject *enemy = new GameObject(this->templateHalfWidth, this->templateHalfHeight, X, this->position[1], this->templateMass);
        enemy->setSprite(this->color);

        enemy->setActiveStatus(true);
        dynamicsWorld->addRigidBody(enemy);
    }
  }

  this->timeElapsed = time(NULL);
}