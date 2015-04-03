#pragma once
#include "GUI.h"
#include"Log.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <ctime>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace std;

namespace UI {
	/// Summary for GUI
	public ref class GUI : public System::Windows::Forms::Form {
	private:
		Logic* plannerLogic;
		String^ currentView;
		bool clearTrigger;

		System::Windows::Forms::TextBox^  displayWindow;
		System::Windows::Forms::TextBox^  userInput;
		System::Windows::Forms::Button^  missedButton;
		System::Windows::Forms::Button^  upcomingButton;
		System::Windows::Forms::Button^  homeButton;
		System::Windows::Forms::Label^  prompt;

		/// Required designer variable.
		System::ComponentModel::Container ^components;

		String^ HOME = "Home";
		String^ UPCOMING = "Upcoming";
		String^ MISSED = "Missed";
		String^ HELP = "Help";
		String^ ALL = "All";
		String^ DONE = "Done";
		String^ SEARCH = "Search";
		String^ CLEAR_PROMPT = "Are you sure you want to clear the entire planner? Enter <Y> to confirm or <N> to cancel";

	public:
		GUI(void){
			InitializeComponent();
			//Add the constructor code here
			plannerLogic = new Logic;
			currentView = HOME;
		}

	protected:
		/// Clean up any resources being used.
		~GUI(){
			if (components)	{
				delete components;
				delete plannerLogic;
				delete currentView;
			}
		}

#pragma region Windows Form Designer generated code
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		void InitializeComponent(void)
		{
			this->displayWindow = (gcnew System::Windows::Forms::TextBox());
			this->userInput = (gcnew System::Windows::Forms::TextBox());
			this->missedButton = (gcnew System::Windows::Forms::Button());
			this->homeButton = (gcnew System::Windows::Forms::Button());
			this->upcomingButton = (gcnew System::Windows::Forms::Button());
			this->prompt = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// displayWindow
			// 
			this->displayWindow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->displayWindow->Location = System::Drawing::Point(10, 12);
			this->displayWindow->Multiline = true;
			this->displayWindow->Name = L"displayWindow";
			this->displayWindow->ReadOnly = true;
			this->displayWindow->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->displayWindow->Size = System::Drawing::Size(339, 291);
			this->displayWindow->TabIndex = 0;
			// 
			// userInput
			// 
			this->userInput->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(8) {
				L"add",
					L"delete",
					L"edit",
					L"clear",
					L"exit",
					L"search",
					L"undo",
					L"help"
			});
			this->userInput->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->userInput->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->userInput->Location = System::Drawing::Point(10, 363);
			this->userInput->Name = L"userInput";
			this->userInput->Size = System::Drawing::Size(339, 20);
			this->userInput->TabIndex = 1;
			this->userInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::userInput_Process);
			// 
			// missedButton
			// 
			this->missedButton->BackColor = System::Drawing::Color::SteelBlue;
			this->missedButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->missedButton->Location = System::Drawing::Point(10, 320);
			this->missedButton->Name = L"missedButton";
			this->missedButton->Size = System::Drawing::Size(109, 28);
			this->missedButton->TabIndex = 2;
			this->missedButton->Text = L"Missed";
			this->missedButton->UseVisualStyleBackColor = false;
			this->missedButton->Click += gcnew System::EventHandler(this, &GUI::missedButton_Click);
			// 
			// homeButton
			// 
			this->homeButton->BackColor = System::Drawing::Color::SteelBlue;
			this->homeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->homeButton->Location = System::Drawing::Point(125, 320);
			this->homeButton->Name = L"homeButton";
			this->homeButton->Size = System::Drawing::Size(109, 28);
			this->homeButton->TabIndex = 3;
			this->homeButton->Text = L"Home";
			this->homeButton->UseVisualStyleBackColor = false;
			this->homeButton->Click += gcnew System::EventHandler(this, &GUI::homeButton_Click);
			// 
			// upcomingButton
			// 
			this->upcomingButton->BackColor = System::Drawing::Color::SteelBlue;
			this->upcomingButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->upcomingButton->Location = System::Drawing::Point(240, 320);
			this->upcomingButton->Name = L"upcomingButton";
			this->upcomingButton->Size = System::Drawing::Size(109, 28);
			this->upcomingButton->TabIndex = 4;
			this->upcomingButton->Text = L"Upcoming";
			this->upcomingButton->UseVisualStyleBackColor = false;
			this->upcomingButton->Click += gcnew System::EventHandler(this, &GUI::upcomingButton_Click);
			// 
			// prompt
			// 
			this->prompt->AutoSize = true;
			this->prompt->Location = System::Drawing::Point(7, 388);
			this->prompt->Name = L"prompt";
			this->prompt->Size = System::Drawing::Size(135, 13);
			this->prompt->TabIndex = 5;
			this->prompt->Text = L"Type \'help\' for the Help List";
			// 
			// GUI
			// 
			this->ClientSize = System::Drawing::Size(371, 457);
			this->Controls->Add(this->prompt);
			this->Controls->Add(this->upcomingButton);
			this->Controls->Add(this->homeButton);
			this->Controls->Add(this->missedButton);
			this->Controls->Add(this->userInput);
			this->Controls->Add(this->displayWindow);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"GUI";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load_1);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		/************************************************************************************************

		Initialization

		************************************************************************************************/

	private: System::Void GUI_Load_1(System::Object^  sender, System::EventArgs^  e) {
		homeButton_Click(sender, e);
	}

			 /************************************************************************************************

			 GUI control functions

			 ************************************************************************************************/
	private: System::Void userInput_Process(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		string searchCheck;

		searchCheck = msclr::interop::marshal_as<std::string>(userInput->Text);

		if (e->KeyCode == Keys::Enter) {
			e->Handled = true;

			if (userInput->Text == "home") {
				executeHome(sender, e);
			}
			else if (userInput->Text == "missed") {
				executeMissed(sender, e);
			}
			else if (userInput->Text == "upcoming") {
				executeUpcoming(sender, e);
			}
			else if (userInput->Text == "help") {
				executeHelp();
			}
			else if (userInput->Text == "show done") {
				executeDone();
			}
			else if (userInput->Text == "all") {
				executeAll();
			}
			else if (userInput->Text == "exit") {
				executeExit();
			}
			else if (userInput->Text == "clear") {
				activateCleartrigger();
			}
			else if ((userInput->Text == "Y" || userInput->Text == "N") && clearTrigger == true) {
				executeClear();
			}
			else if (searchCheck.find("search") != string::npos) {
				executeSearch();
				}
			else {
				processInput(userInput->Text, currentView);
			}

			userInput->Text = "";
		}
	}

	private: System::Void executeHome(System::Object^  sender, System::EventArgs^  e) {
		homeButton_Click(sender, e);
	}

	private: System::Void executeUpcoming(System::Object^  sender, System::EventArgs^  e) {
		upcomingButton_Click(sender, e);
	}

	private: System::Void executeMissed(System::Object^  sender, System::EventArgs^  e) {
		missedButton_Click(sender, e);
	}

	private: System::Void executeHelp() {
		currentView = HELP;
		processInput(userInput->Text, currentView);
	}

	private: System::Void executeDone() {
		currentView = DONE;
		processInput(userInput->Text, currentView);
	}

	private: System::Void executeAll() {
		currentView = ALL;
		processInput(userInput->Text, currentView);
	}

	private: System::Void executeExit() {
		Application::Exit();
	}

	private: System::Void activateCleartrigger() {
		prompt->Text = CLEAR_PROMPT;
		clearTrigger = true;
	}

	private: System::Void executeClear() {
		currentView = SEARCH;
		processInput(userInput->Text, currentView);
		clearTrigger = false;
	}

	private: System::Void executeSearch() {
		currentView = SEARCH;
		colourSwitch(currentView);
		processInput(userInput->Text, currentView);
	}

	private: System::Void processInput(String^ managedInput, String^ managedView) {
		String^ strOutput;

		string unmanagedInput = msclr::interop::marshal_as<std::string>(managedInput);
		string unmanagedView = msclr::interop::marshal_as<std::string>(managedView);

		plannerLogic->processUserInput(unmanagedInput, unmanagedView);

		strOutput = gcnew String(plannerLogic->displayContent().c_str());
		displayWindow->Text = strOutput;
		prompt->Text = gcnew String(plannerLogic->displayOutcome().c_str());
	}

			 /************************************************************************************************

			 GUI view functions

			 ************************************************************************************************/
	private: System::Void colourSwitch(String^ currentView) {
		if (currentView == HOME) {
			homeButton->BackColor = Color::LightSkyBlue;
			missedButton->BackColor = Color::SteelBlue;
			upcomingButton->BackColor = Color::SteelBlue;
		}
		else if (currentView == UPCOMING) {
			upcomingButton->BackColor = Color::LightSkyBlue;
			missedButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
		else if (currentView == MISSED) {
			missedButton->BackColor = Color::LightSkyBlue;
			upcomingButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
		else if (currentView == HELP || currentView == ALL || currentView == SEARCH) {
			missedButton->BackColor = Color::SteelBlue;
			upcomingButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
	}

	private: System::Void switchView(String^ viewType) {
		string unmanagedView = msclr::interop::marshal_as<std::string>(viewType);
		plannerLogic->updateDisplay(unmanagedView);
		displayWindow->Text = gcnew String(plannerLogic->displayContent().c_str());
		colourSwitch(currentView);
	}

	private: System::Void homeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = HOME;
		switchView(currentView);
		prompt->Text = HOME;
	}

	private: System::Void upcomingButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = UPCOMING;
		switchView(currentView);
		prompt->Text = UPCOMING;
	}

	private: System::Void missedButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = MISSED;
		switchView(currentView);
		prompt->Text = MISSED;
	}

	};
}