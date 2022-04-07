#include "Arduino.h"
#include "sumoDebugger.h"

sumoDebugger::sumoDebugger(const driverMotores &driver, const handlerSensores &sensores, const handlerPulsadores &pulsadores)
{
    _driver_pointer = &driver;
    _sensores_pointer = &sensores;
    _pulsadores_pointer = &pulsadores;
}

void sumoDebugger::enableDebugMode()
{
    isEnabled = (*_pulsadores_pointer).checkAllPuls();
    //isEnabled = true;
    if (isEnabled)
    {
        Serial.begin(9600);
        printPins();
    }
}

void sumoDebugger::debugPrint()
{
    (*_pulsadores_pointer).debugPrint();                                       //Imprime en el monitor serial el estado lógico de los pulsadores
    (*_driver_pointer).debugPrint();                                           //Imprime en el monitor serial los valores de las potencias M1 y M2
    (*_sensores_pointer).debugPrint();                                         //Imprime en el monitor serial el estado lógico de los sensores IR y de línea
    Serial.print("IR: '" + String((*_sensores_pointer).checkIR()) + "' ");     //Imprime en el monitor serial el sensor IR que esté detectando en el momento, si existe
    Serial.print("Linea: '" + String((*_sensores_pointer).checkLin()) + "' "); //Imprime en el monitor serial el sensor de línea que esté detectando en el momento, si existe
    Serial.println();
}

void sumoDebugger::printPins()
{
    (*_pulsadores_pointer).printPins();
    (*_driver_pointer).printPins();
    (*_sensores_pointer).printPins();
    Serial.println();
}