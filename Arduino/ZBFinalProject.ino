// Zach Boylan CS 298 Final Project
// Asteroids like game using LED array and Joystick

// only 2 KB of SRAM on Nano

#include <RGB.h>
#include <vector.h>
#include <Enemy.h>
#include <Player.h>
#include <SPI.h>  //for display (player score)

#define RGBPin 2
#define SPISelectPin 10

RGB rgb( RGBPin, 16 );

std::vector<Enemy> enemies;

//    ^ be a ptr vector. Each loop() go through that vector and check
//      if that enemy's location == bullet location - delete from vector
 //           vector.erase(position)
//    for (unsigned i=0; i<myvector.size(); ++i)
 
// player row = 0, 7, 8, 15

// top row locations = 3, 4, 11, 12
// Enemies - yellow - RGB (255, 255, 0)

int playerRow[] = {0, 7, 8, 15};
int enemyRow[] = {3, 4, 11, 12};
int fireRow[] = {1, 6, 9, 14};
 
int pRow, pColumn;    //store grid location data for
int eRow, eColumn;    // pl
int bRow, bColumn;
int grid[4][4] = {
  {0, 7, 8, 15},
  {1, 6, 9, 14),
  {2, 5, 10, 13},
  {3, 4, 11, 12}
}

//int enemyColor[] = {255, 255, 0};
//int playerColor[] = {0, 0, 0};

float redArray[]   = { 179.294, 179.294, 179.294, 160.948, 107.294, 53.647, 35.294, 35.294, 35.294, 35.294, 35.294, 53.647, 107.294, 160.941, 179.294, 179.294 };
float blueArray[]  = {   9.804,  24.706,  40.000,  49.804,  49.804, 49.804, 49.804, 49.804, 49.804, 34.902, 19.608,  9.804,   9.804,   9.804,   8.804,   9.804 };
float greenArray[] = {   9.804,   8.804,   8.804,   9.804,   9.804,  9.804, 19.608, 34.902, 49.804, 49.804, 49.804, 49.804,  49.804,  49.804,  40.000,  24.706 }; 
int delayVal = 75; //originally 75

boolean fire = false;

int playerScore = 0;
int enemyToRemove = -1;

//for switch
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

//for score display
byte currentValue = 16;
byte segmentMapping[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // For joystick
  pinMode(A2, INPUT);       // X value
  pinMode(4, INPUT_PULLUP); // joystick switch (L3/R3)

  // clear LED array
  rgb.clear();

  //random seed for random num generator
  randomSeed(analogRead(0));

  //for score display
  SPI.begin();
  SPI.setBitOrder( MSBFIRST );
  pinMode( SPISelectPin, OUTPUT );

  //Need to input_pullup when using a switch
  // pin 2 or 3 can be used for Interrupts
  // Using switch button
  //pinMode(3, INPUT);  // Will use joystick switch for now
  
}







int loopIndex = 0;
int enemyStart = 0;
int playerStart = 1;
int enemyLocation;   //Need Enemy class and bullet class to keep track of everything and test if collision?
int playerLocation;
int fireLocation;
int randNumber;
int colNum;
int xVal;
bool colFree = true;

