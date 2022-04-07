#ifndef handlerPulsadores_h
#define handlerPulsadores_h

#include "Arduino.h"
#include "driverMotores.h"

class handlerPulsadores
{
public:
    handlerPulsadores(int entPuls[] = NULL, const driverMotores &driver = NULL);
    int checkPuls();
    bool checkAllPuls();
    void pulsTurn();
    void pulsMotorTest();

    void printPins();
    void debugPrint();

private:
    const driverMotores *_driver_pointer;
    int _entPuls[4];
};
#endif