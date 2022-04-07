int salBuzzer = 13;

void setup() {
  Serial.begin(9600);
  
  tone(salBuzzer, 1400, 100);
  delay(150);
  tone(salBuzzer, 1400, 100);
}

void loop() {
  Serial.println();
}
