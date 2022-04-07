#ifndef sumoDebugger_h
#define sumoDebugger_h

#include "Arduino.h"
#include "driverMotores.h"
#include "handlerSensores.h"
#include "handlerPulsadores.h"

class sumoDebugger
{
public:
    sumoDebugger(const driverMotores &driver = NULL, const handlerSensores &sensores = NULL, const handlerPulsadores &pulsadores = NULL);
    void enableDebugMode();
    void printPins();
    void debugPrint();

    bool isEnabled;

private:
    const driverMotores *_driver_pointer;
    const handlerSensores *_sensores_pointer;
    const handlerPulsadores *_pulsadores_pointer;
};

#endif