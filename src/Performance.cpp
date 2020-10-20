#include "Performance.hpp"

#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>

Performance::Performance(pqxx::row row) {
    this->year = boost::lexical_cast<int>(row["year"].c_str());
    this->target = boost::lexical_cast<int>(row["target"].c_str());
    this->actual = boost::lexical_cast<int>(row["actual"].c_str());
}

int Performance::getYear() {
    return this->year;
}

int Performance::getTarget() {
    return this->target;
}

int Performance::getActual() {
    return this->actual;
}

float Performance::calculateBonus(int salary) {
    float ratio = static_cast<float>(this->actual) / static_cast<float>(this->target);

    if (ratio < 1.1f) {
        return 0;
    } else if (ratio >= 1.1f && ratio < 1.2f) {
        return (static_cast<float>(salary) * 1.05f) - salary;
    } else if (ratio >= 1.2f && ratio < 1.35f) {
        return (static_cast<float>(salary) * 1.1f) - salary;
    } else if (ratio >= 1.35f && ratio < 1.5f) {
        return (static_cast<float>(salary) * 1.25f) - salary;
    } else {
        return (static_cast<float>(salary) * 1.5f) - salary;
    }
}