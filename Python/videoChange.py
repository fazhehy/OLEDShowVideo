import change_send
import cv2

cv2.namedWindow('video', cv2.WINDOW_NORMAL)
cv2.resizeWindow('video', 128, 64)
video = cv2.VideoCapture('./video/badapple.mp4')
img = change_send.ImageChange()

videoLst = []
while video.isOpened():
    flag, frame = video.read()
    if not flag:
        break
    img.img_load(frame)
    frame = img.change_threshold()
    videoLst.append(img.get_data())
    cv2.imshow('video', frame)
    if cv2.waitKey(1) == ord('q'):
        break

cv2.destroyAllWindows()

f = open('./video/badapple.txt', mode='w')

for piece in videoLst:
    for data in piece:
        f.write(str(data)+',')
    f.write('\n')

print('Over!')