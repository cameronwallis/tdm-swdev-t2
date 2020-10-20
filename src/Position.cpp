#include "Position.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>

namespace id = boost::uuids;

Position::Position(pqxx::row row) {
    this->ID = boost::lexical_cast<id::uuid>(row["position_id"].c_str());
    this->title = row["title"].c_str();
    this->salary = boost::lexical_cast<int>(row["salary"].c_str());
    this->baseLeave = boost::lexical_cast<int>(row["baseLeave"].c_str());
    this->additionalLeavePerYear = boost::lexical_cast<float>(row["additionalLeavePerYear"].c_str());
    this->employeePensionContributionPercent = boost::lexical_cast<int>(row["employeePensionContributionPercent"].c_str());
    this->employerPensionContributionPercent = boost::lexical_cast<int>(row["employerPensionContributionPercent"].c_str());
}