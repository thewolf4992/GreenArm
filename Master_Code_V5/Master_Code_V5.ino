//Practice Comment
// Files for color sensor library
#include <MD_TCS230.h>
#include <FreqCount.h>
#include "ColorMatch.h"
// Files for servo library
#include "meArm.h" 
#include <Servo.h>

// Pin definitions for color sensor
#define  S2_OUT  12
#define  S3_OUT  13
#define  OE_OUT   4    // LOW = ENABLED
#define  OUT_OUT  5    // Used for freqCount library
// Pin definitions for ultrasonic sensor
#define trigPin 6
#define echoPin 7
// Pin definitions for servos
#define basePin     11
#define shoulderPin 10
#define elbowPin    9
#define gripperPin  8

// Global variables (color sensor)
uint8_t ctIndex;
colorData rgb;
MD_TCS230  CS(S2_OUT, S3_OUT, OE_OUT);
// Global variables (ultrasonic sensor)
long duration;
int uDistance;
// Global Variables (servos)
meArm arm;

void setup() {
  // Initialise serial port
  Serial.begin(57600);
  // Initialise color sensor
  CS.begin();
  // Use calibration parameters ColoMatch header file
  CS.setDarkCal(&sdBlack);
  CS.setWhiteCal(&sdWhite);
  // Initialise servo pins
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  // Set Echo and Trig pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  // Read color from color sensor
  readColor();
  // Read distance from ultrasonic sensor
  ReadDistance();
  //Open then close gripper
  //arm.closeGripper();
  //arm.openGripper();
  //delay(500);
  //Go to point (x,y,z)
  //arm.gotoPoint(0, 100, 50);
  //delay(500); 

}

void readColor() {
  /*Function reads rgb values from color sensor, passes them into 
    the ColorMatch function prints out closest color.*/
  static  bool  waiting;
  
  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available()) 
    {
      colorData  rgb;
      
      CS.getRGB(&rgb);
  
      /* Uncomment to print RGB readings
      Serial.print("RGB [");
      Serial.print(rgb.v  alue[TCS230_RGB_R]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_G]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_B]);
      Serial.println("]");
      */
  
      // find the matching color
      uint8_t  i = colorMatch(&rgb);
    
     // Serial.print(F("\nClosest color is "));
     // Print matching color's name
      Serial.println(ct[i].name); 
      waiting = false;
    }
  }
}

uint8_t colorMatch(colorData *rgb) {
  /*Function matches sensor readings with calibration data by rooting the
    mean square distance between the color and colors in the table.
    Square of the distance is used to ensure that negative distances do not
    subtract from the total.*/
  int32_t   d;
  uint32_t  v, minV = 999999L;
  uint8_t   minI;
  
  for (uint8_t i=0; i<ARRAY_SIZE(ct); i++)
  {
    v = 0;
    for (uint8_t j=0; j<RGB_SIZE; j++)
    {
      d = ct[i].rgb.value[j] - rgb->value[j];
      v += (d * d);
    }
    if (v < minV) // new best
    {
      minV = v;
      minI = i;
    }
    if (v == 0)   // perfect match, no need to search more
      break;
  }
  
  return(minI);
  
  }
  
  void ReadDistance() {
    
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  uDistance= duration*0.034/2;
  // Prints the distance in cm on the Serial Monitor
  Serial.println(uDistance);
}

