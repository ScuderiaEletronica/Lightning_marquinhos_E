/*
 *  TurboKitten Digital Dashboard
 *
 *  This is an Arduino sketch which receives data from a MegaSquirt via CAN BUS
 *  and displays it on a Nextion LCD panel.
 *
 *  Copyright (C) 2015-2016  Chris "Kai" Frederick
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, see <http://www.gnu.org/licenses/>.
 */


#include <mcp_can.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "nextion.cpp"
#include "tick.cpp"

#define PIN_LCD_RX 5
#define PIN_LCD_TX 4
#define PIN_CAN_CS 9                  // chip select
#define PIN_CAN_INT 2                 // interrupt
//#define DEBUG_CAN_ID 1521           // If defined, dump frames sent to this CAN id
#define HOUSEKEEPING_INTERVAL_MS 200  // How frequently to run watchdog, display refresh, etc
#define HOUSEKEEPING_PHASE_MS 100     // When to start first housekeeping run

#define ADC_PAGE_1_INTERVAL_MS 50     // How frequently to transmit ADC Page 1 data
#define ADC_PAGE_1_PHASE_MS 15        // When to start first ADC Page 1 transmission
#define ADC_PAGE_1_ID 0x20            // Destination CAN ID for Page 1

#define ADC_PAGE_2_INTERVAL_MS 50     // How frequently to transmit ADC Page 2 data
#define ADC_PAGE_2_PHASE_MS 25        // When to start first ADC Page 2 transmission
#define ADC_PAGE_2_ID 0x21            // Destination CAN ID for Page 2

MCP_CAN CAN0(PIN_CAN_CS);
SoftwareSerial lcdstream(PIN_LCD_RX, PIN_LCD_TX);

/*
 *  Set up the gauges.
 *  v0,v1,v2 are guages on the left top; l0,l1,l2 are labels to the right of v0,v1,v2;
 *  v3,v4,v5,v6 are gauges on the top right; l3,l4,l5,l6 are labels to the right of v3,v4,v5,v6;
 *  b0,b1,b2,b3 are along the bottom;
 *  warn is a full-width line of text.
 *  Redlines / yellowlines are specified in raw, unscaled units.
 */
//                                   id,  lid, suffix, scale, decimals, red_low, yellow_low, yellow_high, red_high, ref
NextionObject map_g(&lcdstream,    "v0", "l0",     "",    10,        0,       0,          0,        2600,    2800, 20),
              afr_g(&lcdstream,    "v1", "l1",     "",    10,        1,     100,        105,         150,     155, 100),
              rpm_g(&lcdstream,    "v2", "l2",     "",     1,        0,       0,          0,        6500,    7000, 100),
              vss_g(&lcdstream,    "v3", "l3",     "",     1,        0,  -32768,     -32768,       32767,   32767, 200),
              art_g(&lcdstream,    "v4", "l4",     "",    10,        1,  -32768,     -32768,       32767,   32767, 200),
              spk_g(&lcdstream,    "v5", "l5",     "",    10,        1,  -32768,     -32768,       32767,   32767, 50),
              egt_g(&lcdstream,    "v6", "l6",     "",     1,        0,     500,        700,        1600,    1800, 100),
              clt_g(&lcdstream,    "b0",   "", "cltF",    10,        0,     600,       1500,        2000,    2200, 1010),
              mat_g(&lcdstream,    "b1",   "", "matF",    10,        0,     200,        400,        1400,    1600, 200),
              oit_g(&lcdstream,    "b2",   "", "oilF",     1,        0,  -32768,     -32768,       32767,   32767, 1000),
              bat_g(&lcdstream,    "b3",   "",    "v",    10,        1,     120,        130,         147,     150, 500),
              warn_g(&lcdstream, "warn",   "",     "",     0,        0,       0,          0,           0,       0, 50);

/*
 *  Receive and process an incoming CAN frame.  Any known ids will be
 *  decoded and sent to the LCD.
 */
