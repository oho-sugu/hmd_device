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
unsigned int count = 0;
unsigned int state = 0;

void setup() {
  OLED.init();
  OLED.fillRect(0, 0, 95, 63, 0x0000);
}

void loop() {
  switch(state){
    case 0:
      DEMOFill();
      break;
    case 1:
      DEMOPixel();
      break;
    case 2:
      DEMOLine();
      break;
    case 3:
      DEMOCircle();
      break;
    case 4:
      DEMONumber();
      break;
  }
  count++;
  if(count == 100){
    state = (state+1) % 5;
    count = 0;
    OLED.fillRect(0, 0, 95, 63, 0x0000);
  }
}

void DEMOFill(){
  int x0 = random(0,95);
  int y0 = random(0,63);
  int x1 = random(0,95);
  int y1 = random(0,63);
  OLED.fillRect(x0,y0,x1,y1,color);
  color+=16;
}
void DEMOPixel(){
  int x0 = random(0,95);
  int y0 = random(0,63);
  OLED.putPixel(x0,y0,color);
  color+=16;
}
void DEMOLine(){
  int x0 = random(0,95);
  int y0 = random(0,63);
  int x1 = random(0,95);
  int y1 = random(0,63);
  OLED.line(x0,y0,x1,y1,color);
  color+=16;
}
void DEMOCircle(){
  int x0 = random(0,95);
  int y0 = random(0,63);
  int rad = random(0,30);
  OLED.circle(x0,y0,rad,color);
  color+=16;
}

void DEMONumber(){
  int i,j;
  for(i = 0;i<24;i++){
    for(j = 0;j<10;j++){
      OLED.drawNumber(i*4,j*6+2,(j*10+i)%10,color,0x000f);
    }
  }
  color += 16;
}
