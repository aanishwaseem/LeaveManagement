#pragma once
#include "MyTime.h"
#include <msclr/marshal_cppstd.h>

namespace LeaveManagement {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class TimeUserControl : public System::Windows::Forms::UserControl
    {
    public:
        TimeUserControl()
        {
            InitializeComponent();
            UpdateDateDisplay(); // Initialize the display with the current static date
        }

    private:
        Label^ lblCurrentDate;
        Button^ btnNextDay;

        void InitializeComponent(void)
        {
            this->lblCurrentDate = (gcnew System::Windows::Forms::Label());
            this->btnNextDay = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // Label for Current Date
            this->lblCurrentDate->AutoSize = true;
            this->lblCurrentDate->Location = System::Drawing::Point(20, 20);
            this->lblCurrentDate->Size = System::Drawing::Size(100, 20);

            // Button for Next Day
            this->btnNextDay->Location = System::Drawing::Point(20, 60);
            this->btnNextDay->Size = System::Drawing::Size(100, 30);
            this->btnNextDay->Text = L"Next Day";
            this->btnNextDay->Click += gcnew System::EventHandler(this, &TimeUserControl::btnNextDay_Click);

            // Add controls to the UserControl
            this->Controls->Add(this->lblCurrentDate);
            this->Controls->Add(this->btnNextDay);
            this->Size = System::Drawing::Size(250, 120);
            this->ResumeLayout(false);
        }

        void btnNextDay_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Call the NextDay method on the singleton instance of MyTime
            MyTime^ myTime = MyTime::GetInstance();  // Get the singleton instance
            myTime->NextDay(); // Update the date by moving to the next day
            UpdateDateDisplay(); // Update the display after changing the date
        }

        void UpdateDateDisplay()
        {
            // Get the current date from the singleton instance and update the label
            MyTime^ myTime = MyTime::GetInstance();  // Get the singleton instance
            lblCurrentDate->Text = "Current Date: " + myTime->GetDate();
        }
    };
}
