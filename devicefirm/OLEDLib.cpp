/*
 * OLED routine for device
 *
 * Author Suguru Oho
 * Since 2013/04/10
 * 
 * This file is OLED routines of firmware for my HMD device.
 * 
 */

#include "Arduino.h"
#include "OLEDLib.h"
#include <SPI.h>

#define OLEDWIDTH 96
#define OLEDHEIGHT 64

// Font for Hexadecimal
byte OLEDLib::font[240] = {
  0,1,0,1,1,0,0,1,0,0,1,0,0,1,0, //1
  1,1,1,0,0,1,1,1,1,1,0,0,1,1,1, //2
  1,1,1,0,0,1,0,1,1,0,0,1,1,1,1, //3
  1,0,1,1,0,1,1,1,1,0,0,1,0,0,1, //4
  1,1,1,1,0,0,1,1,1,0,0,1,1,1,1, //5
  1,1,1,1,0,0,1,1,1,1,0,1,1,1,1, //6
  1,1,1,0,0,1,0,0,1,0,1,0,0,1,0, //7
  1,1,1,1,0,1,1,1,1,1,0,1,1,1,1, //8
  1,1,1,1,0,1,1,1,1,0,0,1,1,1,1, //9
  1,1,1,1,0,1,1,0,1,1,0,1,1,1,1, //0
  0,1,0,1,0,1,1,0,1,1,1,1,1,0,1, //A
  1,1,0,1,0,1,1,1,1,1,0,1,1,1,1, //B
  1,1,1,1,0,0,1,0,0,1,0,0,1,1,1, //C
  1,1,0,1,0,1,1,0,1,1,0,1,1,1,0, //D
  1,1,1,1,0,0,1,1,0,1,0,0,1,1,1, //E
  1,1,1,1,0,0,1,1,0,1,0,0,1,0,0  //F
};

OLEDLib::OLEDLib(int a_respin, int a_cspin, int a_dcpin)
{
  respin = a_respin;
  cspin = a_cspin;
  dcpin = a_dcpin;
  initialized = false;
}

int OLEDLib::init()
{
  // OLED Setup
  // Digital Output Setting
  pinMode(respin, OUTPUT);
  pinMode(cspin, OUTPUT);
  pinMode(dcpin, OUTPUT);
  
  // SPI Setup
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  delay(200);
  digitalWrite(dcpin, LOW);
  digitalWrite(cspin, LOW);
  digitalWrite(respin, LOW);
  delay(200);
  digitalWrite(respin, HIGH);
  delay(200);

  // start oled init
  SPI.transfer(0xAE);  // display off
  delay(100);

  SPI.transfer(0x75);  // set row address
  SPI.transfer(0x00);  // start 0
  SPI.transfer(OLEDHEIGHT - 1);  // end 63
  SPI.transfer(0x15);  // set col address
  SPI.transfer(0x00);  // start 0
  SPI.transfer(OLEDWIDTH - 1);  // end 95

  SPI.transfer(0xA0); // set remap and data format 0111 0000
  SPI.transfer(0x74);
  SPI.transfer(0xA1); // set display start rom RAM
  SPI.transfer(0x00);
  SPI.transfer(0xA2); // set display offset
  SPI.transfer(0x00);
  SPI.transfer(0xA4); // set display mode
  SPI.transfer(0xA8); // set multiplex ratio
  SPI.transfer(0x3F);
  SPI.transfer(0xAD); // set master configration
  SPI.transfer(0x8F); // external vcc supply selected
  SPI.transfer(0xB0); // set power saving mode
  SPI.transfer(0x1A);
  SPI.transfer(0xB1); // set phase 1 and 2 period adjustment
  SPI.transfer(0x74);
  SPI.transfer(0xB3); // set display clock divide ratio ocillator freq
  SPI.transfer(0xD0);
  SPI.transfer(0x8A); // set second pre-change speed of color A
  SPI.transfer(0x81);
  SPI.transfer(0x8B); // set second pre-change speed of color B
  SPI.transfer(0x82);
  SPI.transfer(0x8C); // set second pre-change speed of color C
  SPI.transfer(0x83);
  SPI.transfer(0xBB); // set pre-change level
  SPI.transfer(0x3E);

  SPI.transfer(0xBE); // set vcomh
  SPI.transfer(0x3E);
  SPI.transfer(0x87); // set master corrent control
  SPI.transfer(0x0F);
  SPI.transfer(0x81); // set contrast control for color A
  SPI.transfer(0x80);
  SPI.transfer(0x82); // set contrast control for color B
  SPI.transfer(0x80);
  SPI.transfer(0x83); // set contrast control for color C
  SPI.transfer(0x80);
  SPI.transfer(0xAF); // display on

  // init done flag set
  initialized = true;
  
  return 0;
}

