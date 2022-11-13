import time
import serial # import serial library

results_file = open("datain.txt","a")

arduinoSerialData = serial.Serial('com5', 115200)
while (1==1):
    if (arduinoSerialData.inWaiting()>0):
        myData = arduinoSerialData.readline() # reads everything as a string
        results_file.write(str(myData))
        print (myData)