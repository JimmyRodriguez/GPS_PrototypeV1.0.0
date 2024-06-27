#include <SoftwareSerial.h>

int enviarAT(String ATcommand, char* resp_correcta, unsigned int tiempo){
    int x = 0;
    bool correcto = 0;
    char respuesta[100];
    unsigned long anterior;
    memset(respuesta, '\0', 100);
    delay(100);

    while (SIM808.available() > 0) SIM808.read();
    SIM808.println(ATcommand);

    x = 0;

    anterior = millis();

    do
    {
        if(SIM808.available() != 0){
            respuesta[x] = SIM808.read();
            x++;

            if(strstr(respuesta, resp_correcta) != NULL){
                correcto = 1;
            }
        }
    } while ((correcto == 0) && ((millis() - anterior ) < tiempo));
    
    Serial.println(respuesta);

    return correcto;
    
}