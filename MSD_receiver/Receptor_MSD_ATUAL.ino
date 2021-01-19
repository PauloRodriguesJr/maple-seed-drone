#include <ServoTimer2.h>
#include <VirtualWire.h>
ServoTimer2 ServoMotor;

#define pinRF  11
#define pinLed 10
#define pinMotor 3
#define pinLEDbase 13

struct tipoPacote {
  int valor1;
  byte valor2;
  int valor3;
};

tipoPacote pacote; 
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

void setup() {

  pinMode(pinLed,OUTPUT);
  pinMode(pinLEDbase,OUTPUT);
  
  ServoMotor.attach(pinMotor);
//  Serial.begin(9600);  //Inicia monitor serial, onde serão escritos os dados

  //Serial.println("Iniciando");
 // delay(5000);
  vw_set_rx_pin(pinRF);
  vw_setup(2000);   
  vw_rx_start();
}

void loop() {

  if ( vw_have_message() ) {
    vw_get_message(buf, &buflen);
    memcpy(&pacote,&buf,buflen);

  
  int var_gamb = map(pacote.valor1, 0, 256, 1000, 2000);
  Serial.println(var_gamb);
  
  analogWrite(pinLed,var_gamb);
  
    ServoMotor.write(var_gamb);
  }  
}
