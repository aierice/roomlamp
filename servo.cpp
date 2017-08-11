#include<HardwareSerial.h>
#include<stdint.h>
#include"servo.h"
#include"UART1.h"

void torque_on() {
  uint8_t sendbuf[100];
  sendbuf[0] = ( int8_t) 0xFA; //Header
  sendbuf[1] = ( int8_t) 0xAF;
  sendbuf[2] = ( int8_t) 0x00; //ID  :keep 0
  sendbuf[3] = ( int8_t) 0x00; //Flag  :keep 0
  sendbuf[4] = ( int8_t) 0x24; //Address num of torque on
  sendbuf[5] = ( int8_t) 0x02; //Length
  sendbuf[6] = ( int8_t) 0x01; //num of motion
  int i;
  for ( i = 1; i <= sendbuf[6]; i++) {
    sendbuf[5 + i * 2] = ( int8_t) i; //VID
    sendbuf[6 + i * 2] = ( int8_t) 0x01; //torque on
  }
  uint8_t checksum = 0;
  for ( i = 2; i <= 6 + 2 * sendbuf[6]; i++) {
    checksum = checksum ^ sendbuf[i];
  }
  sendbuf[7 + 2 * sendbuf[6]] = checksum;
  //  for(i = 0;i <= 7 + 2 * sendbuf[6];i++){
  //  Serial1.write(*(sendbuf+i))
  Serial1.write(sendbuf, 7 + 2 * sendbuf[6] + 1);
  //  }
}



void do_motion( int16_t *motion) {
  uint8_t sendbuf[1000];
  sendbuf[0] = ( int8_t) 0xFA;  //ロングパケットでは固定
  sendbuf[1] = ( int8_t) 0xAF;  //ロングパケットでは固定
  sendbuf[2] = ( int8_t) 0x00;  //ロングパケットでは固定
  sendbuf[3] = ( int8_t) 0x00;  //ロングパケットでは固定
  sendbuf[4] = ( int8_t) 0x1E;  //ロングパケットでは固定
  sendbuf[5] = ( int8_t) 0x05;  //各要素の数の合計。VID(ID)+位置指定+時間指定=5
  sendbuf[6] = ( int8_t) motion[0]; //モーターの数
  uint16_t i = 0;
  int8_t checksum = 0;
  for ( i = 0; i < motion[0]; i++) { //移動
    sendbuf[ 7 + i * 5] = ( int8_t) motion[1 + i * 3]; //IDの指定
    sendbuf[ 8 + i * 5] = ( int8_t) ((( int16_t)motion[2 + i * 3])  & 0xFF); //位置
    sendbuf[ 9 + i * 5] = ( int8_t) ((( int16_t)motion[2 + i * 3])  >> 8);
    sendbuf[10 + i * 5] = ( int8_t) ((( int16_t)motion[3 + i * 3])  & 0xFF);
    sendbuf[11 + i * 5] = ( int8_t) ((( int16_t)motion[3 + i * 3])  >> 8); //時間
  }
  checksum = 0;
  for ( i = 2; i <= 6 + 5 * motion[0]; i++) {
    checksum = checksum ^ sendbuf[i];
  }
  sendbuf[ 7 + 5 * motion[0]] = ( int8_t)checksum;
  Serial1.write(sendbuf, 7 + 5 * motion[0] + 1);
}

