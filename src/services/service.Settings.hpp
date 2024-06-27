
#include <SoftwareSerial.h>

SoftwareSerial SIM808(7, 8); //Seleccionamos los pines 7 como Rx y 8 como Tx


void initConfiguration(){
    SIM808.begin(9600);
    Serial.begin(9600);
    delay(100);
}
 