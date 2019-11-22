#include <mcp_can.h>
#include "MCP(ECU).h"

#define PIN_CAN_INT 2                 // interrupt

int variables[21];

void setup() {
  // put your setup code here, to run once:
  CAN0.begin(CAN_500KBPS);
  Serial.begin(9600);
  Serial1.begin(9600);
  
  pinMode(A13, OUTPUT);
  digitalWrite(A13, 1);

  pinMode(A14, OUTPUT);
  digitalWrite(A14, 0);
}

void loop() {
  if (!digitalRead(PIN_CAN_INT)){
    Variables(variables);
  }

  Serial.print(variables[3]);
  Serial1.print(variables[3]);

  Serial.print(variables[4]);
  Serial1.print(variables[4]);

  Serial.print(variables[5]);
  Serial1.print(variables[5]);

  Serial.print(variables[1]);
  Serial1.print(variables[1]);

  Serial.print(variables[17]);
  Serial1.print(variables[17]);

  Serial.print(variables[15]);
  Serial1.print(variables[15]);

  Serial.print(variables[7]);
  Serial1.print(variables[7]);
}
