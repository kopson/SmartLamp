#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <cstdlib>
#include <cstring>
#include <iostream>

static void usage() {
	std::cout << "usage: test [MODE]\n"
		 << "where MODE may be one of:\n"
		 << "  --compiler\n"
		 << "  --html\n"
		 << "  --text-terse (default)\n"
		 << "  --text-verbose\n";
	exit(0);
}

static std::auto_ptr<Test::Output> cmdline(int argc, char* argv[]) {
	if (argc > 2)
		usage(); // will not return
	
	Test::Output* output = 0;
	
	if (argc == 1) {
		output = new Test::TextOutput(Test::TextOutput::Verbose);
	} else {
		const char* arg = argv[1];
		if (strcmp(arg, "--compiler") == 0) {
			output = new Test::CompilerOutput;
		} else if (strcmp(arg, "--html") == 0) {
			output =  new Test::HtmlOutput;
		} else if (strcmp(arg, "--text-terse") == 0) {
			output = new Test::TextOutput(Test::TextOutput::Terse);
		} else if (strcmp(arg, "--text-verbose") == 0) {
			output = new Test::TextOutput(Test::TextOutput::Verbose);
		} else {
			std::cout << "invalid commandline argument: " << arg << std::endl;
			usage(); // will not return
		}
	}
	
	return std::auto_ptr<Test::Output>(output);
}

#endif /* TESTUTILS_H */