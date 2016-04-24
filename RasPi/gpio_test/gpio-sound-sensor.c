#include <stdio.h>
#include <wiringPi.h>

//int ledPin = 13;                // Connect LED on pin 13, or use the onboard one
int KEY = 0;                 // Connect Touch sensor on Digital Pin 2

void setup()
{
    //pinMode(ledPin, OUTPUT);      // Set ledPin to output mode
    pinMode(KEY, INPUT);       //Set touch sensor pin to input mode
}

void loop()
{
    if(digitalRead(KEY) == LOW)       //Read Touch sensor signal
        printf("Detected\n");
    //else
     //   printf("LOW\n");
    delay(100);
} 

int main(void)
{
    if (wiringPiSetup() == -1)
        return 1;

    setup();

    while(1)
        loop();
}
