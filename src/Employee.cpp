#include "Employee.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>
#include <ctime>

namespace id = boost::uuids;

Employee::Employee(pqxx::row row) {
    this->ID = boost::lexical_cast<id::uuid>(row["employee_id"].c_str());
    this->firstName = row["firstName"].c_str();
    this->lastName = row["lastName"].c_str();
    this->nationalInsurance = row["nationalInsurance"].c_str();
    this->startDate = boost::lexical_cast<int>(row["startDate"].c_str());
    this->positionID = boost::lexical_cast<id::uuid>(row["positionID"].c_str());
}


id::uuid Employee::getId() {
    return this->ID;
}

std::string Employee::getFirstName() {
    return this->firstName;
}

std::string Employee::getLastName() {
    return this->lastName;
}

std::string Employee::getFullName() {
    return this->firstName + " " + this->lastName;
}

std::string Employee::getNI() {
    return this->nationalInsurance;
}

int Employee::getStartDate() {
    return this->startDate;
}

void Employee::fetchPositionDetails(std::shared_ptr<pqxx::connection> c) {

    // Check that the employee was actaully initialised before sending rubbish to the databse
    if (this->positionID.is_nil()) {
        throw new std::runtime_error("No positionID found in class - make sure Employee is initialised");
    }

    std::string fetchCmd = "SELECT * FROM positions WHERE position_id = '" + boost::lexical_cast<std::string>(this->positionID) + "'";

    pqxx::work txn(*c);
    pqxx::row r(txn.exec1(fetchCmd));

    Position p(r);
    this->position = std::make_unique<Position>(p);
}

void Employee::updateEmployee(pqxx::connection c, std::unordered_map<std::string, std::string> updates) {

    std::string updCmd = "UPDATE employees ";

    // loop over every update in the map and add them to the SQL command
    for (auto const& update : updates) {
        if (update.first == "firstName" || update.first == "lastName" || update.first == "nationalInsurance" || update.first == "startDate") {
            updCmd += "SET " + update.first + " = '" + update.second + "', ";
        } else {
            continue;
        }
    }

    // Finish the SQL command
    updCmd += "WHERE employee_id = '" + boost::lexical_cast<std::string>(this->ID) + "'";

    pqxx::work txn(c);
    txn.exec0(updCmd);
    txn.commit();
}

int Employee::getSalary() {
    // Check that fetchPositionData() has already been reun
    if (this->positionID != this->position->ID) {
        throw new std::runtime_error("Position object has not been initialised");
    }

    return this->position->salary;
}

int Employee::getLeave() {
    // Check that fetchPositionData() has already been reun
    if (this->positionID != this->position->ID) {
        throw new std::runtime_error("Position object has not been initialised");
    }

    time_t currentTime = std::time(nullptr);
    struct tm* now = std::localtime(&currentTime);
    // Fix bug that causes now->tm_year to change after start is allocated
    int nowYear = now->tm_year;
    time_t startDate = static_cast<time_t>(this->startDate);
    struct tm* start = std::localtime(&startDate);

    int totalYears = (nowYear) - (start->tm_year);

    int additionalDays = static_cast<int>(static_cast<float>(totalYears) * this->position->additionalLeavePerYear); 
    return this->position->baseLeave + additionalDays;
}
