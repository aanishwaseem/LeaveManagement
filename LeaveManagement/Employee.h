#pragma once
#include <string>
#include <array>

struct Employee {
    std::string id;
    std::string name;
    std::string position;
};

static std::array<Employee, 5> employees = { {
    {"101", "Alice", "Manager"},
    {"102", "Bob", "Engineer"},
    {"103", "Charlie", "Technician"},
    {"104", "David", "Clerk"},
    {"105", "Eve", "HR"}
} };
