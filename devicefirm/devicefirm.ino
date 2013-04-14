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
  OLED.fillRect(0, 0, 95, 63, 0xffff);
}

void loop() {
  int x0 = random(0,95);
  int y0 = random(0,63);
  int x1 = random(0,95);
  int y1 = random(0,63);
  OLED.line(x0,y0,x1,y1,color);
  color += 16;
}

