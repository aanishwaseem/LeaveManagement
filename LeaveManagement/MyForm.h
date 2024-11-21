#pragma once
#include <fstream>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "CompanyPanelForm.h"

namespace LeaveManagement {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ labelID;
        System::Windows::Forms::Label^ labelPassword;
        System::Windows::Forms::TextBox^ textBoxID;
        System::Windows::Forms::TextBox^ textBoxPassword;
        System::Windows::Forms::Button^ buttonLogin;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->labelID = (gcnew System::Windows::Forms::Label());
            this->labelPassword = (gcnew System::Windows::Forms::Label());
            this->textBoxID = (gcnew System::Windows::Forms::TextBox());
            this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
            this->buttonLogin = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // labelID
            // 
            this->labelID->AutoSize = true;
            this->labelID->Location = System::Drawing::Point(50, 50);
            this->labelID->Name = L"labelID";
            this->labelID->Size = System::Drawing::Size(67, 13);
            this->labelID->TabIndex = 0;
            this->labelID->Text = L"Employee ID";
            // 
            // labelPassword
            // 
            this->labelPassword->AutoSize = true;
            this->labelPassword->Location = System::Drawing::Point(50, 100);
            this->labelPassword->Name = L"labelPassword";
            this->labelPassword->Size = System::Drawing::Size(53, 13);
            this->labelPassword->TabIndex = 1;
            this->labelPassword->Text = L"Password";
            // 
            // textBoxID
            // 
            this->textBoxID->Location = System::Drawing::Point(150, 50);
            this->textBoxID->Name = L"textBoxID";
            this->textBoxID->Size = System::Drawing::Size(160, 20);
            this->textBoxID->TabIndex = 2;
            // 
            // textBoxPassword
            // 
            this->textBoxPassword->Location = System::Drawing::Point(150, 100);
            this->textBoxPassword->Name = L"textBoxPassword";
            this->textBoxPassword->PasswordChar = '*';
            this->textBoxPassword->Size = System::Drawing::Size(160, 20);
            this->textBoxPassword->TabIndex = 3;
            // 
            // buttonLogin
            // 
            this->buttonLogin->Location = System::Drawing::Point(150, 150);
            this->buttonLogin->Name = L"buttonLogin";
            this->buttonLogin->Size = System::Drawing::Size(75, 23);
            this->buttonLogin->TabIndex = 4;
            this->buttonLogin->Text = L"Login";
            this->buttonLogin->Click += gcnew System::EventHandler(this, &MyForm::buttonLogin_Click);
            // 
            // MyForm
            // 
            this->ClientSize = System::Drawing::Size(400, 250);
            this->Controls->Add(this->labelID);
            this->Controls->Add(this->labelPassword);
            this->Controls->Add(this->textBoxID);
            this->Controls->Add(this->textBoxPassword);
            this->Controls->Add(this->buttonLogin);
            this->Name = L"MyForm";
            this->Text = L"Login";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void buttonLogin_Click(System::Object^ sender, System::EventArgs^ e) {
            std::string enteredID = msclr::interop::marshal_as<std::string>(this->textBoxID->Text);
            std::string enteredPassword = msclr::interop::marshal_as<std::string>(this->textBoxPassword->Text);

            std::ifstream infile("employees.txt");
            std::string id, password, position;
            bool validCredentials = false;

            while (infile >> id >> password >> position) {
                if (id == enteredID && password == enteredPassword) {
                    validCredentials = true;

                    CompanyPanelForm^ panelForm = gcnew CompanyPanelForm(gcnew String(id.c_str()), gcnew String(position.c_str()));
                    panelForm->Show();
                    this->Hide();
                    break;
                }
            }

            infile.close();

            if (!validCredentials) {
                MessageBox::Show("Invalid ID or Password", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}
