#pragma once
#include "Logic.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <ctime>
/* uncomment to disable assert()
#define NDEBUG		*/
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

		//@author A0111314A

	private:
		//UI operation elements
		Logic* plannerLogic;
		String^ currentView;
		bool clearTrigger;

		//GUI elements
		System::Windows::Forms::TextBox^  displayWindow;
		System::Windows::Forms::TextBox^  userInput;
		System::Windows::Forms::Button^  missedButton;
		System::Windows::Forms::Button^  upcomingButton;
		System::Windows::Forms::Button^  homeButton;
		System::Windows::Forms::Label^  status;


		//constant strings
		String^ VIEWTYPE_HOME = "Home";
		String^ VIEWTYPE_UPCOMING = "Upcoming";
		String^ VIEWTYPE_MISSED = "Missed";
		String^ VIEWTYPE_HELP = "Help";
		String^ VIEWTYPE_ALL = "All";
		String^ VIEWTYPE_DONE = "Done";
		String^ VIEWTYPE_SEARCH = "Search";

		String^ COMMAND_HOME = "home";
		String^ COMMAND_UPCOMING = "upcoming";
		String^ COMMAND_MISSED = "missed";
		String^ COMMAND_HELP = "help";
		String^ COMMAND_ALL = "all";
		String^ COMMAND_SHOW_DONE = "show done";
		String^ COMMAND_SEARCH = "search";
		String^ COMMAND_EXIT = "exit";
		String^ COMMAND_CLEAR = "clear";
		String^ COMMAND_Y = "Y";
		String^ COMMAND_N = "N";
		String^ COMMAND_y = "y";
		String^ COMMAND_n = "n";
		String^ STATUS_CLEAR_PROMPT = "Are you sure you want to clear? Enter <Y> to confirm or <N> to cancel";

		/// Required designer variable.
		System::ComponentModel::Container ^components;

	public:
		GUI(void){
			InitializeComponent();
			//Add the constructor code here
			plannerLogic = new Logic;
			currentView = VIEWTYPE_HOME;
			clearTrigger = false;
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

		//@author generated

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->displayWindow = (gcnew System::Windows::Forms::TextBox());
			this->userInput = (gcnew System::Windows::Forms::TextBox());
			this->missedButton = (gcnew System::Windows::Forms::Button());
			this->homeButton = (gcnew System::Windows::Forms::Button());
			this->upcomingButton = (gcnew System::Windows::Forms::Button());
			this->status = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// displayWindow
			// 
			this->displayWindow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->displayWindow->Location = System::Drawing::Point(10, 12);
			this->displayWindow->Multiline = true;
			this->displayWindow->Name = L"displayWindow";
			this->displayWindow->ReadOnly = true;
			this->displayWindow->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->displayWindow->Size = System::Drawing::Size(496, 291);
			this->displayWindow->TabIndex = 0;
			// 
			// userInput
			// 
			this->userInput->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(10) {
				L"add", L"delete", L"edit",
					L"clear", L"exit", L"search", L"done", L"show done", L"undo", L"help"
			});
			this->userInput->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->userInput->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->userInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
			this->userInput->Location = System::Drawing::Point(10, 355);
			this->userInput->Name = L"userInput";
			this->userInput->Size = System::Drawing::Size(494, 21);
			this->userInput->TabIndex = 1;
			this->userInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::userInput_Process);
			// 
			// missedButton
			// 
			this->missedButton->BackColor = System::Drawing::Color::SteelBlue;
			this->missedButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->missedButton->ForeColor = System::Drawing::SystemColors::ControlText;
			this->missedButton->Location = System::Drawing::Point(63, 310);
			this->missedButton->Name = L"missedButton";
			this->missedButton->Size = System::Drawing::Size(127, 39);
			this->missedButton->TabIndex = 2;
			this->missedButton->Text = L"Missed";
			this->missedButton->UseVisualStyleBackColor = false;
			this->missedButton->Click += gcnew System::EventHandler(this, &GUI::executeMissed);
			// 
			// homeButton
			// 
			this->homeButton->BackColor = System::Drawing::Color::SteelBlue;
			this->homeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->homeButton->Location = System::Drawing::Point(196, 310);
			this->homeButton->Name = L"homeButton";
			this->homeButton->Size = System::Drawing::Size(127, 39);
			this->homeButton->TabIndex = 3;
			this->homeButton->Text = L"Home";
			this->homeButton->UseVisualStyleBackColor = false;
			this->homeButton->Click += gcnew System::EventHandler(this, &GUI::executeHome);
			// 
			// upcomingButton
			// 
			this->upcomingButton->BackColor = System::Drawing::Color::SteelBlue;
			this->upcomingButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->upcomingButton->Location = System::Drawing::Point(329, 309);
			this->upcomingButton->Name = L"upcomingButton";
			this->upcomingButton->Size = System::Drawing::Size(126, 39);
			this->upcomingButton->TabIndex = 4;
			this->upcomingButton->Text = L"Upcoming";
			this->upcomingButton->UseVisualStyleBackColor = false;
			this->upcomingButton->Click += gcnew System::EventHandler(this, &GUI::executeUpcoming);
			// 
			// status
			// 
			this->status->AutoSize = true;
			this->status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
			this->status->Location = System::Drawing::Point(7, 383);
			this->status->Name = L"status";
			this->status->Size = System::Drawing::Size(169, 16);
			this->status->TabIndex = 5;
			this->status->Text = L"Type \'help\' for the Help List";
			// 
			// GUI
			// 
			this->ClientSize = System::Drawing::Size(518, 457);
			this->Controls->Add(this->status);
			this->Controls->Add(this->upcomingButton);
			this->Controls->Add(this->homeButton);
			this->Controls->Add(this->missedButton);
			this->Controls->Add(this->userInput);
			this->Controls->Add(this->displayWindow);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"GUI";
			this->Text = L"Planner4Life";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//@author A0111314A

		/************************************************************************************************

		Initialization

		************************************************************************************************/
		//Function to initialize beginning state of Planner4Life to home screen with loadFile prompt
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
		string strStatus = plannerLogic->displayStatus();

		executeHome(sender, e);
		status->Text = gcnew String(strStatus.c_str());
		missedAlertCheck();
	}

			 /************************************************************************************************

			 GUI control functions

			 ************************************************************************************************/

			 //Handler function that takes in user input and directs it to the different Planner operations
	private: System::Void userInput_Process(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		string searchCheck, clearCommand;
		String^ input = userInput->Text;

		searchCheck = msclr::interop::marshal_as<std::string>(input);

		if (e->KeyCode == Keys::Enter) {
			e->Handled = true;

			if (input == COMMAND_HOME) {
				executeHome(sender, e);
			}
			else if (input == COMMAND_MISSED) {
				executeMissed(sender, e);
			}
			else if (input == COMMAND_UPCOMING) {
				executeUpcoming(sender, e);
			}
			else if (input == COMMAND_HELP) {
				executeHelp();
			}
			else if (input == COMMAND_SHOW_DONE) {
				executeDone();
			}
			else if (input == COMMAND_ALL) {
				executeAll();
			}
			else if (input == COMMAND_EXIT) {
				executeExit();
			}
			else if (input == COMMAND_CLEAR) {
				activateCleartrigger();
			}
			else if ((input == COMMAND_Y || input == COMMAND_N || input == COMMAND_y || input == COMMAND_n) && clearTrigger == true) {
				executeClear();
			}
			else if (searchCheck.find("search") != string::npos) {
				executeSearch();
			}
			else {
				processInput(input, currentView);
			}

			userInput->Text = "";
		}
	}

			 // Parent function to take in all other user input, pass to Logic and return display and user prompt. All user input goes through 
			 // this function, but some specific commads (ie search, show done) require setup of UI state before processing. Their functions 
			 // are listed below
	private: System::Void processInput(String^ managedInput, String^ managedView) {
		String^ StrDisplay;
		String^ StrStatus;
		string unmanagedInput = msclr::interop::marshal_as<std::string>(managedInput);
		string unmanagedView = msclr::interop::marshal_as<std::string>(managedView);

		plannerLogic->processUserInput(unmanagedInput, unmanagedView);
		missedAlertCheck();

		string strDisplay = plannerLogic->displayContent();
		string strStatus = plannerLogic->displayStatus();

		StrDisplay = gcnew String(strDisplay.c_str());
		displayWindow->Text = StrDisplay;
		StrStatus = gcnew String(strStatus.c_str());
		status->Text = StrStatus;
	}

			 //Function to execute 'help' command'
	private: System::Void executeHelp() {
		currentView = VIEWTYPE_HELP;
		processInput(userInput->Text, currentView);
		colourSwitch(currentView);
	}

			 //Function to execute 'show done' command
	private: System::Void executeDone() {
		currentView = VIEWTYPE_DONE;
		processInput(userInput->Text, currentView);
		colourSwitch(currentView);
	}

			 // Function to execute 'all' command
	private: System::Void executeAll() {
		currentView = VIEWTYPE_ALL;
		processInput(userInput->Text, currentView);
		colourSwitch(currentView);
	}

			 //Function to execute 'exit' command
	private: System::Void executeExit() {
		Application::Exit();
	}

			 //Function to set up preliminary action for 'clear' operation - warns user and sets the UI state to allow 'clear' command
	private: System::Void activateCleartrigger() {
		status->Text = STATUS_CLEAR_PROMPT;
		clearTrigger = true;
	}

			 //Function to execute 'clear' operation. Thereafter resets UI state to disallow immediate 'clear' on command. 
	private: System::Void executeClear() {
		currentView = VIEWTYPE_HOME;
		switchView(currentView);

		String^ StrDecision = "clear ";
		StrDecision = StrDecision + userInput->Text;

		processInput(StrDecision, currentView);
		clearTrigger = false;
	}

			 //Function to execute 'search' operation
	private: System::Void executeSearch() {
		currentView = VIEWTYPE_SEARCH;
		processInput(userInput->Text, currentView);
		colourSwitch(currentView);
	}

			 /************************************************************************************************

			 GUI view functions

			 ************************************************************************************************/

			 //Function to control the colour of buttons depending on the view type. Views that are not Home, Upcoming or Missed
			 // are not specially highlighted.
	private: System::Void colourSwitch(String^ currentView) {
		if (currentView == VIEWTYPE_HOME) {
			homeButton->BackColor = Color::LightSkyBlue;
			missedButton->BackColor = Color::SteelBlue;
			upcomingButton->BackColor = Color::SteelBlue;
		}
		else if (currentView == VIEWTYPE_UPCOMING) {
			upcomingButton->BackColor = Color::LightSkyBlue;
			missedButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
		else if (currentView == VIEWTYPE_MISSED) {
			missedButton->BackColor = Color::LightSkyBlue;
			upcomingButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
		else {
			missedButton->BackColor = Color::SteelBlue;
			upcomingButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
	}

			 //Function to check if there are any missed tasks. If there are, "Missed" button text becomes red to alert user
	private: System::Void missedAlertCheck(){
		bool areMissedTasks = plannerLogic->checkMissedStatus();

		if (areMissedTasks){
			missedButton->ForeColor = Color::IndianRed;
		}
		else{
			missedButton->ForeColor = SystemColors::ControlText;
		}
	}

			 //Function to switch the view type of the GUI between Home, Upcoming and Missed.
	private: System::Void switchView(String^ viewType) {
		string unmanagedView = msclr::interop::marshal_as<std::string>(viewType);

		plannerLogic->updateDisplay(unmanagedView);

		string strDisplay = plannerLogic->displayContent();
		displayWindow->Text = gcnew String(strDisplay.c_str());
		colourSwitch(currentView);
	}

			 //Function to execute view change to Home view
	private: System::Void executeHome(System::Object^  sender, System::EventArgs^  e) {
		currentView = VIEWTYPE_HOME;
		switchView(currentView);
		status->Text = VIEWTYPE_HOME;
	}

			 //Function to execute view change to Upcoming view
	private: System::Void executeUpcoming(System::Object^  sender, System::EventArgs^  e) {
		currentView = VIEWTYPE_UPCOMING;
		switchView(currentView);
		status->Text = VIEWTYPE_UPCOMING;
	}

			 //Function to execute view change to Missed view
	private: System::Void executeMissed(System::Object^  sender, System::EventArgs^  e) {
		currentView = VIEWTYPE_MISSED;
		switchView(currentView);
		status->Text = VIEWTYPE_MISSED;
	}
	};
}