#include "Planner4LifeGUI.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace UI;

[STAThread]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUI mainWindow;
	Application::Run(%mainWindow);

	return 0;
}