int OLEDLib::fillRect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
  int i;

  if(!initialized){
    // Error Return
    return 1;
  }

  // normalize coordinate
  if( x1 < x0){
    x0 = x0 ^ x1;
    x1 = x0 ^ x1;
    x0 = x0 ^ x1;
  }
  if( y1 < y0){
    y0 = y0 ^ y1;
    y1 = y0 ^ y1;
    y0 = y0 ^ y1;
  }

  digitalWrite(dcpin, LOW);
  digitalWrite(cspin, LOW);
  
  SPI.transfer(0x15);  // set col address
  SPI.transfer(x0);
  SPI.transfer(x1);
  SPI.transfer(0x75);  // set row address
  SPI.transfer(y0);
  SPI.transfer(y1);
  digitalWrite(cspin, HIGH);

  digitalWrite(dcpin, HIGH);
  digitalWrite(cspin, LOW);

  for(i=0; i<((x1-x0+1)*(y1-y0+1)+1); i++) {
    SPI.transfer((unsigned char)((color >> 8) & 0x00FF));
    SPI.transfer((unsigned char)(color & 0x00FF));
  }

  digitalWrite(cspin, HIGH);
  
  // Normal Return
  return 0;
}

int OLEDLib::putPixel(unsigned int x0, unsigned int y0, unsigned int color)
{
  if(!initialized){
    // Error Return
    return 1;
  }

  digitalWrite(dcpin, LOW);
  digitalWrite(cspin, LOW);
  
  SPI.transfer(0x15);  // set col address
  SPI.transfer(x0);
  SPI.transfer(x0+1);
  SPI.transfer(0x75);  // set row address
  SPI.transfer(y0);
  SPI.transfer(y0+1);
  digitalWrite(cspin, HIGH);

  digitalWrite(dcpin, HIGH);
  digitalWrite(cspin, LOW);

  SPI.transfer((unsigned char)((color >> 8) & 0x00FF));
  SPI.transfer((unsigned char)(color & 0x00FF));

  digitalWrite(cspin, HIGH);
  
  // Normal Return
  return 0;
}

// Code Refered from http://dencha.ojaru.jp/programs_07/pg_graphic_07.html
int OLEDLib::line(int x0, int y0, int x1, int y1, unsigned int color){
    int cx, cy, pos_x, pos_y, i, lim, start, end;
    double e;
    int *p_co1, *p_co2, ddis1, ddis2, dn1, dn2;
    if (adjust_lining_limit(&start, &end, x0, y0, x1, y1, &cx, &cy)<0) return 1;

    int base_axis = (abs(cx)>abs(cy))? 'x' : 'y';
    p_co1 = (base_axis=='x')? &pos_x : &pos_y;
    p_co2 = (base_axis=='x')? &pos_y : &pos_x;
    ddis1 = (base_axis=='x')? 2*cx : 2*cy;
    ddis2 = (base_axis=='x')? 2*cy : 2*cx;
    dn1 = dn2 = 1;
    if (ddis1<0) { dn1=-1; ddis1 = -ddis1; }
    if (ddis2<0) { dn2=-1; ddis2 = -ddis2; }

    pos_x = x0;
    pos_y = y0;

    *p_co1 += dn1* start;
    *p_co2 += dn2* (start*ddis2+ddis1/2) /ddis1;
    e = (ddis1/2 + start*ddis2)%ddis1;

    for(i=start;i<=end;i++){

        putPixel(pos_x, pos_y, color);

        (*p_co1)+=dn1;
        e += ddis2;
        if (e>=ddis1){
            e -= ddis1;
            (*p_co2)+=dn2;
        }
    }
    return 0;
};

