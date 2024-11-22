#pragma once
#include <string>
#include <array>

struct AttendenceStatus {
    bool onDuty;
    bool present;
    AttendenceStatus() : onDuty(false), present(false) {}
};

class Employee {
    std::string id;
    std::string name;
    std::string position;
    AttendenceStatus status;

public:
    Employee() {}

    Employee(std::string id, std::string name, std::string position)
        : id(id), name(name), position(position) {}

    std::string getID() const { return id; }
    std::string getName() const { return name; }
    std::string getPosition() const { return position; }
    AttendenceStatus& getStatus() { return status; }

    void setStatus(const AttendenceStatus& newStatus) { status = newStatus; }
};

// Define global employee array
static std::array<Employee, 5> employees = { {
    {"101", "Alice", "Manager"},
    {"102", "Bob", "Engineer"},
    {"103", "Charlie", "Technician"},
    {"104", "David", "Clerk"},
    {"105", "Eve", "HR"}
} };
