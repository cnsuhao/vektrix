/*
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
*/

package vtx
{
	import adobe.utils.MMExecute;

	public class FlashPreview
	{
		public static function previewWithVektrix()
		{
		MMExecute(
		'var currDoc = fl.getDocumentDOM();'+

		// get the working directory of the current document
		'function getDocumentDirectory()'+
		'{'+
			'var doc_path = currDoc.path;'+

			'var slashIdx = doc_path.lastIndexOf("/");'+
			'var backslashIdx = doc_path.lastIndexOf("\\\\");'+

			// document is a XFL document, remove another directory level
			'if(doc_path.search(".xfl") != -1)'+
			'{'+
				'slashIdx = doc_path.substring(0, slashIdx).lastIndexOf("/");'+
				'backslashIdx = doc_path.substring(0, backslashIdx).lastIndexOf("\\\\");'+
			'}'+

			'if(slashIdx != -1)'+
			'{'+
				'return doc_path.substring(0, slashIdx+1);'+
			'}'+

			'if(backslashIdx != -1)'+
			'{'+
				'return doc_path.substring(0, backslashIdx+1);'+
			'}'+

			'return null;'+
		'}'+

		// get the SWF publish path for the current document
		'function getSwfPath()'+
		'{'+
			'var profileXML = currDoc.exportPublishProfileString();'+
			'var startIdx = profileXML.search("<flashFileName>");'+
			'var endIdx = profileXML.search("</flashFileName>");'+

			'if(startIdx != -1 && endIdx != -1)'+
			'{'+
				'var swf_filename = profileXML.substring(startIdx + 15, endIdx);'+
				'if(swf_filename.length == 0) return null;'+

				'if(swf_filename.indexOf("/") != -1) return swf_filename;'+
				'if(swf_filename.indexOf("\\\\") != -1) return swf_filename;'+

				'return getDocumentDirectory() + swf_filename;'+
			'}'+

			'return null;'+
		'}'+

		// main()
		'if(currDoc == null)'+
		'{'+
			'var errorMsg = \'vektrix Flash Preview: no document open/selected\';'+
			'fl.outputPanel.trace(errorMsg);'+
		'}'+
		'else if(currDoc.path == null)'+
		'{'+
			'var errorMsg = \'vektrix Flash Preview: you have to save the current document before you can preview it\';'+
			'fl.outputPanel.trace(errorMsg);'+
		'}'+
		'else'+
		'{'+
			'var swf_path = getSwfPath();'+
			'if(swf_path == null)'+
			'{'+
				'fl.trace("Internal Error: Unable to retrieve SWF publish path");'+
			'}'+
			'else'+
			'{'+
				'currDoc.publish();'+
				'var cfg_path = "file:///C|/vtxFlashPreview.cfg";'+
				
				'if(FLfile.exists(cfg_path))'+
				'{'+
					'var cmd = FLfile.read(cfg_path);'+
					
					'if(cmd)'+
					'{'+
						"fl.trace('Previewing file with vektrix: \"' + swf_path + '\"');"+
						"cmd = cmd.concat(' \"', swf_path, '\"');"+
						'FLfile.runCommandLine(cmd);'+
					'}'+
					'else'+
					'{'+
						'alert("Config file is empty?");'+
					'}'+
				'}'+
				'else'+
				'{'+
					'alert("Unable to open config file: C:/vtxFlashPreview.cfg");'+
				'}'+
			'}'+
		'}'
		);
		}
	}
}
