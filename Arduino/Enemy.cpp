#include "Enemy.h"

Enemy::Enemy()
{
_row = 3;
_column = 0;
_speed = 3;
}
Enemy::Enemy(int column, int speed)
{
_row = 3;         //enemies always start on top row of our 4x4 LED array
_column = column;
_speed = speed;
}

void Enemy::setLocation(int loc)
{
   _location = loc;
}
int Enemy::getLocation()
{
   return _location;
}
void Enemy::setColumn(int x)
{
   _column = x;
}
int Enemy::getColumn()
{
   return _column;
}
void Enemy::setRow(int x)
{
   _row = x;
}
int Enemy::getRow()
{
   return _row;
}
int Enemy::getSpeed()
{
   return _speed;
}
void Enemy::setTimer(int x)
{
   _timer = x;
}
int Enemy::getTimer()
{
   return _timer;
}
void Enemy::setShowEnemy(bool x)
{
   _showEnemy = x;
}
int Enemy::getShowEnemy()
{
   return _showEnemy;
}
