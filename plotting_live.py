"""
Created on Wed 16 Nov 2022
@author: Zefy Pissaki | zpissaki@gmail.com 
"""
import time
import serial # import serial library
from string import digits
import matplotlib.pyplot as plt # import matpltlib library
from drawnow import *

# create a file to write and read from
# results_file = open("data.txt","a")

# get the start time
start_time = time.time()

time = []
distanceF = []
meas_A =[]
arduinoSerialData = serial.Serial('com5', 115200)
plt.ion() # tell matplotlib that interactive mode is on to plot the live data
cnt = 0 # create counter



def makeFig(): # create a function that makes the desired plot
    # plt.ylim(80,90)
    plt.title('Data live stream')
    plt.grid(True)
    plt.ylabel('Sensor Data')
    plt.plot(distanceF,'ro-', label = 'Zefy')
    plt.legend(loc='upper left')
    plt.xlabel('Time (seconds)')

    # # create second y axis
    # plt2 = plt.twinx()
    # plt2.plot(meas_,'b^-', label = 'Iro')


while True: # loop for forever
    while (arduinoSerialData.inWaiting() == 0): # Wait here until there is data
       pass #do nothing

    myData = arduinoSerialData.readline()       # reads everything as a string
    myData = myData.decode('utf-8').strip()     # decode received data. clean digit string
    
    print (myData) # print the data on the terminal

    dataArray = myData.split(',')
    distance = float( dataArray[0] )
    distanceF.append(distance)
    # meas_A.append(distance+4.0)


    # for eachLine in myData:
    #     if len(eachLine)>1:
    #         x,y = eachLine.split(',')
    #         time.append(float(x))
    #         distance.append(float(y))
    
    drawnow(makeFig) # call drawnow to update the live graph
    plt.pause(.000001)
    cnt = cnt+1 # increment
    if(cnt>50):
        distanceF.pop(0)# get rid of the first element in the array from the plot
# results_file.close()

# get the execution time
end_time = time.time()
elapsed_time = end_time - start_time
print('execution time: ', elapsed_time, 'seconds')