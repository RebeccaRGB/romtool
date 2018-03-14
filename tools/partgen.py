#!/usr/bin/env python

from __future__ import print_function
from datetime import date
from sys import argv
from sys import exit

def escape(s):
	return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;').replace('"', '&quot;')




class PartGenerator(object):
	def generate(self, prefix):
		with open(prefix + "_schematic.svg", "w") as f:
			for line in self.schematic():
				print(line, file=f)
		with open(prefix + "_pcb.svg", "w") as f:
			for line in self.pcb():
				print(line, file=f)
		with open(prefix + "_breadboard.svg", "w") as f:
			for line in self.breadboard():
				print(line, file=f)
		with open(prefix + ".fzp", "w") as f:
			for line in self.fzp(prefix):
				print(line, file=f)




class SOIC(PartGenerator):
	def __init__(self,
	             module_id="SO44",
	             version="1",
	             author="",
	             description="",
	             title="SO44",
	             tags=None,
	             package="SO44",
	             label="SO44",
	             pins=44,
	             schematic_width=5,
	             breadboard_height=10,
	             pad_length=3.0,
	             pad_width=0.7,
	             pad_pitch=1.27,
	             chip_width=12.0,
	             chip_height=27.565,
	             p1_diameter=1.0,
	             p1_xoffset=0.5,
	             p1_yoffset=0.565):
		self.module_id = module_id
		self.version = version
		self.author = author
		self.description = description
		self.title = title
		self.tags = tags if tags is not None else ["SMD"]
		self.package = package
		self.label = label
		self.vpins = (pins + 1) / 2
		self.swidth = schematic_width
		self.bbheight = breadboard_height
		self.pad_length = pad_length
		self.pad_width = pad_width
		self.pad_pitch = pad_pitch
		self.chip_width = chip_width
		self.chip_height = chip_height
		self.p1d = p1_diameter
		self.p1x = p1_xoffset
		self.p1y = p1_yoffset


	@property
	def pins(self):
		return self.vpins * 2


	@pins.setter
	def pins(self, pins):
		self.vpins = (pins + 1) / 2


	def schematic(self):
		yield '<?xml version="1.0" encoding="utf-8" standalone="no"?>'
		yield '<svg xmlns="http://www.w3.org/2000/svg" version="1.1" x="0in" y="0in" width="%gin" height="%gin" viewBox="0 0 %g %g">' % ((self.swidth + 4) / 10.0, (self.vpins + 1) / 10.0, (self.swidth + 4) * 7.2, (self.vpins + 1) * 7.2)
		yield '<g id="schematic">'
		yield '<rect class="interior rect" x="14.85" y="0.45" width="%g" height="%g" fill="#FFFFFF" stroke="#000000" stroke-width="0.9"/>' % (self.swidth * 7.2 - 0.9, (self.vpins + 1) * 7.2 - 0.9)

		for i in range(0, self.vpins):
			yield '<line class="pin" id="connector%dpin" x1="0" y1="%g" x2="14.85" y2="%g" fill="none" stroke="#787878" stroke-width="0.7"/>' % (i, (i + 1) * 7.2, (i + 1) * 7.2)
		for i in range(0, self.vpins):
			yield '<line class="pin" id="connector%dpin" x1="%g" y1="%g" x2="%g" y2="%g" fill="none" stroke="#787878" stroke-width="0.7"/>' % (self.vpins + i, (self.swidth + 2) * 7.2 - 0.45, (self.vpins - i) * 7.2, (self.swidth + 4) * 7.2, (self.vpins - i) * 7.2)
		for i in range(0, self.vpins):
			yield '<text class="text" x="7.425" y="%g" fill="#8C8C8C" font-family="Droid Sans" font-size="2.5" text-anchor="middle">%d</text>' % ((i + 1) * 7.2 - 1.0, i + 1)
		for i in range(0, self.vpins):
			yield '<text class="text" x="%g" y="%g" fill="#8C8C8C" font-family="Droid Sans" font-size="2.5" text-anchor="middle">%d</text>' % ((self.swidth + 3) * 7.2 - 0.225, (self.vpins - i) * 7.2 - 1.0, self.vpins + i + 1)
		for i in range(0, self.vpins):
			yield '<text class="text" x="16.148" y="%g" fill="#8C8C8C" font-family="Droid Sans" font-size="3.5" text-anchor="start">%d</text>' % ((i + 1) * 7.2 + 0.8, i + 1)
		for i in range(0, self.vpins):
			yield '<text class="text" x="%g" y="%g" fill="#8C8C8C" font-family="Droid Sans" font-size="3.5" text-anchor="end">%d</text>' % ((self.swidth + 2) * 7.2 - 1.748, (self.vpins - i) * 7.2 + 0.8, self.vpins + i + 1)
		for i in range(0, self.vpins):
			yield '<rect class="terminal" id="connector%dterminal" x="-0.35" y="%g" width="0.7" height="0.7" fill="none"/>' % (i, (i + 1) * 7.2 - 0.35)
		for i in range(0, self.vpins):
			yield '<rect class="terminal" id="connector%dterminal" x="%g" y="%g" width="0.7" height="0.7" fill="none"/>' % (self.vpins + i, (self.swidth + 4) * 7.2 - 0.35, (self.vpins - i) * 7.2 - 0.35)

		yield '<text class="text" id="label" x="%g" y="%g" font-family="Droid Sans" font-size="4.25" text-anchor="middle">%s</text>' % ((self.swidth + 4) * 3.6, (self.vpins + 1) * 3.6 - 1.8, escape(self.label))
		yield '</g>'
		yield '</svg>'


	def pcb(self):
		width = self.chip_width + self.pad_length * 2.0 + 0.3
		height = self.chip_height + 0.13
		pady = (height - ((self.vpins - 1) * self.pad_pitch) - self.pad_width) / 2.0

		yield '<?xml version="1.0" encoding="utf-8" standalone="no"?>'
		yield '<svg xmlns="http://www.w3.org/2000/svg" version="1.1" x="0in" y="0in" width="%gin" height="%gin" viewBox="0 0 %g %g">' % (width / 25.4, height / 25.4, width, height)
		yield '<g id="silkscreen">'
		yield '<rect x="%g" y="0.065" width="%g" height="%g" fill="none" stroke="#FFFFFF" stroke-width="0.127"/>' % (self.pad_length + 0.15, self.chip_width, self.chip_height)
		yield '<circle cx="%g" cy="%g" r="%g" fill="none" stroke="#FFFFFF" stroke-width="0.127"/>' % (self.pad_length + self.p1x + self.p1d / 2.0 + 0.15, self.p1y + self.p1d / 2.0 + 0.065, self.p1d / 2.0)
		yield '</g>'
		yield '<g id="copper1">'

		for i in range(0, self.vpins):
			yield '<rect id="connector%dpad" x="0" y="%g" width="%g" height="%g" fill="#F7BD13" stroke="none" stroke-width="0"/>' % (i, i * self.pad_pitch + pady, self.pad_length, self.pad_width)
		for i in range(0, self.vpins):
			yield '<rect id="connector%dpad" x="%g" y="%g" width="%g" height="%g" fill="#F7BD13" stroke="none" stroke-width="0"/>' % (self.vpins + i, width - self.pad_length, (self.vpins - i - 1) * self.pad_pitch + pady, self.pad_length, self.pad_width)

		yield '</g>'
		yield '</svg>'


	def breadboard(self):
		width = self.chip_width + self.pad_length * 2.0 + 0.3
		height = self.chip_height + 0.13
		pady = (height - ((self.vpins - 1) * self.pad_pitch) - self.pad_width) / 2.0

		yield '<?xml version="1.0" encoding="utf-8" standalone="no"?>'
		yield '<svg xmlns="http://www.w3.org/2000/svg" version="1.1" x="0in" y="0in" width="%gin" height="%gin" viewBox="0 0 %g %g">' % (self.vpins / 10.0, self.bbheight / 10.0, self.vpins * 7.2, self.bbheight * 7.2)
		yield '<g id="breadboard">'
		yield '<g id="icon">'
		yield '<path d="M 0 0 V %g c 1.192 0 2.16 0.968 2.16 2.16 c 0 1.192 -0.968 2.16 -2.16 2.16 V %g H %g V 0 H 0 z" fill="#1F7A34"/>' % (self.bbheight * 3.6 - 2.16, self.bbheight * 7.2, self.vpins * 7.2)

		if (width > height) != (self.vpins < self.bbheight):
			yield '<g transform="translate(%g %g) scale(2.835)">' % ((self.vpins * 7.2 - width * 2.835) / 2.0, (self.bbheight * 7.2 - height * 2.835) / 2.0)
		else:
			yield '<g transform="translate(%g %g) scale(2.835) rotate(-90)">' % ((self.vpins * 7.2 - height * 2.835) / 2.0, (self.bbheight * 7.2 + width * 2.835) / 2.0)

		for i in range(0, self.vpins):
			yield '<rect x="0" y="%g" width="%g" height="%g" fill="#8C8C8C" stroke="none" stroke-width="0"/>' % (i * self.pad_pitch + pady, self.pad_length, self.pad_width)
		for i in range(0, self.vpins):
			yield '<rect x="%g" y="%g" width="%g" height="%g" fill="#8C8C8C" stroke="none" stroke-width="0"/>' % (width - self.pad_length, (self.vpins - i - 1) * self.pad_pitch + pady, self.pad_length, self.pad_width)

		x1 = self.pad_length + 0.15
		x2 = self.pad_length + 0.277
		x3 = self.pad_length + self.chip_width + 0.023
		x4 = self.pad_length + self.chip_width + 0.15
		y3 = self.chip_height - 0.062
		y4 = self.chip_height + 0.065

		yield '<rect x="%g" y="0.065" width="%g" height="%g" fill="#303030" stroke="none" stroke-width="0"/>' % (x1, self.chip_width, self.chip_height)
		yield '<polygon points="%g 0.065 %g 0.192 %g %g %g %g" fill="#1F1F1F"/>' % (x1, x2, x2, y3, x1, y4)
		yield '<polygon points="%g 0.192 %g 0.065 %g %g %g %g" fill="#1F1F1F"/>' % (x3, x4, x4, y4, x3, y3)
		yield '<polygon points="%g 0.065 %g 0.065 %g 0.192 %g 0.192" fill="#000000"/>' % (x1, x4, x3, x2)
		yield '<polygon points="%g %g %g %g %g %g %g %g" fill="#3D3D3D"/>' % (x1, y4, x2, y3, x3, y3, x4, y4)

		yield '<circle cx="%g" cy="%g" r="%g" fill="#1F1F1F" stroke="none" stroke-width="0"/>' % (self.pad_length + self.p1x + self.p1d / 2.0 + 0.15, self.p1y + self.p1d / 2.0 + 0.065, self.p1d / 2.0)
		yield '</g>'
		yield '<text id="label" x="3.6" y="%g" fill="#FFFFFF" font-family="OCRA" font-size="4.68" text-anchor="start">%s</text>' % (self.bbheight * 3.6 + 1.8, escape(self.label))

		for i in range(0, self.vpins):
			yield '<text transform="translate(%g %g) rotate(-90)" fill="#FFFFFF" font-family="OCRA" font-size="3.24" text-anchor="start">%d</text>' % ((i + 1) * 7.2 - 2.6, self.bbheight * 7.2 - 5.325, i + 1)
		for i in range(0, self.vpins):
			yield '<text transform="translate(%g 5.325) rotate(-90)" fill="#FFFFFF" font-family="OCRA" font-size="3.24" text-anchor="end">%d</text>' % ((self.vpins - i) * 7.2 - 2.6, self.vpins + i + 1)

		yield '</g>'

		y1 = (self.bbheight - 1) * 7.2 + 2.45
		y2 = (self.bbheight - 1) * 7.2 + 3.01
		y3 = self.bbheight * 7.2 - 3.01
		y4 = self.bbheight * 7.2 - 2.45

		for i in range(0, self.vpins):
			x1 = i * 7.2 + 2.45
			x2 = i * 7.2 + 3.01
			x3 = (i + 1) * 7.2 - 3.01
			x4 = (i + 1) * 7.2 - 2.45
			yield '<g id="connector%dpin">' % i
			yield '<rect x="%g" y="%g" width="2.3" height="2.3" fill="#8D8C8C"/>' % (x1, y1)
			yield '<rect x="%g" y="%g" width="1.18" height="1.18" fill="#8C8663"/>' % (x2, y2)
			yield '<polygon points="%g %g %g %g %g %g %g %g" fill="#B8AF82"/>' % (x1, y4, x2, y3, x2, y2, x1, y1)
			yield '<polygon points="%g %g %g %g %g %g %g %g" fill="#80795B"/>' % (x3, y2, x2, y2, x1, y1, x4, y1)
			yield '<polygon points="%g %g %g %g %g %g %g %g" fill="#5E5B43"/>' % (x3, y3, x3, y2, x4, y1, x4, y4)
			yield '<polygon points="%g %g %g %g %g %g %g %g" fill="#9A916C"/>' % (x1, y4, x2, y3, x3, y3, x4, y4)
			yield '</g>'

		for i in range(0, self.vpins):
			x1 = (self.vpins - i - 1) * 7.2 + 2.45
			x2 = (self.vpins - i - 1) * 7.2 + 3.01
			x3 = (self.vpins - i) * 7.2 - 3.01
			x4 = (self.vpins - i) * 7.2 - 2.45
			yield '<g id="connector%dpin">' % (self.vpins + i)
			yield '<rect x="%g" y="2.45" width="2.3" height="2.3" fill="#8D8C8C"/>' % x1
			yield '<rect x="%g" y="3.01" width="1.18" height="1.18" fill="#8C8663"/>' % x2
			yield '<polygon points="%g 4.75 %g 4.19 %g 3.01 %g 2.45" fill="#B8AF82"/>' % (x1, x2, x2, x1)
			yield '<polygon points="%g 3.01 %g 3.01 %g 2.45 %g 2.45" fill="#80795B"/>' % (x3, x2, x1, x4)
			yield '<polygon points="%g 4.19 %g 3.01 %g 2.45 %g 4.75" fill="#5E5B43"/>' % (x3, x3, x4, x4)
			yield '<polygon points="%g 4.75 %g 4.19 %g 4.19 %g 4.75" fill="#9A916C"/>' % (x1, x2, x3, x4)
			yield '</g>'

		yield '</g>'
		yield '</svg>'


	def fzp(self, prefix):
		yield '<?xml version="1.0" encoding="utf-8"?>'
		yield '<module fritzingVersion="0.5.2b.02.18.4756" moduleId="%s">' % escape(self.module_id)
		yield '<version>%s</version>' % escape(self.version)
		yield '<date>%s</date>' % date.today().strftime('%Y-%m-%d')
		yield '<author>%s</author>' % escape(self.author)
		yield '<description>%s</description>' % escape(self.description)
		yield '<title>%s</title>' % escape(self.title)
		yield '<tags>'

		for tag in self.tags:
			yield '<tag>%s</tag>' % escape(tag)

		yield '</tags>'
		yield '<properties>'
		yield '<property name="package">%s</property>' % escape(self.package)
		yield '<property name="family">Generic IC</property>'
		yield '<property name="chip label">%s</property>' % escape(self.label)
		yield '<property name="editable pin labels">true</property>'
		yield '</properties>'
		yield '<views>'
		yield '<breadboardView>'
		yield '<layers image="breadboard/%s_breadboard.svg">' % escape(prefix)
		yield '<layer layerId="breadboard"/>'
		yield '</layers>'
		yield '</breadboardView>'
		yield '<schematicView>'
		yield '<layers image="schematic/%s_schematic.svg">' % escape(prefix)
		yield '<layer layerId="schematic"/>'
		yield '</layers>'
		yield '</schematicView>'
		yield '<pcbView>'
		yield '<layers image="pcb/%s_pcb.svg">' % escape(prefix)
		yield '<layer layerId="copper1"/>'
		yield '<layer layerId="silkscreen"/>'
		yield '</layers>'
		yield '</pcbView>'
		yield '<iconView>'
		yield '<layers image="breadboard/%s_breadboard.svg">' % escape(prefix)
		yield '<layer layerId="icon"/>'
		yield '</layers>'
		yield '</iconView>'
		yield '</views>'
		yield '<connectors>'

		for i in range(0, self.vpins * 2):
			yield '<connector id="connector%d" type="male" name="%d">' % (i, i + 1)
			yield '<description>%d</description>' % (i + 1)
			yield '<views>'
			yield '<breadboardView>'
			yield '<p layer="breadboard" svgId="connector%dpin"/>' % i
			yield '</breadboardView>'
			yield '<schematicView>'
			yield '<p layer="schematic" svgId="connector%dpin" terminalId="connector%dterminal"/>' % (i, i)
			yield '</schematicView>'
			yield '<pcbView>'
			yield '<p layer="copper1" svgId="connector%dpad"/>' % i
			yield '</pcbView>'
			yield '</views>'
			yield '</connector>'

		yield '</connectors>'
		yield '<buses>'
		yield '</buses>'
		yield '</module>'




