#在树莓派上跑的client

import _thread
import random
import socket
import time
import serial

x1_grid=0
y1_grid=0

def socket_send_data(port):
    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 获取本地主机名
    host = '192.168.137.1'
    # 连接服务，指定主机和端口
    s.connect((host, port))
    # 接收小于 1024 字节的数据
    msg = s.recv(1024)
    print(msg.decode('utf-8'))

    current_id=8

    x = [0, 3, 6, 9]
    y = [0, 3, 6, 9]
    global x1_grid
    global y1_grid


    while 1:
        time.sleep(1)
        new_data = [x[x1_grid], y[y1_grid]]
        msg = "".join(str(new_data).strip())
        print(msg)
        current_id += 2
        s.send(msg.encode('utf-8'))

    s.close()

def socket_receive_cmd(port):

    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 获取本地主机名
    host = '192.168.137.1'
    # 连接服务，指定主机和端口
    s.connect((host, port))
    # 接收小于 1024 字节的数据
    msg = s.recv(1024)
    print(msg.decode('utf-8'))
    msg = s.recv(1024)
    msg = msg.decode('utf-8')

    msg = msg.strip("")
    print(msg)  # 机器人的移动指令序列
    '''
    while 1:
        print("im doing it!")
        time.sleep(5)
    '''
    ser = serial.Serial("/dev/ttyUSB1", 115200, timeout=1);

    i = 0

    time.sleep(20)

    current='x'
    global x1_grid
    global y1_grid

    while i<len(msg):
        command = msg[i]
        if command=='s':
            if current=='x':
                x1_grid+=1
            else:
                y1_grid+=1
        if (command=='l')or(command=='r'):
            if current=='x':
                current='y'
            else:
                current='x'

        if len(command) > 0:
            print("Received: %s" % command)
            ser.write(command.encode('utf-8'))
            time.sleep(5)
            print(ser.readall())

        i+=1

    s.close()



_thread.start_new_thread(socket_send_data, (9988,))
_thread.start_new_thread(socket_receive_cmd, (9999,))


while 1:
    pass
