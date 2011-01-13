#include "vtxFile.h"
#include "vtxFileManager.h"
#include "vtxMovie.h"
#include "vtxMovieDebugger.h"
#include "vtxRoot.h"
#include "vtxScriptCallbackListener.h"
#include "vtxScriptEngine.h"

#include "vtxopMovableMovie.h"

// vektrix plugins
#ifdef VTX_STATIC_LIB
#	include "vtxas3Plugin.h"
#	include "vtxcaiPlugin.h"
#	include "vtxcurlPlugin.h"
#	include "vtxfreeimgPlugin.h"
#	include "vtxopPlugin.h"
#	include "vtxswfPlugin.h"
#endif

#include "Ogre.h"
#include "OgreFrameListener.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#ifdef WIN32
#	define MEDIA_PATH vtx::String("../../demos/media")
#else
#	define MEDIA_PATH vtx::String("../demos/media")
#endif

vtx::ogre::MovableMovie* movie = NULL;
Ogre::Camera* camera = NULL;
Ogre::SceneNode* movie_node = NULL;
Ogre::RenderWindow* mWindow = NULL;
OIS::Mouse*	mouse = NULL;

//-----------------------------------------------------------------------
class MovieListener : public vtx::Movie::Listener, public vtx::ScriptCallbackListener
{
public:
	vtx::ScriptParam scriptCallback(const vtx::String& callback_name, const vtx::ScriptParamList& args)
	{
		if(callback_name == "returnValuesToCpp")
		{
			std::cout << callback_name << 
				"(" << 
				(args[0].boolValue() ? "true":"false") << ", " << 
				args[1].intValue() << ", " << 
				args[2].intValue() << ", " << 
				args[3].doubleValue() << ", " << 
				args[4].StringValue() << 
				");" << std::endl;
		}

		return __TIMESTAMP__;
	}

	bool loadingCompleted(vtx::Movie* movie)
	{
		movie->getScriptEngine()->setCallbackListener(&movie_listener);

		//movie_node->attachObject(static_cast<vtx::ogre::MovableMovie*>(movie));
		movie->enableDebugger(true);
		movie->getDebugger()->debugBoundingBoxes(true);

		int width = movie->getFile()->getHeader().width;
		int height = movie->getFile()->getHeader().height;

		if(!mWindow->isFullScreen())
		{
			mWindow->resize(width, height);
		}

		const OIS::MouseState& ms = mouse->getMouseState();
		ms.width = mWindow->getWidth();
		ms.height = mWindow->getHeight();

		float movie_ratio = (float)width/height;
		float window_ratio = camera->getAspectRatio();
		if(movie_ratio > window_ratio)
		{
			// zoom to width
			movie_node->setPosition(-width/2.0f, height/2.0f, 
				-(float)width*0.5f/window_ratio/tanf(camera->getFOVy().valueRadians()*0.5f));
		}
		else
		{
			// zoom to height
			movie_node->setPosition(-width/2.0f, height/2.0f, 
				-(float)height*0.5f/tanf(camera->getFOVy().valueRadians()*0.5f));
		}

		return false;
	}

	bool loadingFailed(vtx::Movie* movie)
	{
		std::cout << "loading of the movie failed !!!" << std::endl;
		return true;
	}
} movie_listener;
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
			else if(mKeyboard->isKeyDown(OIS::KC_LCONTROL))
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

		//VTX_LOG("upd");
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
		else if(e.key == OIS::KC_F8 && movie)
		{
			vtx::ScriptParamList args;
			args.push_back(true);
			args.push_back(12345);
			args.push_back(67890);
			args.push_back(54.321);
			args.push_back("hello world!");
			vtx::ScriptParam result = movie->getScriptEngine()->callScriptFunction("setValuesFromCpp", args);
			std::cout << "return value from AS3: " << result.StringValue() << std::endl;
		}

		return true;
	}

	void loadingCompleted(vtx::File* file)
	{
		std::cout << "loading of file: " << file->getFilename() << " completed...." << std::endl;
	}
};
//-----------------------------------------------------------------------
class SimpleMouseListener : public OIS::MouseListener
{
public: 
	bool mouseMoved(const OIS::MouseEvent& e)
	{
		//VTX_LOG("Mouse moved...");
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
	//VTX_MEM_DEBUG_BREAK(4149);

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
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_cURLPlugin);
	VTX_LOAD_PLUGIN(vektrix_FreeImgPlugin);
	VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

	vtx::FileManager::getSingletonPtr()->addFileContainer(MEDIA_PATH);
	vtx::FileManager::getSingletonPtr()->addFileContainer("");
	vtx::FileManager::getSingletonPtr()->addFileContainer("C:/Users/stone/Desktop/vtx_flash_test");
	vtx::FileManager::getSingletonPtr()->addFileContainer("", "WebFileContainer");

	//VTX_LOAD_PLUGIN(vektrix_EditorPlugin);

	if(!ogre_root->restoreConfig())
	{
		if(!ogre_root->showConfigDialog())
		{
			delete vtx::Root::getSingletonPtr();
			delete ogre_root;
			return false;
		}
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

	camera = sceneMgr->createCamera("MainCamera");
	camera->setAutoAspectRatio(true);
	camera->setNearClipDistance(1);

	Ogre::Viewport* viewPort = mWindow->addViewport(camera);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
	//viewPort->setBackgroundColour(Ogre::ColourValue::White);

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	// setup the manager, keyboard and mouse to handle input
	OIS::InputManager* inputManager = OIS::InputManager::createInputSystem(pl);
	OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

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

	vtx::StringList movies;
	movies.push_back("http://fuse-software.com/vektrix/dyn_text_web.swf");
	movies.push_back("lorem_ipsum2.swf");
	movies.push_back("dyn_text.swf");
	movies.push_back("as3_textfield.swf");
	movies.push_back("cpp_test.swf");
	movies.push_back("video_test.swf");
	movies.push_back("button_test2.swf");

	std::cout << "loadable movies:" << std::endl;
	for(vtx::uint i=0; i<movies.size(); ++i)
	{
		std::cout << "(" << i << ") " << movies.at(i) << std::endl;
	}

	// VEKTRIX
	//char opt = getch();
	//movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", movies.at(atoi(&opt)), "OgreMovableMovie");

	//MovieListener listener(mouse);

	movie_node = sceneMgr->getRootSceneNode()->createChildSceneNode();
	//movie = (vtx::ogre::MovableMovie*)vektrix_root->createMovie("swf_movie", "dyn_text.swf", "OgreMovableMovie", &listener);
	//movie->play();

	//movie = (vtx::ogre::MovableMovie*)vtx::Root::getSingletonPtr()->createMovie("editor_movie", "vtx.ed.Editor", "OgreMovableMovie", &movie_listener);
	movie = (vtx::ogre::MovableMovie*)vtx::Root::getSingletonPtr()->createMovie("swf_movie", "flash_external.swf", "OgreMovableMovie", &movie_listener);
	movie->play();

	movie_node->attachObject(movie);

	//movie_node->setPosition(0, 0, -500);

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
