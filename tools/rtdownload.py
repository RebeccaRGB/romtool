#!/usr/bin/env python

from __future__ import print_function
import serial
import time
from sys import argv
from sys import exit
from sys import stderr
from sys import stdout

def help():
	print("usage: rtdownload.py [<options>] <device> [<output>]", file=stderr)
	print("   -u <path>     serial port connected to Beckie's ROM Tool", file=stderr)
	print("   -d <width>    data width (8, 16le, 16be)", file=stderr)
	print("   -a <width>    address width (8, 8.5, ..., 31)", file=stderr)
	print("   -f <format>   I/O format (raw, hex)", file=stderr)
	print("   -o <path>     path to write to", file=stderr)

def main():
	port = None
	datawidth = "8"
	addrwidth = "16"
	addrmax = 0x10000
	ioformat = "raw"
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
		elif arg == "-d" and i < len(argv):
			if argv[i] == "8":
				datawidth = "8"
			elif argv[i] == "16le" or argv[i] == "16LE":
				datawidth = "16le"
			elif argv[i] == "16be" or argv[i] == "16BE":
				datawidth = "16be"
			else:
				print(argv[i] + " is not valid for -d", file=stderr)
				exit()
			i += 1
		elif arg == "-a" and i < len(argv):
			if argv[i] == "8":
				addrwidth = "8"
				addrmax = 0x100
			elif argv[i] == "8.5":
				addrwidth = "8.5"
				addrmax = 0x180
			elif argv[i] == "9":
				addrwidth = "9"
				addrmax = 0x200
			elif argv[i] == "9.5":
				addrwidth = "9.5"
				addrmax = 0x300
			elif argv[i] == "10":
				addrwidth = "10"
				addrmax = 0x400
			elif argv[i] == "10.5":
				addrwidth = "10.5"
				addrmax = 0x600
			elif argv[i] == "11":
				addrwidth = "11"
				addrmax = 0x800
			elif argv[i] == "11.5":
				addrwidth = "11.5"
				addrmax = 0xC00
			elif argv[i] == "12":
				addrwidth = "12"
				addrmax = 0x1000
			elif argv[i] == "12.5":
				addrwidth = "12.5"
				addrmax = 0x1800
			elif argv[i] == "13":
				addrwidth = "13"
				addrmax = 0x2000
			elif argv[i] == "13.5":
				addrwidth = "13.5"
				addrmax = 0x3000
			elif argv[i] == "14":
				addrwidth = "14"
				addrmax = 0x4000
			elif argv[i] == "14.5":
				addrwidth = "14.5"
				addrmax = 0x6000
			elif argv[i] == "15":
				addrwidth = "15"
				addrmax = 0x8000
			elif argv[i] == "15.5":
				addrwidth = "15.5"
				addrmax = 0xC000
			elif argv[i] == "16":
				addrwidth = "16"
				addrmax = 0x10000
			elif argv[i] == "16.5":
				addrwidth = "16.5"
				addrmax = 0x18000
			elif argv[i] == "17":
				addrwidth = "17"
				addrmax = 0x20000
			elif argv[i] == "17.5":
				addrwidth = "17.5"
				addrmax = 0x30000
			elif argv[i] == "18":
				addrwidth = "18"
				addrmax = 0x40000
			elif argv[i] == "18.5":
				addrwidth = "18.5"
				addrmax = 0x60000
			elif argv[i] == "19":
				addrwidth = "19"
				addrmax = 0x80000
			elif argv[i] == "19.5":
				addrwidth = "19.5"
				addrmax = 0xC0000
			elif argv[i] == "20":
				addrwidth = "20"
				addrmax = 0x100000
			elif argv[i] == "20.5":
				addrwidth = "20.5"
				addrmax = 0x180000
			elif argv[i] == "21":
				addrwidth = "21"
				addrmax = 0x200000
			elif argv[i] == "21.5":
				addrwidth = "21.5"
				addrmax = 0x300000
			elif argv[i] == "22":
				addrwidth = "22"
				addrmax = 0x400000
			elif argv[i] == "22.5":
				addrwidth = "22.5"
				addrmax = 0x600000
			elif argv[i] == "23":
				addrwidth = "23"
				addrmax = 0x800000
			elif argv[i] == "23.5":
				addrwidth = "23.5"
				addrmax = 0xC00000
			elif argv[i] == "24":
				addrwidth = "24"
				addrmax = 0x1000000
			elif argv[i] == "24.5":
				addrwidth = "24.5"
				addrmax = 0x1800000
			elif argv[i] == "25":
				addrwidth = "25"
				addrmax = 0x2000000
			elif argv[i] == "25.5":
				addrwidth = "25.5"
				addrmax = 0x3000000
			elif argv[i] == "26":
				addrwidth = "26"
				addrmax = 0x4000000
			elif argv[i] == "26.5":
				addrwidth = "26.5"
				addrmax = 0x6000000
			elif argv[i] == "27":
				addrwidth = "27"
				addrmax = 0x8000000
			elif argv[i] == "27.5":
				addrwidth = "27.5"
				addrmax = 0xC000000
			elif argv[i] == "28":
				addrwidth = "28"
				addrmax = 0x10000000
			elif argv[i] == "28.5":
				addrwidth = "28.5"
				addrmax = 0x18000000
			elif argv[i] == "29":
				addrwidth = "29"
				addrmax = 0x20000000
			elif argv[i] == "29.5":
				addrwidth = "29.5"
				addrmax = 0x30000000
			elif argv[i] == "30":
				addrwidth = "30"
				addrmax = 0x40000000
			elif argv[i] == "30.5":
				addrwidth = "30.5"
				addrmax = 0x60000000
			elif argv[i] == "31":
				addrwidth = "31"
				addrmax = 0x80000000
			elif (argv[i] == "256" or argv[i] == "256b" or argv[i] == "256B") and datawidth == "8":
				addrwidth = "8"
				addrmax = 0x100
			elif (argv[i] == "384" or argv[i] == "384b" or argv[i] == "384B") and datawidth == "8":
				addrwidth = "8.5"
				addrmax = 0x180
			elif argv[i] == "512" or argv[i] == "512b" or argv[i] == "512B":
				if datawidth == "8":
					addrwidth = "9"
					addrmax = 0x200
				else:
					addrwidth = "8"
					addrmax = 0x100
			elif argv[i] == "768" or argv[i] == "768b" or argv[i] == "768B":
				if datawidth == "8":
					addrwidth = "9.5"
					addrmax = 0x300
				else:
					addrwidth = "8.5"
					addrmax = 0x180
			elif argv[i] == "1024" or argv[i] == "1024b" or argv[i] == "1024B" or argv[i] == "1k" or argv[i] == "1K":
				if datawidth == "8":
					addrwidth = "10"
					addrmax = 0x400
				else:
					addrwidth = "9"
					addrmax = 0x200
			elif argv[i] == "1536" or argv[i] == "1536b" or argv[i] == "1536B" or argv[i] == "1.5k" or argv[i] == "1.5K":
				if datawidth == "8":
					addrwidth = "10.5"
					addrmax = 0x600
				else:
					addrwidth = "9.5"
					addrmax = 0x300
			elif argv[i] == "2048" or argv[i] == "2048b" or argv[i] == "2048B" or argv[i] == "2k" or argv[i] == "2K":
				if datawidth == "8":
					addrwidth = "11"
					addrmax = 0x800
				else:
					addrwidth = "10"
					addrmax = 0x400
			elif argv[i] == "3072" or argv[i] == "3072b" or argv[i] == "3072B" or argv[i] == "3k" or argv[i] == "3K":
				if datawidth == "8":
					addrwidth = "11.5"
					addrmax = 0xC00
				else:
					addrwidth = "10.5"
					addrmax = 0x600
			elif argv[i] == "4096" or argv[i] == "4096b" or argv[i] == "4096B" or argv[i] == "4k" or argv[i] == "4K":
				if datawidth == "8":
					addrwidth = "12"
					addrmax = 0x1000
				else:
					addrwidth = "11"
					addrmax = 0x800
			elif argv[i] == "6144" or argv[i] == "6144b" or argv[i] == "6144B" or argv[i] == "6k" or argv[i] == "6K":
				if datawidth == "8":
					addrwidth = "12.5"
					addrmax = 0x1800
				else:
					addrwidth = "11.5"
					addrmax = 0xC00
			elif argv[i] == "8192" or argv[i] == "8192b" or argv[i] == "8192B" or argv[i] == "8k" or argv[i] == "8K":
				if datawidth == "8":
					addrwidth = "13"
					addrmax = 0x2000
				else:
					addrwidth = "12"
					addrmax = 0x1000
			elif argv[i] == "12288" or argv[i] == "12288b" or argv[i] == "12288B" or argv[i] == "12k" or argv[i] == "12K":
				if datawidth == "8":
					addrwidth = "13.5"
					addrmax = 0x3000
				else:
					addrwidth = "12.5"
					addrmax = 0x1800
			elif argv[i] == "16384" or argv[i] == "16384b" or argv[i] == "16384B" or argv[i] == "16k" or argv[i] == "16K":
				if datawidth == "8":
					addrwidth = "14"
					addrmax = 0x4000
				else:
					addrwidth = "13"
					addrmax = 0x2000
			elif argv[i] == "24576" or argv[i] == "24576b" or argv[i] == "24576B" or argv[i] == "24k" or argv[i] == "24K":
				if datawidth == "8":
					addrwidth = "14.5"
					addrmax = 0x6000
				else:
					addrwidth = "13.5"
					addrmax = 0x3000
			elif argv[i] == "32768" or argv[i] == "32768b" or argv[i] == "32768B" or argv[i] == "32k" or argv[i] == "32K":
				if datawidth == "8":
					addrwidth = "15"
					addrmax = 0x8000
				else:
					addrwidth = "14"
					addrmax = 0x4000
			elif argv[i] == "49152" or argv[i] == "49152b" or argv[i] == "49152B" or argv[i] == "48k" or argv[i] == "48K":
				if datawidth == "8":
					addrwidth = "15.5"
					addrmax = 0xC000
				else:
					addrwidth = "14.5"
					addrmax = 0x6000
			elif argv[i] == "65536" or argv[i] == "65536b" or argv[i] == "65536B" or argv[i] == "64k" or argv[i] == "64K":
				if datawidth == "8":
					addrwidth = "16"
					addrmax = 0x10000
				else:
					addrwidth = "15"
					addrmax = 0x8000
			elif argv[i] == "98304" or argv[i] == "98304b" or argv[i] == "98304B" or argv[i] == "96k" or argv[i] == "96K":
				if datawidth == "8":
					addrwidth = "16.5"
					addrmax = 0x18000
				else:
					addrwidth = "15.5"
					addrmax = 0xC000
			elif argv[i] == "131072" or argv[i] == "131072b" or argv[i] == "131072B" or argv[i] == "128k" or argv[i] == "128K":
				if datawidth == "8":
					addrwidth = "17"
					addrmax = 0x20000
				else:
					addrwidth = "16"
					addrmax = 0x10000
			elif argv[i] == "196608" or argv[i] == "196608b" or argv[i] == "196608B" or argv[i] == "192k" or argv[i] == "192K":
				if datawidth == "8":
					addrwidth = "17.5"
					addrmax = 0x30000
				else:
					addrwidth = "16.5"
					addrmax = 0x18000
			elif argv[i] == "262144" or argv[i] == "262144b" or argv[i] == "262144B" or argv[i] == "256k" or argv[i] == "256K":
				if datawidth == "8":
					addrwidth = "18"
					addrmax = 0x40000
				else:
					addrwidth = "17"
					addrmax = 0x20000
			elif argv[i] == "393216" or argv[i] == "393216b" or argv[i] == "393216B" or argv[i] == "384k" or argv[i] == "384K":
				if datawidth == "8":
					addrwidth = "18.5"
					addrmax = 0x60000
				else:
					addrwidth = "17.5"
					addrmax = 0x30000
			elif argv[i] == "524288" or argv[i] == "524288b" or argv[i] == "524288B" or argv[i] == "512k" or argv[i] == "512K":
				if datawidth == "8":
					addrwidth = "19"
					addrmax = 0x80000
				else:
					addrwidth = "18"
					addrmax = 0x40000
			elif argv[i] == "786432" or argv[i] == "786432b" or argv[i] == "786432B" or argv[i] == "768k" or argv[i] == "768K":
				if datawidth == "8":
					addrwidth = "19.5"
					addrmax = 0xC0000
				else:
					addrwidth = "18.5"
					addrmax = 0x60000
			elif argv[i] == "1048576" or argv[i] == "1048576b" or argv[i] == "1048576B" or argv[i] == "1024k" or argv[i] == "1024K" or argv[i] == "1m" or argv[i] == "1M":
				if datawidth == "8":
					addrwidth = "20"
					addrmax = 0x100000
				else:
					addrwidth = "19"
					addrmax = 0x80000
			elif argv[i] == "1572864" or argv[i] == "1572864b" or argv[i] == "1572864B" or argv[i] == "1536k" or argv[i] == "1536K" or argv[i] == "1.5m" or argv[i] == "1.5M":
				if datawidth == "8":
					addrwidth = "20.5"
					addrmax = 0x180000
				else:
					addrwidth = "19.5"
					addrmax = 0xC0000
			elif argv[i] == "2097152" or argv[i] == "2097152b" or argv[i] == "2097152B" or argv[i] == "2048k" or argv[i] == "2048K" or argv[i] == "2m" or argv[i] == "2M":
				if datawidth == "8":
					addrwidth = "21"
					addrmax = 0x200000
				else:
					addrwidth = "20"
					addrmax = 0x100000
			elif argv[i] == "3145728" or argv[i] == "3145728b" or argv[i] == "3145728B" or argv[i] == "3072k" or argv[i] == "3072K" or argv[i] == "3m" or argv[i] == "3M":
				if datawidth == "8":
					addrwidth = "21.5"
					addrmax = 0x300000
				else:
					addrwidth = "20.5"
					addrmax = 0x180000
			elif argv[i] == "4194304" or argv[i] == "4194304b" or argv[i] == "4194304B" or argv[i] == "4096k" or argv[i] == "4096K" or argv[i] == "4m" or argv[i] == "4M":
				if datawidth == "8":
					addrwidth = "22"
					addrmax = 0x400000
				else:
					addrwidth = "21"
					addrmax = 0x200000
			elif argv[i] == "6291456" or argv[i] == "6291456b" or argv[i] == "6291456B" or argv[i] == "6144k" or argv[i] == "6144K" or argv[i] == "6m" or argv[i] == "6M":
				if datawidth == "8":
					addrwidth = "22.5"
					addrmax = 0x600000
				else:
					addrwidth = "21.5"
					addrmax = 0x300000
			elif argv[i] == "8388608" or argv[i] == "8388608b" or argv[i] == "8388608B" or argv[i] == "8192k" or argv[i] == "8192K" or argv[i] == "8m" or argv[i] == "8M":
				if datawidth == "8":
					addrwidth = "23"
					addrmax = 0x800000
				else:
					addrwidth = "22"
					addrmax = 0x400000
			elif argv[i] == "12582912" or argv[i] == "12582912b" or argv[i] == "12582912B" or argv[i] == "12288k" or argv[i] == "12288K" or argv[i] == "12m" or argv[i] == "12M":
				if datawidth == "8":
					addrwidth = "23.5"
					addrmax = 0xC00000
				else:
					addrwidth = "22.5"
					addrmax = 0x600000
			elif argv[i] == "16777216" or argv[i] == "16777216b" or argv[i] == "16777216B" or argv[i] == "16384k" or argv[i] == "16384K" or argv[i] == "16m" or argv[i] == "16M":
				if datawidth == "8":
					addrwidth = "24"
					addrmax = 0x1000000
				else:
					addrwidth = "23"
					addrmax = 0x800000
			elif argv[i] == "25165824" or argv[i] == "25165824b" or argv[i] == "25165824B" or argv[i] == "24576k" or argv[i] == "24576K" or argv[i] == "24m" or argv[i] == "24M":
				if datawidth == "8":
					addrwidth = "24.5"
					addrmax = 0x1800000
				else:
					addrwidth = "23.5"
					addrmax = 0xC00000
			elif argv[i] == "33554432" or argv[i] == "33554432b" or argv[i] == "33554432B" or argv[i] == "32768k" or argv[i] == "32768K" or argv[i] == "32m" or argv[i] == "32M":
				if datawidth == "8":
					addrwidth = "25"
					addrmax = 0x2000000
				else:
					addrwidth = "24"
					addrmax = 0x1000000
			elif argv[i] == "50331648" or argv[i] == "50331648b" or argv[i] == "50331648B" or argv[i] == "49152k" or argv[i] == "49152K" or argv[i] == "48m" or argv[i] == "48M":
				if datawidth == "8":
					addrwidth = "25.5"
					addrmax = 0x3000000
				else:
					addrwidth = "24.5"
					addrmax = 0x1800000
			elif argv[i] == "67108864" or argv[i] == "67108864b" or argv[i] == "67108864B" or argv[i] == "65536k" or argv[i] == "65536K" or argv[i] == "64m" or argv[i] == "64M":
				if datawidth == "8":
					addrwidth = "26"
					addrmax = 0x4000000
				else:
					addrwidth = "25"
					addrmax = 0x2000000
			elif argv[i] == "100663296" or argv[i] == "100663296b" or argv[i] == "100663296B" or argv[i] == "98304k" or argv[i] == "98304K" or argv[i] == "96m" or argv[i] == "96M":
				if datawidth == "8":
					addrwidth = "26.5"
					addrmax = 0x6000000
				else:
					addrwidth = "25.5"
					addrmax = 0x3000000
			elif argv[i] == "134217728" or argv[i] == "134217728b" or argv[i] == "134217728B" or argv[i] == "131072k" or argv[i] == "131072K" or argv[i] == "128m" or argv[i] == "128M":
				if datawidth == "8":
					addrwidth = "27"
					addrmax = 0x8000000
				else:
					addrwidth = "26"
					addrmax = 0x4000000
			elif argv[i] == "201326592" or argv[i] == "201326592b" or argv[i] == "201326592B" or argv[i] == "196608k" or argv[i] == "196608K" or argv[i] == "192m" or argv[i] == "192M":
				if datawidth == "8":
					addrwidth = "27.5"
					addrmax = 0xC000000
				else:
					addrwidth = "26.5"
					addrmax = 0x6000000
			elif argv[i] == "268435456" or argv[i] == "268435456b" or argv[i] == "268435456B" or argv[i] == "262144k" or argv[i] == "262144K" or argv[i] == "256m" or argv[i] == "256M":
				if datawidth == "8":
					addrwidth = "28"
					addrmax = 0x10000000
				else:
					addrwidth = "27"
					addrmax = 0x8000000
			elif argv[i] == "402653184" or argv[i] == "402653184b" or argv[i] == "402653184B" or argv[i] == "393216k" or argv[i] == "393216K" or argv[i] == "384m" or argv[i] == "384M":
				if datawidth == "8":
					addrwidth = "28.5"
					addrmax = 0x18000000
				else:
					addrwidth = "27.5"
					addrmax = 0xC000000
			elif argv[i] == "536870912" or argv[i] == "536870912b" or argv[i] == "536870912B" or argv[i] == "524288k" or argv[i] == "524288K" or argv[i] == "512m" or argv[i] == "512M":
				if datawidth == "8":
					addrwidth = "29"
					addrmax = 0x20000000
				else:
					addrwidth = "28"
					addrmax = 0x10000000
			elif argv[i] == "805306368" or argv[i] == "805306368b" or argv[i] == "805306368B" or argv[i] == "786432k" or argv[i] == "786432K" or argv[i] == "768m" or argv[i] == "768M":
				if datawidth == "8":
					addrwidth = "29.5"
					addrmax = 0x30000000
				else:
					addrwidth = "28.5"
					addrmax = 0x18000000
			elif argv[i] == "1073741824" or argv[i] == "1073741824b" or argv[i] == "1073741824B" or argv[i] == "1048576k" or argv[i] == "1048576K" or argv[i] == "1024m" or argv[i] == "1024M" or argv[i] == "1g" or argv[i] == "1G":
				if datawidth == "8":
					addrwidth = "30"
					addrmax = 0x40000000
				else:
					addrwidth = "29"
					addrmax = 0x20000000
			elif argv[i] == "1610612736" or argv[i] == "1610612736b" or argv[i] == "1610612736B" or argv[i] == "1572864k" or argv[i] == "1572864K" or argv[i] == "1536m" or argv[i] == "1536M" or argv[i] == "1.5g" or argv[i] == "1.5G":
				if datawidth == "8":
					addrwidth = "30.5"
					addrmax = 0x60000000
				else:
					addrwidth = "29.5"
					addrmax = 0x30000000
			elif argv[i] == "2147483648" or argv[i] == "2147483648b" or argv[i] == "2147483648B" or argv[i] == "2097152k" or argv[i] == "2097152K" or argv[i] == "2048m" or argv[i] == "2048M" or argv[i] == "2g" or argv[i] == "2G":
				if datawidth == "8":
					addrwidth = "31"
					addrmax = 0x80000000
				else:
					addrwidth = "30"
					addrmax = 0x40000000
			elif (argv[i] == "3221225472" or argv[i] == "3221225472b" or argv[i] == "3221225472B" or argv[i] == "3145728k" or argv[i] == "3145728K" or argv[i] == "3072m" or argv[i] == "3072M" or argv[i] == "3g" or argv[i] == "3G") and datawidth != "8":
				addrwidth = "30.5"
				addrmax = 0x60000000
			elif (argv[i] == "4294967296" or argv[i] == "4294967296b" or argv[i] == "4294967296B" or argv[i] == "4194304k" or argv[i] == "4194304K" or argv[i] == "4096m" or argv[i] == "4096M" or argv[i] == "4g" or argv[i] == "4G") and datawidth != "8":
				addrwidth = "31"
				addrmax = 0x80000000
			else:
				print(argv[i] + " is not valid for -a", file=stderr)
				exit()
			i += 1
		elif arg == "-f" and i < len(argv):
			if argv[i] == "raw" or argv[i] == "Raw" or argv[i] == "RAW" or argv[i] == "bin" or argv[i] == "Bin" or argv[i] == "BIN":
				ioformat = "raw"
			elif argv[i] == "hex" or argv[i] == "Hex" or argv[i] == "HEX":
				ioformat = "hex"
			else:
				print(argv[i] + " is not valid for -f", file=stderr)
				exit()
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
		if datawidth != "8":
			addrmax += addrmax
		if ioformat == "hex":
			addrmax += addrmax
		try:
			if output is None:
				with serial.Serial(port=port, baudrate=250000, bytesize=serial.EIGHTBITS,
								   parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
								   xonxoff=False, rtscts=True, dsrdtr=False, timeout=10) as ser:
					time.sleep(5)
					ser.write("d" + datawidth + "\n")
					if ser.readline().strip() != "OK":
						print("No response from device (d)", file=stderr)
						exit()
					ser.write("a" + addrwidth + "\n")
					if ser.readline().strip() != "OK":
						print("No response from device (a)", file=stderr)
						exit()
					ser.write("f" + ioformat + "\n")
					if ser.readline().strip() != "OK":
						print("No response from device (f)", file=stderr)
						exit()
					ser.write("D\n")
					i = 0
					while i < addrmax:
						b = ser.read(1)
						stdout.write(b)
						i += len(b)
					if ioformat == "hex":
						stdout.write("\n")
					fin = ser.readline().strip()
					if fin == "":
						fin = ser.readline().strip()
					if fin != "OK":
						print("No response from device (D)", file=stderr)
					exit()
			else:
				with open(output, "wb") as f:
					with serial.Serial(port=port, baudrate=250000, bytesize=serial.EIGHTBITS,
									   parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
									   xonxoff=False, rtscts=True, dsrdtr=False, timeout=10) as ser:
						time.sleep(5)
						ser.write("d" + datawidth + "\n")
						if ser.readline().strip() != "OK":
							print("No response from device (d)", file=stderr)
							exit()
						ser.write("a" + addrwidth + "\n")
						if ser.readline().strip() != "OK":
							print("No response from device (a)", file=stderr)
							exit()
						ser.write("f" + ioformat + "\n")
						if ser.readline().strip() != "OK":
							print("No response from device (f)", file=stderr)
							exit()
						ser.write("D\n")
						i = 0
						while i < addrmax:
							b = ser.read(1)
							f.write(b)
							i += len(b)
						if ioformat == "hex":
							f.write("\n")
						fin = ser.readline().strip()
						if fin == "":
							fin = ser.readline().strip()
						if fin != "OK":
							print("No response from device (D)", file=stderr)
						exit()
		except KeyboardInterrupt:
			pass

if __name__ == "__main__": main()
