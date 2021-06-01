#双向单通道单独机器人

from collections import deque



dirs = [
    lambda x, y: (x, y + 1),  # 右
    lambda x, y: (x + 1, y),  # 下
    lambda x, y: (x, y - 1),  # 左
    lambda x, y: (x - 1, y),  # 上
]

# BFS
def solve_maze_with_queue(x1, y1, x2, y2):
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
    return path

