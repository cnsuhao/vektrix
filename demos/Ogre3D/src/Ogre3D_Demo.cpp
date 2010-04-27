#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxMovie.h"
#include "vtxMovieDebugger.h"
#include "vtxRoot.h"

#include "vtxopMovableMovie.h"

// vektrix plugins
#include "vtxas3Plugin.h"
#include "vtxcaiPlugin.h"
#include "vtxcurlPlugin.h"
#include "vtxd3d9Plugin.h"
#include "vtxfreeimgPlugin.h"
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

		if(movie)
		{
			if(mKeyboard->isKeyDown(OIS::KC_F2))
			{
				movie_node->translate(0, 0, evt.timeSinceLastFrame * 150.0f, Ogre::Node::TS_WORLD);
			}
			if(mKeyboard->isKeyDown(OIS::KC_F3))
			{
				movie_node->translate(0, 0, -evt.timeSinceLastFrame * 150.0f, Ogre::Node::TS_WORLD);
			}

			// TRANSLATE & ROTATE
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				if(mKeyboard->isKeyDown(OIS::KC_LEFT))
				{
					movie_node->yaw(Ogre::Radian(-evt.timeSinceLastFrame), Ogre::Node::TS_WORLD);
				}
				if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
				{
					movie_node->yaw(Ogre::Radian(+evt.timeSinceLastFrame), Ogre::Node::TS_WORLD);
				}
			}
			else
			{
				if(mKeyboard->isKeyDown(OIS::KC_LEFT))
				{
					movie_node->translate(+evt.timeSinceLastFrame * 150.0f, 0, 0, Ogre::Node::TS_WORLD);
				}
				if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
				{
					movie_node->translate(-evt.timeSinceLastFrame * 150.0f, 0, 0, Ogre::Node::TS_WORLD);
				}
				if(mKeyboard->isKeyDown(OIS::KC_UP))
				{
					movie_node->translate(0, -evt.timeSinceLastFrame * 150.0f, 0, Ogre::Node::TS_WORLD);
				}
				if(mKeyboard->isKeyDown(OIS::KC_DOWN))
				{
					movie_node->translate(0, +evt.timeSinceLastFrame * 150.0f, 0, Ogre::Node::TS_WORLD);
				}
			}
		}

		vtx::Root::getSingletonPtr()->update(evt.timeSinceLastFrame);

		if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
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
		if(movie)
		{
			movie->keyDown(e.key, e.text);
		}

		return true;
	}

	bool keyReleased(const OIS::KeyEvent& e)
	{
		if(movie)
		{
			movie->keyUp(e.key, e.text);
		}

		if(e.key == OIS::KC_F1 && movie)
		{
			vtx::MovieDebugger* dbg = movie->getDebugger();
			if(dbg)
			{
				// toggle boundingbox debugging visuals
				dbg->debugBoundingBoxes(!dbg->debuggingBoundingBoxes());
			}
		}
		else if(e.key == OIS::KC_F4)
		{
			std::cout << "Batch count: " << mWindow->getStatistics().batchCount << std::endl;
		}
		else if(e.key == OIS::KC_F5 && movie)
		{
			if(movie->getDebugger())
			{
				movie->enableDebugger(false);
			}
			else
			{
				movie->enableDebugger(true);
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
	VTX_MEM_DEBUG_ENABLE();
	//VTX_MEM_DEBUG_BREAK(6707);

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

	// vektrix plugins
#if VTX_OS == VTX_WIN32
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
	VTX_LOAD_PLUGIN(vektrix_D3D9Plugin);
#endif
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_cURLPlugin);
	VTX_LOAD_PLUGIN(vektrix_FreeImgPlugin);
	VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);
	VTX_LOAD_PLUGIN(vektrix_XmlPlugin);

	vtx::FileManager::getSingletonPtr()->addFileContainer("../demos/media");
	vtx::FileManager::getSingletonPtr()->addFileContainer("", "WebFileContainer");

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
	camera->setAutoAspectRatio(true);
	camera->setNearClipDistance(1);

	Ogre::Viewport* viewPort = mWindow->addViewport(camera);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.2f, 0.2f, 0.2f, 0.2f));
	//viewPort->setBackgroundColour(Ogre::ColourValue::White);

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
	//movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "http://fuse-software.com/vektrix/dyn_text_web.swf", "OgreMovableMovie");
	movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "dyn_text.swf", "OgreMovableMovie");
	//movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "cpp_test.swf", "OgreMovableMovie");
	//movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "video_test.swf", "OgreMovableMovie");
	movie->play();

	movie_node = sceneMgr->getRootSceneNode()->createChildSceneNode();
	movie_node->attachObject(movie);

	movie->enableDebugger(true);

	if(!mWindow->isFullScreen())
	{
		mWindow->resize(movie->getFile()->getHeader().width * 2, movie->getFile()->getHeader().height * 2);
	}

	ms.width = mWindow->getWidth();
	ms.height = mWindow->getHeight();

	int width = movie->getFile()->getHeader().width;
	int height = movie->getFile()->getHeader().height;

	float movie_ratio = (float)width/height;
	float window_ratio = viewPort->getCamera()->getAspectRatio();
	if(movie_ratio > window_ratio)
	{
		// zoom to width
		movie_node->setPosition(-width/2.0f, height/2.0f, 
			-(float)width*0.5f/window_ratio/tanf(viewPort->getCamera()->getFOVy().valueRadians()*0.5f));
	}
	else
	{
		// zoom to height
		movie_node->setPosition(-width/2.0f, height/2.0f, 
			-(float)height*0.5f/tanf(camera->getFOVy().valueRadians()*0.5f));
	}

	// start the ogre rendering
	ogre_root->startRendering();

	// shutdown
	movie_node->detachAllObjects();

	delete vtx::Root::getSingletonPtr();

	// OIS
	inputManager->destroyInputObject(mouse);mouse = 0;
	inputManager->destroyInputObject(keyboard);keyboard = 0;
	OIS::InputManager::destroyInputSystem(inputManager);inputManager = 0;
	// listeners
	delete frameListener;
	delete mouseListener;
	delete keyListener;
	// Ogre
	delete ogre_root;

	return 0;
}
//-----------------------------------------------------------------------
