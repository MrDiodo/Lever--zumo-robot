#include "handlerPulsadores.h"
#include "driverMotores.h"

handlerPulsadores::handlerPulsadores(int entPuls[], const driverMotores &driver)
{
    _driver_pointer = &driver;

    int pulsNum = sizeof(entPuls) / sizeof(entPuls[0]);
    memcpy(_entPuls, entPuls, sizeof(entPuls[0]) * 4);
    for (int puls : _entPuls)
    {
        pinMode(puls, INPUT);
    }
}

int handlerPulsadores::checkPuls()
{
    for (int puls : _entPuls)
    {
        if (digitalRead(puls))
        {
            return puls;
        }
    }
    return -1;
}

bool handlerPulsadores::checkAllPuls()
{
    for (int puls : _entPuls)
    {
        if (!digitalRead(puls))
        {
            return false;
        }
    }
    return true;
}

void handlerPulsadores::pulsMotorTest()
{
    (*_driver_pointer).M1Set(digitalRead(_entPuls[0]) ? -255 : 0);
    (*_driver_pointer).M1Set(digitalRead(_entPuls[1]) ? 255 : (*_driver_pointer).M1_Potencia);
    (*_driver_pointer).M2Set(digitalRead(_entPuls[2]) ? 255 : 0);
    (*_driver_pointer).M2Set(digitalRead(_entPuls[3]) ? -255 : (*_driver_pointer).M2_Potencia);
}

void handlerPulsadores::debugPrint()
{
    Serial.print("Pulsadores: ' ");
    for (int puls : _entPuls)
    {
        Serial.print(String(digitalRead(puls)) + " ");
    }
    Serial.print("' ");
}

void handlerPulsadores::printPins()
{
    for (int puls : _entPuls)
    {
        Serial.print(String(puls) + " ");
    }
}