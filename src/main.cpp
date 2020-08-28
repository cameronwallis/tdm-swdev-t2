#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <boost/program_options.hpp>
#include <pqxx/pqxx>

#include "InteractiveHandler.hpp"

int main(int argc, char **argv) {

	namespace po = boost::program_options;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("interactive", "Enter interactive terminal")
		("username", po::value<std::string>(), "Username to access the database")
		("password", po::value<std::string>(), "Password to access the database")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		std::cout << desc << "\n";
		std::exit(EXIT_SUCCESS);
	}

	std::shared_ptr<pqxx::connection> conn;
	try {
		conn = std::make_shared<pqxx::connection>("host=localhost port=5434 user=postgres dbname=tdm_test");
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	if (vm.count("interactive")) {
		std::unique_ptr<InteractiveHandler> ih = InteractiveHandler::getNewHandler();

		if (ih == nullptr) {
			std::cerr << "ERROR: Unable to create interactive screen session" << std::endl;
			std::exit(EXIT_FAILURE);
		} else {
			ih->setConnection(conn);
			ih->runInteractive();
		}
	}

	return 0;
}