def help():
	print()
	print("partgen.py - generate Fritzing parts for surface mount ICs")
	print()
	print("-a, --author <string>")
	print("        set part author name")
	print("-b, --label <string>")
	print("        set part label")
	print("-d, --description <string>")
	print("        set part description")
	print("-g, --tags <string>[,<string>][...]")
	print("        set part tags")
	print("-h, --chip-height <float>")
	print("        set IC body length in mm")
	print("-i, --title <string>")
	print("        set part title")
	print("-k, --package <string>")
	print("        set part package type")
	print("-l, --pad-length <float>")
	print("        set lead length in mm")
	print("-m, --module-id <string>")
	print("        set part module id")
	print("-n, --pins <int>")
	print("        set number of pins")
	print("-o, --prefix <string>")
	print("        set prefix for output file names")
	print("-p, --pad-pitch <float>")
	print("        set pitch (distance between centers of adjacent leads) in mm")
	print("-q, --package-all <string>")
	print("        set --module-id, --title, --package, --label, and --prefix")
	print("-r, --breadboard-height <int>")
	print("        set breadth of breadboard view in tenths of an inch")
	print("-s, --schematic-width <int>")
	print("        set width of schematic symbol in tenths of an inch")
	print("-t, --pad-width <float>")
	print("        set lead width in mm")
	print("-v, --version <string>")
	print("        set part version number")
	print("-w, --chip-width <float>")
	print("        set IC body width in mm")
	print("-x, --p1-xoffset <float>")
	print("        set distance from left side to pin 1 indicator in mm")
	print("-y, --p1-yoffset <float>")
	print("        set distance from top side to pin 1 indicator in mm")
	print("-z, --p1-diameter <float>")
	print("        set diameter of pin 1 indicator in mm")
	print()

