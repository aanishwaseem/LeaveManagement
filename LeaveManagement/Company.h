#pragma once

#include "EmployeeRegister.h"
#include "ITimeObserver.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>

using namespace System;
using namespace System::IO;
using namespace std;

namespace LeaveManagement {

    // Declare the employees array outside of the managed class

    public ref class Company : public ITimeObserver
    {
    private:
        // Singleton instance
        static Company^ instance = nullptr;

        // Private constructor to enforce singleton
        Company() {}

    public:
        // Method to access the singleton instance
        static Company^ GetInstance()
        {
            if (instance == nullptr)
            {
                instance = gcnew Company();
            }
            return instance;
        }

        // Implement the Update method for the observer
        virtual void Update(String^ currentDate)
        {
            WriteAttendanceToFile(currentDate);
        }

        // Method to write attendance records to a file
        void WriteAttendanceToFile(String^ currentDate)
        {
            String^ filePath = "AttendanceRecords\\" + currentDate + ".txt";
            Directory::CreateDirectory("AttendanceRecords");

            // Create an instance of EmployeeRegister
            EmployeeRegister^ employeeRegister = EmployeeRegister::GetInstance();

            // Get the list of employees
            List<Employee^>^ employees = employeeRegister->GetEmployees();

            // Create and open the file
            StreamWriter^ writer = gcnew StreamWriter(filePath);

            // Write employee data to the file
            for each (Employee ^ employee in employees)
            {
                writer->WriteLine("ID: " + employee->id);
                writer->WriteLine("Name: " + employee->name);
                writer->WriteLine("Position: " + employee->position);
                writer->WriteLine("Present: " + (employee->status->present ? "Yes" : "No"));
                writer->WriteLine(); // Blank line between records
            }

            // Close the file
            writer->Close();
        }
    };
}
