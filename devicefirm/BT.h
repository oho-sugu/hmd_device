#ifndef BT_h
#define BT_h

#include <SoftwareSerial.h>
#define RxD 2
#define TxD 3
 
// Class definition
class BTLib
{
    public:
      BTLib();
      int init(int baudrate);
      char * readLine();
      void print(char str[]);
      int read();
      int available();
      void waitInitialize();
    private:
      bool initialized;
      void setupBlueToothConnection();
      void sendBlueToothCommand(char command[]);
      void CheckOK();

};

#endif

