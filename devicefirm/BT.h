#ifndef BT_h
#define BT_h

#include <SoftwareSerial.h>
#define RxD 2
#define TxD 3
 
#define DEBUG_ENABLED  1

// Class definition
class BTLib
{
    public:
      BTLib();
      int init(int baudrate);
      unsigned char * readLine();
      void print(char str[]);
      int available();
    private:
      bool initialized;
      void setupBlueToothConnection(int baudrate);
      void sendBlueToothCommand(char command[]);
      void CheckOK();

};

#endif

