#include "SoftwareSerial.h"

#define CA1 A0
#define CA2 A1
#define CA3 A2
#define CA4 A3
#define BTTRY A4

#define A_PH 8
#define A_EN 9
#define B_PH 10
#define B_EN 11

#define FORWARD 0
#define BACKWARD 1
#define RIGHT 1
#define LEFT 0

#define    STX          0x02
#define    ETX          0x03
#define    ledPin       13
#define    SLOW         750                            // Datafields refresh rate (ms)
#define    FAST         250                             // Datafields refresh rate (ms)

int vod = 0; // 1 - Top  2 - Bot  3 - Right 4 - Left  0 - Reset

void sensorTop();
void sensorBot();
void sensorRight();
void sensorLeft();

void controlMotor(int joyX, int joyY);
                           // BlueTooth module: pin#2=TX pin#3=RX
byte cmd[8] = {0, 0, 0, 0, 0, 0, 0, 0};                 // bytes received
byte buttonStatus = 0;                                  // first Byte sent to Android device
long previousMillis = 0;                                // will store last time Buttons status was updated
long sendInterval = SLOW;                               // interval between Buttons status transmission (milliseconds)
String displayStatus = "xxxx";                          // message to Android device

void setup()  {
  Serial.begin(115200);
  Serial.begin(115200);

  while(Serial.available())  Serial.read();         // empty RX buffer

  pinMode(A_PH, OUTPUT);
  pinMode(A_EN, OUTPUT);
  pinMode(B_EN, OUTPUT);
  pinMode(B_PH, OUTPUT);
}

void loop() {
 if(Serial.available())  {                           // data received from smartphone
   delay(2);
   cmd[0] =  Serial.read();
   if(cmd[0] == STX)  {
     int i=1;
     while(Serial.available())  {
       delay(1);
       cmd[i] = Serial.read();
       if(cmd[i]>127 || i>7)                 break;     // Communication error
       if((cmd[i]==ETX) && (i==2 || i==7))   break;     // Button or Joystick data
       i++;
     }
     if     (i==2)          getButtonState(cmd[1]);    // 3 Bytes  ex: < STX "C" ETX >
     else if(i==7)          getJoystickState(cmd);     // 6 Bytes  ex: < STX "200" "180" ETX >
   }
 }
 sendBlueToothData();
}

void sendBlueToothData()  {
 static long previousMillis = 0;
 long currentMillis = millis();
 if(currentMillis - previousMillis > sendInterval) {
   previousMillis = currentMillis;

   Serial.print((char)STX);
   Serial.print(getButtonStatusString());  Serial.print((char)0x1);
   Serial.print(GetdataInt1());            Serial.print((char)0x4);
   Serial.print(GetdataFloat2());          Serial.print((char)0x5);
   Serial.print(displayStatus);
   Serial.print((char)ETX);
 }
}

String getButtonStatusString()  {
 String bStatus = "";
 for(int i=0; i<6; i++)  {
   if(buttonStatus & (B100000 >>i))      bStatus += "1";
   else                                  bStatus += "0";
 }
 return bStatus;
}

int GetdataInt1()  {              // Data dummy values sent to Android device for demo purpose
 static int i= -30;              // Replace with your own code
 i ++;
 if(i >0)    i = -30;
 return i;
}

float GetdataFloat2()  {           // Data dummy values sent to Android device for demo purpose
 static float i=50;               // Replace with your own code
 i-=.5;
 if(i <-50)    i = 50;
 return i;
}

void getJoystickState(byte data[8])    {
 int joyX = (data[1]-48)*100 + (data[2]-48)*10 + (data[3]-48);
 int joyY = (data[4]-48)*100 + (data[5]-48)*10 + (data[6]-48);

 joyX = joyX - 100;
 joyY = joyY - 100;

    joyX = map(joyX, 0, 200, 0, 256);
    joyY = map(joyY, 0, 200, 0, 256);

    controlMotor(joyX, joyY);

}

void getButtonState(int bStatus)  {
 switch (bStatus) {
// -----------------  BUTTON #1  -----------------------
   case 'A':
     buttonStatus |= B000001;
     // Auto
     break;
   case 'B':
     buttonStatus &= B111110;
     // Manu
     break;

// -----------------  BUTTON #2  -----------------------
   case 'C':
     buttonStatus |= B000010;
     break;
   case 'D':
     buttonStatus &= B111101;
     break;

// -----------------  BUTTON #3  -----------------------
   case 'E':
     buttonStatus |= B000100;
     break;
   case 'F':
     buttonStatus &= B111011;
     break;

// -----------------  BUTTON #4  -----------------------
   case 'G':
     buttonStatus |= B001000;
     break;
   case 'H':
     buttonStatus &= B110111;
     sendInterval = SLOW;
    break;

// -----------------  BUTTON #6  -----------------------
   case 'K':
     buttonStatus |= B100000;
    break;
   case 'L':
     buttonStatus &= B011111;
     break;
 }
}

void controlMotor(int joyX, int joyY) {
    boolean sens, dir;
    int16_t speedL, speedR;
    uint8_t x = joyX;
    uint8_t y = joyY;

    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);

    if (x > 128 - 10 && x < 128 + 10)
        x = 128;

    if (y > 128 - 10 && y < 128 + 10)
        y = 128;

    if (x > 128)
    {
        sens = BACKWARD;
        x = x - 128;
    }
    else
    {
        x = 128 - x;
        sens = FORWARD;
    }

    if (y > 128)
    {
        dir = RIGHT;
        y = y - 128;
    }
    else
    {
        y = 128 - y;
        dir = LEFT;
    }

    if (dir == LEFT)
    {
        speedL = 2*x - y*2;
        speedR = 2*x + y*2;
    }
    else
    {
        speedL = 2*x + y*2;
        speedR = 2*x - y*2;
    }

    if (sens == FORWARD)
    {
        digitalWrite (A_PH, HIGH);
        digitalWrite (B_PH, HIGH);
    }
    else
    {
        digitalWrite (A_PH, LOW);
        digitalWrite (B_PH, LOW);
    }



    if (speedL < 0)
    {
        digitalWrite (A_PH, LOW);
        speedL = speedL*-1;
    }
    if (speedR < 0)
    {
        digitalWrite (B_PH, LOW);
        speedR = speedR *-1;
    }
    if (speedL > 255)
        speedL = 255;
    if (speedR > 255)
        speedR = 255;

    analogWrite (A_EN, speedL);
    analogWrite (B_EN, speedR);
}

void sensorTop() {
    vod = 1;
}

void sensorBot() {
    vod = 2;
}

void sensorRight() {
    vod = 3;
}

void sensorLeft() {
    vod = 4;
}