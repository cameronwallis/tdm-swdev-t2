#include "Employee.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>

Employee::Employee() {

}

Employee::Employee(pqxx::row row) {
    this->ID = boost::lexical_cast<boost::uuids::uuid>(row["employee_id"].c_str());
    this->name = row["name"].c_str();
    this->baseLeaveAllowance = boost::lexical_cast<int>(row["base_leave_allowance"].c_str());
    this->leaveDaysUsed = boost::lexical_cast<int>(row["leave_days_used"].c_str());
    this->salary = boost::lexical_cast<int>(row["salary"].c_str());
    this->bonusPercent = boost::lexical_cast<int>(row["bonus_percent"].c_str());
    this->addBonus = boost::lexical_cast<bool>(row["bonus_flag"].c_str());
}