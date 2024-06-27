
#include <Arduino.h>

/// @brief 
/// @param  
void sendSMS(message){

    Serial.println("AT");   
    delay(2000);
    Serial.println("AT+CMGF=1");        
    delay(2000);
    Serial.println("AT+CMGS=\"*\"");
    delay(2000);
    Serial.print("Mensaje de prueba"); 
    delay(2000);
    Serial.write(26);           
    while(1);
}