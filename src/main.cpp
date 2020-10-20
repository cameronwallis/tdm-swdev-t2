#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <boost/program_options.hpp>
#include <pqxx/pqxx>

#include "Performance.hpp"
#include "Employee.hpp"
#include "InteractiveHandler.hpp"

// TODO: 

int main(int argc, char **argv) {

	namespace po = boost::program_options;

	// Create the command line options object
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("interactive", "Enter interactive terminal")
		("fetch", po::value<std::string>(),"Get an employee based on their ID")
		("search", po::value<std::string>(), "Search for an employee by name")
		("insensitive", "Make search case insensitive")
	;

	// Parse options
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		std::cout << desc << "\n";
		std::exit(EXIT_SUCCESS);
	}

	std::string id = "";
	if (vm.count("fetch")) {
		id = vm["fetch"].as<std::string>();
	}

	std::string fragment = "";
	if (vm.count("search")) {
		fragment = vm["search"].as<std::string>();
	}

	// Attempt to connecto to the database - currently uses a fixed connection string with no credentials
	std::shared_ptr<pqxx::connection> conn;
	try {
		conn = std::make_shared<pqxx::connection>("host=localhost port=5434 user=postgres dbname=tdm_test");
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	pqxx::row r;

	// Choose action based on options
	// If user requested a fetch or search 
	if (!id.empty()) {
		std::string fetchMe = "SELECT * FROM employees WHERE employee_id = '" + id + "'";
		pqxx::work txn(*conn);

		r = txn.exec1(fetchMe);
		txn.commit();
	} else if (!fragment.empty()) {
		std::string fetchResults;

		// Alter search if case insensitive option was selected
		if (vm.count("insensitive")) {
			fetchResults = "SELECT * FROM employees WHERE firstname ILIKE '%" + fragment + "%' OR lastname ILIKE '%" + fragment + "%'";
		} else {
			fetchResults = "SELECT * FROM employees WHERE firstname LIKE '%" + fragment + "%' OR lastname LIKE '%" + fragment + "%'";
		}

		// Execute the search
		pqxx::work txn(*conn);
		pqxx::result res = txn.exec(fetchResults);

		// If the search returned multiple records then ask the user to choose one
		// else use the returned record. If no records are returned exit
		if (res.size() == 0) {
			std::cout << "Search returned no users" << std::endl;
			std::exit(EXIT_SUCCESS);
		} else if (res.size() == 1){
			r = res[0];
		} else {
			std::cout << "Search returned multiple users, please select one:" << std::endl;
			for (int i = 0; i < res.size(); ++i) {
				std::cout << i + 1 << ") " << res[i]["firstname"] << " " << res[i]["lastname"] << ", " << res[i]["nationalinsurance"] << std::endl; 
			}
			std::cout << std::endl;
			std:: cout << ">>>";

			std::string input;
			std::cin >> input;

			int index;

			try {
				index = boost::lexical_cast<int>(input);
			} catch (const boost::bad_lexical_cast &e) {
				std::cerr << "Error: Unable to interpret input!" << std::endl;
				std::cerr << "Details: " << e.what() << std::endl;
				std::exit(EXIT_FAILURE);
			}

			if (index <= 0 || index > res.size()) {
				std::cerr << "Error: Please select one of the listed options" << std::endl;
				std::exit(EXIT_FAILURE);
			}

			r = res[index - 1];
		}
	}

	// Construct the employee object
	Employee cameron(r);
	cameron.fetchPositionDetails(conn);

	// Construct the employee object from the retrieved data
	std::string fetchRecentPerf = "SELECT * FROM performance WHERE year = (SELECT MAX(year) FROM performance)";
	pqxx::work txn(*conn);

	// Fetch company performace data from the database for bonus calculations
	pqxx::row perf = txn.exec1(fetchRecentPerf);
	Performance recentPerf(perf);

	// Output calculations
	std::cout << "FULL NAME: " + cameron.getFullName() << std::endl;
	std::cout << "SALARY: " << cameron.getSalary() << std::endl;
	std::cout << "SALARY PER MONTH: " << (static_cast<float>(cameron.getSalary()) / 12.0f) << std::endl; 
	std::cout << "LEAVE: " << cameron.getLeave() << std::endl;

	std::cout << "BONUS: " << recentPerf.calculateBonus(cameron.getSalary()) << std::endl;

	return 0;
}