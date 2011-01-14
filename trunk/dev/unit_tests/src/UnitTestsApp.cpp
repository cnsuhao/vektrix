#include "vtxLogManager.h"

#include "vtxtestsUnitTestHost.h"
#include "vtxtestsUnitTestList.h"

using namespace vtx::tests;

int main(int argc, char** argv)
{
	UnitTestHost host;

	if(argc > 1)
	{
		const vtx::String test_name = argv[1];
		RUN_TEST_FROM_STRING(host, test_name);
	}
	else
		VTX_EXCEPT("Too few arguments, provide a test name as first parameter...");

	delete vtx::LogManager::getSingletonPtr();
}
