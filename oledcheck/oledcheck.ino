#include <SPI.h>

const int RESPIN = 7;
const int CSPIN = 8;
const int DCPIN = 9;

int color = 0;

void writeRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int dot)
{
  int i;

  digitalWrite(DCPIN, LOW);
  digitalWrite(CSPIN, LOW);
  
  SPI.transfer(0x15);  // set col address
  SPI.transfer(x1);
  SPI.transfer(x2);
  SPI.transfer(0x75);  // set row address
  SPI.transfer(y1);
  SPI.transfer(y2);
  digitalWrite(CSPIN, HIGH);

  digitalWrite(DCPIN, HIGH);
  digitalWrite(CSPIN, LOW);
  for(i=0; i<((x2-x1+1)*(y2-y1+1)+1); i++) {
    SPI.transfer((unsigned char)((dot >> 8) & 0x00FF));
    SPI.transfer((unsigned char)(dot & 0x00FF));
  }

  digitalWrite(CSPIN, HIGH);
}

void setup() {
  // Digital Output Setting
  pinMode(RESPIN, OUTPUT);
  pinMode(CSPIN, OUTPUT);
  pinMode(DCPIN, OUTPUT);
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  //SPI.setClockDivider(SPI_CLOCK_DIV4);
  
  delay(200);
  digitalWrite(DCPIN, LOW);
  digitalWrite(CSPIN, LOW);
  digitalWrite(RESPIN, LOW);
  delay(200);
  digitalWrite(RESPIN, HIGH);
  delay(200);

  // start oled init
  SPI.transfer(0xAE);  // display off
  delay(100);

  SPI.transfer(0x75);  // set row address
  SPI.transfer(0x00);  // start 0
  SPI.transfer(0x3F);  // end 63
  SPI.transfer(0x15);  // set col address
  SPI.transfer(0x00);  // start 0
  SPI.transfer(0x5F);  // end 95

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

}

void loop() {
  writeRect(0, 0, 95, 63, color);
  color+=16;
}

