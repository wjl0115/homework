#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vi_lll";
const char* password = "knyqsbzirkirkbh";
#define LED_PIN 2
const int freq = 5000;
const int resolution = 8;

WebServer server(80);
int ledBright = 0; // 全局亮度0-255

// 生成带滑动条+JS的网页
String makeHtmlPage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ex07 网页无级调光</title>
<style>
body{font-family:Arial;text-align:center;margin-top:60px;}
#slider{width:80%;height:30px;margin:30px 0;}
#brightText{font-size:24px;color:#d32f2f;}
</style>
</head>
<body>
<h1>LED无级滑动调光器</h1>
<p>当前亮度：<span id="brightText">0</span></p>
<input type="range" id="slider" min="0" max="255" value="0">

<script>
const slider = document.getElementById("slider");
const text = document.getElementById("brightText");
// 滑动条变动触发请求
slider.addEventListener("input", async function(){
  let val = this.value;
  text.innerText = val;
  // fetch发送GET请求到 /set?bright=数值
  await fetch(`/set?bright=${val}`);
})
</script>
</body>
</html>
)rawliteral";
  return html;
}

// 首页页面
void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makeHtmlPage());
}

// 处理滑动条亮度请求
void handleSetBright() {
  if(server.hasArg("bright")){
    ledBright = server.arg("bright").toInt();
    // 限制范围0~255
    if(ledBright < 0) ledBright = 0;
    if(ledBright > 255) ledBright = 255;
    ledcWrite(LED_PIN, ledBright);
  }
  // 刷新页面
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, freq, resolution);
  ledcWrite(LED_PIN, ledBright);

  // WiFi连接
  WiFi.begin(ssid, password);
  Serial.print("连接WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功");
  Serial.print("访问地址：http://");
  Serial.println(WiFi.localIP());

  // 注册路由
  server.on("/", handleRoot);
  server.on("/set", handleSetBright);
  server.begin();
}

void loop() {
  server.handleClient();
}