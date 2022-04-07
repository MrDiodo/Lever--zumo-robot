#ifndef driverMotores_h
#define driverMotores_h

#include "Arduino.h"

class driverMotores
{
    public:
        driverMotores(int fwdM1 = NULL, int bwdM1 = NULL, int fwdM2 = NULL, int bwdM2 = NULL, int onSpotTurnConst = 190);
        void fwdFull(float power = 1);
        void bwdFull();
        void motorsLOW();
        void M1Set(int pot);
        void M2Set(int pot);

        void onSpotTurn(int deg);
        void fwdTurn(float deg);
        void bwdTurn(float deg);

        void PulsTurn();

        void updateMotors();

        void printPins();
        void debugPrint();

        int M1_Potencia = 0;
        int M2_Potencia = 0;
    private:
        int _fwdM1;
        int _bwdM1;
        int _fwdM2;
        int _bwdM2;

        int _onSpotTurnConst;
};
#endif
