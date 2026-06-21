一、millis () 函数基础知识点

函数作用

millis() 是 Arduino 内置计时函数，开机后从零开始持续计时，返回无符号长整型 (unsigned long) 毫秒数，程序全程独立计时，不受 delay() 阻塞影响。

核心优势（非阻塞核心）

delay(ms) 会卡死整个程序，等待期间无法执行其他代码；

millis() 只读取时间戳，不暂停程序，可同时处理 LED 闪烁、串口输出、传感器读取等多任务。

数据类型注意事项

必须使用 unsigned long 存储时间变量，若用 int 会数值溢出、计时错乱；

单次最大计时约 49.7 天，溢出后自动归零，差值计算不受归零影响。

定时实现原理

记录上一次动作的时间戳 lastTime，每次循环读取当前时间 currentTime；

两者差值 ≥ 设定间隔时，执行目标动作并更新时间戳，实现精准周期性定时。

二、完整代码逐段解析

cpp

运行

// 定义LED引脚2

const int ledPin = 2;

// 存储当前时间、上一次翻转LED的时间戳，必须用unsigned long

unsigned long currentTime;

unsigned long lastTime = 0;

// 定时间隔500ms，每500ms翻转一次LED亮灭

const unsigned long interval = 500;



// LED亮灭状态标记

bool ledState = LOW;



void setup() {

&#x20; Serial.begin(115200); // 开启串口调试，波特率115200

&#x20; pinMode(ledPin, OUTPUT); // 将LED引脚设为输出模式

}



void loop() {

&#x20; currentTime = millis(); // 获取开机至今的当前毫秒时间戳

&#x20; // 判断距离上次翻转LED是否达到500ms间隔

&#x20; if(currentTime - lastTime >= interval)

&#x20; {

&#x20;   lastTime = currentTime; // 更新本次动作的时间戳，重置计时起点

&#x20;   ledState = !ledState; // 状态取反：LOW→HIGH / HIGH→LOW

&#x20;   digitalWrite(ledPin, ledState); // 输出电平控制LED亮灭

&#x20;   // 串口打印调试信息，实时查看LED状态

&#x20;   Serial.print("LED状态切换，当前：");

&#x20;   Serial.println(ledState ? "ON" : "OFF");

&#x20; }

}

三、功能说明

定时逻辑：间隔 500ms 翻转一次 LED，亮 500ms、灭 500ms，完整周期 1000ms，实现 1Hz 无阻塞闪烁；

非阻塞特性：loop() 循环全程不会暂停，可在 if 判断外新增其他业务代码（按键、传感器等）同步运行；

调试辅助：串口实时打印 LED 开关状态，方便观测定时是否精准。

四、关键点

时间变量 currentTime、lastTime 不能用 int，必须 unsigned long；

差值判断使用 >= 而非 ==，避免循环卡顿错过定时节点；

每次执行动作后必须更新 lastTime，否则会无限重复触发 LED 翻转。

