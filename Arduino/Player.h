#ifndef __Player_H__
#define __Player_H__

//Standard includes
#include <Arduino.h>

//This class encapsulates the commands needed to control the illumincation level of two leds
class Player
{
public:
Player();
Player(int location);

void setLocation(int loc);
int getLocation();
void setColumn(int x);
int getColumn();
int getRow();
void setBulletLocation(int loc);
int getBulletLocation();
void setBulletRow(int loc);
int getBulletRow();
void setBulletColumn(int loc);
int getBulletColumn();
void reduceLife();
int getLife();
void setCanFire(bool x);
bool getCanFire();
void setShowBullet(bool x);
bool getShowBullet();

private:
int _location;
int _row = 0;
int _column;
int _life = 3;   //number of lives - decrement if collision or gets into player row
int _bulletLocation;  // 1 bullet at a time or have a separate Bullet class(have multiple bullets at a time)?
int _bulletRow;
int _bulletColumn;
bool _canFire = true;  //can fire again when bullet reaches top row. 1 bullet at a time
bool _showBullet = false;
bool _row0Collision = false;
bool _bulletCollision = false;

};

#endif
