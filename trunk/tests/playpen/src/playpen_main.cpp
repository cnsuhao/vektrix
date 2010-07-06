#include <conio.h>
#include <iostream>

#include <Windows.h>

#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxRoot.h"

// vektrix plugins
#include "vtxas3Plugin.h"
#include "vtxcaiPlugin.h"
#include "vtxcurlPlugin.h"
#include "vtxfreeimgPlugin.h"
#include "vtxopPlugin.h"
#include "vtxswfPlugin.h"
#include "vtxxmlPlugin.h"

using namespace vtx;

class FileListener : public File::Listener
{
public:
	void loadingCompleted(File* file)
	{
		std::cout << "The file: " << file->getFilename() << " finished loading..." << std::endl;
	}
};

int main(int argc, char** argv)
{
	VTX_MEM_DEBUG_ENABLE();
	//VTX_MEM_DEBUG_BREAK(5032);

	Root* vtx_root = new Root();

	LogManager::getSingletonPtr()->logToCout(true);

	// vektrix plugins
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_cURLPlugin);
	VTX_LOAD_PLUGIN(vektrix_FreeImgPlugin);
	VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);
	VTX_LOAD_PLUGIN(vektrix_XmlPlugin);

	FileManager* file_mgr = FileManager::getSingletonPtr();

	file_mgr->addFileContainer("", "WebFileContainer");

	FileListener listener;

	File* file1 = file_mgr->getFile("http://www.geneburch.com/wallpaper/01/1920x1200.jpg", true);
	File* file2 = file_mgr->getFile("http://a1.twimg.com/profile_images/626531386/vtx_logo_normal.png", true);
	File* file3 = file_mgr->getFile("http://fuse-software.com/vektrix/dyn_text_web.swf", true);

	std::cout << "..." << std::endl;

	if(file1) file1->addListener(&listener);
	if(file2) file2->addListener(&listener);
	if(file3) file3->addListener(&listener);

	while(!kbhit())
	{
		vtx_root->update(10);
		Sleep(10);
	}

	delete vtx_root;

	return 0;
}
