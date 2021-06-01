import random
from collections import deque

dirs = [
    lambda x, y: (x, y + 1),  # 右
    lambda x, y: (x + 1, y),  # 下
    lambda x, y: (x, y - 1),  # 左
    lambda x, y: (x - 1, y),  # 上
]


# BFS-two_way
def bfs(x1, y1, x2, y2):
    maze = [
        [1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1]
    ]
    q = deque()
    path = []
    q.append((x1, y1, -1))
    maze[x1][y1] = 2
    while len(q) > 0:
        cur_node = q.popleft()
        path.append(cur_node)
        if cur_node[:2] == (x2, y2):
            realpath = []
            i = len(path) - 1
            while i >= 0:
                realpath.append(path[i][:2])
                i = path[i][2]
            realpath.reverse()
            return realpath
        for d in dirs:
            next_x, next_y = d(cur_node[0], cur_node[1])
            if maze[next_x][next_y] == 0:
                q.append((next_x, next_y, len(path) - 1))  # path列表n-1位置的点是它的父亲
                maze[next_x][next_y] = 2
    # print(' 无路可走')
    return path


# BFS-one_way
def bfs111(x1, y1, x2, y2):
    maze = [
        [1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1]
    ]
    q = deque()
    path = []
    q.append((x1, y1, -1))
    maze[x1][y1] = 2
    while len(q) > 0:
        cur_node = q.popleft()
        path.append(cur_node)
        if cur_node[:2] == (x2, y2):
            realpath = []
            i = len(path) - 1
            while i >= 0:
                realpath.append(path[i][:2])
                i = path[i][2]
            realpath.reverse()
            # print(realpath,len(realpath))
            return realpath

        i = 0
        for d in dirs:
            if (cur_node[0] == 1 or cur_node[0] == 3) and (i == 2):
                i += 1
                continue
            if (cur_node[0] == 2 or cur_node[0] == 4) and (i == 0):
                i += 1
                continue
            if (cur_node[1] == 1 or cur_node[1] == 3) and (i == 1):
                i += 1
                continue
            if (cur_node[1] == 2 or cur_node[1] == 4) and (i == 3):
                i += 1
                continue
            next_x, next_y = d(cur_node[0], cur_node[1])
            i += 1
            if maze[next_x][next_y] == 0:
                q.append((next_x, next_y, len(path) - 1))  # path列表n-1位置的点是它的父亲
                maze[next_x][next_y] = 2
    print(' 无路可走')
    return path


def generate_mission(number):
    mission_start_ary = []
    mission_obj_ary = []
    for i in range(0, number):
        while 1:
            start_pos = (random.randint(1, 4), random.randint(1, 4))
            obj_pos = (random.randint(1, 4), random.randint(1, 4))
            if start_pos != obj_pos:
                break
        mission_start_ary.append(start_pos)
        mission_obj_ary.append(obj_pos)
    return mission_start_ary, mission_obj_ary


def choose_workspace_2(mission_start_ary, mission_obj_ary):
    # frame1: up&down
    single_mission_cnt = 0
    multi_mission_cnt = 0
    multi_mission_list = []
    for i in range(0, len(mission_obj_ary)):
        if (((mission_start_ary[i][0] <= 2) and (mission_obj_ary[i][0] <= 2))
                or ((mission_start_ary[i][0] > 2) and (mission_obj_ary[i][0] > 2))):
            single_mission_cnt += 1
        else:
            multi_mission_cnt += 1
            multi_mission_list.append(i)

    # frame1: left&right
    tsingle_mission_cnt = 0
    tmulti_mission_cnt = 0
    tmulti_mission_list = []
    for i in range(0, len(mission_obj_ary)):
        if (((mission_start_ary[i][1] <= 2) and (mission_obj_ary[i][1] <= 2))
                or ((mission_start_ary[i][1] > 2) and (mission_obj_ary[i][1] > 2))):
            tsingle_mission_cnt += 1
        else:
            tmulti_mission_cnt += 1
            tmulti_mission_list.append(i)

    if single_mission_cnt >= tsingle_mission_cnt:
        return 'frame1', multi_mission_list
    else:
        return 'frame2', tmulti_mission_list


