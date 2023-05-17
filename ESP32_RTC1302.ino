#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(21, 22, 23); // Pines IO, SCLK, CE del RTC DS1302
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(57600); // Inicia la comunicación serial con una velocidad de 57600 baudios
  Serial.print("CONFIGURACIÓN INICIAL ");
  Serial.print(__DATE__); // Imprime la fecha de compilación del programa
  Serial.println(__TIME__); // Imprime la hora de compilación del programa
  
  Rtc.Begin(); // Inicia la comunicación con el RTC DS1302
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__); // Obtiene la fecha y hora de compilación del programa
  printDateTime(compiled); // Imprime la fecha y hora de compilación
  Serial.println();
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); // Obtiene la fecha y hora actual del RTC
  printDateTime(now); // Imprime la fecha y hora actual
  Serial.println();
  
  if (!now.IsValid()) { // Verifica si la fecha y hora actual son válidas
    Serial.println("ERROR EN FECHA Y HORA");
  }
  
  delay(1000); // Espera 1 segundo
}

void printDateTime(const RtcDateTime& dt) {
  char datestring[20];
  snprintf_P(datestring,
              sizeof(datestring),
              PSTR("%02u:%02u:%02u %02u/%02u/%04u"),
              dt.Hour(), dt.Minute(), dt.Second(), // Hora, minutos, segundos
              dt.Day(), dt.Month(), dt.Year()); // Día, mes, año
  
  Serial.println(datestring); // Imprime la fecha y hora en el formato HH:MM:SS DD/MM/YYYY
}
