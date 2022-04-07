#include "Arduino.h"
#include "handlerSensores.h"

//Constructor
handlerSensores::handlerSensores(int entIR[], int entLin[], int sharpTh)
{
  memcpy(_entIR, entIR, sizeof(entIR[0]) * 5); //No se pueden asignar arrays :)
  memcpy(_entLin, entLin, sizeof(entLin[0]) * 4);
  sharpThreshold = sharpTh;

  for (int SenIR : _entIR)
  {
    pinMode(SenIR, INPUT);
  }
  for (int SenLin : _entLin)
  {
    pinMode(SenLin, INPUT_PULLUP);
  }
}

//Devuelve el numero de pin del sensor de línea que esta detectando una linea, si existe.
int handlerSensores::checkLin()
{
  for (int senLin : _entLin)
  {
    if (!digitalRead(senLin))
    {
      return senLin;
    }
  }
  return -1;
}

//Devuelve el numero de pin del sensor IR que esta detectando, si existe.
int handlerSensores::checkIR()
{
  for (int SenIR : _entIR)
  {
    if (analogRead(SenIR) > sharpThreshold)
    {
      return SenIR;
    }
  }
  return -1;
}

void handlerSensores::debugPrint()
{
  Serial.print("IRs: ' ");
  for (int SenIR : _entIR)
  {
    Serial.print(String(analogRead(SenIR)) + " ");
  }
  Serial.print("' Lineas: ' ");
  for (int sensor : _entLin)
  {
    Serial.print(String(!digitalRead(sensor)) + " ");
  }
  Serial.print("' ");
}

void handlerSensores::printPins()
{
  for(int senIR : _entIR)
  {
    Serial.print(String(senIR) + " ");
  }
  for (int senLin : _entLin)
  {
    Serial.print(String(senLin) + " ");
  }
}
