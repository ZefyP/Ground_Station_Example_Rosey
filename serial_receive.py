import time
import serial # import serial library
from string import digits

results_file = open("data.txt","a")

# get the start time
start_time = time.time()

arduinoSerialData = serial.Serial('com5', 115200)
while (1==1):
    if (arduinoSerialData.inWaiting()>0):        
        # get the runtime
        current_time = time.time()
        elapsed_time= current_time - start_time # get runtime in seconds
        elapsed_time = f"{elapsed_time:.2f}"    # limit float precision to 2 decimals

        results_file.write( str(elapsed_time) + ',')
        myData = arduinoSerialData.readline() # reads everything as a string
        myData = myData.decode('utf-8').strip() # decode received data. clean digit string
        results_file.write(str(myData)+ '\n')
        print (myData)

results_file.close()