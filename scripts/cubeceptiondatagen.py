import numpy as np
import sys
import time

random = False
if (len(sys.argv) > 1):
	if (sys.argv[1] == '-r'):
		random = True
	elif (sys.argv[1] == '-i'):
		random = False
motordata = [];
if not random:
	xyzdata = [0, 45, 90, 0, 0]
	for i in range(0, 24):
		motordata.append(4 * i);

while 1:
	if random:
		motordata = np.random.randint(0, 100, 24)
		xyzdata = list(np.random.randint(-180, 180, size=3)) + list(np.random.randint(0, 5, size=2))

	motorline = "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
	xyzline = "%s %s %s %s %s"
	sys.stdout.write(motorline % tuple(motordata))
	sys.stdout.write("\n")
	sys.stdout.write(xyzline % tuple(xyzdata))
	sys.stdout.write("\n")
	sys.stdout.flush()
	
	for i in range(0, 24):
		motordata[i] = motordata[i] + 1
		if motordata[i] > 100:
			motordata[i] = 0

	for i in range(0, 3):
		xyzdata[i] = xyzdata[i] + 1
		if xyzdata[i] > 180:
			xyzdata[i] = -180
	xyzdata[3] = xyzdata[3] + 1
	if xyzdata[3] > 5:
		xyzdata[3] = 0

	time.sleep(0.10)

