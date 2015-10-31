#include "LoRa.h"

LoRa LoRa_Lib;

 int resistance;
 int oldResistance;
 
void setup() 
{
  while(!Serial);
  Serial.begin(115200);
  Serial1.begin(57600);
  
  LoRa_Lib.LoRaConfig();                                        // Run config
  resistance = analogRead(A1);
  oldResistance = resistance;

   /*   Serial.print("INITIAL ");
    Serial.print(resistance);
    Serial.print(":");
    Serial.println(oldResistance);
    */
}

 
void loop() 
{
  resistance = analogRead(A1);
  if (abs(oldResistance - resistance) > 100 ){
    
    Serial.print("We got a change ");
    Serial.print(resistance);
    Serial.print(":");
    Serial.println(oldResistance);
    
    
    
    String dataToSend = "{A:";
    if ( resistance > 600 ){
      dataToSend += "0";
    } else if (resistance > 500 ){
      dataToSend += "1";
    } else if (resistance > 400 ){
      dataToSend += "2";
    } else if (resistance > 300 ){
      dataToSend += "3";
    } else  {
      dataToSend += "4";
    }
    dataToSend += "}";
    
    LoRa_Lib.LoRaSendAndReceive(dataToSend);       
    oldResistance = resistance;
  }


  delay(10);
}
