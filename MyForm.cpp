#pragma once
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace GatorHarmonize;
[STAThread]

void main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    GatorHarmonize::MyForm form;
    Application::Run(% form);

}