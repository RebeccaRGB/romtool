#!/usr/bin/env python

from __future__ import print_function
import serial
import time
from sys import argv
from sys import exit
from sys import stderr
from sys import stdout

def help():
	print("usage: nanddownload.py [<options>] <device> [<output>]", file=stderr)
	print("   -u <path>     serial port connected to Arduino NAND Reader", file=stderr)
	print("   -o <path>     path to write to", file=stderr)

def readlines(ser, output):
	line = ser.readline().strip()
	while line != "":
		output.write(line)
		output.write("\n")
		output.flush()
		line = ser.readline().strip()

def main():
	port = None
	output = None
	i = 1
	while i < len(argv):
		arg = argv[i]
		i += 1
		if arg == "--help":
			help()
			exit()
		elif arg == "-u" and i < len(argv):
			port = argv[i]
			i += 1
		elif arg == "-o" and i < len(argv):
			output = argv[i]
			i += 1
		elif port is None:
			port = arg
		elif output is None:
			output = arg
		else:
			help()
			exit()
	if port is None:
		help()
	else:
		try:
			if output is None:
				with serial.Serial(port=port, baudrate=250000, bytesize=serial.EIGHTBITS,
								   parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
								   xonxoff=False, rtscts=True, dsrdtr=False, timeout=10) as ser:
					time.sleep(5)
					readlines(ser, stdout)
					ser.write("1\n")
					readlines(ser, stdout)
					ser.write("2\n")
					readlines(ser, stdout)
					exit()
			else:
				with open(output, "wb") as f:
					with serial.Serial(port=port, baudrate=250000, bytesize=serial.EIGHTBITS,
									   parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
									   xonxoff=False, rtscts=True, dsrdtr=False, timeout=10) as ser:
						time.sleep(5)
						readlines(ser, f)
						ser.write("1\n")
						readlines(ser, f)
						ser.write("2\n")
						readlines(ser, f)
						exit()
		except KeyboardInterrupt:
			pass

if __name__ == "__main__": main()
