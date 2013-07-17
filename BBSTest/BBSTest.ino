/*
BluetoothBee Demo Code - Flowcontrol Based Implementation
2010,2011 Copyright (c) Seeed Technology Inc.  All right reserved.
 
Author: Visweswara R      Modify:Joinj
 
This demo code is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
 
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
For more details about the product please check http://www.seeedstudio.com/depot/
 
*/
 
 
/* Upload this sketch to Seeeduino and press reset*/
 
#include <SoftwareSerial.h>
#define RxD 2
#define TxD 3
 
#define DEBUG_ENABLED  1
 
SoftwareSerial blueToothSerial(RxD,TxD);

void setup() 
{ 
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
    pinMode(5,OUTPUT);
    setupBlueToothConnection();
} 
 
void loop() 
{ 
  unsigned char control;
  unsigned char temp;
  while(temp!='4')  {
      temp=blueToothSerial.read(); 
  }
  Serial.println("You are connected");
  blueToothSerial.print("You are connected with BT");      //You can write you BT communication logic here
  while(1)  {
    temp=blueToothSerial.read();
    switch(temp)  {
      case 'O':{while(temp!='N')  {temp=blueToothSerial.read();}  digitalWrite(5,HIGH);blueToothSerial.print("5HIGH");break;}
      case 'S':{while(temp!='H')  {temp=blueToothSerial.read();}  digitalWrite(5,LOW);blueToothSerial.print("5LOW");break;}
      default:break;
    }
  }
} 
 
 
void setupBlueToothConnection()
{
    blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
    delay(1000);
    sendBlueToothCommand("\r\n+STWMOD=0\r\n");
    sendBlueToothCommand("\r\n+STNA=SeeedBluetooth-st\r\n");
    sendBlueToothCommand("\r\n+STAUTO=0\r\n");
    sendBlueToothCommand("\r\n+STOAUT=1\r\n");
    sendBlueToothCommand("\r\n +STPIN=0000\r\n");
    delay(2000); // This delay is required.
    sendBlueToothCommand("\r\n+INQ=1\r\n");
    delay(2000); // This delay is required.
}
 
//Checks if the response "OK" is received
void CheckOK()
{
  char a,b;
  while(1)
  {
    if(blueToothSerial.available())
    {
    a = blueToothSerial.read();
 
    if('O' == a)
    {
      // Wait for next character K. available() is required in some cases, as K is not immediately available.
      while(blueToothSerial.available()) 
      {
         b = blueToothSerial.read();
         break;
      }
      if('K' == b)
      {
        break;
      }
    }
   }
  }
 
  while( (a = blueToothSerial.read()) != -1)
  {
    //Wait until all other response chars are received
  }
}
 
void sendBlueToothCommand(char command[])
{
    blueToothSerial.print(command);
    CheckOK();   
}