def main():
	chip = SOIC()
	prefix = chip.module_id
	i = 1
	while i < len(argv):
		arg = argv[i]
		i += 1
		if arg == "--help":
			help()
			exit()
		elif arg == "--soic":
			chip = SOIC()
			prefix = chip.module_id
		elif (arg == "-m" or arg == "--module-id") and i < len(argv):
			chip.module_id = argv[i]
			i += 1
		elif (arg == "-v" or arg == "--version") and i < len(argv):
			chip.version = argv[i]
			i += 1
		elif (arg == "-a" or arg == "--author") and i < len(argv):
			chip.author = argv[i]
			i += 1
		elif (arg == "-d" or arg == "--description") and i < len(argv):
			chip.description = argv[i]
			i += 1
		elif (arg == "-i" or arg == "--title") and i < len(argv):
			chip.title = argv[i]
			i += 1
		elif (arg == "-g" or arg == "--tags") and i < len(argv):
			chip.tags = argv[i].split(',')
			i += 1
		elif (arg == "-k" or arg == "--package") and i < len(argv):
			chip.package = argv[i]
			i += 1
		elif (arg == "-b" or arg == "--label") and i < len(argv):
			chip.label = argv[i]
			i += 1
		elif (arg == "-n" or arg == "--pins") and i < len(argv):
			chip.pins = int(argv[i])
			i += 1
		elif (arg == "-s" or arg == "--schematic-width") and i < len(argv):
			chip.schematic_width = int(argv[i])
			i += 1
		elif (arg == "-r" or arg == "--breadboard-height") and i < len(argv):
			chip.breadboard_height = int(argv[i])
			i += 1
		elif (arg == "-l" or arg == "--pad-length") and i < len(argv):
			chip.pad_length = float(argv[i])
			i += 1
		elif (arg == "-t" or arg == "--pad-width") and i < len(argv):
			chip.pad_width = float(argv[i])
			i += 1
		elif (arg == "-p" or arg == "--pad-pitch") and i < len(argv):
			chip.pad_pitch = float(argv[i])
			i += 1
		elif (arg == "-w" or arg == "--chip-width") and i < len(argv):
			chip.chip_width = float(argv[i])
			i += 1
		elif (arg == "-h" or arg == "--chip-height") and i < len(argv):
			chip.chip_height = float(argv[i])
			i += 1
		elif (arg == "-z" or arg == "--p1-diameter") and i < len(argv):
			chip.p1_diameter = float(argv[i])
			i += 1
		elif (arg == "-x" or arg == "--p1-xoffset") and i < len(argv):
			chip.p1_xoffset = float(argv[i])
			i += 1
		elif (arg == "-y" or arg == "--p1-yoffset") and i < len(argv):
			chip.p1_yoffset = float(argv[i])
			i += 1
		elif (arg == "-o" or arg == "--prefix") and i < len(argv):
			prefix = argv[i]
			i += 1
		elif (arg == "-q" or arg == "--package-all") and i < len(argv):
			chip.module_id = argv[i]
			chip.title = argv[i]
			chip.package = argv[i]
			chip.label = argv[i]
			prefix = argv[i]
			i += 1
		else:
			print("Unknown option: " + arg)
			exit()
	chip.generate(prefix)

if __name__ == "__main__": main()
