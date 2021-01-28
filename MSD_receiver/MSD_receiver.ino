#include <ServoTimer2.h>
#include <VirtualWire.h>
ServoTimer2 ServoMotor;

#define pinRF  11
#define pinLEDdebug  10
#define pinMotor 3
#define pinLEDbase 8

struct Package {
  int valor1;
  byte valor2;
  int valor3;
};

Package pacote; 
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

void setup() {

  pinMode(pinLEDdebug  ,OUTPUT);
  pinMode(pinLEDbase,OUTPUT);
  
  ServoMotor.attach(pinMotor);
//  Serial.begin(9600);  //Inicia monitor serial, onde serão escritos os dados

  //Serial.println("Iniciando");
 // delay(5000);
  vw_set_rx_pin(pinRF);
  vw_setup(2000);   
  vw_rx_start();


  Serial.begin(9600);  //Inicia monitor serial, onde serão escritos os dados
  Serial.println("Iniciando... ");
  delay(1500);
}

void loop() {

  if ( vw_have_message() ) {
    digitalWrite(pinLEDdebug,HIGH);
    vw_get_message(buf, &buflen);
    memcpy(&pacote,&buf,buflen);

    int output = map(pacote.valor1, 0, 179, 1000, 2000);
    Serial.println(output);
  
    ServoMotor.write(output);
    analogWrite(pinLEDdebug,output);
    delay(150);
  }  
}
