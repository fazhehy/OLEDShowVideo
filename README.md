# OLEDShowVideo
利用STM32和0.96寸IIC接口OLED屏幕播放视频
## 程序大致思路
1. 利用OpenCV将视频处理成OLED数据
2. 用python的serial库，通过串口将数据发送给STM32
3. STM32接收数据，显示图片
