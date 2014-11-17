#!/usr/bin/env python

"""A demo client for Open Pixel Control
http://github.com/zestyping/openpixelcontrol

Creates a shifting rainbow plaid pattern by overlaying different sine waves
in the red, green, and blue channels.

To run:
First start the gl simulator using the included "wall" layout

    make
    bin/gl_server layouts/wall.json

Then run this script in another shell to send colors to the simulator

    python_clients/raver_plaid.py

"""

from __future__ import division
import time
import math
import sys

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

if len(sys.argv) == 1:
    IP_PORT = '127.0.0.1:7890'
elif len(sys.argv) == 2 and ':' in sys.argv[1] and not sys.argv[1].startswith('-'):
    IP_PORT = sys.argv[1]
else:
    print
    print '    Usage: raver_plaid.py [ip:port]'
    print
    print '    If not set, ip:port defauls to 127.0.0.1:7890'
    print
    sys.exit(0)


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

print '    sending pixels forever (control-c to exit)...'
print

n_pixels = 200  # number of pixels in the included "wall" layout
fps = 20       # frames per second

# how many sine wave cycles are squeezed into our n_pixels
# 24 happens to create nice diagonal stripes on the wall layout
freq_r = 24
freq_g = 24
freq_b = 24

# how many seconds the color sine waves take to shift through a complete cycle
speed_r = 7
speed_g = -13
speed_b = 19

api = TwitterAPI(consumer_key, consumer_secret, access_token_key, access_token_secret)
r = api.request('search/tweets', {'q':'pizza'})
print r.status_code

for item in r.get_iterator():
	print item['user']['screen_name'], item['text']

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

def textScroll(text="HELLO"):
	app_text = str2mat.Text2LED()
	r = api.request('statuses/update', {'status': 'Running Beaglebone at time %s' % datetime.now()})
	print(r.status_code)
	while True:
		r = api.request('statuses/home_timeline', {'count':1})
		for item in r.get_iterator():
			if 'text' in item:
				text = item['text']
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
			columns = columns[1:]
			columns.append([0,0,0,0,0,0,0,0,0,1])
			time.sleep(1/4)
			i = i+1

def eyes():
	start_time = time.time()
	eyeForward = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,1,0,0,1,0,0,0,
							0,0,1,1,2,2,1,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,1,2,2,1,1,0,0,
							0,0,1,1,0,0,1,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	eyeRight = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,1,2,2,1,0,0,0,
							0,0,1,1,2,2,1,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,0,2,2,0,1,0,0,
							0,0,1,1,0,0,1,1,0,0,
							0,0,1,1,0,0,1,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	eyeLeft = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,1,0,0,1,0,0,0,
							0,0,1,1,0,0,1,1,0,0,
							0,0,1,0,2,2,0,1,0,0,
							0,0,1,2,2,2,2,1,0,0,
							0,0,1,1,2,2,1,1,0,0,
							0,0,1,1,2,2,1,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,0,1,1,0,0,0,0]
	eyeBlink = [0,0,0,0,1,1,0,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,0,1,1,1,1,0,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,1,0,0,
							0,0,1,1,1,1,1,0,0,0,
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
		t = time.time() - start_time
		pixels = []
		for val in randEye:
			pixels.append(val)
		for val in randEye:
			pixels.append(val)
		colors = arrayToColors(pixels)
		client.put_pixels(colors, channel=0)
		#client.put_pixels(pixels, channel=1)
		#client.put_pixels(pixels, channel=2)
		time.sleep(1/3)

def arrayToColors(array):
	colors = []
	for i in array:
		if i is 0:
			colors.append((0,0,0))
		elif i is 1:
			colors.append((128,128,128))
		elif i is 2:
			colors.append((128,0,0))
		else:
			colors.append((0,0,0))
	return colors

#test2()
eyes()
#textScroll()