def deal_multi_mission(frame, multi_mission_list, mission_start_ary, mission_obj_ary):
    # frame1: up&down
    if frame == 'frame1':
        for i in multi_mission_list:
            # mission start in up-space
            if mission_start_ary[i][0] <= 2:
                mission_start_ary.append(mission_start_ary[i])
                # left
                if mission_start_ary[i][1] <= 2:
                    mission_obj_ary.append((2, 2))
                    mission_start_ary.append((3, 2))
                    mission_obj_ary.append(mission_obj_ary[i])
                # right
                else:
                    mission_obj_ary.append((2, 3))
                    mission_start_ary.append((3, 3))
                    mission_obj_ary.append(mission_obj_ary[i])

            # mission start in down-space
            else:
                mission_start_ary.append(mission_start_ary[i])
                # left
                if mission_start_ary[i][1] <= 2:
                    mission_obj_ary.append((3, 2))
                    mission_start_ary.append((2, 2))
                    mission_obj_ary.append(mission_obj_ary[i])
                # right
                else:
                    mission_obj_ary.append((3, 3))
                    mission_start_ary.append((2, 3))
                    mission_obj_ary.append(mission_obj_ary[i])
        for i in multi_mission_list:
            del mission_start_ary[i]
            del mission_obj_ary[i]

    # frame2 left&right
    elif frame == 'frame2':
        for i in multi_mission_list:
            # mission start in left-space
            if mission_start_ary[i][1] <= 2:
                mission_start_ary.append(mission_start_ary[i])
                # up
                if mission_start_ary[i][0] <= 2:
                    mission_obj_ary.append((2, 2))
                    mission_start_ary.append((2, 3))
                    mission_obj_ary.append(mission_obj_ary[i])
                # down
                else:
                    mission_obj_ary.append((3, 2))
                    mission_start_ary.append((3, 3))
                    mission_obj_ary.append(mission_obj_ary[i])

            # mission start in right-space
            else:
                mission_start_ary.append(mission_start_ary[i])
                # up
                if mission_start_ary[i][0] <= 2:
                    mission_obj_ary.append((2, 3))
                    mission_start_ary.append((2, 2))
                    mission_obj_ary.append(mission_obj_ary[i])
                # down
                else:
                    mission_obj_ary.append((3, 3))
                    mission_start_ary.append((3, 2))
                    mission_obj_ary.append(mission_obj_ary[i])
        for i in multi_mission_list:
            del mission_start_ary[i]
            del mission_obj_ary[i]

    return mission_start_ary, mission_obj_ary


def send_mission_list(frame, mission_start_ary, mission_obj_ary):
    mission_start_1 = []
    mission_obj_1 = []
    mission_start_2 = []
    mission_obj_2 = []

    for i in range(0, len(mission_start_ary)):
        # up&down
        if frame == 'frame1':
            if mission_start_ary[i][0] <= 2:
                mission_start_1.append(mission_start_ary[i])
                mission_obj_1.append(mission_obj_ary[i])
            else:
                mission_start_2.append(mission_start_ary[i])
                mission_obj_2.append(mission_obj_ary[i])

        # left&right
        if frame == 'frame2':
            if mission_start_ary[i][1] <= 2:
                mission_start_1.append(mission_start_ary[i])
                mission_obj_1.append(mission_obj_ary[i])
            else:
                mission_start_2.append(mission_start_ary[i])
                mission_obj_2.append(mission_obj_ary[i])

    return mission_start_1, mission_obj_1, mission_start_2, mission_obj_2


def generate_cmd(x1, y1, x2, y2):
    current_direction = 's'
    path = bfs(x1, y1, x2, y2)

    cmd_ary = []

    for i in range(0, len(path) - 1):
        if path[i][0] < path[i + 1][0]:
            cmd_ary.append("S")
            continue
        if path[i][0] > path[i + 1][0]:
            cmd_ary.append("B")
            continue
        if path[i][1] < path[i + 1][1]:
            cmd_ary.append("R")
            continue
        if path[i][1] > path[i + 1][1]:
            cmd_ary.append("L")
            continue

    # print(cmd_ary)

    #    L
    #  B o S
    #    R

    # start:S

    robot_cmd_ary = ""

    i = 0
    while i < len(cmd_ary):
        if cmd_ary[i] == current_direction:
            robot_cmd_ary = robot_cmd_ary + 's'
            i += 1
            continue
        elif (((cmd_ary[i] == "L") and (current_direction == "B"))
              or ((cmd_ary[i] == "S") and (current_direction == "L"))
              or ((cmd_ary[i] == "R") and (current_direction == "S"))
              or ((cmd_ary[i] == "B") and (current_direction == "R"))):
            robot_cmd_ary = robot_cmd_ary + 'r'
            current_direction = cmd_ary[i]
            continue
        elif (((cmd_ary[i] == "B") and (current_direction == "L"))
              or ((cmd_ary[i] == "L") and (current_direction == "S"))
              or ((cmd_ary[i] == "S") and (current_direction == "R"))
              or ((cmd_ary[i] == "R") and (current_direction == "B"))):
            robot_cmd_ary = robot_cmd_ary + 'l'
            current_direction = cmd_ary[i]
            continue
        else:
            robot_cmd_ary = robot_cmd_ary + 'b'
            current_direction = cmd_ary[i]
            continue

    if (current_direction == "L"):
        robot_cmd_ary = robot_cmd_ary + 'r'
    elif (current_direction == "R"):
        robot_cmd_ary = robot_cmd_ary + 'l'
    elif (current_direction == "B"):
        robot_cmd_ary = robot_cmd_ary + 'b'

    # print(robot_cmd_ary)

    return robot_cmd_ary


