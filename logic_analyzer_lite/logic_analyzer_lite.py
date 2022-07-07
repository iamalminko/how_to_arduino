# if it hangs, CTRL+c it and try again a couple of times

import matplotlib.pyplot as plt
import serial
import time


def write_read(serial_port, x):
    serial_port.write(bytes(x, 'utf-8'))
    time.sleep(0.05)

    bytesToRead = serial_port.inWaiting()
    #print("Bytes to read: " + str(bytesToRead))

    data = serial_port.readline()
    return data

# Optional function - not part of logic analyzer functionality
# Gets arrays of timestamps and values 0,1
# Converts these arrays to binary sequence
def A_D_conversion(x, y):
    min_diff = x[1] - x[0]
    for i in range(1, len(x)):
        if x[i]-x[i-1] < min_diff:
            min_diff = x[i]-x[i-1]
    print(min_diff)

    binary = []
    for i in range(1, len(x)):
        diff = x[i] - x[i-1]
        periods = diff/min_diff

        for j in range(int(periods)):
            binary.append(y[i-1])
            print(y[i-1], end='')
    print("\n")
    return binary


# Global variables
line = b''
rows = 8
cols = 2
arr = [[[0, 0] for _ in range(cols)] for _ in range(rows)] # this command fills 2 zero pairs in each row
diff = 0

# Init communication - change COM8 to your port
arduino = serial.Serial(port='COM8', baudrate=115200, timeout=.1)
time.sleep(4)

# Sending a request byte to Arduino - G means go
while line == b'':
    line = write_read(arduino, 'G')

# close the connection so that you can analyse the plot while uploading new code to arduino
arduino.close()

# data is in binary (b'') so we need to encode it to string (str)
data = line.split(b';')

# init first row in arr:
start_index = 0
start_state = []

# set the initial state for each channel
while True:
    pair_split = data[start_index].split(b',')
    if pair_split == [''] or pair_split[0] == b'' or not pair_split[0].isdigit() or not pair_split[1].isdigit():
        start_index += 1
        continue
    start_state = [(int(pair_split[1]) & (1<<x))>>x for x in [7,6,5,4,3,2,1,0]]
    for i in range(8):
        arr[i].append([int(pair_split[0]), start_state[7-i]])
    break

for i in range(1, len(data) - start_index):
    pair = data[i + start_index]
    pair_split = pair.split(b',')
    if pair_split == [''] or pair_split[0] == b'' or not pair_split[0].isdigit() or not pair_split[1].isdigit() or type(pair_split) != list:
        continue
    value = [(int(pair_split[1]) & (1<<x))>>x for x in [7,6,5,4,3,2,1,0]]
    for j in range(8):
        state = value[7-j]
        toggled_value = 0
        if state == 1:
            toggled_value = 1 - arr[j][-1][1]
        arr[j].append([int(pair_split[0]), toggled_value])
        

#print("Buffer_len: ", len(arr)) # length of the array to plot
#x, y = zip(*arr) # separate pairs into two arrays
x, y = zip(*arr[2]) # I used the 2nd column because serial is connected to pin 10 (PINB is 8-15 pins)separate pairs into two arrays

# take first timestamp as reference and subtract from every timestamp in array
# this makes time on the plot start at 0 and not with some 6-digit number
ref = x[0]
x = [a - ref for a in x]

# A/D conversion
#A_D_conversion(x, y)

# You can also invert the binary array
# That makes 1 high and 0 low
#y_inv = [1-a for a in y]
#print(y, y_inv)

# Plot inverted
#plt.step(x,y_inv)

# Plot 
#plt.step(x,y)
plt.step(x[30:61],y[30:61]) # I zoomed in on one timeframe, you can uncomment the line above to get the full plot

# Add Title and Axes names
plt.title("Serial Signal")
plt.xlabel("time")
plt.ylabel("voltage level")

# Display
plt.show()
