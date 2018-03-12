#!/usr/bin/env python

from struct import unpack
from sys import argv
from sys import exit
from sys import stdout

def main():
	key = [255]
	i = 1
	while i < len(argv):
		arg = argv[i]
		i += 1
		if arg == "-k" and i < len(argv):
			try:
				key = [ord(x) for x in argv[i].decode("hex")]
			except:
				print(argv[i] + " is not valid for -k")
				exit()
			i += 1
		else:
			with open(arg, "rb") as f:
				while True:
					txt = [ord(x) for x in f.read(len(key))]
					if len(txt) == 0:
						break
					else:
						txt = [x ^ y for x, y in zip(txt, key)]
						stdout.write(''.join(chr(x) for x in txt))

if __name__ == "__main__": main()
