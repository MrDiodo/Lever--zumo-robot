#ifndef estrategia1_h
#define estrategia1_h

#include "Arduino.h"
#include "driverMotores.h"
#include "handlerPulsadores.h"

class estrategia1
{
public:
    estrategia1(int entIR[] = NULL, int entLin[] = NULL, int entPuls[] = NULL, const driverMotores &driver = NULL, const handlerPulsadores &pulsadores = NULL, int salBuzzer = NULL);
    void exec(int senIR, int senLin);

    int M1_Potencia;
    int M2_Potencia;

private:
    void execLinea(int sensor);
    void execIR(int sensor);
    void initTurn();

    int _entIR[5];
    int _entLin[4];
    int _entPuls[4];

    int _salBuzzer;

    bool _isInit = false;

    const driverMotores *_driver_pointer;
    const handlerPulsadores *_handler_pulsadores;
};

#endif