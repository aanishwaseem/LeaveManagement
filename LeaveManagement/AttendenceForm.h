#pragma once
#include <msclr/marshal_cppstd.h>
#include "EmployeeRegister.h"
#include <string>
#include <array>
#include <vector>

namespace LeaveManagement {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class AttendanceUserControl : public System::Windows::Forms::UserControl
    {
    private:
        ListView^ listViewEmployees;
        Button^ buttonMarkAttendance;

        // Example employee list

    public:
        AttendanceUserControl()
        {
            InitializeComponent();
            PopulateEmployeeList();
        }


    private:
        void InitializeComponent(void)
        {
            this->listViewEmployees = (gcnew System::Windows::Forms::ListView());
            this->buttonMarkAttendance = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // ListView
            this->listViewEmployees->Location = System::Drawing::Point(12, 12);
            this->listViewEmployees->Size = System::Drawing::Size(400, 200);
            this->listViewEmployees->View = View::Details;
            this->listViewEmployees->FullRowSelect = true;

            // Columns
            this->listViewEmployees->Columns->Add("ID", 50, HorizontalAlignment::Left);
            this->listViewEmployees->Columns->Add("Name", 150, HorizontalAlignment::Left);
            this->listViewEmployees->Columns->Add("Position", 100, HorizontalAlignment::Left);
            this->listViewEmployees->Columns->Add("On Duty", 70, HorizontalAlignment::Center);

            // Button
            this->buttonMarkAttendance->Location = System::Drawing::Point(160, 230);
            this->buttonMarkAttendance->Size = System::Drawing::Size(120, 30);
            this->buttonMarkAttendance->Text = L"Mark Attendance";
            this->buttonMarkAttendance->Click += gcnew EventHandler(this, &AttendanceUserControl::buttonMarkAttendance_Click);

            // AttendanceUserControl
            this->ClientSize = System::Drawing::Size(430, 280);
            this->Controls->Add(this->listViewEmployees);
            this->Controls->Add(this->buttonMarkAttendance);
            this->ResumeLayout(false);
        }

        void PopulateEmployeeList()
        {
            listViewEmployees->Items->Clear();
            EmployeeRegister^ employeeRegister = EmployeeRegister::GetInstance();
            List<Employee^>^ employees = employeeRegister->GetEmployees();

            for (int i = 0; i < employees->Count; i++) {
                Employee^ emp = employees[i];
                ListViewItem^ item = gcnew ListViewItem(emp->getID());
                item->SubItems->Add(emp->getName());
                item->SubItems->Add(emp->getPosition());
                item->SubItems->Add(emp->getStatus()->onDuty ? "Yes" : "No");

                // Set item color based on attendance status
                if (emp->getStatus()->present) {
                    item->BackColor = Color::LightGreen;
                }
                else {
                    item->BackColor = Color::Salmon;
                }

                listViewEmployees->Items->Add(item);
            }
        }

        void buttonMarkAttendance_Click(Object^ sender, EventArgs^ e)
        {
            if (listViewEmployees->SelectedItems->Count == 0) {
                MessageBox::Show("Please select an employee.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Get selected employee
            ListViewItem^ selectedItem = listViewEmployees->SelectedItems[0];
            String^ selectedID = selectedItem->Text;
            EmployeeRegister^ employeeRegister = EmployeeRegister::GetInstance();
            List<Employee^>^ employees = employeeRegister->GetEmployees();

            for (int i = 0; i < employees->Count; i++) {
                Employee^ emp = employees[i];
                if (emp->getID() == selectedID) {
                    // Toggle attendance
                    emp->getStatus()->present = !emp->getStatus()->present;

                    // Update item color
                    if (emp->getStatus()->present) {
                        selectedItem->BackColor = Color::LightGreen;
                    }
                    else {
                        selectedItem->BackColor = Color::Salmon;
                    }
                    break;
                }
            }
        }



    };
}
