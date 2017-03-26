#include "GameScene.h"

constexpr float timeStep = 1.0f / 60.0f;

int main (void)
{        
   GameScene *scene = new GameScene();

   scene->loop();

   return 0;   
}
