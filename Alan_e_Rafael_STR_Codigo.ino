#include <glcd.h>                 // biblioteca com os comando do GLCD.. estou usando o LCD painel B
#include "fonts/allFonts.h"       // biblioteca que coloca a fonte do display Arial
#include "bitmaps/allBitmaps.h"   // Carrega as imagens do Dir imagens
#include "DHT.h"                  // Biblioteca de comunicacao do DHT22

DHT dht(53, DHT22);               //Colocando o PINO 53 para receber o sinal de dados do DHT
int motor = 48;                     // colocando o motor como pino 48
void setup()
{ 
  //Configuracao do sensor e porta serial******************************************************************************************
  Serial.begin(9600);             // Inicializa a comunicação serial com Bauldrate de 9600kpbs
  dht.begin();                    // Inicializa a comunicacao como DHT22
  pinMode(motor, OUTPUT); 
 
 //Configuracao do DISPLAY******************************************************************************************
  GLCD.Init();                    // Inicializa a a comunicacao do GLCD invertendo os pixels claros da tela
  GLCD.ClearScreen();             // Limpa o display para apagar possiveis variaveis de lixo na memoria do mesmo
  GLCD.SelectFont(System5x7, BLACK); // Utiliza a fonte Deafaul com letras pretas
  GLCD.ClearScreen();                  
  // PLOTA desenho NO DISPLAY***********************************************************************************
  GLCD.DrawBitmap(alan1,0,0, BLACK);
}

void  loop()
{  

  float h = dht.readHumidity(); //leitura do dado de umidade 
  float t = dht.readTemperature(); // leitura do dado de temperatura
  if ( t >=26 ){ 
  digitalWrite(motor, HIGH);   // liga motor
  delay(5000);  // tempo de estabilizacao do sistema
  GLCD.CursorToXY(20, 55); // coloca na posicao do display linha 20 coluna 55
  GLCD.print("VENTILADOR ON ");    // printa no display o estado do ventilador
  }       
  else  {
  digitalWrite(motor, LOW);    // desliga o motor
  GLCD.CursorToXY(20, 55);  // coloca na posicao do display linha 20 coluna 55
  GLCD.print("VENTILADOR OFF");  // printa no display o estado do ventilador
  }
  
//PLOTA OS VALORES NO DISPLAY********************************************************************************************
 
  GLCD.CursorToXY(20, 30);
  GLCD.print(t);    // printa a temperstura no display
  GLCD.CursorToXY(20, 45);
  GLCD.print(h); // printa a ummidade no display

  

 // JOGA OS DADOS NA SERIAL*********************************************************************************************
 
 Serial.print(t); // printa temperatura na serial
 Serial.print(".");
 Serial.print(" ");
 Serial.print("C      | ");
 Serial.print(h); //printa umidade na serial
 Serial.print(" %  | ");
 delay(100);
} 
  
