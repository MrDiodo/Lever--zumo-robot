#include "driverMotores.h"
#include "Arduino.h"

driverMotores::driverMotores(int fwdM1, int bwdM1, int fwdM2, int bwdM2, int onSpotTurnConst)
{
    _fwdM1 = fwdM1;
    _bwdM1 = bwdM1;
    _fwdM2 = fwdM2;
    _bwdM2 = bwdM2;

    _onSpotTurnConst = onSpotTurnConst;

    //Se establecen los pines del driver de los motores como salidas
    pinMode(_fwdM1, OUTPUT);
    pinMode(_bwdM1, OUTPUT);
    pinMode(_fwdM2, OUTPUT);
    pinMode(_bwdM2, OUTPUT);
}

//Movimiento
void driverMotores::fwdFull(float power)
{
    M1_Potencia = 255 * power;
    M2_Potencia = 255 * power;
}
void driverMotores::bwdFull()
{
    M1_Potencia = -255;
    M2_Potencia = -255;
}

void driverMotores::motorsLOW()
{
    M1_Potencia = 0;
    M2_Potencia = 0;
}

void driverMotores::M1Set(int pot)
{
    M1_Potencia = pot;
}

void driverMotores::M2Set(int pot)
{
    M2_Potencia = pot;
}

void driverMotores::onSpotTurn(int deg) //Giro en el lugar (toma un valor de -90 a 90 grados)
{
    motorsLOW();
    M1_Potencia = deg > 0 ? 255 : -255;
    M2_Potencia = deg > 0 ? -255 : 255;
    updateMotors();
    delay((abs(deg) * long(_onSpotTurnConst)) / 90);
    motorsLOW();
}

void driverMotores::fwdTurn(float deg) //Giro hacia adelante (toma un valor desde -1 a 1)
{
    M1_Potencia = min(255, (255 * (deg + 1)));
    M2_Potencia = min(255, (255 * (1 - deg)));
}
void driverMotores::bwdTurn(float deg) //Giro hacia atras (toma un valor desde -1 a 1)
{
    M1_Potencia = min(255, (255 * (1 - deg)));
    M2_Potencia = min(255, (255 * (deg + 1)));
}

void driverMotores::updateMotors()
{
    analogWrite(_fwdM1, max(0, M1_Potencia));
    analogWrite(_fwdM2, max(0, M2_Potencia));
    analogWrite(_bwdM1, -1 * min(0, M1_Potencia));
    analogWrite(_bwdM2, -1 * min(0, M2_Potencia));
}

void driverMotores::debugPrint()
{
    Serial.print("PM1: '" + String(M1_Potencia) + "' ");
    Serial.print("PM2: '" + String(M2_Potencia) + "' ");
}

void driverMotores::printPins()
{
    Serial.print(String(_fwdM1) + " ");
    Serial.print(String(_bwdM1) + " ");
    Serial.print(String(_fwdM2) + " ");
    Serial.print(String(_bwdM2) + " ");
}
