#include "Enemy.h"

Enemy::Enemy() : GameObject()
{

}

Enemy::Enemy(double halfWidth, double halfHeight, double x, double y, double inverseMass) : GameObject(halfWidth, halfHeight, x, y, inverseMass, b2_dynamicBody)
{
    
}