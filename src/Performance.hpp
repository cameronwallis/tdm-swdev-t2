#pragma once

#include <pqxx/pqxx>

class Performance {
private:
    int year;
    int target;
    int actual;

public:
    Performance() = default;
    Performance(pqxx::row row);
    virtual ~Performance() = default;

    int getYear();
    int getTarget();
    int getActual();

    float calculateBonus(int salary);

};