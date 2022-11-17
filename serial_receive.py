import time
import serial # import serial library
from string import digits

results_file = open("data.txt","a")

arduinoSerialData = serial.Serial('com5', 115200)
while (1==1):
    if (arduinoSerialData.inWaiting()>0):
        myData = arduinoSerialData.readline() # reads everything as a string
        myData = myData.decode('utf-8').strip() # decode received data. clean digit string
        results_file.write(str(myData)+ '\n')
        print (myData)

results_file.close()