#!/usr/bin/env python

import os, glob
import sys

for filename in glob.glob("*.abc"):
	os.remove(filename)
