#include <SPI.h>
#include <mcp_can.h>

const int spiCSPin = 10;
int ledHIGH    = 1;
int ledLOW     = 0;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");
}

byte stmp1[8] = {0xFF, 0xA, 2, 3, 4, 5, 6, 7};
//unsigned char stmp2[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    
void loop() {   
  Serial.println("In loop");
 
  CAN.sendMsgBuf(0x700, 0, 8, stmp1);
  delay(1000);
//  CAN.sendMsgBuf(0x420, 0, 1, stmp2);
//  delay(1000);
 
}
