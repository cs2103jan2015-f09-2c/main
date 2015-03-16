#include "K5-GUI.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace UI;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUI mainWindow;
	Application::Run(%mainWindow);
}