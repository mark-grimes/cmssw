#!/usr/bin/env python
# Reads two files of detector position, rotation and DetId and looks at the corresponding
# lines in both files. If the DetIds on a particular line don't match then it prints both.
# This can be used to create a map between two different DetId mappings.
#
# NOTE that both files have to be in the same order - it only cares which line of the file
# the DetId is on. To get the output from DumpTrackerDetIdInfo in the correct order use the
# Unix command "sort".


import sys

if len(sys.argv)!=3 :
	raise Exception( "Two filenames of sorted DetId positions need to be supplied")

inputFile1=open(sys.argv[1])
inputFile2=open(sys.argv[2])


while True :
	line1=inputFile1.readline()
	line2=inputFile2.readline()
	
	if line1=="" :
		break
	
	detId1=line1.split()[12]
	detId2=line2.split()[12]
	
	if detId1!=detId2 :
		print detId1, detId2
