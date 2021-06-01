#生成单个机器人的路径

import random
from path import solve_maze_with_queue


def generate_cmd(start_pos, obj_pos):
    current_direction = "S"
    # 生成一个任务
    print(start_pos, obj_pos)
    # 生成一个路径
    path = solve_maze_with_queue(start_pos[0], start_pos[1], obj_pos[0], obj_pos[1])

    #print(path)

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

    #print(cmd_ary)

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

    print(robot_cmd_ary)

    return robot_cmd_ary

#print(generate_cmd((4,4),"S"))
