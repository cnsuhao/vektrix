#include "vtxLogManager.h"
#include "vtxStringHelper.h"

#include "vtxtestsUnitTestHost.h"
#include "vtxtestsUnitTestList.h"

#include <conio.h>

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
	{
		std::cout << "You haven't provided a test name as first parameter, choose a test manually..." << std::endl;

		for(int i=0; i<STR_TEST_LIST_LEN; ++i)
			std::cout << "[" << i << "] " << STR_TEST_LIST[i] << std::endl;

		std::string choice;
		std::getline(std::cin, choice);
		int choice_int = vtx::StringHelper::toInt(choice);

		if(choice_int < 0 || choice_int >= STR_TEST_LIST_LEN)
		{
			std::cout << "You have chosen an invalid test index !" << std::endl;
			getch();
		}
		else
			RUN_TEST_FROM_STRING(host, vtx::String(STR_TEST_LIST[choice_int]));
	}
}
