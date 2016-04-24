#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <error.h>

#define dht_dpin  23

/* DHT11 define information & variable & functions ----------------------------*/
// 1wire DHT error status
typedef enum
{
    FAIL   = 0x00,
    PASS = 0x01,
    TIME_OUT_1 = 0xE1,
    TIME_OUT_2 = 0xE2,
    TIME_OUT_3 = 0xE3,
    TIME_OUT_4 = 0xE4,
    TIME_OUT_5 = 0xE5,
    ERROR_CHECK_SUM = 0xC1
} DHT11_Status;

// 1wire DHT data line status
#define LOW     0
#define HIGH        1

// DHT11 read function
int Read_DHT11(void);

// DHT11 data -> 40bit
#define MAX_BIT     40
// [0] : 8bit integral RH data
// [1] : 8bit decimal RH data
// [2] : 8bit integral T data
// [3] : 8bit decimal T data
// [4] : 8bit check sum

uint8_t dht11_val[5];

// MCU Sends out Start Signal to DHT
int StartSignal2DHT(void)
{
    uint8_t counter;

    pinMode(dht_dpin,OUTPUT);

    // 1wire init- to HIGH
    digitalWrite(dht_dpin,HIGH);
    delay(1);   

    // MCU sends out start siganal and pull down voltage for at least 18ms to let DHT11 detect the signal
    digitalWrite(dht_dpin,LOW);
    delay(18);

    // MCU pulls up voltage and waits for DHT response(20~40us)
    digitalWrite(dht_dpin,HIGH);
    pinMode(dht_dpin,INPUT);

    // check : high -> low
    counter = 0;
    while (digitalRead(dht_dpin)  == HIGH)
    {
        // about 3us x 14 = 42us
        delayMicroseconds(1);
        counter++;
        if (counter >= 255) return TIME_OUT_1;
    }

    // DHT sends out response signal & keeps it for 80us
    // check : low -> high
    counter = 0;
    while (digitalRead(dht_dpin)  == LOW)
    {
        // about 3us x 27 = 81us
        delayMicroseconds(1);
        counter++;
        if (counter >= 255) return TIME_OUT_2;
    }

    // DHT pulls up voltage & keeps it for 80us
    // check : high -> low
    counter = 0;
    while (digitalRead(dht_dpin)  == HIGH)
    {
        // about 3us x 27 = 81us
        delayMicroseconds(1);
        counter++;
        if (counter >= 255) return TIME_OUT_3;
    }
    return PASS;
}

int Read_DHT11(void)
{
    uint8_t counter;
    uint8_t i, check_sum = 0;

    // init-
    memset(dht11_val, 0, sizeof(dht11_val));

    // Start data transmission
    for (i = 0; i < MAX_BIT; i++)
    {
        // Start to transmit 1-bit data (50us)
        counter = 0;
        while (digitalRead(dht_dpin)  == LOW)
        {
            // about 3us x 17 = 51us
            delayMicroseconds(1);
            counter++;
            if (counter >= 255) return TIME_OUT_4;
        }

        // 26-28us voltage-length means data "0"
        // 70us voltage-length means 1-bit data "1"
        counter = 0;
        while (digitalRead(dht_dpin) == HIGH)
        {
            // about 3us x 24 = 72us
            delayMicroseconds(1);
            counter++;
            if (counter >= 255)     return TIME_OUT_5;
        }

        // load data
        dht11_val[i / 8] <<= 1;
        if (counter > 16)
        {
            dht11_val[i / 8] |= 1;
        }
    }

    // check sum
    check_sum = dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3];

    if (check_sum != dht11_val[4])  return ERROR_CHECK_SUM;
    else return PASS;
}

int main(void)
{
    int count=10, rtCode;

    if(wiringPiSetupGpio() == -1) return;

    while (count--)
    {
        StartSignal2DHT();
        rtCode = Read_DHT11();
        printf("[%d] ",count);   
        switch (rtCode) 
        {
            case TIME_OUT_1:
                printf("DHT start condition 1 not met. \n");            
                break;
            case TIME_OUT_2:
                printf("DHT sends out response signal & keeps it for 80us Error!!.. \n");
                break;
            case TIME_OUT_3:
                printf("DHT pulls up voltage & keeps it for 80us Error!!..\n");         
                break;
            case TIME_OUT_4:
                printf("Start to transmit 1-bit data (50us) Error!!.. \n");
                break;
            case TIME_OUT_5:
                printf("DHT Data Indication Error!!... \n");
                break;      
            case ERROR_CHECK_SUM:
                printf("Check Sum Error!!...\n");   
                break;          
            case PASS:
                printf("RH:%d.%d%%d.%d'C\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);
                break;
        }
        delay(1000);
    }
    return 0;
}
