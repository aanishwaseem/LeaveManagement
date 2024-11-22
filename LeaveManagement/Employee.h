#pragma once

using namespace System;

public ref class AttendenceStatus
{
public:
    bool onDuty;
    bool present;

    AttendenceStatus() : onDuty(false), present(false) {}
};

public ref class Employee
{
public:
    String^ id;               // Managed String^ type instead of std::string
    String^ name;             // Managed String^ type instead of std::string
    String^ position;         // Managed String^ type instead of std::string
    AttendenceStatus^ status; // Use ref class for the AttendenceStatus

public:
    // Default constructor
    Employee()
    {
        status = gcnew AttendenceStatus();
    }

    // Constructor with parameters
    Employee(String^ id, String^ name, String^ position)
        : id(id), name(name), position(position)
    {
        status = gcnew AttendenceStatus();
    }

    // Getters for properties
    String^ getID() { return id; }
    String^ getName() { return name; }
    String^ getPosition() { return position; }
    AttendenceStatus^ getStatus() { return status; }

    // Set the status
    void setStatus(AttendenceStatus^ newStatus) { status = newStatus; }
};