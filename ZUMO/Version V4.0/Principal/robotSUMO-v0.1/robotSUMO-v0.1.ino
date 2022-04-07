//Entradas
int entIR[] = {17, 16, 15, 14}; //Pines de los sensores Sharp y Baluff
int entLin[] = {13, 12, 11, 10}; //Pines de los sensores de línea
int entDIP[] = {2, 4, 7, 8}; //Pines del DIP Switch
int countIR; //Almacena la cantidad de sensores Infrarojos
int countLin; //Almacena la cantidad de sensores de línea

//Pines de las entradas del doble puente H
int fwdM1 = 5; //Adelante del motor 1
int bwdM1 = 3; //Atras del motor 1
int fwdM2 = 9; //Adelante del motor 2
int bwdM2 = 6; //Atras del motor 2
float constGir = 0.8;

String state = "";
String prevState = "";

void setup() {
  Serial.begin(9600); //Se inicia la comunicacion serial
  
  countIR = sizeof(entIR)/sizeof(entIR[0]); //Almacena la cantidad de sensores Infrarojos
  countLin = sizeof(entLin)/sizeof(entLin[0]); //Almacena la cantidad de sensores de línea
  
  for (int i = 0; i < countIR; i++){ //Itera por cada item del array "entIR" y establece cada pin como una entrada
    pinMode(entIR[i], INPUT);
  }
  for (int i = 0; i < countLin; i++){ //Itera por cada item del array "entLin" y establece cada pin como una entrada
    pinMode(entLin[i], INPUT);
  }
  
  //Se establecen los pines del driver de los motores como salidas 
  pinMode(fwdM1, OUTPUT);
  pinMode(bwdM1, OUTPUT);
  pinMode(fwdM2, OUTPUT);
  pinMode(bwdM2, OUTPUT);

  Serial.println("Arduino listo!");  
  //while(not digitalRead(A7)){} //Espera que se pulse el boton de arranque y espera 5 segundos antes de arrancar.
  Serial.print("5");
  //delay(1000);
  Serial.print("4");
  delay(500);
  Serial.print("3");
  delay(1000);
  Serial.print("2");
  delay(1000);
  Serial.println("1");
  delay(1000);

//  onSpotTurn(res); //Realiza el giro inicial dado por el DIP switch
}
  
void loop() {
  if (not checkLin()){ //Si no se detecta ninguna linea
    if (not checkIR()){ //Si no se detecta nada a traves de los sensores IR
      state = "N/A";
      fwdFull(); //Todos los motores hacia adelante
    }
  }
  if (state != prevState){ //Si el estado actual es diferente del anterior
    motorsLOW(); //Apagar los motores
    prevState = state;
  }
  Serial.println(state);
//  delay(1000);
}

//Evalua que accion tomar segun el estado de los sensores de línea
bool checkLin(){
  if (not digitalRead(entLin[0])){
    fwdTurn(constGir);//Atras izq.
    state = "ATI";
    delay(300);
    return true;
  }
  else if(not digitalRead(entLin[1])){
    bwdFull();
    delay(600);
    onSpotTurn(-90); //Adelante izq.
    state = "ADI";
    return true;
  }
  else if(not digitalRead(entLin[2])){
    bwdFull();
    delay(600);
    onSpotTurn(90);//Adelante der.
    state = "ADD";
    return true;
  }
  else if(not digitalRead(entLin[3])){
    fwdTurn(-1 * constGir);//Atras der.
    state = "ATD";
    delay(300);
    return true;
  }
  return false;
}

//Evalua que accion tomar segun el estado de los sensores IR
bool checkIR(){
  bool senCheck;
  for (int i = 0; i < countIR; i++){
    if (i == 0 || i == 4){ //Los sensores 0 y 4 son los laterales y necesitan una lectura analógica
      senCheck = analogRead(entIR[i]) > 150;
      Serial.print(" analogRead: " + String(analogRead(entIR[i])) + " ");
    }else{
      senCheck = digitalRead(entIR[i]);
    }    
    if (senCheck){
      switch (i){
        case 0: {
          onSpotTurn(90); //O
          state = "O";
          break;
        }
        case 1: {
          fwdTurn(-1 * constGir);//NO
          state = "NO";
          break;
        }
        case 2: {
          fwdTurn(constGir);//NE
          state = "NE";
          break;
        }
        case 3: {
          onSpotTurn(-90);//E
          state = "E";
          break;
        }
      }
      return true;
    }
  }
  return false;
}

//Movimiento
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

void onSpotTurn(int deg) { //Giro en el lugar (toma un valor de -90 a 90 grados)
  motorsLOW();
  if (deg > 0){
    digitalWrite(fwdM2, HIGH);
    digitalWrite(bwdM1, HIGH);
  }else{
    digitalWrite(bwdM2, HIGH);
    digitalWrite(fwdM1, HIGH);
  }
  Serial.println((abs(deg) * long(208)) / 90);
  delay((abs(deg) * long(208)) / 90);
  motorsLOW();
}

void fwdTurn(float deg){ //Giro hacia adelante (toma un valor desde -1 a 1)
  digitalWrite(bwdM1, LOW);
  digitalWrite(bwdM2, LOW);
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
void bwdTurn(float deg){ //Giro hacia atras (toma un valor desde -1 a 1)
  digitalWrite(fwdM1, LOW);
  digitalWrite(fwdM2, LOW);
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

void DIPTurn(){
  for (int i = 0; i < 4; i++){
    if(digitalRead(entDIP[i])){
      switch (i){
        case 0:
          onSpotTurn(-90);
          return;
        case 1:
          onSpotTurn(-45);
          return;
        case 2:
          onSpotTurn(45);
          return;
        case 3:
          onSpotTurn(90);
          return;
      }
    }
  }
}
