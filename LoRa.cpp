#include "Arduino.h"
#include "LoRa.h"


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
  Serial1.write("mac set nwkskey 0A1B2C3D4E5F0A1B2C3D4E5F0A1B2CBD\r\n");
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("appskey: ");
  Serial1.write("mac set appskey 112233445566778899AABBCCDDEEFFBD\r\n");                                  //Set AppSkey for your device!!!!!!!!!!
  delay(1000);
  while(Serial1.available()) Serial.write(Serial1.read());
  LoRaBlink();
  
  Serial.print("adr: ");
  Serial1.write("mac set adr on\r\n");
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

void LoRa::LoRaSendAndReceive()
{   //delay(20000);
    analogWrite(red, 0);
    analogWrite(blue, 255);
    analogWrite(green, 255);
    Serial.print("Sending: ");
    Serial1.write("mac tx cnf 1 AABBCC\r\n");                       //sended item!!!!!!!!!!
    delay(1000);
    if(Serial1.available()) 
    {
      Serial.write(Serial1.read());                                 //receive ok if sensing ok
      delay(5000);
    }
    while(Serial1.available()) 
    {  
      char rx = Serial1.read();                                     //receive incomming message
      Serial.println(rx); 
      if(rx == '1')
      {
        for(int i=0; i<=10; i++)                                    //blink green of message is received 
        {
          analogWrite(red, 0);
          analogWrite(blue, 255);
          analogWrite(green, 255);
          delay(50);
          analogWrite(red, 255);
          analogWrite(blue, 255);
          analogWrite(green, 255);
          delay(50);
        }
      }     
    } 
  analogWrite(red, 255);
  analogWrite(blue, 0);
  analogWrite(green, 0);
  //delay(500);
}

