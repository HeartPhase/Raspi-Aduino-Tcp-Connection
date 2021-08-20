import socket
import time
import cv2
import numpy
import threading
import os, sys
import keyboard
from pynput.keyboard import Key, Listener

before=''
current=None
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(('',8080))
s.listen(1)
print('server started...')

def find_device(sock):
    while True:
        conn,addr=sock.accept()
        print('one device connected')
        start_service(conn)
        break;


def start_service(sock):
    global s
    s = sock
    #recieve_frame(s)
    ty_comm=threading.Thread(target=send_comm)
    ty_frame=threading.Thread(target=recieve_frame, args=(s,))
    ty_comm.start()
    ty_frame.start()
    '''
        with Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()
    '''
    return

def recieve_frame(sock):
    while True:
        try:
            tempdata = sock.recv(10000)

            if (tempdata[0]==tempdata[1]==49 ):
                tempdata_len = tempdata[2:17].decode()
                stringData = sock.recv(int(tempdata_len))
                #print(int(tempdata_len))
                #print(tempdata_len)
                data = numpy.frombuffer(stringData, dtype='uint8')
                tmp = cv2.imdecode(data, 1)  # 解码处理，返回mat图片
                img = cv2.resize(tmp, (480,360)) ## 360p=480*360 /// 720p=1280*720 /// 480p=854*480 /// 1080p=1920*1080
                cv2.imshow('SERVER', img)
                if cv2.waitKey(1) == Key.esc:
                    break

        except:continue
    sock.close()
    cv2.destroyAllWindows()



##此处检测键盘输入
##################################################################
def send_comm():
    keyboard.hook(check)
    keyboard.wait()
'''
def send_comm(sock):
    while True:
        key=input('command: ')
        if key == 'w':
            go_forward(sock)
        if key == 'a':
            go_left(sock)
        if key == 's':
            go_back(sock)
        if key == 'd':
            go_right(sock)
        if key == 'b':
            brake(sock)
        if key == 'q':
            exit_comm(sock)
            break
        if key.isdigit():
            rotate(sock,int(key))
'''

'''
def on_press(key):
    print('{0} 按下'.format(key))
        


# 释放键盘时回调的函数
def on_release(key):
    print('{0} 松开'.format(key))
    if key.char == 'a':
        print('u realse a')
'''





def check(x):
    global before
    global s
    w = keyboard.KeyboardEvent('down', 17, 'w')
    a = keyboard.KeyboardEvent('down', 30, 'a')
    sw = keyboard.KeyboardEvent('down', 31, 's')
    d = keyboard.KeyboardEvent('down', 32, 'd')
    q = keyboard.KeyboardEvent('down', 16, 'q')
    i = keyboard.KeyboardEvent('down', 23, 'i')
    e = keyboard.KeyboardEvent('down', 18, 'e')
    o = keyboard.KeyboardEvent('down', 24, 'o')
    '''
        if x.event_type == 'up' and x.name == a.name:
            if before != 'b':
                brake(s)
                print('a release')
                before='b'
            
        if x.event_type == 'up' and x.name == w.name:
            if before != 'b':
                brake(s)
                print('w release')
                before='b'
            
        if x.event_type == 'up' and x.name == sw.name:
            if before != 'b':
                brake(s)
                print('s release')
                before='b'
            
        if x.event_type == 'up' and x.name == d.name:
            if before != 'b':
                brake(s)
                print('d release')
                before='b'
                
        if x.event_type == 'up' and x.name == i.name:
            if before!=i.name:
                rotate(s,6)
                print('i release')
                before=i.name
    '''

    if x.event_type == 'down' and x.name == a.name:
        if before!=a.name:
            go_left(s)
            print('a down')
            before=a.name

    if x.event_type == 'down' and x.name == w.name:
        if before!=w.name:
            go_forward(s)
            print('w down')
            before=w.name


    if x.event_type == 'down' and x.name == sw.name:
        if before!=sw.name:
            go_back(s)
            print('s down')
            before=sw.name



    if x.event_type == 'down' and x.name == d.name:
        if before!=d.name:
            go_right(s)
            print('d down')
            before=d.name



    if x.event_type == 'down' and x.name == q.name:
        if before!=q.name:
            exit_comm(s)
            print('q down')
            before=q.name


    if x.event_type == 'down' and x.name == e.name:
        if before!=e.name:
            print('brake')
            brake(s)
            before=e.name

    if x.event_type == 'down' and x.name == i.name:
        if before != i.name:
            rotate(s, 0)
            print('i down')
            before = i.name

    if x.event_type == 'down' and x.name == o.name:
        if before != o.name:
            rotate(s, 6)
            print('i down')
            before = o.name
##此处检测键盘输入
##################################################################

def go_forward(sock):
    sock.send('0 1'.encode('utf-8'))


def go_back(sock):
    sock.send('0 2'.encode('utf-8'))


def go_right(sock):
    sock.send('0 3'.encode('utf-8'))


def go_left(sock):
    sock.send('0 4'.encode('utf-8'))


def exit_comm(sock):
    sock.send('exit'.encode('utf-8'))
    sock.close()
    os._exit(0)


def brake(sock):
    sock.send('0 5'.encode('utf-8'))


def rotate(sock,angle):
    tenth=angle//10
    sing=angle%10
    all='2 '+str(tenth)+str(sing)
    sock.send(all.encode('utf-8'))



find_device(s)
