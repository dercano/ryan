#include <stdio.h>
#include <wiringPi.h>

int KEY = 2;                 // Connect Touch sensor on Digital Pin 2

void setup()
{
    pinMode(KEY, INPUT);       //Set touch sensor pin to input mode
}

void loop()
{
    if(digitalRead(KEY) == HIGH)       //Read Touch sensor signal
    {
        printf("Touched!\n");
    }
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
