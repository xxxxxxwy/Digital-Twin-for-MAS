import random

import matplotlib.pyplot as plt

from path import solve_maze_with_queue
from path2 import solve_maze_with_queue111
from numpy import *

def generate_cmd(start_pos, obj_pos):
    current_direction = 's'
    # 生成一个任务
    # print(start_pos, obj_pos)
    # 生成一个路径
    path = solve_maze_with_queue(start_pos[0], start_pos[1], obj_pos[0], obj_pos[1])

    # print(path)

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
        current_direction = "S"
    elif (current_direction == "R"):
        robot_cmd_ary = robot_cmd_ary + 'l'
        current_direction = "S"
    elif (current_direction == "B"):
        robot_cmd_ary = robot_cmd_ary + 'b'
        current_direction = "S"

    # print(robot_cmd_ary)

    return len(robot_cmd_ary)


def generate_cmd1(start_pos, obj_pos):
    current_direction = 's'
    # 生成一个任务
    # print(start_pos, obj_pos)
    # 生成一个路径
    path = solve_maze_with_queue111(start_pos[0], start_pos[1], obj_pos[0], obj_pos[1])

    # print(path)

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
        current_direction = "S"
    elif (current_direction == "R"):
        robot_cmd_ary = robot_cmd_ary + 'l'
        current_direction = "S"
    elif (current_direction == "B"):
        robot_cmd_ary = robot_cmd_ary + 'b'
        current_direction = "S"

    # print(robot_cmd_ary)

    return len(robot_cmd_ary)

lx1=[]
ly1=[]
lx2=[]
ly2=[]
cnt = 0
while cnt<10000:
    x1 = random.randint(1, 4)
    y1 = random.randint(1, 4)
    x2 = random.randint(1, 4)
    y2 = random.randint(1, 4)
    len1=generate_cmd((x1,y1),(x2,y2))
    len2=generate_cmd1((x1, y1), (x2, y2))
    lx1.append(cnt)
    ly1.append(len1)
    lx2.append(cnt)
    ly2.append(len2)
    cnt += 1
ly1.sort()
ly2.sort()
plt.plot(lx1,ly1,color='blue',label='Two-way channel')
plt.plot(lx2,ly2,color='red',label='One-way channel')
plt.legend(loc='upper left')


print(mean(ly2)/mean(ly1))

plt.show()