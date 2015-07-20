#!/usr/bin/python
import sys
import time

vx = 0
vy = 0
vz = 0
rx = 0
ry = 0
rz = 0

usetime = False

if len(sys.argv) > 1:
	if sys.argv[1] == "-t":
		usetime = True

while 1:
	start = time.time()
	command = input('')
	array = command.split(' ')
	if array[0] == 'vx':
		vx = array[1]
	elif array[0] == 'vy':
		vy = array[1]
	elif array[0] == 'vz':
		vz = array[1]
	elif array[0] == 'rx':
		rx = array[1]
	elif array[0] == 'ry':
		ry = array[1]
	elif array[0] == 'rz':
		rz = array[1]
	elif array[0] == 'exit':
		break

	if usetime:
		str = "{0} {1} {2} {3} {4} {5} {6}".format(vx, vy, vz, rx, ry, rz, round((time.time() - start) * 1000))
	else:
		str = "{0} {1} {2} {3} {4} {5} 0".format(vx, vy, vz, rx, ry, rz)
	sys.stdout.write(str)
	sys.stdout.write("\n")
