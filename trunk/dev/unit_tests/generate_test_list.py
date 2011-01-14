#!/usr/bin/env python

'''
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009-2010 Fuse-Software (tm)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
'''

import fileinput, os

# the header file that should be generated
test_list_h = "include/vtxtestsUnitTestList.h"

tests = []

for cat in os.listdir("tests/"):
	if cat[0] != ".":
		for test in os.listdir("tests/" + cat + "/"):
			if test[0] != ".":
				tests.append(cat + "/" + test)

file = open(test_list_h, "w")
file.write("\n/* This is a machine generated file, DON'T ATTEMPT TO EDIT THIS !!! */\n\n")
file.write("#ifndef __vtx_tests_UnitTestList_H__\n")
file.write("#define __vtx_tests_UnitTestList_H__\n\n")

def write_separator(file, prefix = ""):
	file.write(prefix + "//-----------------------------------------------------------------------\n")

prev_cat = ""
for test in tests:
	info = test.partition("/")
	
	if prev_cat != info[0]:
		write_separator(file)
		
	prev_cat = info[0]
	
	file.write("#include \"" + info[0] + "/" + info[2] + "/" + info[2] + ".h\"\n")

write_separator(file)

file.write("#define RUN_TEST_FROM_STRING(host, str) \\\n")
file.write("	if(false){} \\\n")

for test in tests:
	info = test.partition("/")
	name = info[0] + "::" + info[2]
	file.write("	else if(str == \"" + name + "\") \\\n")
	file.write("		host.runTest<" + name + ">(); \\\n	\\\n")

file.write("	else VTX_EXCEPT(\"Unknown test: %s\", test_name.c_str())\n")

write_separator(file)

file.write("\n#endif\n")
file.close()
