#include <iostream>
#include <conio.h>
#include "windows.h"

#include "vtxFileManager.h"
#include "vtxRoot.h"

#include "vtxd3d9MovableMovie.h"

// vektrix plugins
#include "vtxas3Plugin.h"
#include "vtxcaiPlugin.h"
#include "vtxd3d9Plugin.h"
#include "vtxopPlugin.h"
#include "vtxswfPlugin.h"
#include "vtxxmlPlugin.h"

int main(int argc, char** argv)
{
	VTX_MEM_DEBUG_ENABLE();

	// start vektrix
	vtx::Root* vektrix_root = new vtx::Root();

	vtx::LogManager::getSingletonPtr()->logToCout(true);

	vtx::FileManager::getSingletonPtr()->addFileContainer("../demos/Ogre3D/media");

	// vektrix plugins
#if VTX_OS == VTX_WIN32
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
#endif
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_D3D9Plugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

	vtx::d3d9::MovableMovie* d3dmovie = (vtx::d3d9::MovableMovie*)vektrix_root->createMovie("d3d_movie", "shape_test.swf", "D3D9MovableMovie");
	d3dmovie->play();

	vtx::uint timeStep = timeGetTime();
	float delta_time = 0.0f;

	while(!kbhit())
	{
		vektrix_root->update(delta_time);
		timeStep = timeGetTime() - timeStep;
		delta_time = (float)timeStep * 0.001f;
		Sleep(1);
	}

	delete vektrix_root;

	return 0;
}
