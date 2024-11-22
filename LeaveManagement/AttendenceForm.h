#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <msclr/marshal_cppstd.h>
#include "Employee.h"

namespace LeaveManagement {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AttendanceForm : public System::Windows::Forms::UserControl
    {
    public:
        AttendanceForm()
        {
            InitializeComponent();
            LoadEmployeeData();
        }

    protected:
        ~AttendanceForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::ListView^ listViewEmployees;
        System::Windows::Forms::Button^ buttonMarkAttendance;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->listViewEmployees = gcnew System::Windows::Forms::ListView();
            this->buttonMarkAttendance = gcnew System::Windows::Forms::Button();

            // ListView
            this->listViewEmployees->Dock = System::Windows::Forms::DockStyle::Top;
            this->listViewEmployees->Height = 300;
            this->listViewEmployees->View = System::Windows::Forms::View::Details;
            this->listViewEmployees->FullRowSelect = true;
            this->listViewEmployees->MultiSelect = false;

            // ListView Columns
            this->listViewEmployees->Columns->Add("Employee ID", 100, HorizontalAlignment::Left);
            this->listViewEmployees->Columns->Add("Name", 150, HorizontalAlignment::Left);
            this->listViewEmployees->Columns->Add("Position", 150, HorizontalAlignment::Left);

            // Button: Mark Attendance
            this->buttonMarkAttendance->Text = L"Mark Attendance";
            this->buttonMarkAttendance->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->buttonMarkAttendance->Height = 50;
            this->buttonMarkAttendance->Click += gcnew System::EventHandler(this, &AttendanceForm::OnMarkAttendanceClicked);

            // Add Controls
            this->Controls->Add(this->listViewEmployees);
            this->Controls->Add(this->buttonMarkAttendance);
        }

        // Load employee data from EmployeeData.h
        void LoadEmployeeData()
        {
            for (const auto& employee : employees)
            {
                ListViewItem^ item = gcnew ListViewItem(gcnew String(employee.id.c_str()));
                item->SubItems->Add(gcnew String(employee.name.c_str()));
                item->SubItems->Add(gcnew String(employee.position.c_str()));

                // Set initial item color to red
                item->BackColor = Color::Red;
                this->listViewEmployees->Items->Add(item);
            }
        }

        // Event: Mark Attendance
        void OnMarkAttendanceClicked(System::Object^ sender, System::EventArgs^ e)
        {
            if (this->listViewEmployees->SelectedItems->Count > 0)
            {
                ListViewItem^ selectedItem = this->listViewEmployees->SelectedItems[0];
                selectedItem->BackColor = Color::Green; // Mark as attended
            }
            else
            {
                MessageBox::Show("Please select an employee to mark attendance.", "No Selection", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }
    };
}