def two_way(lx, ly):
    frame, multi_mission_ary = choose_workspace_2(lx, ly)

    a, b = deal_multi_mission(frame, multi_mission_ary, lx, ly)

    q, w, e, r = send_mission_list(frame, a, b)

    length = 0
    len1 = 0

    for i in range(0, len(q)):
        cmd = generate_cmd(q[i][0], q[i][1], w[i][0], w[i][1])

        length = length + len(cmd)

    for i in range(0, len(e)):
        cmd = generate_cmd(e[i][0], e[i][1], r[i][0], r[i][1])

        len1 = len1 + len(cmd)

    return max(length, len1)


def one_way(lx, ly):
    lx1 = []
    ly1 = []
    lx2 = []
    ly2 = []
    for i in range(0, len(lx)):
        if i % 2 == 0:
            lx1.append(lx[i])
            ly1.append(ly[i])
        else:
            lx2.append(lx[i])
            ly2.append(ly[i])

    length = 0
    len1 = 0

    for i in range(0, len(lx1)):
        cmd = generate_cmd(lx1[i][0], lx1[i][1], ly1[i][0], ly1[i][1])

        length = length + len(cmd)

    for i in range(0, len(lx2)):
        cmd = generate_cmd(lx2[i][0], lx2[i][1], ly2[i][0], ly2[i][1])

        len1 = len1 + len(cmd)

    return max(length, len1)


# 画图
'''
pltx=[]
plty=[]
pltz=[]
pltw=[]
pltaa=[]

n=500
lx,ly=generate_mission(n)
pltx.append(one_way(lx,ly))
plty.append(one_way(lx,ly)+n*0.5)
pltz.append(one_way(lx,ly)+n)
pltw.append(two_way(lx,ly))
x1=lx[0:100]
x2=lx[100:200]
x3=lx[200:300]
x4=lx[300:400]
x5=lx[400:500]
y1 = ly[0:100]
y2 = ly[100:200]
y3 = ly[200:300]
y4 = ly[300:400]
y5 = ly[400:500]
pltaa.append(two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5))

n=1000
lx,ly=generate_mission(n)
pltx.append(one_way(lx,ly))
plty.append(one_way(lx,ly)+n*0.5)
pltz.append(one_way(lx,ly)+n)
pltw.append(two_way(lx,ly))
x1=lx[0:200]
x2=lx[200:400]
x3=lx[400:600]
x4=lx[600:800]
x5=lx[800:1000]
y1 = ly[0:200]
y2 = ly[200:400]
y3 = ly[400:600]
y4 = ly[600:800]
y5 = ly[800:1000]
pltaa.append(two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5))

n=5000
lx,ly=generate_mission(n)
pltx.append(one_way(lx,ly))
plty.append(one_way(lx,ly)+n*0.5)
pltz.append(one_way(lx,ly)+n)
pltw.append(two_way(lx,ly))
x1=lx[0:1000]
x2=lx[1000:2000]
x3=lx[2000:3000]
x4=lx[3000:4000]
x5=lx[4000:5000]
y1 = ly[0:1000]
y2 = ly[1000:2000]
y3 = ly[2000:3000]
y4 = ly[3000:4000]
y5 = ly[4000:5000]
pltaa.append(two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5))

n=10000
lx,ly=generate_mission(n)
pltx.append(one_way(lx,ly))
plty.append(one_way(lx,ly)+n*0.5)
pltz.append(one_way(lx,ly)+n)
pltw.append(two_way(lx,ly))
x1=lx[0:2000]
x2=lx[2000:4000]
x3=lx[4000:6000]
x4=lx[6000:8000]
x5=lx[8000:10000]
y1 = ly[0:2000]
y2 = ly[2000:4000]
y3 = ly[4000:6000]
y4 = ly[6000:8000]
y5 = ly[8000:10000]
pltaa.append(two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5))



plt.bar(range(0,40,10),pltx,color='blue',label="One-way channel")
plt.bar(range(1,41,10),plty,color='blue')
plt.bar(range(2,42,10),pltz,color='blue')
plt.bar(range(3,43,10),pltw,color='red',label="Two-way channel(fixed workplace)")
plt.bar(range(4,44,10),pltaa,color='orange',label="Two-way channel(dynamic workplace)")
plt.xticks([2,12,22,32],['500','1000','5000','10000'])
plt.legend(loc="upper left")
plt.show()
'''

