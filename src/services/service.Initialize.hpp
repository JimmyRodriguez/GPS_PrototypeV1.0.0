#include <SoftwareSerial.h>


void initSIM808(){

    int respuesta = 0;

    if (enviarAT("AT", "OK", 2000) == 0){
        delay(2000);

        while (respuesta == 0) {
            respuesta = enviarAT("AT", "OK", 2000);
            SIM808.println(respuesta);
        }
    }

    while (enviarAT("AT+CREG?", "+CREG: 0,1", 1000) == 0) {
    }

    
    Serial.println("-----------Inicializando Red de Comunicaciones-------------");
    enviarAT("AT+CLIP=1\r", "OK", 1000);
    enviarAT("AT+CMGF=1\r", "OK", 1000);
    enviarAT("AT+CNMI=2,2,0,0,0\r", "OK", 1000);
    Serial.println("----------------------------------------------------------");
    Serial.println();
    Serial.println("-----------------Inicializando GPS---------------------------");
    if(enviarAT("AT+CGNSPWR=1", "OK", 1000) == 1){
        Serial.println("Modulo GPS Activado");
    }
    Serial.println("----------------------------------------------------------");

}