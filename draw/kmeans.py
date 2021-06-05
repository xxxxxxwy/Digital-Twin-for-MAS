from sklearn.cluster import KMeans
import numpy as np
from random import randint
import matplotlib.pyplot as plt

black=(10,30)
gray=(30,60)
white=(65,90)

def straight_line_normal_case(num):
    points=[]
    for i in range(0,num):
        #left:black right:black
        points.append([randint(black[0],black[1]),randint(black[0],black[1])])
        #left:black right:gray
        points.append([randint(black[0],black[1]),randint(gray[0],gray[1])])
        #left:gray right:black
        points.append([randint(gray[0],gray[1]),randint(black[0],black[1])])
    return points

def straight_line_wrong_case(num):
    points=[]
    for i in range(0,num):
        #left gray right gray
        points.append([randint(gray[0],gray[1]),randint(gray[0],gray[1])])
    return points

def turn_normal_case(num):
    points = []
    for i in range(0, num):
        # left:black right:black
        points.append([randint(black[0],black[1]), randint(black[0],black[1])])
        # left:black right:gray
        points.append([randint(black[0],black[1]), randint(gray[0],gray[1])])
        # left:gray right:black
        points.append([randint(gray[0],gray[1]), randint(black[0],black[1])])
    return points

def cross_normal_case(num):
    points=[]
    for i in range(0,num):
        #left:white right white
        points.append([randint(white[0],white[1]),randint(white[0],white[1])])
    return points

def generate_fake_data(cmd_ary):
    points=[]
    for i in range(0,len(cmd_ary)):
        if (cmd_ary[i]=='l')or(cmd_ary[i]=='r'):
            points+=turn_normal_case(2)
        else:
            points+=straight_line_normal_case(4)
            points+=cross_normal_case(3)
    return points


points=generate_fake_data("rsslsrs")



lx=[]
ly=[]
for i in range(0,len(points)):
    lx.append(points[i][0])
    ly.append(points[i][1])

print("blue:",len(lx))
plt.scatter(lx,ly,color='blue',marker='o')

points1=straight_line_wrong_case(20)

lx=[]
ly=[]
for i in range(0,len(points1)):
    lx.append(points1[i][0])
    ly.append(points1[i][1])

print("red:",len(lx))
plt.scatter(lx, ly, color='red',marker='v')
plt.show()



data=points+points1
# 构造数据样本点集X，并计算K-means聚类
#X = np.array([[1, 2], [1, 4], [1, 0], [4, 2], [4, 4], [4, 0]])
X = np.array(data)
kmeans = KMeans(n_clusters=5, random_state=0).fit(X)

# 输出及聚类后的每个样本点的标签（即类别），预测新的样本点所属类别
#print(kmeans.labels_)

#print(kmeans.cluster_centers_)



lx1=[]
ly1=[]
lx2=[]
ly2=[]
lx3=[]
ly3=[]
lx4=[]
ly4=[]
lx5=[]
ly5=[]
for i in range(0,len(data)):
    if kmeans.labels_[i]==0:
        lx1.append(data[i][0])
        ly1.append(data[i][1])
    if kmeans.labels_[i]==1:
        lx2.append(data[i][0])
        ly2.append(data[i][1])
    if kmeans.labels_[i]==2:
        lx3.append(data[i][0])
        ly3.append(data[i][1])
    if kmeans.labels_[i]==3:
        lx4.append(data[i][0])
        ly4.append(data[i][1])
    if kmeans.labels_[i]==4:
        lx5.append(data[i][0])
        ly5.append(data[i][1])




plt.scatter(lx1, ly1, color='red',marker='o')
plt.scatter(lx2, ly2, color='gold',marker='v')
plt.scatter(lx3, ly3, color='blue',marker='s')
plt.scatter(lx4, ly4, color='green',marker='*')
plt.scatter(lx5, ly5, color='cyan',marker='+')
plt.show()


points1=straight_line_wrong_case(10)
print(kmeans.predict(points1))

#print(kmeans.predict([[0, 0], [4, 4], [2, 1]]))
'''
cmd len 3
blue 36
red 20
test 10
result 0.7 0.6 0.7 0.4 0.5 0.9 0.8 0.6

0.65

cmd len 6
blue 78
red 40
test 10
result 0.7 0.6 0.7 0.7 0.8 0.9 0.8 0.6

0.73

cmd len 11
blue 120
red 60
test 10
result 0.8 0.6 0.6 0.8 0.6 0.6 0.5

0.64
'''

