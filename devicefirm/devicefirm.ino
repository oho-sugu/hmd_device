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
//#include "SoftpotLib.h"

// Instancialize
OLEDLib OLED = OLEDLib();
BTLib BlueTooth = BTLib();
//SoftpotLib Softpot = SoftpotLib();

unsigned int color = 0;

char h2i(char a)
{
  if ('0' <= a && a <= '9'){
    return a - '0';
  }
  if ('A' <= a && a <= 'F'){
    return a - 'A' + 10;
  }
  return 0;
}

int f2b(int a,int b){return a*10+b;}
int f2i(int a,int b,int c,int d){return a*0xFFF+b*0xFF+c*0xF+d;}

void setup() {
  OLED.init();
  OLED.fillRect(0, 0, 95, 63, 0x0000);
  BlueTooth.init(38400);
}

void loop() {
  unsigned char temp;
  unsigned char d[16];
  
  BlueTooth.waitInitialize();

  BlueTooth.print("You are Connected with BT\n\r");
  
  while(1){
    temp = BlueTooth.read();
    switch(temp) {
      case 'P':
        for(int i = 0;i < 8;i++){
          d[i] = BlueTooth.read();
        }
        OLED.putPixel( f2b(h2i(d[0]), h2i(d[1])),
                       f2b(h2i(d[2]), h2i(d[3])),
                       f2i(h2i(d[4]), h2i(d[5]), h2i(d[6]), h2i(d[7])));
        BlueTooth.print("PixelOK\n\r");
        break;
      case 'L':
        for(int i = 0;i < 12;i++){
          d[i] = BlueTooth.read();
        }
        OLED.line( f2b(h2i(d[0]), h2i(d[1])),
                   f2b(h2i(d[2]), h2i(d[3])),
                   f2b(h2i(d[4]), h2i(d[5])),
                   f2b(h2i(d[6]), h2i(d[7])),
                   f2i(h2i(d[8]), h2i(d[9]), h2i(d[10]), h2i(d[11])));
        BlueTooth.print("LineOK\n\r");
        break;
      case 'F':
        for(int i = 0;i < 12;i++){
          d[i] = BlueTooth.read();
        }
        OLED.fillRect( f2b(h2i(d[0]), h2i(d[1])),
                       f2b(h2i(d[2]), h2i(d[3])),
                       f2b(h2i(d[4]), h2i(d[5])),
                       f2b(h2i(d[6]), h2i(d[7])),
                       f2i(h2i(d[8]), h2i(d[9]), h2i(d[10]), h2i(d[11])));
        BlueTooth.print("FRectOK\n\r");
        break;
      case 'C':
        for(int i = 0;i < 10;i++){
          d[i] = BlueTooth.read();
        }
        OLED.circle( f2b(h2i(d[0]), h2i(d[1])),
                       f2b(h2i(d[2]), h2i(d[3])),
                       f2b(h2i(d[4]), h2i(d[5])),
                       f2i(h2i(d[6]), h2i(d[7]), h2i(d[8]), h2i(d[9])));
        BlueTooth.print("CircleOK\n\r");
        break;
      case 'N':
        for(int i = 0;i < 16;i++){
          d[i] = BlueTooth.read();
        }
        OLED.drawNumbers( f2b(h2i(d[0]), h2i(d[1])),
                          f2b(h2i(d[2]), h2i(d[3])),
                          f2i(h2i(d[4]), h2i(d[5]), h2i(d[6]), h2i(d[7])),
                          f2i(h2i(d[8]), h2i(d[9]), h2i(d[10]), h2i(d[11])),
                          f2i(h2i(d[12]), h2i(d[13]), h2i(d[14]), h2i(d[15])));
        BlueTooth.print("NumberOK\n\r");
        break;
      default:
        break;
    }
  }
}

