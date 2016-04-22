#include <stdio.h>
#include <wiringPi.h>

#define SW      1        // BCM_GPIO 18

#define LED1    4       // BCM_GPIO 23
#define LED2    5       // BCM_GPIO 24

int main (void)
{
  if (wiringPiSetup() == -1)
    return 1 ;

  pinMode(SW, INPUT);

  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);

  for(;;)
  {
    digitalWrite(LED1, 0);    // Off
 //   digitalWrite(LED2, 0);    // Off
    //printf("LED Off\n");

    if(digitalRead(SW) == 0)
    {
      printf("switch == 0 \n");
      digitalWrite(LED1, 1);  // On
      printf("LED On \n");
//      digitalWrite(LED2, 1);  // On
      delay(1000) ;             // mS
    }
  }
  return 0 ;
}
