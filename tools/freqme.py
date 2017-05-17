#!/usr/bin/env python

from struct import unpack
from sys import argv
from sys import exit

def main():
	keysize = 64
	i = 1
	while i < len(argv):
		arg = argv[i]
		i += 1
		if arg == "-k" and i < len(argv):
			try:
				keysize = int(argv[i])
			except:
				print(argv[i] + " is not valid for -k")
				exit()
			i += 1
		else:
			with open(arg, "rb") as f:
				counts = [[0 for x in range(0, 256)] for x in range(0, keysize)]
				while True:
					bytes = f.read(keysize)
					if len(bytes) == 0:
						break
					else:
						for idx, val in enumerate(unpack("B" * len(bytes), bytes)):
							counts[idx][val] += 1
				for count in counts:
					mcv = [x for (y, x) in sorted([(y, x) for (x, y) in enumerate(count)], reverse=True)]
					print(', '.join(['{:02X}'.format(x) for x in mcv][:10]))

if __name__ == "__main__": main()
