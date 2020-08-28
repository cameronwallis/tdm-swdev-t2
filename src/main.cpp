#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <boost/program_options.hpp>

#include "InteractiveHandler.hpp"

int main(int argc, char **argv) {

	namespace po = boost::program_options;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("compression", po::value<int>(), "set compression level")
		("interactive", "Enter interactive terminal")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		std::cout << desc << "\n";
		std::exit(EXIT_SUCCESS);
	}

	if (vm.count("compression")) {
		std::cout << "Compression level was set to " 
	 << vm["compression"].as<int>() << ".\n";
	} else {
		std::cout << "Compression level was not set.\n";
	}

	if (vm.count("interactive")) {
		std::unique_ptr<InteractiveHandler> ih = InteractiveHandler::getNewHandler();

		if (ih == nullptr) {
			std::cerr << "ERROR: Unable to create interactive screen session" << std::endl;
			std::exit(EXIT_FAILURE);
		} else {
			ih->runInteractive();
		}
	}

	return 0;
}