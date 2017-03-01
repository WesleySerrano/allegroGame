#include "GameScene.h"

constexpr float timeStep = 1.0f / 60.0f;

int main (void)
{        
   GameScene *scene = new GameScene();
   
   while(42)
   {
      scene->getDynamicsWorld()->stepSimulation(timeStep);
      for (int j = scene->getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; --j) 
      {
            GameObject *obj = (GameObject*)scene->getDynamicsWorld()->getCollisionObjectArray()[j];
            btVector3 position = obj->getPosition();

            cout << "Obj " << j << " X: " << position.getX() << " Y: " << position.getY() << " Z: " << position.getZ() << endl;
      }
   }

   return 0;   
}
