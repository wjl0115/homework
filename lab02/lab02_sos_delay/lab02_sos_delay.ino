const int ledPin = 2; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // S：3次短闪
  for(int i=0; i<3; i++) { 
    digitalWrite(ledPin, HIGH); delay(200); 
    digitalWrite(ledPin, LOW); delay(200); 
  }
  delay(500);
  // O：3次长闪
  for(int i=0; i<3; i++) { 
    digitalWrite(ledPin, HIGH); delay(600); 
    digitalWrite(ledPin, LOW); delay(200); 
  }
  delay(500);
  // S：3次短闪
  for(int i=0; i<3; i++) { 
    digitalWrite(ledPin, HIGH); delay(200); 
    digitalWrite(ledPin, LOW); delay(200); 
  }
  delay(2000); // SOS完整一轮后长停顿
  Serial.println("一轮SOS信号发送完成");
}