#在树莓派上跑的client

import _thread
import random
import socket
import time
import serial

x_grid=0
y_grid=0
status=0
sensor1=0
sensor2=0


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


    x = [0, 3, 6, 9]
    y = [0, 3, 6, 9]
    global x_grid
    global y_grid
    global status
    global sensor1
    global sensor2
    current_id=7

    while 1:
        time.sleep(1)
        new_data = [current_id, sensor1,sensor2, random.randint(30, 80),
                    status,
                    x[x_grid], y[y_grid],0, 0]
        msg = "".join(str(new_data).strip())
        print(msg)
        current_id += 1
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
    global x_grid
    global y_grid
    global status
    global sensor1
    global sensor2

    while i<len(msg):
        command = msg[i]
        if command=='s':
            if current=='x':
                x_grid+=1
            else:
                y_grid+=1
        if (command=='l')or(command=='r'):
            if current=='x':
                current='y'
            else:
                current='x'
        status=int(100*(i+1)/len(msg))
        if len(command) > 0:
            print("Received: %s" % command)
            ser.write(command.encode('utf-8'))
            time.sleep(5)
            feedback=ser.readall()
            print(feedback.decode('utf-8'))
            feedback=feedback.decode('utf-8')
            value1=feedback[0]+feedback[1]
            print(value1)
            value2=feedback[4]+feedback[5]
            print(value2)
            sensor1=int(value1)
            sensor2=int(value2)
            
            
            

        i+=1

    s.close()



_thread.start_new_thread(socket_send_data, (8888,))
_thread.start_new_thread(socket_receive_cmd, (8899,))


while 1:
    pass
