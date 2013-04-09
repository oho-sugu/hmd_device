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

// Pin Define
// For OLED drive
#define PINRES 7
#define PINCS 8
#define PINDC 9
// For Softpot (Analog)
#define PINSPOT 3
// For Bluetooth
#define PINRxD 2
#define PINTxD 3


