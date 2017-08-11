/*

   ESP32 Time Example

   Author:  kerikun11 (Github: kerikun11)
   Date:    2017.02.24

*/

#include <WiFi.h>
#include "esp32-hal-log.h"
#include "config.h"
#include "Time.h"
#include"myWiFi.h"
#include"mySD.h"

void TIME_Configuration() {
  Serial.begin(115200);
  WIFI_Configuration();
  /*  log_i("Connecting to %s", wifi_ssid);
    Serial.printf("Connecting to %s", wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
      log_i("wait...");
      delay(1000);
    }
    log_i("WiFi connected");
  */
  Time.set_time();
}

void time_get() {
  time_t t = time(NULL);
  log_d("Time: %s", ctime(&t));
  Serial.printf("Time: %s\n\r", ctime(&t));
//  char buff[20];
//  ctime(&t).toCharArray(buff, 20);
  appendFile(SD, "/time_get.txt",  ctime(&t));
  appendFile(SD, "/time_get.txt", "ですよー\n");
}

