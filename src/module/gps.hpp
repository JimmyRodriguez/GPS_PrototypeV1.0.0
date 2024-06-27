#include <Arduino.h>

void setGPSconnect()
{
  String msgtype = "RMC";

  Serial.print( "AT+CGNSPWR=1\n");
  delay( 1000 );

  Serial.print( "AT+CGNSSEQ=\"" + msgtype + "\"" + "\n" );
  delay( 1000 );

}


String getCoord()
{
  Serial.print( "AT+CGNSINF\n" );
  delay( 1000 );
}

String getCoord2()
{

  char coord[256];
  int i=0;

  
  Serial.print( "AT+CGNSINF\n" );
  delay( 2000 );

  while( Serial.available()!=0 && i<( sizeof(coord) - 1 ) )
  {
   coord[i] = (char)Serial.read();
   i++; 
  }
  coord[i] = '\0';
  
  String result = String(coord);
  String lon = result.substring(36 , 45);
  String lat = result.substring(45 , 56);
  String coordinates = lon + lat;
    
  Serial.println("Result = " + result);
  Serial.println("Longtitude = " + lon);
  Serial.println("Latitude = " + lat);
  Serial.println("Coordinates = " + coordinates);

  return coordinates;
}