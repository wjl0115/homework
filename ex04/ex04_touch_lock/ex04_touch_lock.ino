#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 500

bool ledState = false;
int lastTouchValue = 100;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 60; // 软件防抖

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  unsigned long now = millis();
  int currTouch = touchRead(TOUCH_PIN);

  // 防抖判断：间隔60ms才采样一次触摸值
  if (now - debounceTime > debounceDelay) {
    // 上升沿检测：上一次没触摸，当前触摸
    if (lastTouchValue > THRESHOLD && currTouch < THRESHOLD) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      Serial.print("触摸自锁切换，LED状态：");
      Serial.println(ledState ? "亮" : "灭");
    }
    lastTouchValue = currTouch;
    debounceTime = now;
  }
}