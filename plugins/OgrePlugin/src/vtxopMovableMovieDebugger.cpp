/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxopMovableMovieDebugger.h"
#include "vtxFile.h"
#include "vtxopMovableMovie.h"

#include "OgreManualObject.h"
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

				int width = mParent->getFile()->getHeader().width;
				int height = mParent->getFile()->getHeader().height;

				mManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
				mManualObject->position(0, 0, 0);
				mManualObject->position(width, 0, 0);
				mManualObject->position(width, -height, 0);
				mManualObject->position(0, -height, 0);
				mManualObject->position(0, 0, 0);
				mManualObject->end();

				const Vector2& mouse_pos = mParent->getMouseAbs();

				mManualObject->begin("BaseWhiteNoLighting");
				mManualObject->position(mouse_pos.x, -mouse_pos.y-10.0, 0.1);
				mManualObject->position(mouse_pos.x+5.0, -mouse_pos.y-8.0, 0.1);
				mManualObject->position(mouse_pos.x, -mouse_pos.y, 0.1);
				mManualObject->end();
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovieDebugger::debugObjectBoundingBox(const BoundingBox& bb)
		{

		}
		//-----------------------------------------------------------------------
	}
}
