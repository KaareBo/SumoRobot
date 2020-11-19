#include <Sumo.h>
#include <SharpIR.h>

//Definer pins
#define startButton 8
#define octopus1 A7
#define octopus2 A6
#define sharpPin A5

//enA = 13, In1 = 12, In2 = 11, enB = 14, In3 = 9, In4 = 10
Sumo sumo(13, 12, 11, 14, 9, 10);
SharpIR sharp(SharpIR::GP2Y0A41SK0F, sharpPin);

//Kalibreringsverdier for SharpIR-sensor
int calibrateSensor[] = {70, 220, 385, 440, 490, 524, 536, 555, 572, 576};
int calibrateValue[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

//Definerer variabler
bool robotOn = false;
int buttonPrev = 0;
int delayCount = 0;

int distance = 0;
int frontLine = 0;
int backLine = 0;

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


//Dersom roboten er av starter vi funksjonen på nytt
 if(robotOn == false){
  delayCount = 0;
  return;
 }


 
//Sjekk sensorene
distance = multiMap(analogRead(sharpPin), calibrateSensor, calibrateValue, 10);




//Robotreglene tilsier at begge roboter må vente 5 sekunder før de starter
//For å ikke vente 5 sekunder hver runde legger jeg til et if-statement som venter 5 sekunder dersom det er første gang koden kjøres
//etter at kampen er i gang, og ignoreres de andre gangene. Når roboten skrues av resettes counteren
 if(delayCount == 0){
  delay(5000);
  delayCount += 1;
 }

 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//Hvis linje-sensoren oppdager en hvit strek kjører den i motsatt retning
//Sensor foran
if(digitalRead(octopus1) == 1){
  for(int i = 0; i <= 1000; i++){   //Vi vil ikke at den med et uhell skal kjøre av bana når den prøver å kjøre unna en annen strek
    if(digitalRead(octopus2) == 1){ //så vi kjører litt, sjekker om vi er utfor streken, og kjører videre
      scanRight(270);               //Hvis vi treffer den andre linja snur vi rundt
      return;
    }
    sumo.backwards(255);
    delay(1);
  }
  scanRight(100);
}


//Bakre sensor
if(digitalRead(octopus1) == 1){
  for(int i = 0; i <= 1000; i++){   
    if(digitalRead(octopus2) == 1){ 
      scanRight(270);              
      return;
    }
    sumo.backwards(255);
    delay(1);
  }
  scanRight(100);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//Sjekker om man kan se motstanderen
if(scanRight(30) == 1){
  charge();
  }
  

if(scanLeft(60) == 1){
  charge();
  }
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





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





//Scanner mens den roterer i stedet for å scanne og så rotere
int scanRight(int steps){
  for(int i = 0; i <= steps; i++){
    sumo.right(100, 1);
    if(distance != 50){ //Ser etter motstandere
      return(1);
    }
    if(digitalRead(octopus1) == 1){ //Ser etter hvit linje, snur seg hvis den ser den
      sumo.left(100, steps);
      return;
    }
  }
  return(0);
}



int scanLeft(int steps){
  for(int i = 0; i <= steps; i++){
    sumo.left(100, 1);
    if(distance != 50){ //Ser etter motstandere
      return(1);
    }
     if(digitalRead(octopus1) == 1){ //Ser etter hvit linje, snur seg hvis den ser den
      sumo.left(100, steps);
      return;
    }
  }
  return(0);
}




void charge(){
  while(distance != 50){
    sumo.forwards(255);
    distance = multiMap(analogRead(sharpPin), calibrateSensor, calibrateValue, 10);
  }
  sumo.stop();
}
