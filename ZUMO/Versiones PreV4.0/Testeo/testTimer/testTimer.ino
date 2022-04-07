
//Entradas
int entIR[] = {17, 16, 15, 14}; //Pines de los sensores Sharp y Baluff
int entLin[] = {13, 12, 11, 10}; //Pines de los sensores de línea
int entDIP[] = {2, 4, 7, 8}; //Pines del DIP Switch
int countIR; //Almacena la cantidad de sensores Infrarojos
int countLin; //Almacena la cantidad de sensores de línea

//Pines de las entradas del doble puente H
int fwdM1 = 9; //Adelante del motor 1
int bwdM1 = 6; //Atras del motor 1
int fwdM2 = 5; //Adelante del motor 2
int bwdM2 = 3; //Atras del motor 2
float constGir = 0.8;

String state = "";
String prevState = "";
bool TIMER1_TASK = false;

void setup() {
  Serial.begin(9600); //Se inicia la comunicacion serial
  
  cli();//stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  
  // set compare match register for 1hz increments  
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
  
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
  
  while(not digitalRead(7)){} //Espera que se pulse el boton de arranque y espera 5 segundos antes de arrancar.
  Serial.print("5");
  delay(1000);
  Serial.print("4");
  delay(1000);
  Serial.print("3");
  delay(1000);
  Serial.print("2");
  delay(1000);
  Serial.println("1");
  delay(1000);

//  onSpotTurn(res); //Realiza el giro inicial dado por el DIP switch
}
  
void loop() {
  if (TIMER1_TASK){
    
  }
//  if (not checkLin()){ //Si no se detecta ninguna linea
//    if (not TIMER1_TASK){
//      state = "N/A";
//      fwdFull(); //Todos los motores hacia adelante
//    }
//  }
//  if (state != prevState){ //Si el estado actual es diferente del anterior
//    motorsLOW(); //Apagar los motores
//    prevState = state;
//  }
//  Serial.println(state);
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
  Serial.println();
  startTask1((abs(deg) * long(208)) / 90);
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

//Tasking

ISR(TIMER1_COMPA_vect){
  finishTask1();
}

void startTask1(int mil){
  int counterLim = mil * long(15624) / 1000;
  Serial.println(counterLim);
  if (counterLim >= 65536){return;}
  cli();
  TCNT1 = 0;
  OCR1A = counterLim;
  sei();
}

void finishTask1(){
  if (TIMER1_TASK){
    motorsLOW();
    Serial.println("Task Finished!");
  }
}