void handleCANFrame(String *valor)
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
      *valor=(           ntohs(*( uint16_t *) &rxBuf[0]));  // Seconds ECU has been on
      *(valor+1)=(           ntohs(*( uint16_t *) &rxBuf[6]));  // Engine RPM
      break;

    case 1522:
      *(valor+2)=(           ntohs(*( int16_t *) &rxBuf[0]));  // Barometric pressure
      *(valor+3)=(           ntohs(*( int16_t *) &rxBuf[2]));  // Manifold air pressure
      *(valor+4)=(           ntohs(*( int16_t *) &rxBuf[4]));  // Manifold air temperature
      *(valor+5)=(           ntohs(*( int16_t *) &rxBuf[6]));  // Coolant temperature
      break;

    case 1523:
      *(valor+6)=(           ntohs(*( int16_t *) &rxBuf[0]));  // Throttle possition
      *(valor+7)=(           ntohs(*( int16_t *) &rxBuf[2]));  // Battery voltage
      break;

    case 1524:
      *(valor+8)=(           ntohs(*( int16_t *) &rxBuf[6]));  // Air density correction
      break;

    case 1525:
      *(valor+9)=(           ntohs(*( int16_t *) &rxBuf[0]));  // Warmup correction
      break;

    case 1526:
      *(valor+10)=(          ntohs(*( int16_t *) &rxBuf[2]));  // VE value table/bank 1
      *(valor+11)=(          ntohs(*( int16_t *) &rxBuf[4]));  // VE value table/bank 2
      break;

    case 1528:
      *(valor+12)=(          *( int16_t *) &rxBuf[2]);  //'Load'  used for fuel table lookup e.g. equals MAP in Speed-Density
      break;

    case 1551:
      *(valor+14)=(          ntohs(*(uint8_t *) &rxBuf[0]));  // AFR cyl#1
      break;

    case 1553:
      *(valor+15)=(          ntohs(*( int8_t *) &rxBuf[6]));  // Current gear selected
      break;

    case 1554:
      *(valor+16)=(          ntohs(*( int16_t *) &rxBuf[0]));  // Voltage from O2 cyl#1
      break;

    case 1562:
      *(valor+17)=(          ntohs(*(uint16_t *) &rxBuf[0]));  // Vehicle Speed 1
      break;

    case 1566:
      *(valor+18)=(          ntohs(*( int16_t *) &rxBuf[4]));  // Injection Timming Angle (primary)
      break;

    case 1572:
      *(valor+19)=(          ntohs(*(uint16_t *) &rxBuf[6]));  // Average fuel consumption
      break;

    case 1573:
      *(valor+20)=(          ntohs(*( int16_t *) &rxBuf[0]));  // Fuel pressure 1
      break;

    case 1574:
      *(valor+21)=(          ntohs(*( int16_t *) &rxBuf[0]));  // Battery current (alternator system)
      break;
  }
}

void setup()
{
  CAN0.begin(CAN_500KBPS);      // Assumes module with 16MHz clock - use CAN_1000KBPS for 8MHz clock.
  lcdstream.begin(115200);
  lcdstream.print(EOC);         // Terminate any partial command sent before boot
  warn_g.pco("RED");
  Serial.begin(115200);
  Serial.println("Boot");
}

// Refresh all the label values.
void refresh_labels()
{
  map_g.label("MAP kPa");
  afr_g.label("AFR");
  rpm_g.label("RPM");
  art_g.label("AFR trgt");
  vss_g.label("VSS mph");
  spk_g.label("Advance");
  egt_g.label("EGT degF");
}

// Check the watchdog on all gauges.
void check_watchdogs()
{
  map_g.watchdog();
  afr_g.watchdog();
  rpm_g.watchdog();
  art_g.watchdog();
  vss_g.watchdog();
  spk_g.watchdog();
  egt_g.watchdog();
  clt_g.watchdog();
  mat_g.watchdog();
  oit_g.watchdog();
  bat_g.watchdog();
  warn_g.watchdog();
  lcdstream.print("clk.val=0" EOC);  // Reset the Nextion watchdog
}

// Sample ADCs and transmit them to CAN
void can_send_adc(
  uint16_t can_id,     // CAN ID to send sample data
  uint8_t a,           // Analog pin ID
  uint8_t b,           // Analog pin ID
  uint8_t c,           // Analog pin ID
  uint8_t d            // Analog pin ID
  )
{
  uint16_t samples[4];
  samples[0] = htons(analogRead(a));
  samples[1] = htons(analogRead(b));
  samples[2] = htons(analogRead(c));
  samples[3] = htons(analogRead(d));
  CAN0.sendMsgBuf(can_id, 0, 8, (byte *) &samples);
}

void loop()
{
  String valor[22];
  static Tick housekeeping_tick(HOUSEKEEPING_INTERVAL_MS, HOUSEKEEPING_PHASE_MS),
              adc_page_1_tick(    ADC_PAGE_1_INTERVAL_MS,   ADC_PAGE_1_PHASE_MS),
              adc_page_2_tick(    ADC_PAGE_2_INTERVAL_MS,   ADC_PAGE_2_PHASE_MS);

  if (housekeeping_tick.tocked()) {
    refresh_labels();
    check_watchdogs();
  }

  if (adc_page_1_tick.tocked()) {
    can_send_adc(ADC_PAGE_1_ID, A0, A1, A2, A3);
  }

  if (adc_page_2_tick.tocked()) {
    can_send_adc(ADC_PAGE_2_ID, A4, A5, A6, A7); // Note that A6 and A7 don't physically exist on DIP28-based AVRs
  }

  if (!digitalRead(PIN_CAN_INT)) { // CAN frame waiting in receive buffer
    handleCANFrame(valor);
  }
}
