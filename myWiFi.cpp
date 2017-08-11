/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will print the IP address of your WiFi Shield (once connected)
  to the Serial monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 5.

  If the IP address of your shield is yourAddress:
  http://yourAddress/H turns the LED on
  http://yourAddress/L turns it off

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the Wifi.begin() call accordingly.

  Circuit:
   WiFi shield attached
   LED attached to pin 5

  created for arduino 25 Nov 2012
  by Tom Igoe

  ported for sparkfun esp32
  31.01.2017 by Jan Hendrik Berlin

*/

#include<stdint.h>
int16_t mygo[] = {2, 1, 1000, 100, 2, 3, 4};
int16_t myback[] = {2, 1, -1000, 100, 2, 3, 4};
int16_t origin[] = {1, 1, 0, 100};

#include <WiFi.h>
#include<math.h>
#include"myWiFi.h"
#include"servo.h"
#include"Time.h"
#include"mySD.h"
const char* ssid     = "SSR-NETWORK";
const char* password = "nagatsudaumee2040";
WiFiServer server(80);

void WIFI_Configuration()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void serval() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:

            #include "html.h"
            client.println(html);

            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            //ここに条件式を書けば毎回読み込むことはないので早いし、列の途中で割り込みしてくることがないので美しい。行の途中の割り込みまでの対策はできていない
            char strK[] = "GET /po?name=K";
            char strL[] = "GET /po?name=L";
            char strN[] = "GET /po?name=N";//フォームに数字入力があったら
            char strcL[100];
            currentLine.toCharArray(strcL, 100);
            if (strstr(strcL, strK)) {
              run_K();
            }
            if (strstr(strcL, strL)) {
              run_L();
            }
            if (strstr(strcL, strN)) {
              // N以下の抽出する数字をintに変換,numに代入
              int8_t numofsearch = currentLine.indexOf(strN) + sizeof(strN) - 1;
              int16_t num;
              String currentLine_tmp = currentLine.substring(numofsearch, numofsearch + 20);
              num = currentLine_tmp.toInt();
              run_N(num);
            }
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        //        if (currentLine.endsWith("GET /po?name=K")) {
        //ここに書いておくと改行のたびに呼ばれてよくない
        /*        char str[] = "GET /po?name=K";
                char strcL[100];
                currentLine.toCharArray(strcL, 100);
                if (strstr(strcL, str)) {
                  run_K();
                  Serial.println("yatta yatta!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                }
        */
        /*
                else if (currentLine.endsWith("GET /po?name=-10")) {
                  origin[2] = -1000;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-9")) {
                  origin[2] = -900;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-8")) {
                  origin[2] = -800;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-7")) {
                  origin[2] = -700;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-6")) {
                  origin[2] = -600;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-5")) {
                  origin[2] = -500;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-4")) {
                  origin[2] = -400;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-3")) {
                  origin[2] = -300;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-2")) {
                  origin[2] = -200;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=-1")) {
                  origin[2] = -100;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=0")) {
                  origin[2] = 00;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=15")) {
                  origin[2] = 1500;
                  do_motion(origin);
                }

                else if (currentLine.endsWith("GET /po?name=14")) {
                  origin[2] = 1400;
                  do_motion(origin);
                }

                else if (currentLine.endsWith("GET /po?name=13")) {
                  origin[2] = 1300;
                  do_motion(origin);
                }

                else if (currentLine.endsWith("GET /po?name=12")) {
                  origin[2] = 1200;
                  do_motion(origin);
                }

                else if (currentLine.endsWith("GET /po?name=11")) {
                  origin[2] = 1100;
                  do_motion(origin);
                }

                else if (currentLine.endsWith("GET /po?name=10")) {
                  origin[2] = 1000;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=9")) {
                  origin[2] = 900;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=8")) {
                  origin[2] = 800;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=7")) {
                  origin[2] = 700;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=6")) {
                  origin[2] = 600;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=5")) {
                  origin[2] = 500;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=4")) {
                  origin[2] = 400;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=3")) {
                  origin[2] = 300;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=2")) {
                  origin[2] = 200;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=1")) {
                  origin[2] = 100;
                  do_motion(origin);
                }
                else if (currentLine.endsWith("GET /po?name=0")) {
                  origin[2] = 0;
                  do_motion(origin);
                }
        */
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void run_K() {
  static uint8_t cnt;
  Serial.printf("ただいま%4d回目のKでしてー", ++cnt);
  appendFile(SD, "/time_get.txt", "ただいま");
  char buff[2] = {0, 0};
  buff[0] = '0' + (char)cnt;
  appendFile(SD, "/time_get.txt", buff);
  appendFile(SD, "/time_get.txt", "回目のKでしてー\n");
  time_get();
  do_motion(mygo);
}

void run_L() {
  static uint8_t cnt;
  Serial.printf("ただいま%4d回目のLでしてー", ++cnt);
  appendFile(SD, "/time_get.txt", "ただいま");
  char buff[2] = {0, 0};
  buff[0] = '0' + (char)cnt;
  appendFile(SD, "/time_get.txt", buff);
  appendFile(SD, "/time_get.txt", "回目のLでしてー\n");
  time_get();
  do_motion(myback);
}

void run_N(int16_t num){
  origin[2] = num*10;
  do_motion(origin);
}

