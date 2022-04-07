#include <TimerOne.h>

#include "driverMotores.h"
#include "handlerSensores.h"
#include "handlerPulsadores.h"
#include "sumoDebugger.h"

#include "estrategia1.h"

//Entradas
int entIR[] = {A0, A1, A5, A2, A3}; //Pines de los sensores Sharp y Baluff
int entLin[] = {A4, 12, 11, 10};    //Pines de los sensores de línea
int entPulsadores[] = {2, 4, 7, 8}; //Pines del DIP Switch

//Pines de las entradas del doble puente H
const int fwdM1 = 3; //Adelante del motor 1
const int bwdM1 = 5; //Atras del motor 1
const int fwdM2 = 6; //Adelante del motor 2
const int bwdM2 = 9; //Atras del motor 2

int salBuzzer = 13; //Pin de salida del buzzer

int strat = 1;

driverMotores driver(fwdM1, bwdM1, fwdM2, bwdM2, 190);
handlerSensores sensores(entIR, entLin, 150);
handlerPulsadores pulsadores(entPulsadores, driver);

estrategia1 strat1(entIR, entLin, entPulsadores, driver, pulsadores, salBuzzer);

sumoDebugger debugger(driver, sensores, pulsadores);

void timerCallback(){ //Funcion que ejecuta el timer cada vez q cumple un ciclo
  driver.runThread();
}

void setup()
{
  Serial.begin(9600);
  debugger.enableDebugMode();
  if (debugger.isEnabled)
  {
    strat1.isInit = true;
  }
  
  Timer1.initialize(20000); //El timer cumple un ciclo cada 20000 microsegundos (20ms)
  Timer1.attachInterrupt(timerCallback);

  tone(salBuzzer, 1400, 100);
  delay(200);
  tone(salBuzzer, 1400, 100);
}

void loop()
{
  //int asdf = millis();
  if (debugger.isEnabled)
  {
    if (!(pulsadores.checkPuls() == -1))
    {
      pulsadores.pulsMotorTest();
    }
    else
    {
      stratExec();
    }
    debugger.debugPrint();
  }
  else
  {
    stratExec();
  }
  driver.updateMotors();
  //Serial.println(millis() - asdf);
}

void stratExec()
{
  int senLinea = sensores.checkLin();
  int senIR = sensores.checkIR();

  switch (strat)
  {
  case 1:
    strat1.exec(senIR, senLinea);
    break;
  }
}
