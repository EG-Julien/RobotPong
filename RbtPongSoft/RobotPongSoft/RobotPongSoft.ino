#include <Arduino.h>

#define SPEED 200

#define CA1 A0 // AVANT
#define CA2 A1 // ARRIERE
#define CA3 A2 // GAUCHE
#define CA4 A3 // DROITE

#define A_PH 8
#define A_EN 9
#define B_PH 10
#define B_EN 11

#define    STX          0x02
#define    ETX          0x03
#define    SLOW         750

byte cmd[8] = {0, 0, 0, 0, 0, 0, 0, 0};
byte buttonStatus = 0;
long previousMillis = 0;
long sendInterval = SLOW;

#define FORWARD 0
#define BACKWARD 1
#define RIGHT 1
#define LEFT 0
#define AUTO 0
#define MANU 1

int state = MANU;

void controlMotor(int x, int y);
void speedMotor(int __speeda, int __speedb);
int randomAngle(void);
void getJoystickState(byte data[8]);
void getButtonState(int bStatus);

void setup() {
    pinMode(13, OUTPUT);
    digitalWrite(13, OUTPUT);

    pinMode(A_EN, OUTPUT);
    pinMode(A_PH, OUTPUT);
    pinMode(B_EN, OUTPUT);
    pinMode(B_PH, OUTPUT);

    Serial.begin(115200);

    pinMode(CA1, INPUT);
    pinMode(CA2, INPUT);
    pinMode(CA3, INPUT);
    pinMode(CA4, INPUT);
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
            if (i == 2)
                getButtonState(cmd[1]);
            else if(i == 7 && state == AUTO)
                getJoystickState(cmd);
        }
    }

    if (state == MANU) {
        if (digitalRead(CA1) == 1) { // FRONT
            speedMotor(0 - SPEED, 0 - SPEED);
            delay(300);
            speedMotor(SPEED, randomAngle());
            delay(300);
        }

        if (digitalRead(CA3) == 1) { // LEFT
            speedMotor(0 - SPEED, 0 - SPEED);
            delay(300);
            speedMotor(SPEED, randomAngle());
            delay(300);
        }

        if (digitalRead(CA4) == 1) { // RIGHT
            speedMotor(0 - SPEED, 0 - SPEED);
            delay(300);
            speedMotor(randomAngle(), SPEED);
            delay(300);
        }

        if (digitalRead(CA2) == 1) { // BACK
            speedMotor(SPEED, SPEED);
            delay(300);
            speedMotor(randomAngle(), SPEED);
            delay(300);
        }

        speedMotor(SPEED, SPEED);

        delay(10);
    }
}

int randomAngle()  {
    return (int)random(-300, 300);
}

void speedMotor(int __speeda, int __speedb) {
    if (__speeda < 0) {
        __speeda = 255 + __speeda;
        digitalWrite(A_PH, HIGH);
    } else {
        digitalWrite(A_PH, LOW);
    }

    analogWrite(A_EN, __speeda);

    if (__speedb < 0) {
        __speedb = 255 + __speedb;
        digitalWrite(B_PH, HIGH);
    } else {
        digitalWrite(B_PH, LOW);
    }

    analogWrite(B_EN, __speedb);

}

void controlMotor(int x, int y) {

    analogWrite(A_EN, 100);
    analogWrite(B_EN, 100);

    /*
    x = (int)map(x, -100, 100, -255, 255);
    y = (int)map(y, -100, 100, -255, 255);

    boolean sens, dir;
    uint8_t speedL, speedR;

    if (y > 0)
        sens = FORWARD;
    if (y < 0) {
        sens = BACKWARD;
        y = 255 + y;
    }

    if (x > 0)
        dir = RIGHT;
    if (x < 0) {
        dir = LEFT;
        x = 255 + x;
    }

    if (dir == LEFT) {
        speedL = x - y;
        speedR = x + y;
    } else {
        speedL = x + y;
        speedR = x - y;
    }

    Serial.print(speedL);
    Serial.print(" ");
    Serial.println(speedR);

    if (sens == FORWARD) {
        digitalWrite (A_PH, HIGH);
        digitalWrite (B_PH, HIGH);
    } else {
        digitalWrite (A_PH, LOW);
        digitalWrite (B_PH, LOW);
    }

    if (speedL < 0) {
        digitalWrite (A_PH, LOW);
        speedL = speedL*-1;
    }

    if (speedR < 0) {
        digitalWrite (B_PH, LOW);
        speedR = speedR *-1;
    }

    if (speedL > 255)
        speedL = 255;
    if (speedR > 255)
        speedR = 255;

    analogWrite (A_EN, speedL);
    analogWrite (B_EN, speedR);*/

}

void getJoystickState(byte data[8])    {
    int joyX = (data[1]-48)*100 + (data[2]-48)*10 + (data[3]-48);
    int joyY = (data[4]-48)*100 + (data[5]-48)*10 + (data[6]-48);

    joyX = joyX - 200;
    joyY = joyY - 200;

    controlMotor(joyX, joyY);

}

void getButtonState(int bStatus)  {
    switch (bStatus) {
// -----------------  BUTTON #1  -----------------------
        case 'A':
            buttonStatus |= B000001;
            state = AUTO;
            break;
        case 'B':
            buttonStatus &= B111110;
            state = MANU;
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