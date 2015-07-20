import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys

fig = plt.figure()
fig.canvas.set_window_title("Cubeception Heatmap")

ax = fig.add_subplot(111)

data = np.zeros((4,6))
im = ax.imshow(data, interpolation='none', vmin=0, vmax=100, cmap='Blues')

ax.set_xticks(np.arange(data.shape[1]), minor=False)
ax.set_yticks(np.arange(data.shape[0]), minor=False)

ax.invert_yaxis()
ax.xaxis.tick_top()

ax.set_xticklabels(['XF', 'XR', 'YF', 'YR', 'ZF', 'ZR'], minor=False)
ax.set_yticklabels([1, 2, 3, 4], minor=False)

def animate(i):
	line = sys.stdin.readline()
	array = (line.split(' '))

	if len(array) == 24:
		for i in range(0, 6):
			for j in range(0, 4):
				data[j][i] = float(array[(i*4)+j])
		im.set_data(data)

ani = animation.FuncAnimation(fig, animate, interval=5)
plt.show()




