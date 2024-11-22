#pragma once

#include <msclr/marshal_cppstd.h>
#include "Employee.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

public ref class EmployeeRegister
{
private:
    List<Employee^>^ employees;

    // Private static instance of EmployeeRegister (singleton instance)
    static EmployeeRegister^ instance = nullptr;

    // Private constructor to prevent direct instantiation
    EmployeeRegister()
    {
        employees = gcnew List<Employee^>();
    }

public:
    // Public static method to access the singleton instance
    static EmployeeRegister^ GetInstance()
    {
        if (instance == nullptr)
        {
            instance = gcnew EmployeeRegister();
        }
        return instance;
    }

    // Method to add a new employee
    void AddEmployee(String^ id, String^ name, String^ position)
    {
        Employee^ newEmployee = gcnew Employee(id, name, position);
        employees->Add(newEmployee);
    }

    // Method to get a list of all employees
    List<Employee^>^ GetEmployees()
    {
        return employees;
    }

    // Method to find an employee by ID
    Employee^ FindEmployeeById(String^ id)
    {
        for (int i = 0; i < employees->Count; i++)
        {
            if (employees[i]->id == id)
            {
                return employees[i];
            }
        }
        return nullptr; // Return nullptr if employee not found
    }

    // Method to remove an employee by ID
    bool RemoveEmployeeById(String^ id)
    {
        Employee^ employeeToRemove = FindEmployeeById(id);
        if (employeeToRemove != nullptr)
        {
            employees->Remove(employeeToRemove);
            return true;
        }
        return false;
    }
};
