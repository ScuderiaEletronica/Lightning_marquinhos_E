#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define PIN_CAN_CS A15
//#define DEBUG_CAN_ID 1521           // If defined, dump frames sent to this CAN id



MCP_CAN CAN0(PIN_CAN_CS);

/*
 *  Receive and process an incoming CAN frame.  Any known ids will be
 *  decoded and sent to the LCD.
 */
void Variables(int *variable)
{
  uint8_t len,        // Number of bytes received
          rxBuf[8];   // CAN BUS receive buffer
  uint32_t rxId;      // CAN BUS device/arbitration ID

  CAN0.readMsgBuf(&len, rxBuf);
  rxId = CAN0.getCanId();

#ifdef DEBUG_CAN_ID
  if (rxId == DEBUG_CAN_ID) {
    Serial.print(rxId);
    Serial.print(" ");
    uint8_t i;
    for (i = 0; i < 8; i++) {
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
    }
    Serial.println(" !");
  }
#endif

  switch (rxId) {
    case 1520:
      *variable=(           *( uint16_t *) &rxBuf[0]);  // Seconds ECU has been on
      *(variable+1)=(           *( uint16_t *) &rxBuf[6]);  // Engine RPM
      break;

    case 1522:
      *(variable+2)=(           *( int16_t *) &rxBuf[0]);  // Barometric pressure
      *(variable+3)=(           *( int16_t *) &rxBuf[2]);  // Manifold air pressure
      *(variable+4)=(           *( int16_t *) &rxBuf[4]);  // Manifold air temperature
      *(variable+5)=(           *( int16_t *) &rxBuf[6]);  // Coolant temperature
      break;

    case 1523:
      *(variable+6)=(           *( int16_t *) &rxBuf[0]);  // Throttle possition
      *(variable+7)=(           *( int16_t *) &rxBuf[2]);  // Battery voltage
      break;

    case 1524:
      *(variable+8)=(           *( int16_t *) &rxBuf[6]);  // Air density correction
      break;

    case 1525:
      *(variable+9)=(           *( int16_t *) &rxBuf[0]);  // Warmup correction
      break;

    case 1526:
      *(variable+10)=(          *( int16_t *) &rxBuf[2]);  // VE value table/bank 1
      *(variable+11)=(          *( int16_t *) &rxBuf[4]);  // VE value table/bank 2
      break;

    case 1528:
      *(variable+12)=(          *( int16_t *) &rxBuf[2]);  // 'Load'  used for fuel table lookup e.g. equals MAP in Speed-Density
      break;

    case 1551:
      *(variable+14)=(          *(uint8_t *) &rxBuf[0]);  // AFR cyl#1
      break;

    case 1553:
      *(variable+15)=(          *( int8_t *) &rxBuf[6]);  // Current gear selected
      break;

    case 1554:
      *(variable+16)=(          *( int16_t *) &rxBuf[0]);  // Voltage from O2 cyl#1
      break;

    case 1562:
      *(variable+17)=(          *(uint16_t *) &rxBuf[0]);  // Vehicle Speed 1
      break;

    case 1566:
      *(variable+18)=(          *( int16_t *) &rxBuf[4]);  // Injection Timming Angle (primary)
      break;

    case 1572:
      *(variable+19)=(          *(uint16_t *) &rxBuf[6]);  // Average fuel consumption
      break;

    case 1573:
      *(variable+20)=(          *( int16_t *) &rxBuf[0]);  // Fuel pressure 1
      break;

    case 1574:
      *(variable+21)=(          *( int16_t *) &rxBuf[0]);  // Battery current (alternator system)
      break;
  }
}
