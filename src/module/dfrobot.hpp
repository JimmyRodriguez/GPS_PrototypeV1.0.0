#include <library/DFRobot_SIM808/src/DFRobot_SIM808.h>

  //Mobile phone number, need to change
  #define PHONE_NUMBER "+50242120098"  

  //The content of messages sent
  #define MESSAGE  "hello,world"

  DFRobot_SIM808 sim808(&Serial);

  void setting() {
    //mySerial.begin(9600);
    Serial.begin(19200);

   //******** Initialize sim808 module *************
    while(!sim808.init()) {
        delay(1000);
        Serial.print("Sim808 init error\r\n");
    }  
    Serial.println("Sim808 init success");
    Serial.println("Start to send message ...");
    
    if( sim808.attachGPS()){
    Serial.println("Open the GPS power success");
    }
 }
  
  void getData() {
    if (sim808.getGPS()) {
        sim808.sendSMS(PHONE_NUMBER,(sim808.GPSdata.minute)); 
        Serial.print(sim808.GPSdata.year); 
        Serial.print("/");
        Serial.print(sim808.GPSdata.month);
        Serial.print("/");
        Serial.print(sim808.GPSdata.day);
        Serial.print(" ");
        Serial.print(sim808.GPSdata.hour);
        Serial.print(":");
        Serial.print(sim808.GPSdata.minute);
        Serial.print(":");
        Serial.print(sim808.GPSdata.second);
        Serial.print(":");
        Serial.println(sim808.GPSdata.centisecond);
        Serial.print("latitude :");
        Serial.println(sim808.GPSdata.lat);
        Serial.print("longitude :");
        Serial.println(sim808.GPSdata.lon);
        Serial.print("speed_kph :");
        Serial.println(sim808.GPSdata.speed_kph);
        Serial.print("heading :");
        Serial.println(sim808.GPSdata.heading);
        Serial.print("altitude :");
        Serial.println(sim808.GPSdata.altitude);
        Serial.println();
        
        //************* Turn off the GPS power ************
        sim808.detachGPS();
        }  
  }