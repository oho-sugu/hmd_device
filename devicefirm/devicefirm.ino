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
unsigned int f2i(unsigned int a,unsigned int b,unsigned int c,unsigned int d)
{return 0x0000FFFF & ((a&0xF)<<12 | (b&0xF)<<8 | (c&0xF)<<4 | d&0xF);}

void disptest()
{
  // Color Fill
  OLED.fillRect(0,0,95,63, 0xFFFF);
  delay(5000);
  OLED.fillRect(0,0,95,63, 0xF800);
  delay(5000);
  OLED.fillRect(0,0,95,63, 0x07E0);
  delay(5000);
  OLED.fillRect(0,0,95,63, 0x001F);
  delay(5000);
  OLED.fillRect( 0,0,32,63, 0xF800);
  OLED.fillRect(33,0,64,63, 0x07E0);
  OLED.fillRect(65,0,95,63, 0x001F);
  delay(5000);
  OLED.fillRect( 0,0,95,63, 0x0000);
  
  // Mesh
  OLED.line (  0,  0,  0, 63, 0xFFFF );
  OLED.line ( 10,  0, 10, 63, 0xFFFF );
  OLED.line ( 20,  0, 20, 63, 0xFFFF );
  OLED.line ( 30,  0, 30, 63, 0xFFFF );
  OLED.line ( 40,  0, 40, 63, 0xFFFF );
  OLED.line ( 50,  0, 50, 63, 0xFFFF );
  OLED.line ( 60,  0, 60, 63, 0xFFFF );
  OLED.line ( 70,  0, 70, 63, 0xFFFF );
  OLED.line ( 80,  0, 80, 63, 0xFFFF );
  OLED.line ( 90,  0, 90, 63, 0xFFFF );

  OLED.line (  0,  0, 95,  0, 0xFFFF );
  OLED.line (  0, 10, 95, 10, 0xFFFF );
  OLED.line (  0, 20, 95, 20, 0xFFFF );
  OLED.line (  0, 30, 95, 30, 0xFFFF );
  OLED.line (  0, 40, 95, 40, 0xFFFF );
  OLED.line (  0, 50, 95, 50, 0xFFFF );
  OLED.line (  0, 60, 95, 60, 0xFFFF );

  // Center Circle
  OLED.circle ( 48, 32, 10, 0xFFFF);
  
  delay(5000);
  OLED.fillRect(0, 0, 95, 63, 0x0000);
}

void setup() {
  OLED.init();
  OLED.fillRect(0, 0, 95, 63, 0x0000);
  BlueTooth.init(38400);
}

void loop() {
  unsigned char temp;
  unsigned char d[16];
  
  BlueTooth.waitInitialize();

  BlueTooth.print("you are connected with bt\n\r");

  disptest();
  
  while(1){
    temp = BlueTooth.read();
    switch(temp) {
      case 'I': // INFO
        BlueTooth.print("ok\n\r");
        break;
      case 'D': // DEMO
        disptest();
        BlueTooth.print("ok\n\r");
        break;
      case 'P': // PIXEL
        for(int i = 0;i < 8;i++){
          d[i] = BlueTooth.read();
        }
        OLED.putPixel( f2b(h2i(d[0]), h2i(d[1])),
                       f2b(h2i(d[2]), h2i(d[3])),
                       f2i(h2i(d[4]), h2i(d[5]), h2i(d[6]), h2i(d[7])));
        BlueTooth.print("PixelOK\n\r");
        break;
      case 'L': // LINE
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
      case 'F': // FILLRECT
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
      case 'C': // CIRCLE
        for(int i = 0;i < 10;i++){
          d[i] = BlueTooth.read();
        }
        OLED.circle( f2b(h2i(d[0]), h2i(d[1])),
                       f2b(h2i(d[2]), h2i(d[3])),
                       f2b(h2i(d[4]), h2i(d[5])),
                       f2i(h2i(d[6]), h2i(d[7]), h2i(d[8]), h2i(d[9])));
        BlueTooth.print("CircleOK\n\r");
        break;
      case 'N': // NUMBER
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

