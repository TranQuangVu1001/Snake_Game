# ITR-VN INTERN FW – TRAINING - PROJECT
# 🐍 SNAKE 🎮
## PROJECT: SNAKE GAME USE STM32 WITH SSD1306 OLED AND TOUCHPAD TTP229
#
## TARGET: The purpose of knowing how to use I2C - UART - SPI and how to build a driver. 
#
![](https://github.com/Platane/snk/raw/output/github-contribution-grid-snake.svg)
## Describe
In this project the classic Snake game has been programmed using the STM32F4xx-Discovery board, the SSD1306 OLED display connected via I2C. Using the board's integrated Touch-pad TPP229 to move the snake.
#
## Pin map
-    SSD1306 OLED

|Port|I2C2|
|----|----|
|SCL |PB10|
|SDA |PB11|

- TOUCH PAD TTP229

|Port|SPI1|
|----|----|
|SCL |PA2|
|MISO|PA3|
#
## Touch pad 
|Number|Direction|
|------|---------|
|NUM_2|KEY_UP|
|NUM_5|KEY_LEFT|
|NUM_7|KEY_RIGHT|
|NUM_10|KEY_DOWN|
|NUM_15|KEY_START|


## Flow chart
[![flowchart.png](https://i.postimg.cc/nrv5jS1j/Bi-u-kh-ng-c-ti-u-drawio.png)](https://postimg.cc/vxZXCzkb)
## Image demo
[![1.png](https://i.postimg.cc/PfDK6hyj/1.png)](https://postimg.cc/XXVwJRtH)
## Video demo
![](2.gif)
## Author
- Vu Tran
- Vinh Le
- Hieu Ha

