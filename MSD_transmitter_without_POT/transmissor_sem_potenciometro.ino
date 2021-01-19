#include <VirtualWire.h>
#define pinPot A0
#define pinRF  12    //Para o teste 0,O TRANSMISSOR ESTA OK.
#define pinLED 13
#define pinLED2 11

//int Buffer = 0; // para  dados recebidos na porta serial - Montar vetor de dados... pro pacote =)


struct tipoPacote {     // O pacote inclui os parâmetros necessarios para caracterizar o envio de dados
  int valor1 =0;           // Valor entre 1000 e 2000 que definirá o % de Thrust do BLDC.   
  byte valor2=0;
  int valor3 = 0;       //É o dado utilizado para controle do Servo!(Beta)
  };

tipoPacote pacote; 

void setup() {
  
  vw_set_tx_pin(pinRF);        //Set the digital IO pin to use for transmit data. Defaults to 12.
  
  vw_set_ptt_inverted(true);  //By default the PTT pin goes high when the transmitter is enabled. 
                              //This flag forces it low when the transmitter is enabled. Required for the DR3100.
                             
  vw_setup(2000);          //Initialise the VirtualWire software, to operate at speed bits per second. 
                           //Call this once in your setup() after any vw_set_* calls.
                           //You must call vw_rx_start() after this before you will get any messages.
    pinMode(pinLED, OUTPUT);
    pinMode(pinLED2, OUTPUT);


  Serial.begin(9600);  //Inicia monitor serial, onde serão escritos os dados
  Serial.println("Iniciando... ");
  delay(1500);
  Serial.println("Aperte qualquer tecla para iniciar");
  while(!Serial.available());  //Só continua quando vc mandar algo!
  Serial.println("Envie dados entre 1000 e 2000 para o motor ");//Sending messages for the user ,futuro: rotina de decolagem.
  delay(1500);                 //Sugestão -Add resposta em  % de feedback transmitido ao moço, só mudar serial  msg

  Serial.println("Insira um valor de 1000 a 2000 de Thrust ");
}

void loop() {
     digitalWrite(pinLED, HIGH);

   //if (Serial.available() > 0)
 // {
   
//  int Buffer = Serial.parseInt();
 // if(Buffer>999){

    //Parte que modifiquei do código
  //Le o valor do potenciometro
 int  valor = Serial.parseInt();
  //Converte o valor para uma faixa entre 0 e 179
  valor = map(valor, 0, 1023, 0, 179);  //Observar os intervalos de operação, tinha colocado 1000 - 2000!
  //Mostra o valor no serial monitor
 // Serial.print("Potenciometro: ");
  Serial.println(valor);
  //Envia o valor para o motor

//
  
    int  leitura1 = valor;   //Buffer; 
    byte leitura2 = map(leitura1, 0,179, 0, 1023); 
    int  leitura3 = map(leitura1, 0, 1023, 120, 0);

    pacote.valor1 = leitura1;
    pacote.valor2 = leitura2;
    pacote.valor3 = leitura3;
 
    Serial.println(pacote.valor1);
    analogWrite(pinLED2,valor);
    vw_send((uint8_t *)&pacote, sizeof(pacote));
    vw_wait_tx(); 
    digitalWrite(pinLED, LOW);
    delay(50);
    
   // }
 // }
}
