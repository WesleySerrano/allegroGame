#include "Spawner.h"

Spawner::Spawner()
{

}

Spawner::Spawner(int numberOfObjects, int objectsPerRound, int width, int horizontalPosition, int verticalPosition, double timeInterval)
{
    this->position = new int[2];

    this->NUMBER_OF_OBJECTS = numberOfObjects;
    this->objectsPerRound = 1;//objectsPerRound;
    this->objects = new Enemy*[this->NUMBER_OF_OBJECTS];
    this->width = width;
    this->position[0] = horizontalPosition;
    this->position[1] = verticalPosition;
    this->timeInterval = timeInterval;
    this->timeElapsed = 0.0;

    this->activeObjects = 0;
}

void Spawner::setTemplateParameters(Enemy* templateObject)
{
    this->templateHalfWidth = templateObject->getHalfWidth();
    this->templateHalfHeight = templateObject->getHalfHeight();
    this->templateMass = templateObject->getInverseMass();
}

void Spawner::setTemplateSprite(float r, float g, float b)
{
    this->color.Set(r, g, b);
}

void Spawner::spawn()
{
  double secs = (double)(time(NULL) - this->timeElapsed);

  if((this->timeElapsed == 0) || (secs >= this->timeInterval))
  {
    srand(time(NULL));
    const int OBJECTS_TO_SPAWN = (this->objectsPerRound > (this->NUMBER_OF_OBJECTS - this->activeObjects)) ? (this->NUMBER_OF_OBJECTS - this->activeObjects) : this->objectsPerRound ;

    int *previousPositions = new int[OBJECTS_TO_SPAWN];

    for(int i = 1; i <= OBJECTS_TO_SPAWN; i++)
    {
        int r = rand();
        bool previouslyUsed = true;
        int X = r%this->width + this->position[0];

        /*while(previouslyUsed)
        {
            for(int j = 0; j < i - 1; j++)
            {
                if(X == previousPositions[j])
                {

                    X = r%this->width + this->position[0];
                    break;
                }

                if(j == i - 1) previouslyUsed = false;
            }
        }*/
        previousPositions[i - 1] = X;

        this->activeObjects++;

        Enemy *enemy = new Enemy(this->templateHalfWidth, this->templateHalfHeight, X, this->position[1], this->templateMass);
        enemy->setSprite(this->color);

        enemy->setActiveStatus(true);
        enemy->setVisibleStatus(true);
    }
  }

  this->timeElapsed = time(NULL);
}