#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vi_lll";
const char* password = "knyqsbzirkirkbh";
#define LED_PIN 2
#define TOUCH_PIN 4
#define THRESHOLD 20

WebServer server(80);
bool isArm = false;    // 布防状态
bool alarmLock = false; // 报警锁定

// 网页生成（布防/撤防双按钮）
String makePage() {
  String armState = isArm ? "已布防" : "未布防";
  String alarmState = alarmLock ? "⚠️ 报警锁定中！" : "正常无警报";
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ex08 安防报警主机</title>
<style>
body{text-align:center;font-family:Arial;margin-top:60px;}
.btn{padding:12px 24px;font-size:18px;margin:10px;}
.arm{background:#2e7d32;color:white;border:none;}
.disarm{background:#c62828;color:white;border:none;}
</style>
</head>
<body>
<h1>物联网安防报警器</h1>
<p>系统状态：<b>)rawliteral" + armState + R"rawliteral(</b></p>
<p>警报状态：<b>)rawliteral" + alarmState + R"rawliteral(</b></p>
<a href="/arm"><button class="btn arm">布防 Arm</button></a>
<a href="/disarm"><button class="btn disarm">撤防 Disarm</button></a>
<p>提示：布防后触摸引脚会触发持续报警，仅网页撤防可解除</p>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makePage());
}

// 布防接口
void handleArm() {
  isArm = true;
  server.sendHeader("Location", "/");
  server.send(303);
}
// 撤防接口（清除报警锁定）
void handleDisarm() {
  isArm = false;
  alarmLock = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // WiFi连接
  WiFi.begin(ssid, password);
  Serial.print("WiFi连接中");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n连接成功，访问IP：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  int touchVal = touchRead(TOUCH_PIN);
  // 布防状态下触摸触发锁定报警
  if(isArm && !alarmLock && touchVal < THRESHOLD){
    alarmLock = true;
    Serial.println("检测入侵，触发报警锁定！");
  }

  // 报警锁定时LED高频闪烁
  if(alarmLock){
    digitalWrite(LED_PIN, HIGH);
    delay(80);
    digitalWrite(LED_PIN, LOW);
    delay(80);
  }else{
    digitalWrite(LED_PIN, LOW);
  }
}