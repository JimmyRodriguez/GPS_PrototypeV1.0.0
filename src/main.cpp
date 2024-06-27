#include <Arduino.h>
#include <SoftwareSerial.h>
//#include <module/function.hpp>
#include <services/service.Settings.hpp>
#include <services/service.Command.hpp>
#include <services/service.Initialize.hpp>


//Variables Globales
unsigned long leer;
String cadena; 
String strFecha; 
String strLat;
String strLon;
unsigned long tActual, tEsperado = 20000;
char trama[100];
char cFecha[15]; 
char cLon[10]; 
char cLat[10]; 
char datosGPS[100];
int respuesta;
char aux_str[150];
int led = 13;


void setup() {

  pinMode(13,OUTPUT);

  initConfiguration();

  initSIM808();

}

void loop()
{
  if((unsigned long)(millis() - tActual) > tEsperado){
   SIM808.println("AT+CGNSINF");

    if(cLon[0] == '-'){
    
      digitalWrite(led,HIGH);
      strcat(datosGPS, "Fecha: ");
      strcat(datosGPS, cFecha);
      strcat(datosGPS, " Latitud: ");
      strcat(datosGPS, cLat);
      strcat(datosGPS, " Longitud: ");
      strcat(datosGPS, cLon);

      Serial.println(datosGPS);
      memset(datosGPS, '\0', 100);
      digitalWrite(led,LOW);

    }else{
      Serial.println(".............Waiting Data GPS Recolecting................");
    }

    tActual = millis();

  }

  while (SIM808.available() > 0){
    int cont = 0;
    leer = SIM808.read();
    cadena += (char)leer;

    if(leer == '\n'){
      //Serial.print(cadena);
      cadena.toCharArray(trama,100);
      cadena = "";
      char *p = trama;
      char *token;

      while ((token = strtok_r(p, ",", &p)) != NULL )      
      {

        cont = cont + 1;
       
        //  Serial.println(token);

        if(cont == 3){
         strFecha = token;
        }

        if(cont == 4){
          strLat = token;
        }

        if(cont == 5){
          strLon = token;
          break;
        }
      }

    // Serial.println(strFecha);
    // Serial.println( strLat);
    // Serial.println(strLon);
    // delay(2000);

    strFecha.toCharArray(cFecha,15);
    strLat.toCharArray(cLat,10);
    strLon.toCharArray(cLon,10);

    }
  }

}

