#include "Player.h"

Player::Player()
{
_row = 3;
_column = 0;
_speed = 3;
}
Player::Player(int column, int speed)
{
_row = 3;         //enemies always start on top row of our 4x4 LED array
_column = column;
_speed = speed;
}

void Player::setLocation(int loc)
{
   _location = loc;
}
int Player::getLocation()
{
   return _location;
}
void Player::setColumn(int x)
{
   _column = x;
}
int Player::getColumn()
{
   return _column;
}
int Player::getRow()
{
   return _row;
}
void Player::setBulletLocation(int loc)
{
   _bulletLocation = loc;
}
int Player::getBulletLocation()
{
   return _bulletLocation;
}
void Player::setBulletColumn(int x)
{
   _bulletColumn = x;
}
int Player::getBulletColumn()
{
   return _bulletColumn;
}
void Player::setBulletRow(int x)
{
   _bulletRow = x;
}
int Player::getBulletRow()
{
   return _bulletRow;
}
void Player::reduceLife()
{
   _life--;
}
int Player::getLife()
{
   return _life;
}
void Player::setCanFire(bool x)
{
   _canFire = x;
}
bool Player::getCanFire()
{
   return _canFire;
}
void Player::setShowBullet(bool x)
{
   _showBullet = x;
}
bool Player::getShowBullet()
{
   return _showBullet;
}
