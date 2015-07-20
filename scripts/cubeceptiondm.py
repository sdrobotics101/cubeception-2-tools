import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.gridspec as gridspec
import numpy as np
import sys
import time
import re

plt.rc('grid', color='#d6cf2e', linewidth=1, linestyle='-')

fig = plt.figure(figsize=(12, 5), dpi=100)
fig.canvas.set_window_title("Cubeception Control Center")

ax1 = plt.subplot2grid((2,5), (0,0), rowspan=2, colspan=2)
ax2 = plt.subplot2grid((2,5), (0,2), rowspan=2, colspan=2, polar=True, axisbg='#3c963c')
ax3 = plt.subplot2grid((2,5), (0,4), rowspan=2, axisbg='blue')
plt.tight_layout()

data = np.zeros((4,6))
im = ax1.imshow(data, interpolation='none', aspect='auto', vmin=0, vmax=100, cmap='Blues')

ax1.set_xticks(np.arange(data.shape[1]), minor=False)
ax1.set_yticks(np.arange(data.shape[0]), minor=False)

ax1.invert_yaxis()
ax1.xaxis.tick_top()

ax1.set_xticklabels(['XF', 'XR', 'YF', 'YR', 'ZF', 'ZR'], minor=False)
ax1.set_yticklabels([1, 2, 3, 4], minor=False)

ax2.plot([0], color='blue', lw=5, label='X')
ax2.plot([0], color='black', lw=5, label='Y')
ax2.plot([0], color='white', lw=5, label='Z')
ax2.legend(framealpha=0, bbox_to_anchor=(1.14,1.14))

ax2.set_theta_zero_location("N")
ax2.set_xticklabels(['0','45','90','135','180','-135','-90','-45'])
ax2.set_yticklabels([])

ax2.set_rmax(2.0)

arr1 = ax2.arrow(0, 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'blue', facecolor = 'blue', lw = 3, zorder = 9)
arr2 = ax2.arrow(0, 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'black', facecolor = 'black', lw = 3, zorder = 9)
arr3 = ax2.arrow(0, 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'white', facecolor = 'white', lw = 3, zorder = 10)

ax3.set_xlim(0,2)
ax3.set_ylim(0,5.5)

ax3.set_xticklabels([])
ax3.set_yticklabels([])

ax3.invert_yaxis()

ax3.hlines([0.1, 1.1, 2.1, 3.1, 4.1, 5.1], 0.90, 1.1, color='orange')
for i in range(0, 6):
	ax3.text(0.87, i+0.15, i, horizontalalignment='right', color='orange')

pt = ax3.plot(1, 0, 'ws', ms=0, mfc='w')

def animate(i):
	line = sys.stdin.readline()
	line = re.sub(' +', ' ', line)
	array = line.split(' ')

	if len(array) == 24:
		for i in range(0, 6):
			for j in range(0, 4):
				data[j][i] = float(array[(i*4)+j])
		im.set_data(data)

	if len(array) == 5:
		global arr1
		global arr2
		global arr3
		arr1.remove()
		arr2.remove()
		arr3.remove()
		ax3.lines.pop(0)

		X = float(array[0])
		Y = float(array[1])
		Z = float(array[2])
		D = float(array[3]) + 0.1

		arr1 = ax2.arrow(X * (np.pi/180), 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'blue', facecolor = 'blue', lw = 3, zorder = 9)
		arr2 = ax2.arrow(Y * (np.pi/180), 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'black', facecolor = 'black', lw = 3, zorder = 9)
		arr3 = ax2.arrow(Z * (np.pi/180), 0.5, 0, 1, alpha = 1, width = 0.007, edgecolor = 'white', facecolor = 'white', lw = 3, zorder = 10)
		pt = ax3.plot(1, D, 'ws', ms=50, mfc='w')

	
ani = animation.FuncAnimation(fig, animate, interval=5)
plt.show()
