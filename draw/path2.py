#单向单通道单独机器人
from collections import deque



dirs = [
    lambda x, y: (x, y + 1),  # 右
    lambda x, y: (x + 1, y),  # 下
    lambda x, y: (x, y - 1),  # 左
    lambda x, y: (x - 1, y),  # 上
]

# BFS
def solve_maze_with_queue111(x1, y1, x2, y2):
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
            #print(realpath,len(realpath))
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