# 画图
'''
pltx=[]
plty=[]
pltz=[]
pltw=[]

n=1000
lx,ly=generate_mission(n)

pltx.append(two_way(lx,ly))

x1=lx[0:500]
x2=lx[500:1000]
y1=ly[0:500]
y2=ly[500:1000]
plty.append(two_way(x1,y1)+two_way(x2,y2))


x1=lx[0:200]
x2=lx[200:400]
x3=lx[400:600]
x4=lx[600:800]
x5=lx[800:1000]
y1 = ly[0:200]
y2 = ly[200:400]
y3 = ly[400:600]
y4 = ly[600:800]
y5 = ly[800:1000]
pltz.append(two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5))

x1=lx[0:100]
x2=lx[100:200]
x3=lx[200:300]
x4=lx[300:400]
x5=lx[400:500]
x6=lx[500:600]
x7=lx[600:700]
x8=lx[700:800]
x9=lx[800:900]
x10=lx[900:1000]
y1 = ly[0:100]
y2 = ly[100:200]
y3 = ly[200:300]
y4 = ly[300:400]
y5 = ly[400:500]
y6 = ly[500:600]
y7 = ly[600:700]
y8 = ly[700:800]
y9 = ly[800:900]
y10 = ly[900:1000]
pltw.append(
    two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5)+
    two_way(x6,y6)+two_way(x7,y7)+two_way(x8,y8)+two_way(x9,y9)+two_way(x10,y10)
            )

plt.bar(10,pltx,color='blue',label='Two-way channel')
plt.bar(20,plty,color='blue')
plt.bar(30,pltz,color='blue')
plt.bar(40,pltw,color='blue')
plt.xticks([10,20,30,40],['fixed','2 groups','5 groups','10 groups'])
plt.legend(loc="upper right")
plt.show()
'''

# 画图
'''
pltx=[]
plty=[]
pltz=[]
pltw=[]

n=10000
lx,ly=generate_mission(n)

pltx.append(two_way(lx,ly))

x1=lx[0:5000]
x2=lx[5000:10000]
y1=ly[0:5000]
y2=ly[5000:10000]
plty.append(two_way(x1,y1)+two_way(x2,y2))


x1=lx[0:2000]
x2=lx[2000:4000]
x3=lx[4000:6000]
x4=lx[6000:8000]
x5=lx[8000:10000]
y1 = ly[0:2000]
y2 = ly[2000:4000]
y3 = ly[4000:6000]
y4 = ly[6000:8000]
y5 = ly[8000:10000]
pltz.append(two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5))

x1=lx[0:1000]
x2=lx[1000:2000]
x3=lx[2000:3000]
x4=lx[3000:4000]
x5=lx[4000:5000]
x6=lx[5000:6000]
x7=lx[6000:7000]
x8=lx[7000:8000]
x9=lx[8000:9000]
x10=lx[9000:10000]
y1 = ly[0:1000]
y2 = ly[1000:2000]
y3 = ly[2000:3000]
y4 = ly[3000:4000]
y5 = ly[4000:5000]
y6 = ly[5000:6000]
y7 = ly[6000:7000]
y8 = ly[7000:8000]
y9 = ly[8000:9000]
y10 = ly[9000:10000]
pltw.append(
    two_way(x1,y1)+two_way(x2,y2)+two_way(x3,y3)+two_way(x4,y4)+two_way(x5,y5)+
    two_way(x6,y6)+two_way(x7,y7)+two_way(x8,y8)+two_way(x9,y9)+two_way(x10,y10)
            )

plt.bar(10,pltx,color='blue',label='Two-way channel')
plt.bar(20,plty,color='blue')
plt.bar(30,pltz,color='blue')
plt.bar(40,pltw,color='blue')
plt.xticks([10,20,30,40],['fixed','2 groups','5 groups','10 groups'])
plt.legend(loc="upper right")
plt.show()
'''
