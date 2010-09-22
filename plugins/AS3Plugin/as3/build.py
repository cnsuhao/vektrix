#!/usr/bin/env python

import os;
import sys;

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

cmd = "python %CASPIN_HOME%/tools/cspcompile.py flash ";

for str in packages:
	cmd += str + " ";


os.system(cmd);

os.system("python %CASPIN_HOME%/tools/cspgenerate.py flash");

