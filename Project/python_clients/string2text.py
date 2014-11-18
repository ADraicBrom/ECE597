#!/usr/bin/env python
from myalphabet import *

class Text2LED():

	def __init__(self):
		pass

	def get_column(self, matrix, i):
		column = []
		for row in matrix:
			column.append(row[i])
		column.append(0)
		column.append(1)
		return column

	def matrix_to_column_list(self, text):
		text2tick = []
		start = 0
		for z in range(len(text)):
			for c in range(0,8):
				try:
					col = self.get_column(text[z], c)
					#text2tick[start] = col
					text2tick.append(col)
					start += 1
				except IndexError:
					break
		return text2tick 

	def map_string_to_matrix(self, string):
		'''takes a string, converts it to uppercase, and 
		returns the matching matrix variable if a letter match
		is made.
		       
		USAGE:
		mapStringToMatrix("teststring")
		'''
		string = string.upper()
		matrixOfText = []
		for letter in string:
			matrixOfText.append(myalphabet[letter])
		matrixOfText.append(myalphabet['_'])
		#print matrixOfText
		return matrixOfText

	def pixels_to_colors(self, array):
		pixels = []
		for i in array:
			if i == 0:
				pixels.append((0,0,0))
			else:
				pixels.append((128,128,128))
		return pixels
