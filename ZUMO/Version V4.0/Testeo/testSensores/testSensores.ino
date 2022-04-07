int sens[] = {17, 16, 15, 14, 13, 12, 11, 10};
char readChar;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < (sizeof(sens)/sizeof(sens[0])); i++){
    pinMode(sens[i], INPUT);
  }
}

void loop() {
  readChar = Serial.available() ? (char) Serial.read() : 'n';
  
  for (int i = 0; i < (sizeof(sens)/sizeof(sens[0])); i++){
    Serial.print(sens[i] + " ")
  }
  
  for (int i = 0; i < (sizeof(sens)/sizeof(sens[0])); i++){
    String senCheck;
    if (i == 0 ||  i == 3){
      senCheck = String(analogRead(sens[i]));// > 150;
    }else{
      senCheck = String(digitalRead(sens[i]));
    }
    Serial.print(senCheck + "  ");
  }
  Serial.println();
  //String(sens[i]) + ": " 
}
