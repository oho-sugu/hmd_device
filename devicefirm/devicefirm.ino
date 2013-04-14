/*
 * Firmware for device
 *
 * Author Suguru Oho
 * Since 2013/04/10
 * 
 * This file is entry point / main program of firmware for my HMD device.
 * 
 *
 */

// Include Space
// For OLED drive
#include <SPI.h>
#include "OLEDLib.h"
// For Bluetooth
#include <SoftwareSerial.h>

// Pin Define
// For OLED drive
#define PINRES 7
#define PINCS 8
#define PINDC 9
// For Softpot (Analog)
#define PINSPOT 1
// For Bluetooth
#define PINRxD 2
#define PINTxD 3

OLEDLib OLED = OLEDLib(PINRES, PINCS, PINDC);
unsigned int color = 0;

void setup() {
  OLED.init();
  OLED.fillRect(0, 0, 95, 63, 0x0000);
}

void loop() {
  int i;
  for(int i = 0;i<10;i++){
    OLED.drawNumber(10+i*4,10,i,0xffff,0x000f);
  }
  color += 16;
}

