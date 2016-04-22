#include <stdio.h>
#include <wiringPi.h>

#define LED1 4 // BCM_GPIO 23

int main (void)
{
    if (wiringPiSetup() == -1)
        return 1;

    pinMode(LED1, OUTPUT);

    for(;;)
    {
        digitalWrite(LED1, 1);
	printf("On\n");
        delay(1000);
        digitalWrite(LED1, 0);
	printf("Off\n");
        delay(1000);
    }

    return 0;
}
