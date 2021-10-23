/*  reloj_RTC_lcd7segmentos */
// Librería para manejar fechas y horas utilizando DS3231 RTC conectado via I2C y Wire 
// Basado en el ejemplo ds3231 de la librería
#include <Wire.h>
#include "RTClib.h"

//Librería para manejar el display LCD 7 segmentos x 4
//https://github.com/avishorp/TM1637
#include <Arduino.h>
#include <TM1637Display.h>



// Pines de conexión al módulo de 4 x 7 segmentos(Digital Pins)
#define CLK 2
#define DIO 3

//Inicializo el display
TM1637Display display(CLK, DIO);


uint8_t data[] = { 0x00, 0x00, 0x00, 0x00 };

//Instancio el reloj
RTC_DS3231 rtc;


void setup() {

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //Limpio el display ("apago" todos los segmentos
  display.setBrightness(0x0f);
  display.setSegments(data);
  
}

void loop() {

  DateTime fechahora = rtc.now();

  int hora = fechahora.hour();
  int minutos = fechahora.minute();
  int segundos = fechahora.second();

  if(segundos%2==0)
  {
    display.showNumberDecEx(hora*100+minutos, 0b01000000, true, 4, 0);
  }
  else
  {
    display.showNumberDecEx(hora*100+minutos, 0b00000000, true, 4, 0);
  }

  
  delay(1000);

}
