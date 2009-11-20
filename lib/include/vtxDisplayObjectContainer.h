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
#ifndef __vtxDisplayObjectContainer_H__
#define __vtxDisplayObjectContainer_H__

#include "vtxPrerequesites.h"
#include "vtxInteractiveObject.h"

namespace vtx
{
	class vtxExport DisplayObjectContainer : public InteractiveObject
	{
	public:
		typedef std::map<uint, MovableObject*> Layers;

		DisplayObjectContainer(Resource* resource);
		virtual ~DisplayObjectContainer();

		void addChild(MovableObject* object);
		bool addChildAt(MovableObject* object, uint layer);
		MovableObject* getChildAt(uint layer);
		bool removeChildAt(uint layer);
		void clearLayers();

		virtual void _update(const float& delta_time = 0.0f);

	protected:
		Layers mLayers;
	};
}

#endif