void loop() {
  // put your main code here, to run repeatedly:

  // Generating new enemies
  randNumber = random(100) % 3;
  colNum = random(100) % 4;
  if (randNumber == 1)  //try to spawn new enemy
  {
    // check all existing enemies to see if can spawn new enemy
    for (int i = 0; i < enemies.size(); i++)
    {
      if (enemies[i].getColumn() == colNum)
      {
        colFree = false;  //this column has an enemy so can not spawn the enemy 
      }
    }
    if (colFree)
    {
      //spawn enemy
      enemies.push_back(Enemy(colNum, 3));
    }
    colFree = true;  //set back to true for next loop()
  }

  //check for collision
  // a bullet won't be on grid unless getCanFire == false
  if (!player.getCanFire()) 
  {
    for (int i = 0; i < enemies.size(); i++) //cycle through all enemies
    {
      if (player.getBulletLocation() == enemies[i].getLocation())
      {
        //if collision - hide bullet and enemy
        playerScore++;                   // increment player score
        Serial.println("Player score: " + playerScore);
        player.setShowBullet(false);     //hide bullet
        player.setCanFire(true);         //allow player to fire new bullet
        enemies[i].setShowEnemy(false);  //hide enemy - need this if just going to delete them on line 132?
        enemyToRemove = i;  //after for loop - remove enemy from vector
      }
    }
    if (enemyToRemove > -1)
    {
      enemies.erase(enemyToRemove);  // need to call enemy destructor function?
      enemyToRemove = -1;            // set back to -1 for next loop()
    }
  }

  //update bullet location
  if (!player.getCanFire())
  {
    player.setBulletRow(player.getBulletRow()+1);
    
    if (player.getBulletRow() == 4)
    {
      // if bullet is moving off the grid
      player.setShowBullet(false);     //hide bullet - might not need this?
      player.setCanFire(true);         //allow player to fire new bullet
    }
    else
    {
      player.setBulletLocation(grid[player.getBulletRow()][player.getBulletColumn()]);
    }
    
  }

  //update enemy locations
  for (int i = 0; i < enemies.size(); i++)
  {
    if (enemies[i].getRow() == 0)
    {
      //if enemy already on row 0 before updating
      //currently only spawning 1 enemy at a time and all moving at same speed so only 1 will be on row 0 at a time
      // if multiple can be on row 0 at a time then have to do: https://stackoverflow.com/questions/18292371/deleting-a-vector-element-in-a-loop-based-upon-a-conditional-statement
      player.reduceLife();  //reduce player life by 1
      Serial.println("Player health: " + player.getLife());
      enemyToRemove = i;   
    }
    else
    {
      // Move enemy down 1 row
      // **currently not taking into effect enemy speed
      enemies[i].setRow(enemies[i].getRow()-1);
    
      enemies[i].setLocation(grid[enemies[i].getRow()][enemies[i].getColumn()]);
    }
    
  }
  if (enemyToRemove > -1)
    {
      enemies.erase(enemyToRemove);  // need to call enemy destructor function?
      enemyToRemove = -1;            // set back to -1 for next loop()
    }

  // old code - just move along top row
  //enemyLocation = enemyRow[enemyStart];  
  //enemyStart++;
  //if (enemyStart == 4)
  //{
    //enemyStart = 0;
  //}
  
  //Joystick 
  delay(400);
  
  //Serial.print("X value = ");
  //Serial.print(analogRead(2));
  //Serial.println();


//update player location
  xVal = analogRead(2);
  if (xVal < 300)
  {
    if (player.getColumn() > 0)
    {
      player.setColumn(player.getColumn()-1);
    }
  }
  if (xVal > 700)
  {
    if (player.getColumn() < 3)
    {
      player.setColumn(player.getColumn()+1);
    }
  }
  player.setLocation( grid[0][player.getColumn()] );


  

  //Clear previous frame
  rgb.clear();
  //Show enemy location
  //          green, red, blue



  //Show player location
  rgb.setColor(player.getLocation(), 0, 0, 244);
  
  // Light up location of each enemy alive
  for (int i=0; i < enemies.size(); ++i)
  {
    rgb.setColor(enemies[i].getLocation(), 255, 255, 0);
  }
  //rgb.setColor(enemyLocation, 255, 255, 0);

  //show bullet location
  if (player.getShowBullet())
  {
    rgb.setColor(player.getBulletLocation(), 0, 244, 4);
  }
  

  //Show bullet location if canFire = false and showBullet = true
  //if (!player.getCanFire() && player.getShowBullet())
  //{
    //rgb.setColor(player.getBLocation(), 0, 244, 4);
  //}
  

  // Do a 2-dim array for possible enemy locations?
  //   Then can easily keep column and go down rows
  //   Same thing with bullet
  //   Then check if locations are equal to each other for collison
  //          Go to Orange color to show collison

  

  // if fire == true, show bullet
  // currently using switch button
  //    *** Switch on joystick works but when pressed - sends 0/LOW
  //reading = digitalRead(3);  //switch button

  //Firing bullet
  reading = digitalRead(4);    //joystick switch
  //if (reading == HIGH && player.getCanFire())  //switch button
  if (reading == LOW && player.getCanFire())     //joystick switch
  {
    player.setBulletRow(1);
    player.setBulletColumn(player.getColumn());
    player.setBulletLocation(grid[player.getBulletRow()][player.getBulletColumn()]);
    //fireLocation = fireRow[playerStart]; //old code - fire above current player location
    player.setShowBullet(true);
    rgb.setColor(player.getBulletLocation(), 0, 244, 4);
    player.setCanFire(false);
    Serial.println("Switch pressed");  // ***This Works
  }
  //reading = LOW; //should go to LOW on its own if not pressed


  
  
  
  //Show new frame
  rgb.show();

  //update score display
  updateShiftRegister( segmentMapping[ playerScore ] );

  fire = false;

  /*
  // game over screen
  while (player.getHealth() == 0)
  {
   for(int i = 0; i < 16; i++ )
   {
    rgb.clear();
    int index = ( i + loopIndex ) % 16;
    float redValue   = redArray[ index ];
    float greenValue = greenArray[ index ];
    float blueValue  = blueArray[ index ];
    rgb.setColor( i, greenValue, redValue, blueValue );
    rgb.show();
    delay( delayVal );
   }
   loopIndex = (loopIndex + 1) % 16;
  } 
  */
}

void updateShiftRegister( byte value )
{
  digitalWrite( SPISelectPin, LOW );
  SPI.transfer( value );
  digitalWrite( SPISelectPin, HIGH );
}

// ISR = interrupt service routine
//void switchLED_ISR()
//{
  //fire = true;
//}
