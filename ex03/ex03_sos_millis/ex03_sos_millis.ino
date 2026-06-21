const int led = 2;

// 亮灭时长
const unsigned long flashOn = 200;
const unsigned long flashOff = 200;
const unsigned long longFlash = 600;
const unsigned long wordGap = 500;
const unsigned long loopGap = 2000;

unsigned long now;
unsigned long prevTime = 0;
bool light = LOW;

// SOS流程阶段
enum Stage{
  S_dot, gap1,
  O_line, gap2,
  S_dot2, endWait
};
Stage step = S_dot;
int count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
}

void loop() {
  now = millis();
  unsigned long wait;
  if(light)
    wait = (step == O_line) ? longFlash : flashOn;
  else
    wait = (step == endWait) ? loopGap : flashOff;

  if(now - prevTime < wait)
    return;
  prevTime = now;

  switch(step)
  {
    case S_dot:
      light = !light;
      digitalWrite(led, light);
      if(!light){
        count++;
        if(count >= 3){
          count = 0;
          step = gap1;
        }
      }
      break;
    case gap1:
      step = O_line;
      break;
    case O_line:
      light = !light;
      digitalWrite(led, light);
      if(!light){
        count++;
        if(count >= 3){
          count = 0;
          step = gap2;
        }
      }
      break;
    case gap2:
      step = S_dot2;
      break;
    case S_dot2:
      light = !light;
      digitalWrite(led, light);
      if(!light){
        count++;
        if(count >= 3){
          count = 0;
          step = endWait;
        }
      }
      break;
    case endWait:
      light = LOW;
      digitalWrite(led, LOW);
      step = S_dot;
      Serial.println("一轮SOS非阻塞信号发送完成");
      break;
  }
}