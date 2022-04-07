int entIR[] = {A0, A1, A5, A2, A3}; //Pines de los sensores Sharp y Baluff
int entLin[] = {13, 12, 11, 10};    //Pines de los sensores de línea
int entPulsadores[] = {2, 4, 7, 8}; //Pines del DIP Switch

int arrayDest[4];

void setup()
{
    Serial.begin(9600);
    memcpy(arrayDest, entLin, sizeof(entLin));
    for (int item : arrayDest)
    {
        Serial.println(item);
    }
}

void loop()
{
    
}