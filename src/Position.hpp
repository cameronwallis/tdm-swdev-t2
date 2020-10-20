#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <pqxx/pqxx>

#include "Employee.hpp"

namespace id = boost::uuids;

class Employee;

class Position {

private:
    id::uuid ID;
    std::string title;
    int salary;
    int baseLeave;
    float additionalLeavePerYear;
    int employeePensionContributionPercent;
    int employerPensionContributionPercent;


public:
    Position() = default;
    Position(pqxx::row row);
    virtual ~Position() = default;
    friend class Employee;
};