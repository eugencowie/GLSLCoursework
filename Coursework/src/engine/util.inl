#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>

using namespace std;

namespace util
{
	inline void panic(const string& message, const string& details = "")
	{
		// Print error message to console
		cerr << message << endl << details << endl;

		// Attempt to trigger debugger
		assert(false);

		// Exit indicating failure
		exit(EXIT_FAILURE);
	}
}
