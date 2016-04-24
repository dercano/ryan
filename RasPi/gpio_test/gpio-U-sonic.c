#include <stdio.h>
#include <wiringPi.h>

#define TRIG 4
#define ECHO 3

int main(void)
{
    int distance=0;
    int pulse=0;

	if( wiringPiSetup() == -1)
		return 1;

	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	for(;;)
	{
		printf("Send TRIG\n");
		digitalWrite(TRIG, LOW);
		usleep(2);
		digitalWrite(TRIG, HIGH);
		usleep(20);

		digitalWrite(TRIG, LOW);

		while(digitalRead(ECHO) == LOW);
		long startTime = micros();
		while(digitalRead(ECHO) == HIGH);
		long travelTime = micros() - startTime;

		int distance = travelTime / 58;
		printf("Distance: %d cm\n", distance);
		delay(100);
	}
}
