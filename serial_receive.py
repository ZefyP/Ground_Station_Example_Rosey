import time
import serial # import serial library
from string import digits

results_file = open("data.txt","a")

# get the start time
start_time = time.time()

arduinoSerialData = serial.Serial('com5', 115200)
while (1==1):
    if (arduinoSerialData.inWaiting()>0):
        # record timestamp in seconds
        now = time.time()
        runtime = int(now - start_time)
        results_file.write(str(runtime) + ',')

        myData = arduinoSerialData.readline() # reads everything as a string
        myData = myData.decode('utf-8').strip() # decode received data. clean digit string
        results_file.write(str(myData)+ '\n')
        print (myData)

results_file.close()

# get the execution time
end_time = time.time()
elapsed_time = end_time - start_time
print('execution time: ', elapsed_time, 'seconds')