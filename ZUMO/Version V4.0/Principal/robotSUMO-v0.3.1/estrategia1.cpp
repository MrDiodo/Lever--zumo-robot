#include "Arduino.h"
#include "driverMotores.h"
#include "estrategia1.h"
#include "handlerPulsadores.h"

estrategia1::estrategia1(int entIR[], int entLin[], int entPuls[], const driverMotores &driver, const handlerPulsadores &pulsadores, int salBuzzer)
{
    memcpy(_entIR, entIR, sizeof(entIR) * 5); //No se pueden asignar arrays :)
    memcpy(_entLin, entLin, sizeof(entIR) * 4);
    memcpy(_entPuls, entPuls, sizeof(entPuls) * 4);

    _salBuzzer = salBuzzer;

    _driver_pointer = &driver;
    _handler_pulsadores = &pulsadores;
}

void estrategia1::exec(int senIR, int senLin)
{
    if (!isInit)
    {
        initTurn();
    }
    if (!(senIR == -1))
    {
        execIR(senIR);
    }
    else
    {
        execLinea(senLin);
    }
}

void estrategia1::execLinea(int sensor)
{
    if (sensor == _entLin[0]) // Pin A4
    {
        (*_driver_pointer).fwdTurn(0.8, 150); //Atras izq.
    }
    else if (sensor == _entLin[1]) // Pin 12
    {
        (*_driver_pointer).bwdFull();
        (*_driver_pointer).onSpotTask(600, -90); //Adelante izq.
    }
    else if (sensor == _entLin[2]) // Pin 11
    {
        (*_driver_pointer).bwdFull();
        (*_driver_pointer).onSpotTask(600, 90); //Adelante der.
    }
    else if (sensor == _entLin[3]) // Pin 10
    {
        (*_driver_pointer).fwdTurn(-0.8, 150); //Atras der.
    }
}

void estrategia1::execIR(int sensor) //Los sensores estan ordenados de mayor a menor importancia
{
    if (sensor == _entIR[0])
    {
        (*_driver_pointer).onSpotTurn(90); //O
    }
    else if (sensor == _entIR[4])
    {
        (*_driver_pointer).onSpotTurn(-90); //E
    }
    else if (sensor == _entIR[2])
    {
        (*_driver_pointer).fwdFull(1); //N
    }
    else if (sensor == _entIR[3])
    {
        (*_driver_pointer).onSpotTurn(-45); //NE
    }
    else if (sensor == _entIR[1])
    {
        (*_driver_pointer).onSpotTurn(45); //NO
    }
}

void estrategia1::initTurn()
{
    int puls = -1;
    while (puls == -1)
    {
        puls = (*_handler_pulsadores).checkPuls();
    }

    tone(_salBuzzer, 1400, 200);
    delay(1000);
    tone(_salBuzzer, 1200, 100);
    delay(1000);
    tone(_salBuzzer, 1200, 100);
    delay(1000);
    tone(_salBuzzer, 1200, 100);
    delay(1000);
    tone(_salBuzzer, 1200, 100);
    delay(1000);
    tone(_salBuzzer, 1400, 500);

    if (puls == _entPuls[0])
    {
        (*_driver_pointer).onSpotTurn(-90);
    }
    else if (puls == _entPuls[1])
    {
        (*_driver_pointer).onSpotTurn(-45);
    }
    else if (puls == _entPuls[2])
    {
        (*_driver_pointer).onSpotTurn(45);
    }
    else if (puls == _entPuls[3])
    {
        (*_driver_pointer).onSpotTurn(90);
    }
    isInit = true;
}
