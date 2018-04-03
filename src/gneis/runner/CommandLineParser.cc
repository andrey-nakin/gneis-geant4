#include <memory.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "gneis/runner/CommandLineParser.hh"

gneis::runner::CommandLineParser::CommandLineParser(int argc_, char* argv_[],
		bool const silent) :
		returnCode(0), randomSeed(0), fileSuffix(""), parsedArgc(0), parsedArgv(
				nullptr) {
	Parse(argc_, argv_, silent);
}

gneis::runner::CommandLineParser::CommandLineParser(
		CommandLineParser const & src) :
		returnCode(src.returnCode), randomSeed(src.randomSeed), fileSuffix(
				src.fileSuffix), parsedArgc(src.parsedArgc), parsedArgv(
				Dup(src.parsedArgc, src.parsedArgv)) {

}

gneis::runner::CommandLineParser::~CommandLineParser() {
	delete parsedArgv;
}

void gneis::runner::CommandLineParser::Parse(int argc, char* argv[],
		bool const silent) {

	int res;

	if (silent) {
		::opterr = 0;
	}

	::optind = 1;	//	reset getopt
	while ((res = ::getopt(argc, argv, "r:s:h?")) != -1) {
		switch (res) {
		case 'r':
			randomSeed = std::stol(::optarg);
			break;

		case 's':
			fileSuffix = ::optarg;
			break;

		case 'h':
		case '?':
			if (!silent) {
				std::cerr << "Usage: [options] <script file>\n"
						"Options:\n"
						"\t-r <integer>\trandom generator seed number\n"
						"\t-s <any>\tsuffix in output files' names\n"
						"";
			}
			returnCode = 1;
			break;
		}
	}

	parsedArgc = argc - optind + 1;
	parsedArgv = new char*[parsedArgc];
	parsedArgv[0] = argv[0];
	for (int i = 1; i < parsedArgc; i++) {
		parsedArgv[i] = argv[i + optind - 1];
	}
}

char** gneis::runner::CommandLineParser::Dup(int const argc, char** const argv) {
	char** const result = new char*[argc];
	::memcpy(result, argv, argc * sizeof(result[0]));
	return result;
}