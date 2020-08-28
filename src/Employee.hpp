#pragma once

#include <pqxx/pqxx>
#include <boost/uuid/uuid.hpp>

namespace id = boost::uuids;

class Employee {

private:
    id::uuid ID;
    std::string name;
    int baseLeaveAllowance;
    int leaveDaysUsed;
    int salary;
    int bonusPercent;
    bool addBonus;


public:
    Employee();
    Employee(pqxx::row data);

};