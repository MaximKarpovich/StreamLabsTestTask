#include <iostream>
#include "obs.h"
#include "util/profiler.h"


int main()
{
	auto version = obs_get_version_string();
	std::cout << "Version: " << version << std::endl;

	auto store = profiler_name_store_create();
	auto result = obs_startup("en-US", NULL, store);
	auto inited = obs_initialized();

	std::cout << "Result = " << result << std::endl;
	std::cout << "Inited = " << inited << std::endl;
	
	return 0;
}