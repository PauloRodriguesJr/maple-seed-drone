#include <VirtualWire.h>
#define pinPot A0
#define pinRF  12
#define pinLED 13
#define pinLED_debug 11

//int Buffer = 0; // para  dados recebidos na porta serial 

struct Package{ // O pacote inclui os parâmetros necessarios para caracterizar o envio de dados
  int  valor1 = 0;   //  Range 0- 1023
  byte valor2 = 0;    // no idea yet
  int  valor3 = 0;   // Range 1000 -2000
  };
  
Package pacote; 

void setup() {
  
  vw_set_tx_pin(pinRF);      //Set the digital IO pin to use for transmit data. Defaults to 12.
  
  vw_set_ptt_inverted(true); //By default the PTT pin goes high when the transmitter is enabled. 
                             //This flag forces it low when the transmitter is enabled. Required for the DR3100.                             
  vw_setup(2000);            //Initialise the VirtualWire software, to operate at speed bits per second. 
                             //Call this once in your setup() after any vw_set_* calls.
                             //You must call vw_rx_start() after this before you will get any messages.
  pinMode(pinLED, OUTPUT);
  pinMode(pinLED_debug, OUTPUT);

  Serial.begin(9600);  //Inicia monitor serial, onde serão escritos os dados
  Serial.println("Iniciando... ");
  delay(1500);
  Serial.println("Aperte qualquer tecla para iniciar");
  while(!Serial.available());  //Só continua quando vc mandar algo!
  Serial.println("Envie dados entre 1000 e 2000 para o motor");//Sending messages for the user ,futuro: rotina de decolagem.
  delay(1500);   //Sugestão -Add resposta em  % de feedback transmitido ao moço, só mudar serial  msg
  Serial.println("Insira um valor de 1000 a 2000 de Thrust ");
}

void loop() {
  digitalWrite(pinLED, HIGH);
  //Le o valor do potenciometro
  int measurement_raw = analogRead(pinPot);
  Serial.print("Measurement raw: ");
  Serial.println(measurement_raw);
  //Converte o valor para uma faixa entre 0 e 179
  //int measurement = map(measurement_raw, 0, 179, 0, 1023); //Observar os intervalos de operação, tinha colocado 1000 - 2000!
  //Mostra o valor no serial monitor
  Serial.print("Potentiometer Measurement: ");
  Serial.println(measurement_raw);
  //Envia o valor para o motor

  int  leitura1 = measurement_raw;   //Buffer; 
  byte leitura2 = sizeof(leitura1);//map(leitura1, 0,179, 0, 1023); 
  int  leitura3 = map(measurement_raw, 0, 1023, 1000, 2000); // Dado pro motor

  pacote.valor1 = leitura1;
  pacote.valor2 = leitura2;
  pacote.valor3 = leitura3;
 
  analogWrite(pinLED_debug, measurement_raw);
  vw_send((uint8_t *)&pacote, sizeof(pacote));
  vw_wait_tx(); 
  
  digitalWrite(pinLED, LOW);
  delay(1);
}
