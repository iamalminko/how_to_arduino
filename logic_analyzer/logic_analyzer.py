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
arr = []
diff = 0

# Init communication - change COM8 to your port
arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)

# Sending a request byte to Arduino - G means go
while line == b'':
	line = write_read(arduino, 'G')

#print(line) # printing the line read

# close the connection so that you can analyse the plot while uploading new code to arduino
arduino.close() 

# data is in binary (b'') so we need to encode it to string (str)
line = line.decode("utf-8")
sep = line.split(";") # each pair is separated by ;

# loop over pairs and store them in arr as integer pairs
for pair in sep:
	pair_split = pair.split(",")
	#print(pair_split)
	if pair_split == ['']:
		continue
	sep = list(map(int, pair_split))

	#print(sep[0]-diff) # print time intervals
	diff = sep[0]
	arr.append(sep)

#arr = arr[1:]
#print("Buffer_len: ", len(arr)) # length of the array to plot
x, y = zip(*arr) # separate pairs into two arrays

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
plt.step(x,y)

# Add Title and Axes names
plt.title("Serial Signal")
plt.xlabel("time")
plt.ylabel("voltage level")

# Display
plt.show()
