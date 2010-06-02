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

#include "vtxopMovableMovieDebugger.h"

#include "vtxBoundingBox.h"
#include "vtxFile.h"
#include "vtxopMovableMovie.h"

#include "OgreManualObject.h"
#include "OgreMaterialManager.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableMovieDebugger::MovableMovieDebugger(Movie* parent) 
			: MovieDebugger(parent), 
			mManualObject(NULL), 
			mNode(NULL)
		{
			mRedMaterial = Ogre::MaterialManager::getSingleton().create("vtxRedDebugMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			Ogre::Pass* pass = mRedMaterial->getTechnique(0)->getPass(0);
			pass->setSelfIllumination(Ogre::ColourValue::Red);
			pass->setAmbient(Ogre::ColourValue::Red);
			pass->setSpecular(Ogre::ColourValue::Red);
			pass->setDiffuse(Ogre::ColourValue::Red);

			mGreenMaterial = Ogre::MaterialManager::getSingleton().create("vtxGreenDebugMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			pass = mGreenMaterial->getTechnique(0)->getPass(0);
			pass->setSelfIllumination(Ogre::ColourValue::Green);
			pass->setAmbient(Ogre::ColourValue::Green);
			pass->setSpecular(Ogre::ColourValue::Green);
			pass->setDiffuse(Ogre::ColourValue::Green);

			mBlueMaterial = Ogre::MaterialManager::getSingleton().create("vtxBlueDebugMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			pass = mBlueMaterial->getTechnique(0)->getPass(0);
			pass->setSelfIllumination(Ogre::ColourValue::Blue);
			pass->setAmbient(Ogre::ColourValue::Blue);
			pass->setSpecular(Ogre::ColourValue::Blue);
			pass->setDiffuse(Ogre::ColourValue::Blue);

			mBckgrContrastClrMaterial = Ogre::MaterialManager::getSingleton().create("vtxBckgrContrastClrMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			const Color& bckgr_clr = mParent->getFile()->getHeader().bgcolor;
			Ogre::ColourValue clr(
				1.0f-bckgr_clr.r, 
				1.0f-bckgr_clr.g, 
				1.0f-bckgr_clr.b, 
				1.0f-bckgr_clr.a);

			pass = mBckgrContrastClrMaterial->getTechnique(0)->getPass(0);
			pass->setSelfIllumination(clr);
			pass->setAmbient(clr);
			pass->setSpecular(clr);
			pass->setDiffuse(clr);

			MovableMovie* movie = dynamic_cast<MovableMovie*>(mParent);
			if(movie)
			{
				mNode = movie->getParentSceneNode();

				if(mNode)
				{
					Ogre::SceneManager* mgr = mNode->getCreator();
					mManualObject = mgr->createManualObject("vtx_" + mParent->getName() + "_Debugger");
					mNode->attachObject(mManualObject);
				}
			}
		}
		//-----------------------------------------------------------------------
		MovableMovieDebugger::~MovableMovieDebugger()
		{
			if(mNode)
			{
				Ogre::SceneManager* mgr = mNode->getCreator();
				mNode->detachObject(mManualObject);
				mgr->destroyManualObject(mManualObject);
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovieDebugger::preDebug()
		{
			if(mManualObject)
			{
				// clear previous input
				mManualObject->clear();

				Ogre::Real width = (Ogre::Real)mParent->getFile()->getHeader().width;
				Ogre::Real height = (Ogre::Real)mParent->getFile()->getHeader().height;

				mManualObject->begin(mRedMaterial->getName(), Ogre::RenderOperation::OT_LINE_STRIP);
				mManualObject->position(0, 0, 0);
				mManualObject->position(width, 0, 0);
				mManualObject->position(width, -height, 0);
				mManualObject->position(0, -height, 0);
				mManualObject->position(0, 0, 0);
				mManualObject->end();

				const Vector2& mouse_pos = mParent->getMouseAbs();

				mManualObject->begin(mRedMaterial->getName());
				mManualObject->position(mouse_pos.x, -mouse_pos.y-10.0f, 0.1f);
				mManualObject->position(mouse_pos.x+5.0f, -mouse_pos.y-8.0f, 0.1f);
				mManualObject->position(mouse_pos.x, -mouse_pos.y, 0.1f);
				mManualObject->end();
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovieDebugger::drawBoundingBox(const BoundingBox& bb)
		{
			if(mManualObject)
			{
				mManualObject->begin(mGreenMaterial->getName(), Ogre::RenderOperation::OT_LINE_STRIP);

				mManualObject->position(bb.getMinX(), -bb.getMinY(), 0.1f);
				mManualObject->position(bb.getMaxX(), -bb.getMinY(), 0.1f);
				mManualObject->position(bb.getMaxX(), -bb.getMaxY(), 0.1f);
				mManualObject->position(bb.getMinX(), -bb.getMaxY(), 0.1f);
				mManualObject->position(bb.getMinX(), -bb.getMinY(), 0.1f);

				mManualObject->end();
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovieDebugger::startDebugLine()
		{
			if(mManualObject)
			{
				mManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovieDebugger::debugLine(const Vector2& point)
		{
			mManualObject->position(point.x, -point.y, 1);
		}
		//-----------------------------------------------------------------------
		void MovableMovieDebugger::endDebugLine()
		{
			if(mManualObject)
			{
				mManualObject->end();
			}
		}
		//-----------------------------------------------------------------------
	}
}
