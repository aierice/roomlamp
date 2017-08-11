#include"UART1.h"
#include"mySD.h"
#include"servo.h"
#include"myWiFi.h"
#include"Time.h"

void setup() {
  Serial.begin(115200);
  UART1_Configuration();
  SD_Configuration();
  WIFI_Configuration();
  TIME_Configuration();
  torque_on();
  time_get();
//  deleteFile(SD, "/time_get.txt");
  writeFile(SD, "/time_get.txt", "Hello\n");
}

void loop() {
  serval();
}
