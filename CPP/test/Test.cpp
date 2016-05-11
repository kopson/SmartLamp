#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../lib/inc/cpptest.h"
#include "inc/RationalTestSuite.h"
#include "inc/MatrixTestSuite.h"
#include "inc/TestUtils.h"

using namespace std;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// Main test program
int __attribute__((deprecated)) main(int argc, char* argv[]) {
	try {
		Test::Suite ts;
		ts.add(auto_ptr<Test::Suite>(new RationalTestSuite));
		ts.add(auto_ptr<Test::Suite>(new MatrixTestSuite));

		// Run the tests
		auto_ptr<Test::Output> output(cmdline(argc, argv));
		ts.run(*output, true);

		Test::HtmlOutput* const html = dynamic_cast<Test::HtmlOutput*>(output.get());
		if (html) {
			html->generate(cout, true, "Test");
		}
	} catch (...) {
		cout << "unexpected exception encountered\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

#pragma GCC diagnostic pop