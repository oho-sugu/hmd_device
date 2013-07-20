/*
 * Bluetooth routine for device
 *
 * Author Suguru Oho
 * Since 2013/04/15
 * 
 * This file is Bluetooth routines of firmware for my HMD device.
 * 
 */

#include "Arduino.h"
#include "BT.h"

SoftwareSerial blueToothSerial(RxD,TxD);

BTLib::BTLib()
{
  initialized = false;
}

int BTLib::init(int baudrate)
{
  // Bluetooth Setup
  // Digital Output Setting
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  
  // init done flag set
  initialized = true;

  return 0;
}

void BTLib::waitInitialize()
{
  unsigned char temp;

  while(temp!='4')  {
    temp=blueToothSerial.read(); 
  }
}

void BTLib::setupBlueToothConnection()
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
void BTLib::CheckOK()
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
 
void BTLib::sendBlueToothCommand(char command[])
{
    blueToothSerial.print(command);
    CheckOK();
}

char * BTLib::readLine(){
  char temp;
  char str[30];
  int counter = 0;
  
  while(1){
    str[counter] = blueToothSerial.read();
    
    if(counter > 0 && str[counter-1] == 0x0D && str[counter] == 0x0A){
      break;
    }
    counter++;
    if(counter >= 29){
      break;
    }
  }
  
  // Terminate by NULL
  str[counter] = 0x00;
  return str;
}

void BTLib::print(char str[]){
  blueToothSerial.print(str);
}

int BTLib::read(){
  while(1){
    if(blueToothSerial.available()){
      return blueToothSerial.read();
    }
  }
}

int BTLib::available(){
  return blueToothSerial.available();
}

