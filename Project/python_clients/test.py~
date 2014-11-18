#!/usr/bin/env python

"""
This script runs various color displays for the ECE597 LED Helmet Project.

Instructions for use can be found at http://elinux.org/ECE597_Fall2014_LED_Helmet
"""

from __future__ import division
import time
import math
import sys, getopt

from random import randint

import opc
import color_utils

import string2text as str2mat

from TwitterAPI import TwitterAPI
from datetime import datetime

consumer_key = 'x3MbLSOKR1qui9e3T8aKqVSIt'
consumer_secret = 'acMWxLjWub0ZxlGHdg5ysSnWRXSQVA9G8StB5KoD0I67T0Tr4o'
access_token_key = '397862583-6BKBzIt9R1uuQqnJ2GQFml9AdlWFewC0r4ks2lGa'
access_token_secret = 'u3yO3IprlRFXn1ZntoxZG83XNaUnKs1ujcowQQHnGGvKt'

#-------------------------------------------------------------------------------
# handle command line
IP_PORT = '127.0.0.1:7890'

#-------------------------------------------------------------------------------
# connect to server

client = opc.Client(IP_PORT)
if client.can_connect():
    print '    connected to %s' % IP_PORT
else:
    # can't connect, but keep running in case the server appears later
    print '    WARNING: could not connect to %s' % IP_PORT
print


#-------------------------------------------------------------------------------
# send pixels

n_pixels = 200  # number of pixels in the included "wall" layout
fps = 20       # frames per second

api = TwitterAPI(consumer_key, consumer_secret, access_token_key, access_token_secret)
#r = api.request('search/tweets', {'q':'pizza'})
#print r.status_code

#for item in r.get_iterator():
#	print item['user']['screen_name'], item['text']

#-------------------------------------------------------------------------------
# test1()
# Use this test to ensure all pixels function
def test1():
	start_time = time.time()
	while True:
		t = time.time() - start_time
		pixels = []
		for i in range(n_pixels):
			if i%33 < 11:
				r = 64
				g = 0
				b = 0
			elif i%33 < 22:
				r = 0
				g = 64
				b = 0
			elif i%33 <33:
				r = 0
				g = 0
				b = 64
			else:
				r = 64
				g = 64
				b = 64
			pixels.append((r,g,b))
		client.put_pixels(pixels, channel=0)
		#client.put_pixels(pixels, channel=1)
		#client.put_pixels(pixels, channel=2)
		print 'frame'
		time.sleep(1/fps)

#-------------------------------------------------------------------------------
# test2()
# Use this test to ensure continuity between arrays
def test2():
	while True:
		pixels = []
		for i in range(n_pixels):
			if i%33 < 11:
				r = 64
				g = 0
				b = 0
			elif i%33 < 22:
				r = 0
				g = 64
				b = 0
			elif i%33 <33:
				r = 0
				g = 0
				b = 64
			else:
				r = 64
				g = 64
				b = 64
			pixels.append((r,g,b))
			client.put_pixels(pixels, channel=1)
			time.sleep(1/fps)
		for i in range(n_pixels-100):
			pixels.append((0,0,0))

#-------------------------------------------------------------------------------
# flashingLights()
# Randomly flashing lights are sent to the arrays
def flashingLights():
	start_time = time.time()
	pixels = []
	frame = 0
	for i in range(n_pixels):
		r = 200 - i
		g = i
		b = 10*(i % 10) 
		pixels.append((r,g,b))
	client.put_pixels(pixels, channel=0)
	while True:
		t = time.time() - start_time
		pixels = []
		frame=frame+1
		cos = math.cos((t/1)*math.pi*2)
		for i in range(n_pixels):
			r = color_utils.remap(math.cos((200 - i + frame))*math.pi*2,-1,1,0,128)
			g = color_utils.remap(math.cos((i + frame))*math.pi*2,-1,1,0,128)
			b = color_utils.remap(math.cos((10*(i%10)+frame))*math.pi*2,-1,1,0,128)
			pixels.append((r,g,b))
		client.put_pixels(pixels,channel=0)
		time.sleep(1/fps)

#-------------------------------------------------------------------------------
# textScroll(text)
# Displays scrolling text. Uses last tweet of user if not defined.
def textScroll(text):
	app_text = str2mat.Text2LED()
	if text == '':
		r = api.request('statuses/user_timeline', {'count':1})
		for item in r.get_iterator():
			if 'text' in item:
				text = item['text']
		print r.status_code
	while True:
		textMatrix = app_text.map_string_to_matrix(text)
		columns = app_text.matrix_to_column_list(textMatrix)
		i=0
		while i<len(columns)+1:
			pixels=[]
			for col in columns:
				for val in col:
					pixels.append(val)
			colors = app_text.pixels_to_colors(pixels)
			client.put_pixels(colors, channel=0)
			columns.append(columns[0])
			columns = columns[1:]			
			time.sleep(1/4)
			i = i+1

