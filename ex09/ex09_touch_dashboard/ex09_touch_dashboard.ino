#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vi_lll";
const char* password = "knyqsbzirkirkbh";
#define TOUCH_PIN 4

WebServer server(80);

// 仪表盘网页，JS定时器循环拉取触摸数值
String makeDashPage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ex09 触摸传感器实时仪表盘</title>
<style>
body{font-family:Arial;text-align:center;margin-top:80px;}
#touchNum{font-size:60px;color:#0d47a1;font-weight:bold;}
.tip{color:#666;font-size:16px;}
</style>
</head>
<body>
<h1>触摸传感器实时数据仪表盘</h1>
<p>实时采样数值：</p>
<div id="touchNum">--</div>
<p class="tip">手指靠近引脚 → 数值变小；离开 → 数值恢复变大</p>

<script>
// 每100ms自动拉取一次数据
async function updateData(){
  let res = await fetch("/getTouch");
  let num = await res.text();
  document.getElementById("touchNum").innerText = num;
}
// 循环定时刷新
setInterval(updateData, 100);
</script>
</body>
</html>
)rawliteral";
  return html;
}

// 首页仪表盘
void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makeDashPage());
}

// 接口：返回当前触摸原始数值，供网页AJAX读取
void handleGetTouchData() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);

  // WiFi连接
  WiFi.begin(ssid, password);
  Serial.print("连接WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi就绪，访问地址：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/getTouch", handleGetTouchData);
  server.begin();
}

void loop() {
  server.handleClient();
}