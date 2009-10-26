#include "Ogre3D_Demo.h"

int main(int argc, char* argv[])
{
	vtxDemoApplication app;

	try
	{
		app.go();
	}
	catch(Ogre::Exception& e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

