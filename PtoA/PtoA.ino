String x;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()>0){
      x = Serial.readString();
        Serial.println(x);
  }
}
