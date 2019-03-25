#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include "mcp_can.h"
#include "Fonts/FreeMonoBoldOblique12pt7b.h"
#include "Fonts/FreeSerif9pt7b.h"

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
#define spiCSPin 9

//Assigned Messaged Addresses
#define addr1 = 0x700
#define addr2 = 0x701
#define addr3 = 0x702
#define addr4 = 0x703

//Screen display titles
#define msg1 "RPM"
#define msg2 "SPEED"
#define msg3 "TEMP"


Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;

MCP_CAN CAN(spiCSPin);

void setup() {
  Serial.begin(115200);

  Serial.println("RA8875 start");
  /* Initialise the display using 'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_480x272)) {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("CAN BUS Init OK!");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.fillScreen(RA8875_WHITE);
  tft.setFont(&FreeMonoBoldOblique12pt7b);
}

void loop() {
  printTest();
}

void printTest() {
  byte len = 0;
  byte buf[8];
  tft.textMode();
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&len, buf);

    unsigned long canId = CAN.getCanId();
    Serial.println("-----------------------------");
    Serial.print("Data from ID: 0x");
    Serial.println(canId, HEX);

    tft.fillScreen(RA8875_CYAN);
    tft.drawLine(0, 180, 480, 180, RA8875_BLACK);
    tft.drawLine(160, 155, 160, 250, RA8875_BLACK);
    tft.drawLine(320, 155, 320, 250, RA8875_BLACK);
    tft.drawLine(0, 250, 480, 250, RA8875_BLACK);
    tft.textTransparent(RA8875_BLACK);
    tft.textEnlarge(1);
    tft.textSetCursor(55, 150);
    tft.textWrite(msg1);
    tft.textSetCursor(200, 150);
    tft.textWrite(msg2);
    tft.textSetCursor(365, 150);
    tft.textWrite(msg3);

    if (canId == 0x700) {
      String val1 = String(buf[0]);
      String val2 = String(buf[1]);
      String binData = "";
      int dataSize = sizeof(buf)/sizeof(buf[0]);
      for (int i = dataSize - 1; i >= 0; i--) {
        binData += bitRead(buf[1], i);
      }
      Serial.print(binData);
      
      tft.textSetCursor(365, 200);
      tft.print(val1);
      tft.textSetCursor(275, 200);
      tft.print(val2);
    }

    Serial.println();
  }
}
