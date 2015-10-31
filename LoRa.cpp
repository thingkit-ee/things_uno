#include "Arduino.h"
#include "LoRa.h"

static char* getMeHex(char character)
{
  switch(character)
  {
    case 'A':
      return "41";
    case 'B':
      return "42";
    case 'C':
      return "43";
    default:
      return "44";    
  }
}

void LoRa::LoRaConfig()
{
  Serial.print("Reset: ");                                                                                //Device reset
  Serial1.write("sys reset\r\n");
  delay(2000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  delay(1000);                                                                                            //Receive device model
  Serial.print("Device:  ");
  Serial1.write("sys get ver\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("Battery: ");                                                                              //Receive voltage feedback
  Serial1.write("sys get vdd\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("EUI: ");                                                                                  //
  Serial1.write("sys get hweui\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("addr: ");                                                                                 //Set device address for your device!!!!!!!!!!!
  Serial1.write("mac set devaddr 000011BD\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("nwkskey: ");                                                                              //Set NwkSkey key for your device!!!!!!!!!!!
  Serial1.write("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("appskey: ");
  Serial1.write("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");                                  //Set AppSkey for your device!!!!!!!!!!
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("adr: ");
  Serial1.write("mac set adr off\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("Pwr: ");                                                                            
  Serial1.write("mac set pwridx 1\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("Join: ");
  Serial1.write("mac join abp\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  analogWrite(red, 255);
  analogWrite(blue, 0);
  analogWrite(green, 0);
}
void LoRa::LoRaSendAndReceive(String message)
{   
    int messageLength = message.length();
    Serial.print("Sending: ");
    Serial.println(message);
    Serial1.write("mac tx uncnf 1 ");
    
    
    for (int i = 0; i < messageLength; i++)
    {
      Serial1.print(message.charAt(i), HEX);
      LoRaBlink();  
      
    }
    Serial1.write("\r\n");
    LoRaBlinkOff();
    delay(1000);
    

    while(Serial1.available()) 
    {
      char rx = Serial1.read();
      Serial.print(rx);
      if(rx == '1')
      {
        Serial.println("Message received back!");
      }
      delay(10); 
    }

    delay(10000);
    if (!Serial1.available())
      return;

    Serial.println("Got something from GW:");
    while(Serial1.available()) 
    {
      char rx = Serial1.read();
      Serial.print(rx);
      if(rx == '1')
      {
        Serial.println("Message received back2!");
      }     
    }
}

