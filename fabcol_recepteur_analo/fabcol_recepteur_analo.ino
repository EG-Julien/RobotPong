// Recepteur

#include <SPI.h>
#include "RF24.h"

#define CSN_nRF  10
#define CE_nRF   A0

#ifndef OLD_VERSION
#define A_PH     8
#define A_EN     6
#define B_PH     7
#define B_EN     5 
#define BUZZER   A4
#else
#define A_PH     8
#define A_EN     7
#define B_PH     6
#define B_EN     5 
#define BUZZER   A4
#endif

RF24 radio(CE_nRF, CSN_nRF);

void setup()
{
    // Serial.begin (9600);
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openReadingPipe(1, (const uint8_t*)"SUMOA");
    radio.openWritingPipe((const uint8_t*)"REMOA");

    pinMode (BUZZER, OUTPUT);
    pinMode (A_PH, OUTPUT);
    pinMode (A_EN, OUTPUT);
    pinMode (B_PH, OUTPUT);
    pinMode (B_EN, OUTPUT);

    Serial.begin (9600);

    radio.startListening();
}

/*
UP = 0
 DOWN = 1023
 LEFT = 1023
 RIGHT = 0
 */
#define FORWARD 0
#define BACKWARD 1
#define RIGHT 1
#define LEFT 0

void cmdMotor (uint16_t n)
{
    boolean sens, dir;
    int16_t speedL, speedR;
    uint8_t x =  highByte (n);
    uint8_t y =  lowByte (n);

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

    Serial.print (x);
    Serial.print (" ");
    Serial.println (y);

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



void loop()
{
    uint32_t n;

    if (radio.available())
    {
        radio.read(&n, 4);
        cmdMotor(n);
    }
}



