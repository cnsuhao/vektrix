#!/usr/bin/env python

import os, glob
import sys

def compile_class(clazz):
	cmd = "python %CASPIN_HOME%/tools/cspcompile.py " + clazz + " " + clazz + ".as"
	if os.system(cmd) != 0:
		exit(1)

def link_abc(package):
	abc_files = glob.glob(package.replace("_", "/") + "/*.abc")
	cmd = "python %CASPIN_HOME%/tools/cspcompile.py " + package + " "
	for file in abc_files:
		cmd += file + " "
	if os.system(cmd) != 0:
		exit(1)

def compile(output, input):
	cmd = "python %CASPIN_HOME%/tools/cspcompile.py " + output + " " + input
	if os.system(cmd) != 0:
		exit(1)

def generate(package, dependencies):
	namespace = package.replace("_", "::")
	if os.system("python %CASPIN_HOME%/tools/cspgenerate.py " + package + " " + dependencies) != 0:
		exit(1)

if len(sys.argv) < 2 or sys.argv[1] != "multi":
	packages = [
	"flash/accessibility/*.as", 
	"flash/display/*.as", 
	"flash/events/*.as", 
	"flash/filters/*.as", 
	"flash/geom/*.as", 
	"flash/media/*.as", 
	"flash/net/*.as", 
	"flash/system/*.as" ,
	"flash/text/*.as", 
	"flash/ui/*.as", 
	"flash/utils/*.as", 
	"vektrix/*.as"
	]

	files = "";

	for str in packages:
		files += str + " ";

	compile("flash", files)
	generate("flash", "")

else:
	print "----------------------------------------------"
	print " COMPILATION"
	print "----------------------------------------------"

	compile_class("flash/accessibility/Accessibility")
	compile_class("flash/accessibility/AccessibilityProperties")
	
	link_abc("flash_accessibility")

	#compile("flash_events",			"flash/events/*.as")
	#compile("flash_display",		"flash/display/*.as")
	#compile("flash_filters",		"flash/filters/*.as")
	#compile("flash_geom",			"flash/geom/*.as")
	#compile("flash_media",			"flash/media/*.as")
	#compile("flash_net",			"flash/net/*.as")
	#compile("flash_system",			"flash/system/*.as")
	#compile("flash_text",			"flash/text/*.as")
	#compile("flash_ui",				"flash/ui/*.as")
	#compile("flash_utils",			"flash/utils/*.as")
	#compile("vektrix",				"vektrix/*.as")

	print "----------------------------------------------"
	print " GENERATION"
	print "----------------------------------------------"

	#generate("flash_accessibility",	"")
	#generate("flash_events",		"flash_utils.abc")
	#generate("flash_display",		"flash_utils.abc flash_net.abc flash_system.abc flash_events.abc")
	#generate("flash_filters",		"")
	#generate("flash_geom",			"")
	#generate("flash_media",			"")
	#generate("flash_net",			"")
	#generate("flash_system",		"")
	#generate("flash_text",			"flash_display.abc")
	#generate("flash_ui",			"")
	#generate("flash_utils",			"flash_events.abc")
	#generate("vektrix",				"flash_events.abc")
