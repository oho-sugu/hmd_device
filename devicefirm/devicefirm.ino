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
// For Bluetooth
#include <SoftwareSerial.h>

// My Lib
#include "OLEDLib.h"
#include "BT.h"
#include "SoftpotLib.h"

// Instancialize
OLEDLib OLED = OLEDLib();
BTLib BlueTooth = BTLib();
SoftpotLib Softpot = SoftpotLib();

void setup() {
  OLED.init();
  OLED.fillRect(0, 0, 95, 63, 0x0000);
//  BlueTooth.init(38400);
}

void loop() {
  OLED.drawNumbers(10,10,Softpot.read(),0xffff,0x0000);
}

