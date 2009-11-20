#pragma once

#include "vtxFileManager.h"
#include "vtxMovie.h"
#include "vtxRoot.h"

#include "vtxopMovableMovie.h"

#include "ExampleApplication.h"

vtx::ogre::MovableMovie* movie;
SceneNode* movie_node = NULL;

class vtxDemoFrameListener : public ExampleFrameListener
{
public:
	vtxDemoFrameListener(RenderWindow* win, Camera* cam) : ExampleFrameListener(win, cam)
	{

	}

	bool frameStarted(const FrameEvent& evt)
	{
		if(ExampleFrameListener::frameStarted(evt) == false)
		{
			return false;
		}

		mWindow->setActive(true);

		if(mKeyboard->isKeyDown(OIS::KC_1))
		{
			movie_node->yaw(Degree(evt.timeSinceLastFrame * 50.0f));
		}
		else if(mKeyboard->isKeyDown(OIS::KC_2))
		{
			movie_node->pitch(Degree(evt.timeSinceLastFrame * 50.0f));
		}
		else if(mKeyboard->isKeyDown(OIS::KC_3))
		{
			movie_node->roll(Degree(evt.timeSinceLastFrame * 50.0f));
		}

		const OIS::MouseState& state = mMouse->getMouseState();

		movie->setMouseAbs(state.X.abs, state.Y.abs);

		vtx::Root::getSingletonPtr()->update(evt.timeSinceLastFrame);

		return true;
	}
};

class vtxDemoApplication : public ExampleApplication
{
public:
	vtxDemoApplication() {}

protected:
	virtual void createFrameListener(void)
	{
		mFrameListener = new vtxDemoFrameListener(mWindow, mCamera);
		mRoot->addFrameListener(mFrameListener);
	}

	void createScene(void)
	{
		mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

		mCamera->getViewport()->setBackgroundColour(ColourValue(0.2, 0.2, 0.2));

		vtx::Root* root = vtx::Root::getSingletonPtr();
		vtx::LogManager::getSingletonPtr()->logToCout(true);

		vtx::FileManager::getSingletonPtr()->addFileContainer("../demos/Ogre3D/media");
		//vtx::FileManager::getSingletonPtr()->addFileContainer("../../../Media/vektrix");

#ifdef _DEBUG
		root->loadPlugin("vektrix_SwfPlugin_d");
		//root->loadPlugin("vektrix_XmlPlugin_d");
		root->loadPlugin("vektrix_OgrePlugin_d");
#else
		root->loadPlugin("vektrix_SwfPlugin");
		//root->loadPlugin("vektrix_XmlPlugin");
		root->loadPlugin("vektrix_OgrePlugin");
#endif

		movie = (vtx::ogre::MovableMovie*)root->createMovie("swf_movie", "button.swf", "OgreMovableMovie");
		movie->play();

		movie_node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		movie_node->attachObject(movie);
		movie_node->setPosition(0, 0, -100);
	}

	void destroyScene()
	{
		movie_node->detachAllObjects();
	}
};
