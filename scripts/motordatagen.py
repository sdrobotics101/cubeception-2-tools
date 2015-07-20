import numpy as np
import sys
import time

random = False
if (len(sys.argv) > 1):
	if (sys.argv[1] == '-r'):
		random = True
	elif (sys.argv[1] == '-i'):
		random = False
data = [];
if not random:
	for i in range(0, 24):
		data.append(4 * i);

while 1:
	if random:
		data = np.random.randint(0, 100, 24)

	line = "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
	sys.stdout.write(line % tuple(data))
	sys.stdout.write("\n")
	sys.stdout.flush()
	
	for i in range(0, 24):
		data[i] = data[i] + 1
		if data[i] > 100:
			data[i] = 0
	
	time.sleep(0.10)
