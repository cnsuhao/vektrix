#include "vtxswfParser2.h"

#include "vtxKeyframe.h"
#include "vtxTimeline.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void SwfParser2::handleShowFrame()
		{
			if(!mCurrentMovieClip)
			{
				++mMainFrameIndex;

				if(mCurrentKeyframe->getEventCount())
				{
					mCurrentKeyframe->setIndex(mMainFrameIndex);
					mTimeline->addKeyframe(mCurrentKeyframe);
					mCurrentKeyframe = NULL;

					if(mMainFrameIndex < mHeader.frames)
					{
						mCurrentKeyframe = new Keyframe;
					}
				}
			}
		}
		//-----------------------------------------------------------------------
	}
}
