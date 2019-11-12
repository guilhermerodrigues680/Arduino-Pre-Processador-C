/*
 * Pré-processador C com arduino
 * 
 * Links:
 * https://www.deviceplus.com/how-tos/arduino-guide/arduino-preprocessor-directives-tutorial/
 * https://community.particle.io/t/solved-disable-serial-ifdef-debug-not-working-best-practice/14105
 * https://forum.arduino.cc/index.php?topic=46900.0
 * https://www.embarcados.com.br/pre-processador-c-parte-1/
 * https://www.embarcados.com.br/pre-processador-c-compilacao-condicional-parte-2/
 * https://www.embarcados.com.br/pre-processador-c-diagnostico-parte-3/
 */

//// SELECAO DE DISPOSTIVO ////

#define DEVICE_1  1
#define DEVICE_2  2
#define DEVICE_3  3

// Dispositivo selecionado:
#define DEVICE DEVICE_1

#if DEVICE == DEVICE_1
# include "device_1.h"
#elif DEVICE == DEVICE_2
# include "device_2.h"
#elif DEVICE == DEVICE_3
# include "device_3.h"
#else
#error O dispositivo não foi definido! Observe a linha define DEVICE
#endif

////  PRÉ-PROCESSADOR C  ////

#define PINO_LED LED_BUILTIN
// Aceita somente texto, nao aceita variaveis
#define MSG_FORMAT(type, arg) #type ": " arg


//// FUNCOES DE DEBUG (0 = DESATIVADO, 1 = ATIVADO) ////

#define DEBUG 1

#if DEBUG
// Se o DEBUG estiver ativado, o pre processador escreve as funcoes.

#warning >Debug Ativado<

// Iniciar a porta serial
#define DEBUG_BEGIN()\
          Serial.begin(9600);\
          Serial.println(F("DEBUG ATIVADO"));

// Imprime o modelo do dispositivo
#define DEBUG_PRINT_DISPOSITIVO()\
          Serial.print(F("Dispositivo: "));\
          Serial.print(DEVICE);\
          Serial.print(F(" - Modelo: "));\
          Serial.println(MODELO);

// Imprime uma mensagem
#define DEBUG_PRINT(msg)\
          Serial.print(F("DEBUG: "));\
          Serial.println(msg);

// Delay quando o debug esta ativado
#define DEBUG_DELAY()\
          delay(2000);

// Diretivas auxiliares de DEBUG
#define DEBUG_AUX()\
          Serial.print("DEBUG AUX: ");\
          Serial.print(__LINE__);\
          Serial.print(" | ");\
          Serial.print(__FILE__);\
          Serial.print(" | ");\
          Serial.print(__DATE__);\
          Serial.print(" | ");\
          Serial.println(__TIME__);

#else
// Quando o DEBUG esta desativado, as funcoes não existem (codigo em branco).
#define DEBUG_BEGIN()
#define DEBUG_PRINT_DISPOSITIVO()
#define DEBUG_PRINT(msg)
#define DEBUG_DELAY()
#define DEBUG_AUX()
#endif

/*
 * 
 */
void setup() {
  DEBUG_BEGIN();
  DEBUG_PRINT_DISPOSITIVO();
  
  // Escreve no momento da copilacao (__LINE__ aparentemente nao funciona com pragma)
  #pragma message "Um texto qualquer"
  #pragma message "Linha do programa atual: " __LINE__
  #pragma message "Caminho do arquivo: " __FILE__
  #pragma message "Data: " __DATE__
  #pragma message "Horario: " __TIME__
  
  // Escreve no Serial apos a copilacao
  DEBUG_AUX();
  
  pinMode(PINO_LED, OUTPUT);

}

/*
 * 
 */
void loop() {
  DEBUG_PRINT("Void loop");
  DEBUG_PRINT(velPisca); // DEBUG da variavel velPisca

  //DEBUG_DELAY(); // Delay para DEBUG
  
  digitalWrite(PINO_LED, HIGH);
  delay(velPisca); // Variavel do dispositivo selecionado
  digitalWrite(PINO_LED, LOW);
  delay(velPisca); // Variavel do dispositivo selecionado
}
