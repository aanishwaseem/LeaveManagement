#include "MyForm.h"

void main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    LeaveManagement::MyForm form;
    Application::Run(% form);
}