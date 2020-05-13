#!/usr/bin/env python3

#Suin Kim
#CS265-005
#Assignment 2

import sys
import os
import stat
import re

#checks arguments provided
def checkArg():
	if (len(sys.argv) == 1): #if no argument provided, use current directory
		return os.getcwd()

	elif (len(sys.argv) == 2):
		if (os.path.isdir(sys.argv[1])): #if valid directory provided as argument, use that
			return os.path.abspath(sys.argv[1])

		else:
			print(sys.argv[1], "is not a valid directory.") 
			sys.exit()
	
	else:
		print("Too many arguments provided")
		sys.exit()

#checks if item is a regular file(or, symlink), directory, a named pipe, or a socket
def checkType(directory, item):
	try: #if item exists in directory, checks type
		os.path.exists(os.path.join(directory, item))
		mode = os.stat(os.path.join(directory, item)).st_mode

		if stat.S_ISREG(mode):
			return "file"

		elif stat.S_ISDIR(mode):
			return "dir"

		elif stat.S_ISFIFO(mode):
			return "fifo"

		elif stat.S_ISSOCK(mode):
			return "sock"

	except: #if item does not exist in directory, assume it is a regular file
		return "file"

#generates dir.xml in given directory
def dropXml(directory):
	xml = open(os.path.join(directory, "dir.xml"), "w")
	xml.write("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<direntry>\n")

	if (os.path.isfile(os.path.join(directory, "README"))): #if README file exists in directory
		readme(directory, xml) #get index and/or required nodes
	
	other(directory, xml) #get other node and items not listed in README

	xml.write("</direntry>\n")
	xml.close

#parses README file and adds index and/or required nodes to dir.xml
def readme(directory, xml):
	readme = open(os.path.join(directory, "README"), "r")
	readmeString = readme.read()
	readme.close()
	readmeItems = list(filter(None, re.split("[:\n]+", readmeString)))
	
	if (readmeItems[0] == "index"): #if README has index entry
		xml.write("\t<index>\n\t\t<file>" + readmeItems[1] + "</file>\n\t</index>\n") #index only contains one file
		
		if (len(readmeItems) > 2): #if readmeItems has more than two elements, README has required entry
			xml.write("\t<required>\n")

			for i in range(3, len(readmeItems)): #items for required entry start at list index 3, checks type for each item
				itemType = checkType(directory, readmeItems[i])
				xml.write("\t\t<" + itemType + ">" + readmeItems[i] + "</" + itemType + ">\n")

			xml.write("\t</required>\n")
		
	else: #if README only has required entry
		xml.write("\t<required>\n")

		for i in range(1, len(readmeItems)): #items for required entry start at list index 1 since there is no index entry, checks type for each item
			itemType = checkType(directory, readmeItems[i])
			xml.write("\t\t<" + itemType + ">" + readmeItems[i] + "</" + itemType + ">\n")

		xml.write("\t</required>\n")

#adds other node to dir.xml
def other(directory, xml):
	xml.write("\t<other>\n")
	
	if (os.path.isfile(os.path.join(directory, "README"))): #if README file exists, check for duplicate items
		readme = open(os.path.join(directory, "README"), "r")
		readmeString = readme.read()
		readme.close()
		readmeItems = list(filter(None, re.split("[:\n]+", readmeString)))

		otherItems = os.listdir(directory)

		items = [i for i in otherItems if i not in readmeItems] #omit items in README for other entry

	else:
		items = os.listdir(directory) #if no README file exists, no need to check for duplicate items

	items.remove("dir.xml") #do not include dir.xml 

	for item in items: #checks type for each item and adds to other entry
		itemType = checkType(directory, item )
		xml.write("\t\t<" + itemType + ">" + item + "</" + itemType + ">\n")
	
	xml.write("\t</other>\n")

#main
def main():
	rootdir = checkArg() #get root directory
	dropXml(rootdir) #generates dir.xml for root directory

	for root, dirs, files in os.walk(rootdir): #recursive call with os.walk() to generate dir.xml for subdirectories 
		dropXml(os.path.abspath(root))

if __name__ == "__main__":
	main()
