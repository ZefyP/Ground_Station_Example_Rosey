"""
Created on Wed 16 Nov 2022
@author: Zefy Pissaki | zpissaki@gmail.com 
"""
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig = plt.figure()
ax = fig.add_subplot(1,1,1)

file_data = open("data.txt","r").read()
dataArray = file_data.split('\n')
time = []
distance = []
for eachLine in dataArray:
    if len(eachLine)>1:
        x,y = eachLine.split(',')
        time.append(float(x))
        distance.append(float(y))
ax.clear()
ax.plot(time,distance)

plt.show()

# def Main():
#     ani = animation.FuncAnimation(fig, animate, interval=1000)
#     plt.show()
#     print("done")

# Main()