#!/usr/bin/python
import sys
import time
import numpy as np

random = False
if (len(sys.argv) > 1):
	if (sys.argv[1] == '-r'):
		random = True
	elif (sys.argv[1] == '-i'):
		random = False

X = 0
Y = 45
Z = 90

while 1:
	if random:
		data = np.random.randint(-180, 180, size=5)
	else:
		data = [X, Y, Z, 0, 0]
	
	line = "%s %s %s %s %s" 

	sys.stdout.write(line % tuple(data))
	sys.stdout.write("\n")
	sys.stdout.flush()
	
	if not random:
		X = X + 1
		Y = Y + 1
		Z = Z + 1
		if X > 180:
			X = -180
		if Y > 180:
			Y = -180
		if Z > 180:
			Z = -180

	time.sleep(0.10)
