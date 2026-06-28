# homework
程序设计作业
Version1: Create ex01 folder, implement basic HelloWorld program.
Version2: Add encapsulated input() function for keyboard input and output.

作业 ex04 ~ ex09

## 前置说明

1. 软件环境：Arduino IDE，已安装ESP32开发板支持包

2. 通用操作：带WiFi的ex07/ex08/ex09代码，需修改 `ssid`、`password` 为自己可用WiFi；手机/电脑需与ESP32连接同一个WiFi才能访问网页；所有程序串口监视器波特率统一设置115200

---

## ex04 触摸自锁开关（无WiFi、纯硬件IO程序）

### 硬件接线

LED长脚 → GPIO2；LED短脚 → GND；金属触摸片 → GPIO4

### 运行步骤

1. 打开仓库文件夹内 `ex04/ex04\_touch\_lock.ino`

2. Arduino IDE选择开发板「ESP32 Dev Module」，选择设备COM端口

3. 点击编译校验无报错，上传烧录至ESP32开发板

4. 打开串口监视器观察触摸状态打印

### 预期实验现象

触摸GPIO4金属片瞬间，LED保持常亮，松手灯光不熄灭；再次触摸引脚，LED熄灭；快速反复触摸不会出现误触发。

---

## ex05 多档位触摸调速呼吸灯（无WiFi、纯PWM硬件程序）

### 硬件接线

LED长脚 → GPIO2；LED短脚 → GND；金属触摸片 → GPIO4

### 运行步骤

1. 打开 `ex05/ex05\_touch\_gear\_breath.ino`

2. 匹配ESP32开发板与COM端口，编译、上传代码

3. 上电后LED自动持续呼吸渐变，触摸引脚切换速度档位

### 预期实验现象

LED持续平滑明暗渐变；每触摸一次金属片，呼吸节奏切换一档，共区分慢速、中速、急促快速3种效果。

---

## ex06 双通道反相PWM警车双闪灯效（无WiFi、纯双路PWM程序）

### 硬件接线

灯A长脚 → GPIO2，短脚 → GND；灯B长脚 → GPIO13，短脚 → GND；无需触摸引脚

### 运行步骤

1. 打开 `ex06/ex06\_police\_two\_pwm.ino`

2. 选择对应开发板与端口，编译上传代码

3. 上电自动运行渐变灯效，无需额外操作

### 预期实验现象

LED A逐渐变亮的同时LED B同步变暗，亮度到达极值后自动反向循环，灯光过渡柔和无频闪。

---

## ex07 Web网页端无级调光器
### 硬件接线

LED长脚 → GPIO2；LED短脚 → GND；无需触摸引脚

### 运行步骤

1. 打开 `ex07/ex07\_web\_slider\_dimmer.ino`，修改代码顶部WiFi名称、WiFi密码并保存

2. 选择ESP32开发板、对应COM端口，编译上传代码

3. 打开串口监视器，复制打印出的设备IP地址

4. 手机/电脑连接同一WiFi，浏览器输入IP打开控制面板，拖动滑动条调节亮度

### 预期实验现象

页面出现0~255范围滑动条，拖动滑块时LED亮度实时同步平滑变化，页面实时显示当前亮度数值。

---

## ex08 物联网安防报警器模拟实验
### 硬件接线

LED长脚 → GPIO2；LED短脚 → GND；金属触摸片 → GPIO4

### 运行步骤

1. 打开 `ex08/ex08\_security\_alarm.ino`，替换代码内WiFi账号密码

2. 编译、烧录代码至ESP32，串口读取网页访问IP

3 浏览器打开网页，先点击【布防Arm】按钮开启安防系统

4. 触摸GPIO4金属片触发报警；点击【撤防Disarm】关闭灯光、重置警报状态

### 预期实验现象

未布防状态下触摸引脚无任何灯光反应；布防后触摸引脚，LED高频持续闪烁锁定报警，松手不会停止，仅网页撤防操作可熄灭LED。

--

## ex09 实时传感器Web仪表盘
### 硬件接线

金属触摸片连接GPIO4
### 运行步骤

1. 打开 `ex09/ex09\_touch\_dashboard.ino`，修改WiFi名称、密码保存文件

2. 编译上传代码，串口监视器获取网页IP地址

3. 同WiFi设备浏览器访问IP，观察页面实时数字变化

### 预期实验现象

网页中央大号数字持续自动刷新；手指靠近触摸引脚，页面数值变小；手指离开引脚，数值自动恢复变大，实现实时触摸数据监控面板。

