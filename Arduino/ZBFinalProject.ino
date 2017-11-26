// Zach Boylan CS 298 Final Project
// Asteroids like game using LED array and Joystick

#include <RGB.h>
#include <vector>

#define RGBPin 2

RGB rgb( RGBPin, 16 );

//std::vector<Enemy> enemies;

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

//for switch
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // For joystick
  pinMode(A2, INPUT);

  // clear LED array
  rgb.clear();

  //random seed for random num generator
  randomSeed(analogRead(0));

  //Need to input_pullup when using a switch
  // pin 2 or 3 can be used for Interrupts
  //pinMode(3, INPUT_PULLUP);
  pinMode(3, INPUT);

  // How does this know to call it when switch is pressed?
  //attachInterrupt(0, switchLED_ISR, CHANGE);
}




int loopIndex = 0;
int enemyStart = 0;
int playerStart = 1;
int enemyLocation;   //Need Enemy class and bullet class to keep track of everything and test if collision?
int playerLocation;
int fireLocation;

void loop() {
  // put your main code here, to run repeatedly:

  int randNumber = random(100) % 3;
  if (randNumber == 1)
  {
    // spawn new enemy
    
  }
  enemyLocation = enemyRow[enemyStart];
  enemyStart++;
  if (enemyStart == 4)
  {
    enemyStart = 0;
  }
  
  //Joystick 
  delay(400);
  
  //Serial.print("X value = ");
  //Serial.print(analogRead(2));
  //Serial.println();

  int xVal = analogRead(2);
  if (xVal < 300)
  {
    if (playerStart > 0)
    {
      playerStart--;
    }
  }
  if (xVal > 700)
  {
    if (playerStart < 3)
    {
      playerStart++;
    }
  }
  playerLocation = playerRow[playerStart];

  //Clear previous frame
  rgb.clear();
  //Show enemy location
  //          green, red, blue
  rgb.setColor(enemyLocation, 255, 255, 0);
  //Show player location
  rgb.setColor(playerLocation, 0, 0, 244);

  // Do a 2-dim array for possible enemy locations?
  //   Then can easily keep column and go down rows
  //   Same thing with bullet
  //   Then check if locations are equal to each other for collison
  //          Go to Orange color to show collison

  // if fire == true, show bullet
  reading = digitalRead(3);
  if (reading == HIGH)
  {
    fireLocation = fireRow[playerStart]; //fire above current player location
    rgb.setColor(fireLocation, 0, 244, 4);
    Serial.println("Switch pressed");  // ***This Works
  }
  reading = LOW;
  //Show new frame
  rgb.show();

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

// ISR = interrupt service routine
void switchLED_ISR()
{
  fire = true;
}
