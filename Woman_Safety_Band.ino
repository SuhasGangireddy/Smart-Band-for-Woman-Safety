#include <SoftwareSerial.h>
#include<TinyGPS.h>
SoftwareSerial mySerial(9, 10);
SoftwareSerial gpsSerial(4,3);
TinyGPS gps;
float lattitude,longitude;
char msg;
char call;
int num=100;
#include <MPU6050_tockn.h>
#include <Wire.h>
long timer = 0;
MPU6050 mpu6050(Wire);

void setup()
{ gpsSerial.begin(9600);
  mySerial.begin(9600);    
  Serial.begin(9600);
    Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}


void loop()
{
    mpu6050.update();

  if(millis() - timer > 1000){
   
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    timer = millis();
  }
   if (mySerial.available()>0)
 Serial.write(mySerial.read());
 
    while (gpsSerial.available())
  {
    int c = gpsSerial.read();
    if (gps.encode(c))
    {
float slat,slon;
      gps.f_get_position(&slat, &slon);
      Serial.print("Latitude :");
      Serial.println(slat, 6);
      Serial.print("Longitude:");
      Serial.println(slon, 6);
     
    }
  }
  if(mpu6050.getAccX()>1.00)
  {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"xxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
 //  mySerial.println(laty);// The SMS text you want to send
  //delay(100);
   //mySerial.println(lony);// The SMS text you want to send
  //delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  }
}
