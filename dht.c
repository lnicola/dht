//  Example program
//  15-January-2012
//  Dom and Gert
//


// Access from ARM Running Linux

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <bcm2835.h>
#include <unistd.h>

#define MAXTIMINGS 100

int take_reading(int pin);
int readDHT(int pin, float *temperature, float *humidity);

int main(int argc, char **argv)
{
  if (!bcm2835_init())
        return 1;

  if (argc != 2) {
	printf("usage: %s GPIOpin#\n", argv[0]);
	printf("example: %s 4 - Read from GPIO #4\n", argv[0]);
	return 2;
  }
  
  int dhtpin = atoi(argv[1]);

  if (dhtpin <= 0) {
	printf("Please select a valid GPIO pin #\n");
	return 3;
  }

  for (int c = 0; c < 5; c++)
  {
      if (take_reading(dhtpin))
          return 0;
  }
  
  return 4;
} // main

int take_reading(int pin)
{
    float t, h;

    if (readDHT(pin, &t, &h))
    {
        printf("%.1f %.1f\n", t, h);
        return 1;
    }

    return 0;
}

int readDHT(int pin, float *temperature, float *humidity) {
  int data[5];
  int counter = 0, cnt = 0;
  int laststate = HIGH;
  int j=0;

  bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);

  bcm2835_gpio_write(pin, HIGH);
  usleep(500000);  // 500 ms
  bcm2835_gpio_write(pin, LOW);
  usleep(20000);

  bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  // wait for pin to drop?
  while (bcm2835_gpio_lev(pin) == 1 && cnt < 20000) {
    usleep(1);
    cnt++;
  }

  if (cnt == 20000)
      return 0;

  // read data!
  for (int i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while ( bcm2835_gpio_lev(pin) == laststate) {
	counter++;
	//nanosleep(1);		// overclocking might change this?
        if (counter == 1000)
	  break;
    }
    laststate = bcm2835_gpio_lev(pin);
    if (counter == 1000) break;

    if ((i>3) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      data[j/8] <<= 1;
      if (counter > 200)
        data[j/8] |= 1;
      j++;
    }
  }

  if ((j >= 39) &&
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    *humidity = (data[0] * 256 + data[1]) / 10.0f;
	*temperature = ((data[2] & 0x7F) * 256 + data[3]) / 10.0f;
    if (data[2] & 0x80)
        *temperature = -*temperature;

    return 1;
  }

  return 0;
} 