#-------------------------------------------------------------------------------
# eyes()
# Sends a pattern of randomly moving eyes to the LED arrays
def eyes():
	eyeForward = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,1,1,0,0,1,1,0,0,
							0,0,1,0,2,2,0,1,0,0,
							0,0,1,2,2,3,2,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,0,2,2,0,1,0,0,
							0,0,1,1,0,0,1,1,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	eyeRight = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,1,1,2,2,1,1,0,0,
							0,0,1,2,2,3,2,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,0,2,2,0,1,0,0,
							0,0,1,0,0,0,0,1,0,0,
							0,0,1,1,0,0,1,1,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	eyeLeft = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,1,1,0,0,1,1,0,0,
							0,0,1,0,0,0,0,1,0,0,
							0,0,1,0,2,2,0,1,0,0,
							0,0,1,2,2,3,2,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,1,2,2,1,1,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	eyeBlink = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	while True:
		selection = randint(0,3)
		randEye = []
		if selection is 0:
			randEye = eyeForward
		if selection is 1:
			randEye = eyeLeft
		if selection is 2:
			randEye = eyeRight
		if selection is 3:
			randEye = eyeBlink
		pixels = []
		for val in randEye:
			pixels.append(val)
		for val in randEye:
			pixels.append(val)
		colors = arrayToColors(pixels)
		client.put_pixels(colors, channel=0)
		time.sleep(1/2)

#-------------------------------------------------------------------------------
# smileyFace
# Sends a bouncing smiley face to the LED arrays
def smileyFace():
	pixels = []
	i = 0
	middle = [0,0,0,0,4,4,0,0,0,0,
						0,0,4,4,4,4,4,4,0,0,
						0,4,4,5,5,4,5,4,4,0,
						0,4,4,5,5,4,5,5,4,0,
						4,4,4,4,4,4,5,5,4,4,
						4,4,4,4,4,4,5,5,4,4,
						0,4,4,5,5,4,5,5,4,0,
						0,4,4,5,5,4,5,4,4,0,
						0,0,4,4,4,4,4,4,0,0,
						0,0,0,0,4,4,0,0,0,0]
	up = [0,0,0,0,4,4,0,0,0,0,
						0,0,4,4,4,4,4,4,0,0,
						0,4,5,5,4,5,4,4,4,0,
						0,4,5,5,4,5,5,4,4,0,
						4,4,4,4,4,5,5,4,4,4,
						4,4,4,4,4,5,5,4,4,4,
						0,4,5,5,4,5,5,4,4,0,
						0,4,5,5,4,5,4,4,4,0,
						0,0,4,4,4,4,4,4,0,0,
						0,0,0,0,4,4,0,0,0,0]
	down = [0,0,0,0,4,4,0,0,0,0,
						0,0,4,4,4,4,4,4,0,0,
						0,4,4,4,5,5,4,5,4,0,
						0,4,4,4,5,5,4,5,5,0,
						4,4,4,4,4,4,4,5,5,4,
						4,4,4,4,4,4,4,5,5,4,
						0,4,4,4,5,5,4,5,5,0,
						0,4,4,4,5,5,4,5,4,0,
						0,0,4,4,4,4,4,4,0,0,
						0,0,0,0,4,4,0,0,0,0]
	while True:
		pixels=[]
		i = i + 1
		if i % 4 == 0:
			for val in middle:
				pixels.append(val)
			for val in middle:
				pixels.append(val)
		elif i % 4 == 1:
			for val in up:
				pixels.append(val)
			for val in down:
				pixels.append(val)
		elif i % 4 == 2:
			for val in middle:
				pixels.append(val)
			for val in middle:
				pixels.append(val)
		elif i % 4 == 3:
			for val in down:
				pixels.append(val)
			for val in up:
				pixels.append(val)
		colors = arrayToColors(pixels)
		client.put_pixels(colors,channel=0)
		time.sleep(1/3)

#-------------------------------------------------------------------------------
# arrayToColors(array)
# Takes an array of single ints and converts it into an array of RGB tuples
def arrayToColors(array):
	colors = []
	for i in array:
		if i is 0:
			colors.append((0,0,0))
		elif i is 1:
			colors.append((128,128,128))
		elif i is 2:
			colors.append((128,0,0))
		elif i is 3:
			colors.append((256,0,256))
		elif i is 4:
			colors.append((128,128,0))
		elif i is 5:
			colors.append((0,0,0))
		else:
			colors.append((0,0,0))
	return colors

#-------------------------------------------------------------------------------
# main method
def main(argv):
	pattern = ""
	text = ""
	try:
		opts, args = getopt.getopt(argv,"hp:t:",["pattern=","text="])
	except getopt.GetoptError:
		print 'test.py -p <pattern> -t <optional_text>'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'test.py -p <pattern> -t <optional_text>'
			print ' '
			print 'USE -t TO DISPLAY CUSTOM TEXT INSTEAD OF TWITTER FEED'
			print ' '
			print 'PATTERN OPTIONS:'
			print ' test1          -- Lines 11 long of 1 color alternating'
			print ' test2          -- Fills grids pixel by pixel'
			print ' flashingLights -- Pseudo-random flashing lights'
			print ' eyes           -- Displays randomly moving eyes'
			print ' textScroll     -- Displays last tweet as scrolling text'
			print ' smileyFace     -- Displays a bouncing smiley face'
			sys.exit()
		elif opt in ("-p", "--pattern"):
			pattern =  arg
		elif opt in ("-t", "--text"):
			text = arg
	if pattern == 'test1':
		print 'RUNNING test1'
		test1()
	elif pattern == 'test2':
		print 'RUNNING test2'
		test2()
	elif pattern == 'flashingLights':
		print 'RUNNING flashingLights'
		flashingLights()
	elif pattern == 'eyes':
		print 'RUNNING eyes'
		eyes()
	elif pattern == 'textScroll':
		print 'RUNNING textScroll'
		textScroll(text)
	elif pattern == 'smileyFace':
		print 'RUNNING smileyFace'
		smileyFace()
	else:
		print 'Input correct pattern option. -h for help.'
		sys.exit(2)

if __name__ == "__main__":
   main(sys.argv[1:])
