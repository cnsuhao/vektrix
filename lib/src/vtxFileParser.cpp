#include "vtxFileParser.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	FileParser::FileParser()
	{
		it = mErrors.begin();
		end = mErrors.end();
	}
	//-----------------------------------------------------------------------
	FileParser::~FileParser()
	{

	}
	//-----------------------------------------------------------------------
	String FileParser::getError()
	{
		if(it == end)
		{
			return "";
		}

		return *it++;
	}
	//-----------------------------------------------------------------------
	void FileParser::error(const String& error)
	{
		mErrors.push_back(error);

		it = mErrors.begin();
		end = mErrors.end();
	}
	//-----------------------------------------------------------------------
}
