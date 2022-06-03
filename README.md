# OLEDShowVideo
利用STM32和0.96寸IIC接口OLED屏幕播放视频
## 程序大致思路
1. 利用OpenCV将视频处理成OLED数据
2. 用python的serial库，通过串口将数据发送给STM32
3. STM32接收数据，显示图片

## 视频效果
![image](https://github.com/Scale08/OLEDShowVideo/blob/main/%E8%A7%86%E9%A2%91%E6%95%88%E6%9E%9C.gif)

## 使用方式
1. 使用usart1，即PA9(TxD),PA10(RxD)，将线接好
2. 编译keil工程，将程序烧录进stm32
3. 运行videoChange.py，会得到一个txt文件（前提是你已安装好库）
4. 运行send.py，将数据发送给stm32
