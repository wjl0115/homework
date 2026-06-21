const int ledPin = 2;
unsigned long currentTime;
unsigned long lastTime = 0;
const unsigned long interval = 500; // 500ms翻转一次，1Hz完整周期

bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  currentTime = millis();
  // 判断间隔到达
  if(currentTime - lastTime >= interval)
  {
    lastTime = currentTime;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.print("LED状态切换，当前：");
    Serial.println(ledState ? "ON" : "OFF");
  }
}