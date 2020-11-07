#include <Sumo.h>
#include <SharpIR.h>

//Definer pins
#define startButton 8
#define octopus A7
#define sharpPin A6

//enA 13, In1 12, In2 11, enB 14, In3 9, In4 10
Sumo sumo(13, 12, 11, 14, 9, 10);
SharpIR sharp(SharpIR::GP2Y0A41SK0F, sharpPin);

//Kalibreringsverdier for SharpIR-sensor
int calibrateSensor[] = {70, 220, 385, 440, 490, 524, 536, 555, 572, 576};
int calibrateValue[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

//Definerer variabler
bool robotOn = false;
int buttonPrev = 0;

void setup() {
  Serial.begin(9600);

  pinMode(startButton, INPUT);
}

void loop() {
//Denne funksjonen sjekker om på-knappen er blitt byttet, og forandrer på en bool dersom den er blitt det
 if(digitalRead(startButton) == 1 && buttonPrev != 1){
  robotOn = !robotOn;
 }
buttonPrev = digitalRead(startButton);

 if(robotOn == false){
  return;
 }
}


//Her er en funksjon jeg fant på nettet. Sharp-sensoren gir ut en analog verdi i en ikke-lineær graf, og må derfor kalibreres
//Jeg fant funksjonen her: https://playground.arduino.cc/Main/MultiMap/
int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  //Først sjekker funksjonen om verdien oppgitt er innenfor skopet oppgitt i arrayen
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size - 1]) return _out[size - 1];

  //Deretter finner den posisjonen i arrayen som er høyere enn verdien
  uint8_t pos = 1; 
  while (val > _in[pos]) pos++;

  //Hvis du er akkurat på verdien, flott! Returner den
  if (val == _in[pos]) return _out[pos];

  //Jeg har prøvd å forstå denne formelen, men jeg skjønner den ikke. Det eneste jeg har kommet fram til er at det ligner en prosent-formel
  return (val - _in[pos - 1]) * (_out[pos] - _out[pos - 1]) / (_in[pos] - _in[pos - 1]) + _out[pos - 1];
}
