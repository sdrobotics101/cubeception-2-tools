import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys

fig = plt.figure()
fig.canvas.set_window_title("Cubeception Depth")

ax = fig.add_subplot(111, axisbg='blue')
ax.set_xlim(0,2)
ax.set_ylim(0,5.5)

ax.set_xticklabels([])
ax.set_yticklabels([])

ax.invert_yaxis()

ymin = 0
ymax = 5
x = 1

ax.hlines([0.1, 1.1, 2.1, 3.1, 4.1, 5.1], 0.90, 1.1, color='orange')
for i in range(0, 6):
	ax.text(0.87, i+0.17, i, horizontalalignment='right', color='orange')

pt = ax.plot(x, 0, 'ws', ms=15, mfc='w')

def animate(i):
	line = sys.stdin.readline()
	array = (line.split(' '))

	if len(array) == 5:
		D = float(array[3]) + 0.1
		ax.lines.pop(0)
		pt = ax.plot(x, D, 'ws', ms=10, mfc='w')

ani = animation.FuncAnimation(fig, animate, interval=5)
plt.show()

