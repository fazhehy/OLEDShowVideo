import change_send
import time


uart = change_send.UART('COM14', 500000, 1)

f = open('./video/badapple.txt', mode='r')

n = 0
time.sleep(1)
for line in f.readlines():

    for i in line.replace('\n', '').split(','):
        if i != '':
            uart.send(int(i))
