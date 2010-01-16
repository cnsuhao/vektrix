// uncomment this if you want to statically link to vektrix
//#define VTX_STATIC_LIB
#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxMovie.h"
#include "vtxMovieDebugger.h"
#include "vtxRoot.h"

#include "vtxopMovableMovie.h"

// vektrix plugins
#include "vtxas3Plugin.h"
#include "vtxcaiPlugin.h"
#include "vtxopPlugin.h"
#include "vtxswfPlugin.h"
#include "vtxxmlPlugin.h"

#include "Ogre.h"
#include "OgreFrameListener.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

vtx::ogre::MovableMovie* movie = NULL;
Ogre::SceneNode* movie_node = NULL;
Ogre::RenderWindow* mWindow = NULL;

//-----------------------------------------------------------------------
class SimpleFrameListener : public Ogre::FrameListener 
{
public: 
	SimpleFrameListener(OIS::Keyboard* keyboard, OIS::Mouse* mouse) 
	{ 
		mKeyboard = keyboard; 
		mMouse = mouse; 
	} 

	bool frameStarted(const Ogre::FrameEvent& evt) 
	{
		mKeyboard->capture();
		mMouse->capture();

		vtx::Root::getSingletonPtr()->update(evt.timeSinceLastFrame);

		if(mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q)) 
			return false; 

		return true; 
	} 

	bool frameEnded(const Ogre::FrameEvent& evt) 
	{ 
		return true; 
	} 
private: 
	OIS::Keyboard* mKeyboard; 
	OIS::Mouse* mMouse; 
}; 
//-----------------------------------------------------------------------
class SimpleKeyListener : public OIS::KeyListener 
{
public: 
	bool keyPressed(const OIS::KeyEvent& e)
	{
		return true;
	}

	bool keyReleased(const OIS::KeyEvent& e)
	{
		if(e.key == OIS::KC_F1 && movie)
		{
			vtx::MovieDebugger* dbg = movie->getDebugger();
			if(dbg)
			{
				// toggle boundingbox debugging visuals
				dbg->debugBoundingBoxes(!dbg->debuggingObjectBoundingBoxes());
			}
		}

		return true;
	}
};
//-----------------------------------------------------------------------
class SimpleMouseListener : public OIS::MouseListener
{
public: 
	bool mouseMoved(const OIS::MouseEvent& e)
	{
		if(movie)
		{
			movie->setMouseRel(e.state.X.abs/(float)mWindow->getWidth(), e.state.Y.abs/(float)mWindow->getHeight());
		}

		return true;
	}

	bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		if(movie)
		{
			movie->mouseDown();
		}

		return true;
	}

	bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
	{
		if(movie)
		{
			movie->mouseUp();
		}

		return true;
	}
};
//-----------------------------------------------------------------------
int main(int argc, char **argv)
{
	//VTX_MEM_DEBUG_ENABLE();
	//VTX_MEM_DEBUG_BREAK(2838);

	// start vektrix
	vtx::Root* vektrix_root = new vtx::Root();

	Ogre::Root* ogre_root = new Ogre::Root("", "ogre.cfg", "Ogre.log");

	// ogre plugins
#if VTX_OS == VTX_WIN32
#	ifdef _DEBUG
		ogre_root->loadPlugin("RenderSystem_Direct3D9_d");
		ogre_root->loadPlugin("RenderSystem_GL_d");
#	else
		ogre_root->loadPlugin("RenderSystem_Direct3D9");
		ogre_root->loadPlugin("RenderSystem_GL");
#	endif
#endif

#if VTX_OS == VTX_LINUX
		ogre_root->loadPlugin("RenderSystem_GL");
#endif

	vtx::LogManager::getSingletonPtr()->logToCout(true);

	vtx::FileManager::getSingletonPtr()->addFileContainer("../demos/Ogre3D/media");

	// vektrix plugins
#if VTX_OS == VTX_WIN32
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
#endif
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);
	VTX_LOAD_PLUGIN(vektrix_XmlPlugin);

	if(!ogre_root->showConfigDialog())
	{
		delete vtx::Root::getSingletonPtr();
		delete ogre_root;
		return false;
	}

	// override floating point mode
	Ogre::RenderSystem* render_system = ogre_root->getRenderSystem();
	if(render_system->getName() == "Direct3D9 Rendering Subsystem")
	{
		render_system->setConfigOption("Floating-point mode", "Consistent");
	}

	mWindow = ogre_root->initialise(true, "vektrix Ogre3D Demo");

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::SceneManager* sceneMgr = ogre_root->createSceneManager(Ogre::ST_GENERIC); 

	Ogre::Camera* camera = sceneMgr->createCamera("MainCamera"); 

	Ogre::Viewport* viewPort = mWindow->addViewport(camera);
	viewPort->setBackgroundColour(Ogre::ColourValue::White);

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	// setup the manager, keyboard and mouse to handle input
	OIS::InputManager* inputManager = OIS::InputManager::createInputSystem(pl);
	OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	OIS::Mouse*	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

	// tell OIS about the window's dimensions
	const OIS::MouseState &ms = mouse->getMouseState();
	ms.width = mWindow->getWidth();
	ms.height = mWindow->getHeight();

	// key events
	SimpleKeyListener* keyListener = new SimpleKeyListener();
	keyboard->setEventCallback(keyListener);

	// mouse events
	SimpleMouseListener* mouseListener = new SimpleMouseListener();
	mouse->setEventCallback(mouseListener);

	// render events
	SimpleFrameListener* frameListener = new SimpleFrameListener(keyboard, mouse);
	ogre_root->addFrameListener(frameListener); 

	// VEKTRIX
	movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "button_test2.swf", "OgreMovableMovie");
	movie->play();

	movie_node = sceneMgr->getRootSceneNode()->createChildSceneNode();
	movie_node->attachObject(movie);
	int width = movie->getFile()->getHeader().width;
	int height = movie->getFile()->getHeader().height;
	movie_node->setPosition(-width/2.0f, height/2.0f, -500);

	movie->enableDebugger(true);

	// start the ogre rendering
	ogre_root->startRendering();

	// shutdown
	movie_node->detachAllObjects();

	delete vtx::Root::getSingletonPtr();

	// OIS
	inputManager->destroyInputObject(mouse); mouse = 0;
	inputManager->destroyInputObject(keyboard); keyboard = 0;
	OIS::InputManager::destroyInputSystem(inputManager); inputManager = 0;
	// listeners
	delete frameListener;
	delete mouseListener;
	delete keyListener;
	// Ogre
	delete ogre_root;

	return 0;
}
//-----------------------------------------------------------------------
