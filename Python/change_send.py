import cv2
import numpy as np
import serial


class UART(serial.Serial):

    def __init__(self, port, baudrate, timeout):
        try:
            super().__init__(port=port, baudrate=baudrate, timeout=timeout)
        except serial.serialutil.SerialException:
            print('找不到串口！')
        except Exception as result:
            print("未知错误 %s" % result)

    def send(self, byte):
        super().write(chr(byte).encode('iso-8859-1'))

    def receive(self):
        return super().read()

    def close(self):
        super().close()


class ImageChange(object):

    def __init__(self):
        self.__img = np.zeros((64, 128), np.uint8)
        self.__img_lst = []

    def img_load(self, image):
        self.__img = image

    def img_read(self):
        self.__img_lst = []
        return self.__img

    def change_threshold(self):
        self.__img = cv2.cvtColor(self.__img, cv2.COLOR_BGR2GRAY)
        self.__img = cv2.resize(self.__img, (128, 64))
        ret, self.__img = cv2.threshold(self.__img, 127, 255, cv2.THRESH_BINARY)
        return self.__img

    def change_canny(self):
        self.__img = cv2.cvtColor(self.__img, cv2.COLOR_BGR2GRAY)
        self.__img = cv2.resize(self.__img, (128, 64))
        self.__img = cv2.Canny(self.__img, 50, 100)

        return self.__img

    def __page_deal(self, pageNum):
        data = 0
        for x in range(128):
            for y in range(8):
                temp = self.__img[y + pageNum * 8][x]
                if temp == 255:
                    data |= 0x01 << y
            self.__img_lst.append(data)
            data = 0

    def get_data(self):
        for i in range(8):
            self.__page_deal(i)
        return self.__img_lst

