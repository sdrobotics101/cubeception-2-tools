#!/usr/bin/python
import cv2.cv as cv
import time
import sys

print("Opening camera")
capture = cv.CaptureFromCAM(0)
time.sleep(5)
print("Camera opened")

numImages = 10
period = 1

if len(sys.argv) == 3:
	numImages = int(sys.argv[1])
	period = float(sys.argv[2])
elif len(sys.argv) == 2:
	numImages = int(sys.argv[1])

print("Taking {0} images with {1} second delay".format(numImages, period))

for i in range(0, numImages):
	img = cv.QueryFrame(capture)
	cv.SaveImage("/home/ubuntu/images/img{0}.png".format(i), img)
	print("Saved image {0}".format(i))
	time.sleep(period)
