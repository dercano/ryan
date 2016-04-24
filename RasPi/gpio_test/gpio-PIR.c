#include <stdio.h>
#include <wiringPi.h>

# define PIR 1

int main(void)
{
	if(wiringPiSetup() == -1)
		return 1;

	pinMode(PIR, INPUT);

	for(;;)
	{
		if(digitalRead(PIR) == 0)
		{
			//printf("Not Detection\n");
			delay(1000);
		} else {
			printf("Deteced!!\n");
			delay(1000);
		}
	}
	return 0;
}
