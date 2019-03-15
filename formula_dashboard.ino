#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include "mcp_can.h"

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
//#define spiCSPin 10

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;

//MCP_CAN CAN(spiCSPin);

void setup() {
  Serial.begin(115200);

  Serial.println("RA8875 start");
  /* Initialise the display using 'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_480x272)) {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

//  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
//    Serial.println("CAN BUS Init Failed");
//    delay(100);
//  }
  //Serial.println("CAN BUS Init OK!");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.fillScreen(RA8875_WHITE);
  
  tft.textMode();
  
  //  tft.fillCircle(350, 255, 12, RA8875_GREEN);
  //  tft.fillCircle(374, 255, 12, RA8875_MAGENTA);
  //  tft.drawLine(350, 243, 350, 180, RA8875_RED);
  //  tft.drawLine(374, 243, 374, 180, RA8875_BLUE);
  //  tft.drawLine(350, 180, 362, 160, RA8875_BLACK);
  //  tft.drawLine(374, 180, 362, 160, RA8875_BLACK);
  //  tft.drawLine(350, 180, 374, 180, RA8875_BLACK);
}

void loop() {
  printTest();
}

void printTest() {
  byte len = 0;
  byte buf[1];
  tft.textMode();
  
//  if (CAN_MSGAVAIL == CAN.checkReceive()) {
//    CAN.readMsgBuf(&len, buf);
//
//    unsigned long canId = CAN.getCanId();
//    Serial.println("-----------------------------");
//    Serial.print("Data from ID: 0x");
//    Serial.println(canId, HEX);
//
//    if (canId == 0x69) {
//      tft.fillScreen(RA8875_WHITE);
//      for (int i = 0; i < len; i++) {
//        Serial.print(buf[i]);
//        Serial.print("\t first");
//        tft.textMode();
//        tft.textTransparent(RA8875_BLACK);
//        tft.textSetCursor(5, 155);
//        tft.textEnlarge(2);
//        tft.textWrite("1 ");
//      }
//    }
//    else if (canId == 0x420) {
//      tft.fillScreen(RA8875_WHITE);
//      for (int i = 0; i < len; i++) {
//        Serial.print(buf[i]);
//        Serial.print("\t second");
//        tft.textMode();
//        tft.textTransparent(RA8875_BLACK);
//        tft.textSetCursor(100, 155);
//        tft.textEnlarge(3);
//        tft.textWrite("2 ");
//      }
//    }
//    Serial.println();
//  }
}
