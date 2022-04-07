#ifndef handlerSensores_h
#define handlerSensores_h

#include "Arduino.h"

class handlerSensores
{
public:
    handlerSensores(int entIR[] = NULL, int entLin[] = NULL, int sharpTh = NULL);
    int checkLin();
    int checkIR();

    void printPins();
    void debugPrint();

    int sharpThreshold;

private:
    int _entIR[5];
    int _entLin[4];
};

#endif