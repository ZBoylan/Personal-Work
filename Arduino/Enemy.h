#ifndef __Enemy_H__
#define __Enemy_H__

//Standard includes
#include <Arduino.h>

//This class encapsulates the commands needed to control the illumincation level of two leds
class Enemy
{
public:
Enemy();
Enemy(int column, int speed);

~Enemy();  //destroy enemy objects when collision occurs - needed?

void setLocation(int loc);
int getLocation();
void setColumn(int x);
int getColumn();
void setRow(int x);
int getRow();
int getSpeed();
void setTimer(int x);
int getTimer();
void setShowEnemy(bool x);
bool getShowEnemy();

private:
int _location;
int _row;          // location = grid[_row][_column]
int _column;
int _speed;  // 1 fastest - 3 slowest
int _timer;  // when timer hits 0 -> move enemy down 1
bool _showEnemy = true;

};

#endif

//    Keep a vector of enemies in the main program?