// Code Refered from http://dencha.ojaru.jp/programs_07/pg_graphic_07.html
int OLEDLib::adjust_lining_limit(int *p_start, int *p_end, int sx, int sy, int ex, int ey, int *p_cx, int *p_cy){
    int img_lim, img_lim_other, base_lim, other_lim;
    int *p_res, base_co, other_co, tmp, cx, cy;
    cx=*p_cx=ex-sx;
    cy=*p_cy=ey-sy;
    int base_axis = (abs(cx)>abs(cy))? 'x' : 'y';
    *p_start = *p_end = 0;

    if (!cx && !cy) return -1;
    // x,yの長いほうの座標軸をベースにする
    if (base_axis=='x'){    // x 座標ベース
        img_lim = OLEDWIDTH;
        img_lim_other = OLEDHEIGHT;
        base_lim = cx;
        other_lim = cy;
    }
    else{   // y 座標ベース
        img_lim = OLEDWIDTH;
        img_lim_other = OLEDHEIGHT;
        base_lim = cy;
        other_lim = cx;
    }

    for(int i=0;i<2;i++){
        if (i==0) {
            p_res = p_start;
            base_co  = (base_axis=='x')? sx : sy;
            other_co = (base_axis=='x')? sy : sx;
        }
        else if (i==1) {
            p_res = p_end;
            base_co  = (base_axis=='x')? ex : ey;
            other_co = (base_axis=='x')? ey : ex;
            other_lim = -other_lim;
        }

        // x,yの長いほうの座標軸で判定
        if (base_co<0)     *p_res=-base_co;
        if (base_co>=img_lim) *p_res= base_co-img_lim+1;

        // x,yの短いほうの座標軸で判定
        if (!other_lim) continue;
        tmp = other_co + ((*p_res) * (2*other_lim) + abs(base_lim))/(2*base_lim);

        int aim_co;
        if (tmp<0) { aim_co = -other_co; }
        else if (tmp>=img_lim_other) { aim_co = other_co-img_lim_other+1; }
        else continue;  // 範囲内

        tmp = aim_co*2*abs(base_lim)-abs(base_lim);
        *p_res = tmp/abs(2*other_lim);
        if (i==0 && tmp%abs(2*other_lim)) (*p_res)++;
        if (i==1) (*p_res)++;
    }
    *p_end = abs(base_lim) - *p_end;
    return 0;
}

// Code Refered from http://dencha.ojaru.jp/programs_07/pg_graphic_09a1.html
int OLEDLib::circle(unsigned int x0, unsigned int y0, unsigned int radius, unsigned int color)
{
  if(!initialized){
    // Error Return
    return 1;
  }

  int cx, cy, d, dH, dD;
  
  d  = 1 - radius;
  dH = 3;
  dD = 5 - 2 * radius;
  cy = radius;
  
  for(cx = 0; cx <= cy; cx++){
    if(d < 0) {
      d  += dH;
      dH += 2;
      dD += 2;
    } else {
      d  += dD;
      dH += 2;
      dD += 4;
      --cy;
    }
    
    putPixel( cy + x0,  cx + x0, color);
    putPixel( cx + x0,  cy + x0, color);
    putPixel(-cx + x0,  cy + x0, color);
    putPixel(-cy + x0,  cx + x0, color);
    putPixel(-cy + x0, -cx + x0, color);
    putPixel(-cx + x0, -cy + x0, color);
    putPixel( cx + x0, -cy + x0, color);
    putPixel( cy + x0, -cx + x0, color);
    
  }
}

int OLEDLib::drawNumber(unsigned int x0, unsigned int y0, unsigned int number, unsigned int color, unsigned int background)
{
  int i;

  if(!initialized){
    // Error Return
    return 1;
  }
  
  // Range 0-15
  if(number < 0x00 || 0x0F < number){
    // Error Return
    return 1;
  }

  digitalWrite(dcpin, LOW);
  digitalWrite(cspin, LOW);
  
  SPI.transfer(0x15);  // set col address
  SPI.transfer(x0);
  SPI.transfer(x0 + 2);
  SPI.transfer(0x75);  // set row address
  SPI.transfer(y0);
  SPI.transfer(y0 + 4);
  digitalWrite(cspin, HIGH);

  digitalWrite(dcpin, HIGH);
  digitalWrite(cspin, LOW);

  for(i=0; i<16; i++) {
    if(font[number*15+i] == 1){
      SPI.transfer((unsigned char)((color >> 8) & 0x00FF));
      SPI.transfer((unsigned char)(color & 0x00FF));
    } else {
      SPI.transfer((unsigned char)((background >> 8) & 0x00FF));
      SPI.transfer((unsigned char)(background & 0x00FF));
    }
  }

  digitalWrite(cspin, HIGH);
  
  // Normal Return
  return 0;
}

