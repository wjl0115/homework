#define LED_A 2
#define LED_B 4
// 课件统一PWM参数
const int freq = 5000;
const int resolution = 8;

int valA = 0;
int step = 1;

void setup() {
  Serial.begin(115200);
  // 两路独立PWM通道绑定
  ledcAttach(LED_A, freq, resolution);
  ledcAttach(LED_B, freq, resolution);
}

void loop() {
  // A灯亮度0~255递增
  ledcWrite(LED_A, valA);
  // B灯与A完全反相：A=0则B=255，A=255则B=0
  ledcWrite(LED_B, 255 - valA);

  valA += step;
  // 到达亮度边界反向渐变
  if (valA <= 0 || valA >= 255) {
    step = -step;
  }
  delay(8); // 控制渐变顺滑度
}