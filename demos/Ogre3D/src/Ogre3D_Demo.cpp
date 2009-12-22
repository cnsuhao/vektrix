#define OIS_DYNAMIC_LIB

#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxMovie.h"
#include "vtxRoot.h"

#include "vtxopMovableMovie.h"

#include "Ogre.h" 
#include "OgreFrameListener.h" 
#include <OIS/OIS.h>

vtx::ogre::MovableMovie* movie = NULL;
Ogre::SceneNode* movie_node = NULL;
Ogre::RenderWindow* mWindow = NULL;

using namespace Ogre; 

class SimpleFrameListener : public FrameListener 
{
public: 
	SimpleFrameListener(OIS::Keyboard* keyboard, OIS::Mouse* mouse) 
	{ 
		mKeyboard = keyboard; 
		mMouse = mouse; 
	} 

	bool frameStarted(const FrameEvent& evt) 
	{
		mKeyboard->capture();
		mMouse->capture();

		//const OIS::MouseState& state = mMouse->getMouseState();

		//movie->setMouseRel(state.X.abs/(float)mWindow->getWidth(), state.Y.abs/(float)mWindow->getHeight());

		//if(state.buttonDown(OIS::MB_Left))
		//{
		//	movie->mouseDown();
		//}
		//else 
		//{
		//	movie->mouseUp();
		//}

		vtx::Root::getSingletonPtr()->update(evt.timeSinceLastFrame);

		if(mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q)) 
			return false; 

		return true; 
	} 

	bool frameEnded(const FrameEvent& evt) 
	{ 
		return true; 
	} 
private: 
	OIS::Keyboard* mKeyboard; 
	OIS::Mouse* mMouse; 
}; 

class SimpleKeyListener : public OIS::KeyListener 
{
public: 
	bool keyPressed(const OIS::KeyEvent& e){ return true; }

	bool keyReleased(const OIS::KeyEvent& e){ return true; }
};

class SimpleMouseListener : public OIS::MouseListener
{
public: 
	bool mouseMoved(const OIS::MouseEvent& e)
	{
		movie->setMouseRel(e.state.X.abs/(float)mWindow->getWidth(), e.state.Y.abs/(float)mWindow->getHeight());

		return true;
	}

	bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		movie->mouseDown();

		return true;
	}

	bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		movie->mouseUp();

		return true;
	}
};

int main(int argc, char **argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(4055);

	// start vektrix
	new vtx::Root();

	Root* ogre_root = new Root("", "ogre.cfg", "Ogre.log");

	vtx::Root* vektrix_root = vtx::Root::getSingletonPtr();
	vtx::LogManager::getSingletonPtr()->logToCout(true);

	vtx::FileManager::getSingletonPtr()->addFileContainer("../demos/Ogre3D/media");

#ifdef _DEBUG
	// vektrix plugins
	vektrix_root->loadPlugin("vektrix_AS3Plugin_d");
	vektrix_root->loadPlugin("vektrix_SwfPlugin_d");
	//vektrix_root->loadPlugin("vektrix_XmlPlugin_d");
	vektrix_root->loadPlugin("vektrix_OgrePlugin_d");

	// ogre plugins
	ogre_root->loadPlugin("RenderSystem_Direct3D9_d");
	ogre_root->loadPlugin("RenderSystem_GL_d");
#else
	// vektrix plugins
	vektrix_root->loadPlugin("vektrix_AS3Plugin");
	vektrix_root->loadPlugin("vektrix_SwfPlugin");
	//vektrix_root->loadPlugin("vektrix_XmlPlugin");
	vektrix_root->loadPlugin("vektrix_OgrePlugin");

	// ogre plugins
	ogre_root->loadPlugin("RenderSystem_Direct3D9");
	ogre_root->loadPlugin("RenderSystem_GL");
#endif

	if(!ogre_root->showConfigDialog())
	{
		delete ogre_root;
		return false;
	}

	mWindow = ogre_root->initialise(true, "vektrix Ogre3D Demo");

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	SceneManager* sceneMgr = ogre_root->createSceneManager(ST_GENERIC); 

	Camera* camera = sceneMgr->createCamera("MainCamera"); 

	Viewport* viewPort = mWindow->addViewport(camera);
	//viewPort->setBackgroundColour(Ogre::ColourValue::Red);

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//setup the manager, keyboard and mouse to handle input
	OIS::InputManager* inputManager = OIS::InputManager::createInputSystem(pl);
	OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	OIS::Mouse*	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

	//tell OIS about the window's dimensions
	//unsigned int width, height, depth;
	//int top, left;
	//window->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = mouse->getMouseState();
	ms.width = mWindow->getWidth();
	ms.height = mWindow->getHeight();

	//key events
	SimpleKeyListener* keyListener = new SimpleKeyListener();
	keyboard->setEventCallback(keyListener);

	//mouse events
	SimpleMouseListener* mouseListener = new SimpleMouseListener();
	mouse->setEventCallback(mouseListener);

	//render events
	SimpleFrameListener* frameListener = new SimpleFrameListener(keyboard, mouse);
	ogre_root->addFrameListener(frameListener); 

	// VEKTRIX
	movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "vtx_button.swf", "OgreMovableMovie");
	movie->play();

	movie_node = sceneMgr->getRootSceneNode()->createChildSceneNode();
	movie_node->attachObject(movie);
	int width = movie->getFile()->getHeader().width;
	int height = movie->getFile()->getHeader().height;
	movie_node->setPosition(-width/2.0f, height/2.0f, -500);

	movie->enableDebugger(true);

	ogre_root->startRendering();

	movie_node->detachAllObjects();

	delete vtx::Root::getSingletonPtr();

	//OIS
	inputManager->destroyInputObject(mouse); mouse = 0;
	inputManager->destroyInputObject(keyboard); keyboard = 0;
	OIS::InputManager::destroyInputSystem(inputManager); inputManager = 0;
	//listeners
	delete frameListener; 
	delete mouseListener; 
	delete keyListener;
	//Ogre
	delete ogre_root;

	return 0;
}

//int main(int argc, char* argv[])
//{
//	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	//_CrtSetBreakAlloc(4961);
//
//	vtxDemoApplication app;
//
//	// start vektrix
//	new vtx::Root();
//
//	try
//	{
//		app.go();
//	}
//	catch(Ogre::Exception& e)
//	{
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else
//		std::cerr << "An exception has occured: " <<
//			e.getFullDescription().c_str() << std::endl;
//#endif
//	}
//
//	delete vtx::Root::getSingletonPtr();
//
//	return 0;
//}

