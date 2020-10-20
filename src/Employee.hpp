#pragma once

#include <unordered_map>
#include <pqxx/pqxx>
#include <boost/uuid/uuid.hpp>
#include <memory>
#include "Position.hpp"

namespace id = boost::uuids;

class Position;

class Employee {

private:
    id::uuid ID;
    std::string firstName;
    std::string lastName;
    std::string nationalInsurance;
    id::uuid positionID;
    std::unique_ptr<Position> position;
    int startDate;


public:
    Employee() = default;
    Employee(pqxx::row row);

    id::uuid getId();
    std::string getFirstName();
    std::string getLastName();
    std::string getFullName();
    std::string getNI();
    int getStartDate();
    std::string formatStartDate();

    void fetchPositionDetails(std::shared_ptr<pqxx::connection> c);

    void updateEmployee(pqxx::connection c, std::unordered_map<std::string, std::string> updates);

    int getSalary();
    int getLeave();

};