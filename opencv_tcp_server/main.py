import socket
import cv2
import numpy
import threading
import os, sys

# import RPi.GPIO
import serial

ip = '192.168.3.32'  ## 当前目标主机ip
port = 8080

true = True
video = cv2.VideoCapture(0)
width = 480  ## 360p=480*360 /// 720p=1280*720 /// 480p=854*480 /// 1080p=1920*1080
height = 360
video.set(cv2.CAP_PROP_FRAME_WIDTH, width)
video.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((ip, port))
ser=serial.Serial('/dev/ttyAMA0',9600)

def send_frame(v, s):  ## send the video to target
    while True:
        success, image = v.read()
        #b, g, r = cv2.split(image)  # 拆分通道
        #image = cv2.merge([r, g, b])  # 合并通道
        ret, jpeg = cv2.imencode('.jpg', image)
        img_code = numpy.array(jpeg)
        img_data = img_code.tobytes()
        plength = '1' + '1' + str(len(img_data)).ljust(16)

        try:
            s.send(plength.encode('utf-8'))
            #print(len(img_data))
            s.send(img_data)

        except:
            v.release()
            s.close()
            os._exit(0)


def recieve_comm(s):
    while true:
        try:
            recve = s.recv(1024)
            msg = recve.decode()
            #print(msg)
            if (len(msg) >= 3):
                if msg == "exit":
                    s.close()
                    os._exit(0)

                if (recve[0] == 48):
                    if (recve[2] == 1+48):
                        run()

                    elif (recve[2] == 2+48):
                        back()

                    elif (recve[2] == 3+48):
                        right()

                    elif (recve[2] == 4+48):
                        left()

                    elif (recve[2] == 5+48):
                        brake()

                    else:
                        print('this is an error num in [0,x]')

                elif recve[0] == 48+2:
                    # 此处更改一下格式为 ['2', 'x', '-', 'y'], 加了一个“-”
                    if (recve[3]>=48):
                        tenth = recve[2] - 48
                        sing = recve[3] - 48
                        roatate(tenth * 10 + sing)

                    else:
                        print('this is an error num in [2,xx]')


        except:
            s.close()
            os._exit(0)
    return msg


def run():
    print('run')
    ser.write('\x00\x01'.encode('utf-8'))
    return


def back():
    print('back')
    ser.write('\x00\x02'.encode('utf-8'))
    return


def right():
    print('right')
    ser.write('\x00\x03'.encode('utf-8'))
    return


def left():
    print('left')
    ser.write('\x00\x04'.encode('utf-8'))
    return


def brake():
    print('brake')
    ser.write('\x00\x05'.encode('utf-8'))
    return


def roatate(angle):
    print('rotate ',str(angle))
    final='2'+str(angle)
    all=final.decode("hex")
    ser.write(all)
    return

try:
    if ser.isOpen==False:
        ser.open()
except:
    print('make sure serial is connected')
threading.Thread(target=send_frame, args=(video, sock,)).start()
threading.Thread(target=recieve_comm, args=(sock,)).start()
