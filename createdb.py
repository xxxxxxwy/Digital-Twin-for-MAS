#启动MAS服务器和数据库
#首先启动这个文件

import _thread
import socket
import sqlite3
import time

#路径生成函数 此处为了方便演示，使用固定的路径
from gnrt_cmd import generate_cmd

#102机器人的坐标位置（全局变量、0
x1_grid=0
y1_grid=0

#接收103机器人发送的数据，结合102的坐标，写入数据库.只有这个线程写入数据库，因为sqlite不允许多线程一起修改数据
def socket_receive_data_103(port):
    # 连接数据库
    conn = sqlite3.connect('mydb.db')
    c = conn.cursor()
    # 创建表
    c.execute('''DROP TABLE IF EXISTS weather''')
    c.execute('''CREATE TABLE weather (ID int PRIMARY KEY NOT NULL,
        sensor1 float, sensor2 float, sensor3 float,status float,
        x int,y int,x1 int,y1 int)''')
    # 填写fake数据
    # 格式：id sensor1 sensor2 sensor3 status x y x1 y1
    purchases = [(1, 1, 1, 1, 0, 0, 0, 0, 0),
                 (2, 1, 1, 1, 0, 0, 0, 0, 0),
                 (3, 1, 1, 1, 0, 0, 0, 0, 0),
                 (4, 1, 1, 1, 0, 0, 0, 0, 0),
                 (5, 1, 1, 1, 0, 0, 0, 0, 0),
                 (6, 1, 1, 1, 0, 0, 0, 0, 0),
                 ]
    c.executemany('INSERT INTO weather VALUES (?,?,?,?,?,?,?,?,?)', purchases)
    current_id = 7
    #首先填入7组数据，为了echart初始化的时候有较好的视觉效果
    print("db created")
    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 获取本地主机名
    host = '192.168.137.1'
    s.bind((host, port))
    # 设置最大连接数，超过后排队
    s.listen(5)

    #102机器人的坐标 全局变量
    global x1_grid
    global y1_grid

    while 1:
        # 建立客户端连接
        clientsocket, addr = s.accept()
        print("连接地址: %s" % str(addr))
        msg = '连接到了数据socket！' + "\r\n"
        clientsocket.send(msg.encode('utf-8'))
        break

    #开始接收数据
    while 1:
        msg = clientsocket.recv(1024)
        msg = msg.decode('utf-8')
        msg = msg.lstrip("[")
        msg = msg.rstrip("]")
        msg = msg.split(",")
        print(msg)

    #如果连接了102机器人，那么msg后两个元素应该取全局变量的坐标
        #msg[-2] = x1_grid
        #msg[-1] = y1_grid
        msg[-2]=0
        msg[-1]=0
        new_data = [msg]
        #向数据库写入数据
        c.executemany('INSERT INTO weather VALUES (?,?,?,?,?,?,?,?,?)', new_data)
        conn.commit()

    # 关闭
    clientsocket.close()

#102机器人的接受数据线程。102可以传入各种数据（此处只传了坐标），需要使用全局变量，因为只有103机器人能够修改数据库（sqlite3特性）
def socket_receive_data_102(port):
    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 获取本地主机名
    host = '192.168.137.1'
    s.bind((host, port))
    # 设置最大连接数，超过后排队
    s.listen(5)

    #引入全局变量
    global x1_grid
    global y1_grid

    while 1:
        # 建立客户端连接
        clientsocket, addr = s.accept()
        print("连接地址: %s" % str(addr))
        msg1 = '连接到了数据socket！' + "\r\n"
        clientsocket.send(msg1.encode('utf-8'))
        break

    while 1:
        msg = clientsocket.recv(1024)
        msg = msg.decode('utf-8')
        msg = msg.lstrip("[")
        msg = msg.rstrip("]")
        msg = msg.split(",")
        print(msg)

        x1_grid=msg[0]
        y1_grid=msg[1]



    # 关闭
    clientsocket.close()

#发送指令的线程，可以固定指令（传入cmd），可以直接生成cmd= generate_cmd(start_pos, obj_pos)
def socket_send_cmd(port,cmd):
    #cmd= generate_cmd(start_pos, obj_pos)
    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 获取本地主机名
    host = '192.168.137.1'
    s.bind((host, port))
    # 设置最大连接数，超过后排队
    s.listen(5)
    while 1:
        # 建立客户端连接
        clientsocket, addr = s.accept()
        print("连接地址: %s" % str(addr))
        msg = '连接到了指令socket！' + "\r\n"
        clientsocket.send(msg.encode('utf-8'))
        break

    clientsocket.send(cmd.encode('utf-8'))

    #没什么用，指机器人正在执行任务
    while 1:
        print("he is doing it!")
        time.sleep(5)

    # 关闭
    clientsocket.close()




#103 normal
_thread.start_new_thread(socket_receive_data_103,(8888,))
_thread.start_new_thread(socket_send_cmd, (8899,'slsrs',))

#102
_thread.start_new_thread(socket_receive_data_102,(9988,))
_thread.start_new_thread(socket_send_cmd, (9999,'rslsl',))

while 1:
    pass
