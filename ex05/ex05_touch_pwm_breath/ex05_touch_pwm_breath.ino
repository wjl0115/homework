#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 500

const int freq = 5000;
const int resolution = 8;

int gear = 1; // 1慢 / 2中 / 3快 三档位
int brightness = 0;
int step = 1;

// 触摸防抖变量
int lastTouchValue = 100;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 60;

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, freq, resolution);
}

void loop() {
  unsigned long now = millis();
  int currTouch = touchRead(TOUCH_PIN);

  // 触摸档位切换逻辑
  if (now - debounceTime > debounceDelay) {
    if (lastTouchValue > THRESHOLD && currTouch < THRESHOLD) {
      gear = gear + 1;
      if (gear > 3) gear = 1; // 3档循环 1→2→3→1
      Serial.print("切换呼吸档位：");
      Serial.println(gear);
    }
    lastTouchValue = currTouch;
    debounceTime = now;
  }

  // 根据档位修改呼吸速度delay
  int speedDelay;
  switch (gear) {
    case 1: speedDelay = 30; break; // 慢速呼吸
    case 2: speedDelay = 15; break; // 中速呼吸
    case 3: speedDelay = 5; break;  // 急促快速呼吸
  }

  // 呼吸渐变逻辑 ledcWrite
  ledcWrite(LED_PIN, brightness);
  brightness += step;
  if (brightness <= 0 || brightness >= 255) {
    step = -step;
  }
  delay(speedDelay);
}