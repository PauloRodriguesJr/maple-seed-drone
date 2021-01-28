#include <VirtualWire.h>
#define pinPot A0
#define pinRF  12
#define pinLED 13
#define pinLED_debug 11

//int Buffer = 0; // para  dados recebidos na porta serial 

struct Package{ // O pacote inclui os parâmetros necessarios para caracterizar o envio de dados
  int  valor1 = 0;    // Valor entre 1000 e 2000 que definirá o % de Thrust do BLDC.   
  byte valor2 = 0;
  int  valor3 = 0;   //É o dado utilizado para controle do Servo!(Beta)
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

  Serial.begin(9600);  // starts serial monitor
  Serial.println("Starting... ");
  delay(1000);
  Serial.println("Press any key to start"); 
  while(!Serial.available());  //Só continua quando vc mandar algo!
  Serial.println("Enter a value between 0 and 1024");
  delay(1000);
}

void loop() {
  digitalWrite(pinLED, HIGH);
  if (Serial.available() > 0)
  {
  int buff = Serial.parseInt();
  if(buff<1023){
    //Mostra o valor no serial monitor
    Serial.print("Potenciometro: ");
    Serial.println(buff);
    //Envia o valor para o motor
    int  leitura1 = buff; 
    byte leitura2 = map(leitura1, 0,179, 0, 1023); 
    int  leitura3 = map(leitura1, 0, 1023, 1000, 2000);
  
    pacote.valor1 = leitura1;
    pacote.valor2 = leitura2;
    pacote.valor3 = leitura3;
   
    Serial.println(pacote.valor1);
    analogWrite(pinLED_debug, buff);
    vw_send((uint8_t *)&pacote, sizeof(pacote));
    vw_wait_tx(); 
    digitalWrite(pinLED, LOW);

    }
  }
}
