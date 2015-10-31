#include "LoRa.h"

LoRa LoRa_Lib;

void setup() 
{
  while(!Serial);
  Serial.begin(115200);
  Serial1.begin(57600);
  
  LoRa_Lib.LoRaConfig();                                        // Run config
}

void loop() 
{
  int buttonValue = analogRead(A1);
    //Serial.println(buttonValue); 
  if(buttonValue == 0)
  {
    LoRa_Lib.LoRaSendAndReceive();                              // Make a new ping 
  }
}


