#include "SoftBody.h"

SoftBody::SoftBody() : GameObject()
{

}

SoftBody::SoftBody(int numberOfNodes, double startX, double startY, double startOffset, double maxOffset, double nodesMass, btDiscreteDynamicsWorld* dynamicsWorld, bool fixed)
{
  this->numberOfNodes = numberOfNodes;
  this->nodes = new GameObject*[numberOfNodes];

   const float HALF_WIDTH = 2, HALF_HEIGHT = 2;

  for(int i = 0; i < numberOfNodes; i++)
  {
      this->nodes[i] = new GameObject(HALF_WIDTH, HALF_HEIGHT, startX + i*startOffset, startY, nodesMass);
      this->nodes[i]->setActiveStatus(true);

      if(i > 0)
      {
        btPoint2PointConstraint* c = new btPoint2PointConstraint(*this->nodes[i - 1], *this->nodes[i], btVector3(maxOffset, 0, 0), btVector3(-maxOffset, 0, 0));
        dynamicsWorld->addConstraint(c);
      }
      dynamicsWorld->addRigidBody(this->nodes[i]);
  }

  if(fixed)
  {
    dynamicsWorld->addConstraint(new btPoint2PointConstraint(*this->nodes[0], btVector3(0,0,0)));
    dynamicsWorld->addConstraint(new btPoint2PointConstraint(*this->nodes[numberOfNodes - 1], btVector3(0,0,0)));
  }
}

void SoftBody::render()
{
    for(int i = 1; i < this->numberOfNodes; i++)
    {
        btVector3 p0 = this->nodes[i - 1]->getPosition();
        btVector3 p1 = this->nodes[i]->getPosition();
        const double X0 = p0.getX(), Y0 = -p0.getY() + Allegro::HEIGHT;
        const double X1 = p1.getX(), Y1 = -p1.getY() + Allegro::HEIGHT;
        al_draw_line(X0,Y0,X1,Y1,al_map_rgb(255,255,0),2);
    }
}

