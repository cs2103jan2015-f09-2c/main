#pragma once
#include "Logic.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <ctime>

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace std;

namespace UI {
	/// Summary for K5GUI
	public ref class K5GUI : public System::Windows::Forms::Form {
	private:
		GUI* s;
	private: System::Windows::Forms::Label^  prompt;

			 String^ currentView;

	public:
		K5GUI(void)
		{
			InitializeComponent();
			//Add the constructor code here
			s = new GUI;
			currentView = "Home";
		}

	protected:
		/// Clean up any resources being used.
		~K5GUI()
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
			this->userInput->Location = System::Drawing::Point(10, 363);
			this->userInput->Name = L"userInput";
			this->userInput->Size = System::Drawing::Size(339, 20);
			this->userInput->TabIndex = 1;
			this->userInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &K5GUI::userInput_KeyPress);
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
			this->missedButton->Click += gcnew System::EventHandler(this, &K5GUI::missedButton_Click);
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
			this->homeButton->Click += gcnew System::EventHandler(this, &K5GUI::homeButton_Click);
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
			this->upcomingButton->Click += gcnew System::EventHandler(this, &K5GUI::upcomingButton_Click);
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
			// K5GUI
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
			this->Name = L"K5GUI";
			this->Load += gcnew System::EventHandler(this, &K5GUI::K5GUI_Load_1);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void K5GUI_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void K5GUI_Load_1(System::Object^  sender, System::EventArgs^  e) {
		homeButton_Click(sender, e);
	}
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
		else if (currentView == "Help" || currentView == "All") {
			missedButton->BackColor = Color::SteelBlue;
			upcomingButton->BackColor = Color::SteelBlue;
			homeButton->BackColor = Color::SteelBlue;
		}
	}
	private: System::Void switchView(String^ viewType) {
		string unmanagedView = msclr::interop::marshal_as<std::string>(viewType);
		s->updateDisplay(unmanagedView);
		displayWindow->Text = gcnew String(s->displayContent().c_str());
	}
			 //switch window
	private: System::Void homeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = "Home";
		switchView(currentView);
		colourSwitch(currentView);
	}
			 //switch window
	private: System::Void upcomingButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = "Upcoming";
		switchView(currentView);
		colourSwitch(currentView);
	}
			 //switch window
	private: System::Void missedButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = "Missed";
		switchView(currentView);
		colourSwitch(currentView);
	}
			 //takes in user input
	private: System::Void userInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		String^ strOutput;

		if (e->KeyChar == (char)13) {
			if (userInput->Text == "home") {
				homeButton_Click(sender, e);
			}
			else if (userInput->Text == "missed") {
				missedButton_Click(sender, e);
			}
			else if (userInput->Text == "upcoming") {
				upcomingButton_Click(sender, e);
			}
			else if (userInput->Text == "exit") {
				Application::Exit();
			}
			else if (userInput->Text == "help") {
				currentView = "Help";
				s->processUserInput("help", "Help");
				displayWindow->Text = gcnew String(s->displayContent().c_str());
				colourSwitch(currentView);
			}
			else if (userInput->Text == "all") {
				currentView = "All";
				s->processUserInput("all", "All");
				displayWindow->Text = gcnew String(s->displayContent().c_str());
				colourSwitch(currentView);
			}
			else {
				String^ managedInput = userInput->Text;
				string unmanagedInput = msclr::interop::marshal_as<std::string>(managedInput);

				String^ managedView = currentView;
				string unmanagedView = msclr::interop::marshal_as<std::string>(managedView);

				s->processUserInput(unmanagedInput, unmanagedView);
				strOutput = gcnew String(s->displayContent().c_str());
				displayWindow->Text = strOutput;
				prompt->Text = gcnew String(s->displayOutcome().c_str());
			}

			userInput->Text = "";
		}
	}
	};
}