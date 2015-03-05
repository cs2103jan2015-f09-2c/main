#pragma once
#include "GUI.h"
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace std;

string currentView;

namespace UI {
	/// <summary>
	/// Summary for K5GUI
	/// </summary>
	public ref class K5GUI : public System::Windows::Forms::Form {
	private: 
		GUI* s;
		

	public:
		
		K5GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			s = new GUI;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~K5GUI()
		{
			if (components)
			{
				delete components;
				delete s;
			}
		}
	private: System::Windows::Forms::TextBox^  displayWindow;
	private: System::Windows::Forms::TextBox^  userInput;
	private: System::Windows::Forms::Button^  missedButton;
	private: System::Windows::Forms::Button^  upcomingButton;
	private: System::Windows::Forms::Button^  homeButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->displayWindow = (gcnew System::Windows::Forms::TextBox());
			this->userInput = (gcnew System::Windows::Forms::TextBox());
			this->missedButton = (gcnew System::Windows::Forms::Button());
			this->homeButton = (gcnew System::Windows::Forms::Button());
			this->upcomingButton = (gcnew System::Windows::Forms::Button());
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
			this->missedButton->BackColor = System::Drawing::SystemColors::Control;
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
			this->homeButton->Location = System::Drawing::Point(125, 320);
			this->homeButton->Name = L"homeButton";
			this->homeButton->Size = System::Drawing::Size(109, 28);
			this->homeButton->TabIndex = 3;
			this->homeButton->Text = L"Home";
			this->homeButton->UseVisualStyleBackColor = true;
			this->homeButton->Click += gcnew System::EventHandler(this, &K5GUI::homeButton_Click);
			// 
			// upcomingButton
			// 
			this->upcomingButton->Location = System::Drawing::Point(240, 320);
			this->upcomingButton->Name = L"upcomingButton";
			this->upcomingButton->Size = System::Drawing::Size(109, 28);
			this->upcomingButton->TabIndex = 4;
			this->upcomingButton->Text = L"Upcoming";
			this->upcomingButton->UseVisualStyleBackColor = true;
			this->upcomingButton->Click += gcnew System::EventHandler(this, &K5GUI::upcomingButton_Click);
			// 
			// K5GUI
			// 
			this->ClientSize = System::Drawing::Size(361, 410);
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
	}
	//switch window
	private: System::Void homeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		currentView = "Home";
		String^ strHome = gcnew String(s->switchView("Home").c_str());
		
		displayWindow->Text = strHome;
	}
	//switch window
	private: System::Void upcomingButton_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ strUpcoming = gcnew String(s->switchView("Upcoming").c_str());
		currentView = "Upcoming";
		displayWindow->Text = strUpcoming;
	}
	//switch window
	private: System::Void missedButton_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ strMissed = gcnew String(s->switchView("Missed").c_str());
		currentView = "Missed";
		displayWindow->Text = strMissed;
	}
	//takes in user input
	private: System::Void userInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		String^ managedInput;
		String^ strOutput;
		//if function detects enter keypress
		if (e->KeyChar == (char)13) {
			//convert String^ to std::string, pass to processUserInput and print result in displayWindow
			managedInput = userInput->Text;
			string unmanagedInput = msclr::interop::marshal_as<std::string>(managedInput);
		
			strOutput = gcnew String(s->processUserInput(unmanagedInput /*,currentView*/).c_str());

			//need to check if strouput is an edit. if yes, userInput->Text = (whatever edit content), then loop back to start. else, perform next two lines
			displayWindow->Text = strOutput;
			userInput->Text = "";
		}
	}
};
}
