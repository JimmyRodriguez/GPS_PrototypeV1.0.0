#include <SoftwareSerial.h>

SoftwareSerial SIM808(7, 8);


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

void initSIM808(){

    SIM808.begin(9600);
    Serial.begin(9600);
    delay(100);

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

    Serial.println("Inicializando Red de Comunicaciones");
    enviarAT("AT+CLIP=1\r", "OK", 1000);
    enviarAT("AT+CMGF=1\r", "OK", 1000);
    enviarAT("AT+CNMI=2,2,0,0,0\r", "OK", 1000);

    Serial.println("Inicializando GPS");

    if(enviarAT("AT+CGNSPWR=1", "OK", 1000) == 1){
        Serial.println("GPS Activado");
    }

}
