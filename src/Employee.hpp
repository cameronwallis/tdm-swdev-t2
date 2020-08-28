#pragma once

#include <pqxx/pqxx>

class Employee {

private:

public:
    Employee();
    Employee(pqxx::row data);

};