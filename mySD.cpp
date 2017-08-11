/*
   Connect the SD card to the following pins:

   SD Card | ESP32
      D2       -
      D3       SS
      CMD      MOSI
      VSS      GND
      VDD      3.3V
      CLK      SCK
      VSS      GND
      D0       MISO
      D1       -
*/
#include<stdint.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "mySD.h"

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  //"Listing directory: %s\n", dirname

  File root = fs.open(dirname);
  if (!root) {
    //"Failed to open directory"
    return;
  }
  if (!root.isDirectory()) {
    //"Not a directory"
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      //"  DIR : "
      //file.name()
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      //"  FILE: "
      //file.name()
      //"  SIZE: "
      //file.size()
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char * path) {
  //"Creating Dir: %s\n", path
  if (fs.mkdir(path)) {
    //"Dir created"
  } else {
    //"mkdir failed"
  }
}

void removeDir(fs::FS &fs, const char * path) {
  //"Removing Dir: %s\n", path
  if (fs.rmdir(path)) {
    //"Dir removed"
  } else {
    //"rmdir failed"
  }
}

void readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  //"Writing file: %s\n", path

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    //"Failed to open file for writing"
    return;
  }
  if (file.print(message)) {
    //"File written"
  } else {
    //"Write failed"
  }
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  //"Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    //Failed to open file for appending"
    Serial.println("failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    //Message appended"
        Serial.println("Append achieved");
  } else {
    //Append failed"
    Serial.println("Append failed");
  }
}

void renameFile(fs::FS &fs, const char * path1, const char * path2) {
  //"Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    //File renamed"
  } else {
    //Rename failed"
  }
}

void deleteFile(fs::FS &fs, const char * path) {
  //Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    //File deleted"
  } else {
    //Delete failed"
  }
}

void testFileIO(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    //   Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    //Failed to open file for reading"
  }


  file = fs.open(path, FILE_WRITE);
  if (!file) {
    //Failed to open file for writing"
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  //  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}

void SD_Configuration() {
  Serial.begin(115200);
  if (!SD.begin()) {
    //"Card Mount Failed"
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    //"No SD card attached"
    return;
  }

  //"SD Card Type: "
  /*  if (cardType == CARD_MMC) {
    } else if (cardType == CARD_SD) {
    } else if (cardType == CARD_SDHC) {
    } else {
    }
  */

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  //("SD Card Size: %lluMB\n", cardSize
  /*
      listDir(SD, "/", 0);
      createDir(SD, "/mydir"
      listDir(SD, "/", 0);
      removeDir(SD, "/mydir"
      listDir(SD, "/", 2);
      writeFile(SD, "/hello.txt", "Hello "
      appendFile(SD, "/hello.txt", "World!\n"
      readFile(SD, "/hello.txt"
      deleteFile(SD, "/foo.txt"
      renameFile(SD, "/hello.txt", "/foo.txt"
      readFile(SD, "/foo.txt"
      testFileIO(SD, "/test.txt"
  */
}

