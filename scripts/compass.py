import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys

plt.rc('grid', color='#d6cf2e', linewidth=1, linestyle='-')

fig = plt.figure()
fig.canvas.set_window_title("Cubeception Compass")

ax = fig.add_subplot(111, polar=True, axisbg='#3c963c')

ax.plot([0], color='blue', lw=5, label='X')
ax.plot([0], color='black', lw=5, label='Y')
ax.plot([0], color='white', lw=5, label='Z')
ax.legend(framealpha=0, bbox_to_anchor=(1.17,1.13))

ax.set_theta_zero_location("N")
ax.set_xticklabels(['0','45','90','135','180','-135','-90','-45'])
ax.set_yticklabels([])

ax.set_rmax(2.0)
plt.grid(True)

arr1 = ax.arrow(0, 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'blue', facecolor = 'blue', lw = 3, zorder = 9)
arr2 = ax.arrow(0, 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'black', facecolor = 'black', lw = 3, zorder = 9)
arr3 = ax.arrow(0, 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'white', facecolor = 'white', lw = 3, zorder = 10)

def animate(i):
	line = sys.stdin.readline()
	array = (line.split(' '))

	if len(array) == 5:
		global arr1
		global arr2
		global arr3
		arr1.remove()
		arr2.remove()
		arr3.remove()

		X = float(array[0])
		Y = float(array[1])
		Z = float(array[2])
		arr1 = ax.arrow(X * (np.pi/180), 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'blue', facecolor = 'blue', lw = 3, zorder = 9)
		arr2 = ax.arrow(Y * (np.pi/180), 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'black', facecolor = 'black', lw = 3, zorder = 9)
		arr3 = ax.arrow(Z * (np.pi/180), 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'white', facecolor = 'white', lw = 3, zorder = 10)

ani = animation.FuncAnimation(fig, animate, interval=5)
plt.show()
