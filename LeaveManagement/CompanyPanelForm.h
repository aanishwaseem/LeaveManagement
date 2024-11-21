#pragma once
#include <Windows.h>

namespace LeaveManagement {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class CompanyPanelForm : public System::Windows::Forms::Form
    {
    private:
        String^ employeeId;
        String^ position;
        array<String^>^ allTabs; // Store tab names
        array<String^>^ allowedTabs; // Store allowed tabs for the user

    public:
        CompanyPanelForm(String^ userId, String^ userPosition)
        {
            employeeId = userId;
            position = userPosition;
            InitializeComponent();
            InitializeTabs();
            SetPermissions();
        }

    protected:
        ~CompanyPanelForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TabControl^ tabControl;
        System::Windows::Forms::TabPage^ tabHome;
        System::Windows::Forms::TabPage^ tabReports;
        System::Windows::Forms::TabPage^ tabManageAttendance;
        System::Windows::Forms::TabPage^ tabManageLeaves;
        System::Windows::Forms::TabPage^ tabApplyLeaves;
        System::Windows::Forms::Label^ lblEmployeeId;
        System::Windows::Forms::Label^ lblPosition;
        System::Windows::Forms::Button^ btnLogout;

        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->tabControl = (gcnew System::Windows::Forms::TabControl());
            this->tabHome = (gcnew System::Windows::Forms::TabPage());
            this->tabReports = (gcnew System::Windows::Forms::TabPage());
            this->tabManageAttendance = (gcnew System::Windows::Forms::TabPage());
            this->tabManageLeaves = (gcnew System::Windows::Forms::TabPage());
            this->tabApplyLeaves = (gcnew System::Windows::Forms::TabPage());
            this->lblEmployeeId = (gcnew System::Windows::Forms::Label());
            this->lblPosition = (gcnew System::Windows::Forms::Label());
            this->btnLogout = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // TabControl
            this->tabControl->Controls->Add(this->tabHome);
            this->tabControl->Controls->Add(this->tabReports);
            this->tabControl->Controls->Add(this->tabManageAttendance);
            this->tabControl->Controls->Add(this->tabManageLeaves);
            this->tabControl->Controls->Add(this->tabApplyLeaves);
            this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tabControl->Location = System::Drawing::Point(0, 0);
            this->tabControl->Name = L"tabControl";

            // Home Tab
            this->tabHome->Text = L"Home";
            this->tabHome->Controls->Add(this->lblEmployeeId);
            this->tabHome->Controls->Add(this->lblPosition);
            this->tabHome->Controls->Add(this->btnLogout);
            this->tabHome->BackColor = System::Drawing::Color::White;

            // Employee ID Label
            this->lblEmployeeId->AutoSize = true;
            this->lblEmployeeId->Location = System::Drawing::Point(20, 20);
            this->lblEmployeeId->Text = L"Employee ID: ";

            // Position Label
            this->lblPosition->AutoSize = true;
            this->lblPosition->Location = System::Drawing::Point(20, 50);
            this->lblPosition->Text = L"Position: ";

            // Logout Button
            this->btnLogout->Location = System::Drawing::Point(20, 150);
            this->btnLogout->Size = System::Drawing::Size(75, 23);
            this->btnLogout->Text = L"Logout";
            this->btnLogout->Click += gcnew System::EventHandler(this, &CompanyPanelForm::btnLogout_Click);

            // Tab Pages
            this->tabReports->Text = L"View Reports";
            this->tabReports->BackColor = System::Drawing::Color::White;

            this->tabManageAttendance->Text = L"Manage Attendance";
            this->tabManageAttendance->BackColor = System::Drawing::Color::White;

            this->tabManageLeaves->Text = L"Manage Leaves";
            this->tabManageLeaves->BackColor = System::Drawing::Color::White;

            this->tabApplyLeaves->Text = L"Apply for Leaves";
            this->tabApplyLeaves->BackColor = System::Drawing::Color::White;

            // CompanyPanelForm
            this->ClientSize = System::Drawing::Size(600, 400);
            this->Controls->Add(this->tabControl);
            this->Name = L"CompanyPanelForm";
            this->Text = L"Company Panel";
            this->ResumeLayout(false);
        }

        void InitializeTabs()
        {
            // Define all available tabs
            allTabs = gcnew array<String^> { "Home", "View Reports", "Manage Attendance", "Manage Leaves", "Apply for Leaves" };

            // Update Home tab details dynamically
            lblEmployeeId->Text = L"Employee ID: " + employeeId;
            lblPosition->Text = L"Position: " + position;
        }

        void SetPermissions()
        {
            // Define allowed tabs based on position
            if (position == "Guard") {
                allowedTabs = gcnew array<String^> { "Home", "View Reports", "Manage Attendance" };
            }
            else if (position == "Employee") {
                allowedTabs = gcnew array<String^> { "Home", "View Reports", "Apply for Leaves" };
            }
            else if (position == "Director") {
                allowedTabs = allTabs; // Director has access to all tabs
            }

            // Remove tabs that are not allowed
            for each (String ^ tabName in allTabs)
            {
                if (Array::IndexOf(allowedTabs, tabName) == -1)
                {
                    TabPage^ tabPage = FindTabByName(tabName);
                    if (tabPage != nullptr) {
                        this->tabControl->TabPages->Remove(tabPage);
                    }
                }
            }
        }

        TabPage^ FindTabByName(String^ name)
        {
            // Find a tab by its name
            for each (TabPage ^ tab in this->tabControl->TabPages)
            {
                if (tab->Text == name) {
                    return tab;
                }
            }
            return nullptr;
        }

        void btnLogout_Click(Object^ sender, EventArgs^ e)
        {
            // Logout and show the Login Page

            this->Close();
        }
    };
}
