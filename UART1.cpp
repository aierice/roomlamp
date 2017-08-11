#include<HardwareSerial.h>
#include"UART1.h"
HardwareSerial  Serial1(1);
void UART1_Configuration() {
  Serial1.begin(115200, SERIAL_8N1, 32, 25);//speed,configu,Rx,Tx
}

