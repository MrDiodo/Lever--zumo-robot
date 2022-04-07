int entIR[] = {14, 12, 11, 10, 15};
int entLin[] = {13, 16, 17, 8};
int fwdM1 = 3;
int bwdM1 = 5;
int fwdM2 = 6;
int bwdM2 = 9;
int constGir = -0.5;

int entPuls[] = {2, 4, 7, 8}; //Pines del DIP Switch

int _onSpotTurnConst = 190;

int M1_Potencia = 0;
int M2_Potencia = 0;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < (sizeof(entIR)/sizeof(entIR[0])); i++){
    pinMode(entIR[i], INPUT);
  }
  for (int i = 0; i < (sizeof(entLin)/sizeof(entLin[0])); i++){
    pinMode(entLin[i], INPUT);
  }
  pinMode(fwdM1, OUTPUT);
  pinMode(bwdM1, OUTPUT);
  pinMode(fwdM2, OUTPUT);
  pinMode(bwdM2, OUTPUT);
  motorsLOW();
  
  int puls = -1;
  while (puls == -1)
  {
      puls = checkPuls();
  }

  if (puls == entPuls[0])
  {
      onSpotTurn(-90);
  }
  else if (puls == entPuls[1])
  {
      onSpotTurn(-45);
  }
  else if (puls == entPuls[2])
  {
      onSpotTurn(45);
  }
  else if (puls == entPuls[3])
  {
      onSpotTurn(90);
  }
}

void loop() {
  Serial.println();
}

//Movimiento

void onSpotTurn(int deg) //Giro en el lugar (toma un valor de -90 a 90 grados)
{
    motorsLOW();
    if (deg > 0)
    {
        M1_Potencia = 255;
        M2_Potencia = -255;
    }
    else
    {
        M1_Potencia = -255;
        M2_Potencia = 255;
    }
    updateMotors();
    delay((abs(deg) * long(_onSpotTurnConst)) / 90);
    motorsLOW();
}

void fwdFull(){
  digitalWrite(fwdM1, HIGH);
  digitalWrite(fwdM2, HIGH);
  digitalWrite(bwdM1, LOW);
  digitalWrite(bwdM2, LOW);
}
void bwdFull(){
  digitalWrite(bwdM1, HIGH);
  digitalWrite(bwdM2, HIGH);
  digitalWrite(fwdM1, LOW);
  digitalWrite(fwdM2, LOW);
}

void motorsLOW(){
  digitalWrite(fwdM1, LOW);
  digitalWrite(fwdM2, LOW);
  digitalWrite(bwdM1, LOW);
  digitalWrite(bwdM2, LOW);
}

void fwdTurn(float deg){
  if (deg > 0){
    int valM2 = 255 * (1 - deg);
    digitalWrite(fwdM1, HIGH);
    analogWrite(fwdM2, valM2);
  }
  else{
    int valM1 = 255 * (1 - abs(deg));
    digitalWrite(fwdM2, HIGH);
    analogWrite(fwdM1, valM1);
  }
}
void bwdTurn(float deg){
  if (deg > 0){
    int valM2 = 255 * (1 - deg);
    digitalWrite(bwdM1, HIGH);
    analogWrite(bwdM2, valM2);
  }
  else{
    int valM1 = 255 * (1 - abs(deg));
    digitalWrite(bwdM2, HIGH);
    analogWrite(bwdM1, valM1);
  }
}

void updateMotors()
{
    analogWrite(fwdM1, max(0, M1_Potencia));
    analogWrite(fwdM2, max(0, M2_Potencia));
    analogWrite(bwdM1, -1 * min(0, M1_Potencia));
    analogWrite(bwdM2, -1 * min(0, M2_Potencia));
}

int checkPuls()
{
    for (int puls : entPuls)
    {
        if (digitalRead(puls))
        {
            return puls;
        }
    }
    return -1;
}
