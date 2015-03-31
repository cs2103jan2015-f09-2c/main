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
		Logic* s;
	private: System::Windows::Forms::Label^  prompt;

			 String^ currentView;
			 bool clearTrigger;

	public:
		GUI(void)
		{
			InitializeComponent();
			//Add the constructor code here
			s = new Logic;
			currentView = "Home";
		}

	protected:
		/// Clean up any resources being used.
		~GUI()
		{
			if (components)
			{
				delete components;
				delete s;
				delete currentView;
			}
		}
	private: System::Windows::Forms::TextBox^  displayWindow;
	private: System::Windows::Forms::TextBox^  userInput;
	private: System::Windows::Forms::Button^  missedButton;
	private: System::Windows::Forms::Button^  upcomingButton;
	private: System::Windows::Forms::Button^  homeButton;

	private:
		/// Required designer variable.
		System::ComponentModel::Container ^components;

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
				L"add <task description>; date <start date> to <end date>; time <start time> to <end time>",
					L"delete <index number>", 
					L"edit <task index >: <key in new task in 'add' format>", 
					L"clear", 
					L"exit", 
					L"search <target word>",
					L"undo", 
					L"help"
			});
			this->userInput->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->userInput->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->userInput->Location = System::Drawing::Point(10, 363);
			this->userInput->Name = L"userInput";
			this->userInput->Size = System::Drawing::Size(339, 20);
			this->userInput->TabIndex = 1;
			this->userInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::userInput_KeyDown);
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

		private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
		}

		private: System::Void GUI_Load_1(System::Object^  sender, System::EventArgs^  e) {
			homeButton_Click(sender, e);
		}

		/************************************************************************************************

											GUI control functions

		************************************************************************************************/		
		private: System::Void userInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			string searchCheck;

			searchCheck = msclr::interop::marshal_as<std::string>(userInput->Text);

			if (e->KeyCode == Keys::Enter) {
				e->Handled = true;

				if (userInput->Text == "home") {
					homeButton_Click(sender, e);
				}
				else if (userInput->Text == "missed") {
					missedButton_Click(sender, e);
				}
				else if (userInput->Text == "upcoming") {
					upcomingButton_Click(sender, e);
				}
				else if (userInput->Text == "help") {
					currentView = "Help";
					helpView(currentView);
				}
				else if (userInput->Text == "all") {
					currentView = "All";
					allView(currentView);
				}
				else if (userInput->Text == "exit") {
					Application::Exit();
				}
				else if (userInput->Text == "clear") {
					prompt->Text = "Are you sure? Enter Y to confirm or N to deny";
					clearTrigger = true;
				}
				else if ((userInput->Text == "Y" || userInput->Text == "N") && clearTrigger == true) {
					processInput(userInput->Text, currentView);
				}
				else {
					//check for search command
					if (searchCheck.find("search") != string::npos) {
						currentView = "Search";
						colourSwitch(currentView);
					}
					processInput(userInput->Text, currentView);
				}

				userInput->Text = "";
			}
		}

		private: System::Void processInput(String^ managedInput, String^ managedView) {
			String^ strOutput;

			string unmanagedInput = msclr::interop::marshal_as<std::string>(managedInput);
			string unmanagedView = msclr::interop::marshal_as<std::string>(managedView);

			s->processUserInput(unmanagedInput, unmanagedView);

			strOutput = gcnew String(s->displayContent().c_str());
			displayWindow->Text = strOutput;
			prompt->Text = gcnew String(s->displayOutcome().c_str());
		}

		 /************************************************************************************************

												 GUI view functions

		 ************************************************************************************************/
		 private: System::Void colourSwitch(String^ currentView) {
			 if (currentView == "Home") {
				 homeButton->BackColor = Color::LightSkyBlue;
				 missedButton->BackColor = Color::SteelBlue;
				 upcomingButton->BackColor = Color::SteelBlue;
			 }
			 else if (currentView == "Upcoming") {
				 upcomingButton->BackColor = Color::LightSkyBlue;
				 missedButton->BackColor = Color::SteelBlue;
				 homeButton->BackColor = Color::SteelBlue;
			 }
			 else if (currentView == "Missed") {
				 missedButton->BackColor = Color::LightSkyBlue;
				 upcomingButton->BackColor = Color::SteelBlue;
				 homeButton->BackColor = Color::SteelBlue;
			 }
			 else if (currentView == "Help" || currentView == "All" || currentView == "Search") {
				 missedButton->BackColor = Color::SteelBlue;
				 upcomingButton->BackColor = Color::SteelBlue;
				 homeButton->BackColor = Color::SteelBlue;
			 }
		 }

		private: System::Void switchView(String^ viewType) {
			string unmanagedView = msclr::interop::marshal_as<std::string>(viewType);
			s->updateDisplay(unmanagedView);
			displayWindow->Text = gcnew String(s->displayContent().c_str());
			colourSwitch(currentView);
		}

		private: System::Void helpView(String^ viewType) {
			s->processUserInput("help", "Help");
			switchView(currentView);
			prompt->Text = gcnew String(s->displayOutcome().c_str());
		}

		private: System::Void allView(String^ viewType) {
			s->processUserInput("all", "All");
			switchView(currentView);
			prompt->Text = gcnew String(s->displayOutcome().c_str());
		}

		private: System::Void homeButton_Click(System::Object^  sender, System::EventArgs^  e) {
			currentView = "Home";
			switchView(currentView);
			prompt->Text = "Home";
		}

		private: System::Void upcomingButton_Click(System::Object^  sender, System::EventArgs^  e) {
			currentView = "Upcoming";
			switchView(currentView);
			prompt->Text = "Upcoming";
		}

		private: System::Void missedButton_Click(System::Object^  sender, System::EventArgs^  e) {
			currentView = "Missed";
			switchView(currentView);
			prompt->Text = "Missed";
		}

	};
}