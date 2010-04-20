#pragma once


namespace LogReader {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Utilities;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();
			mainStatus = gcnew CompositeStatusBar();
			this->Controls->Add(this->mainStatus);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  logView;
	protected: 

	private: System::Windows::Forms::CheckedListBox^  listLogs;
	private: System::Windows::Forms::SplitContainer^  splitMain;
	protected: 


	private: System::Windows::Forms::RadioButton^  radioTextMode;
	private: System::Windows::Forms::RadioButton^  radioListMode;
	private: System::Windows::Forms::CheckBox^  checkDuplicates;

	private: CompositeStatusBar^ mainStatus;






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
			this->logView = (gcnew System::Windows::Forms::ListView());
			this->listLogs = (gcnew System::Windows::Forms::CheckedListBox());
			this->splitMain = (gcnew System::Windows::Forms::SplitContainer());
			this->radioTextMode = (gcnew System::Windows::Forms::RadioButton());
			this->radioListMode = (gcnew System::Windows::Forms::RadioButton());
			this->checkDuplicates = (gcnew System::Windows::Forms::CheckBox());
			this->splitMain->Panel1->SuspendLayout();
			this->splitMain->Panel2->SuspendLayout();
			this->splitMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// logView
			// 
			this->logView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->logView->Location = System::Drawing::Point(0, 0);
			this->logView->Margin = System::Windows::Forms::Padding(5);
			this->logView->Name = L"logView";
			this->logView->Size = System::Drawing::Size(784, 562);
			this->logView->TabIndex = 0;
			this->logView->UseCompatibleStateImageBehavior = false;
			// 
			// listLogs
			// 
			this->listLogs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listLogs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listLogs->FormattingEnabled = true;
			this->listLogs->Location = System::Drawing::Point(0, 0);
			this->listLogs->Margin = System::Windows::Forms::Padding(0);
			this->listLogs->Name = L"listLogs";
			this->listLogs->Size = System::Drawing::Size(604, 62);
			this->listLogs->Sorted = true;
			this->listLogs->TabIndex = 1;
			// 
			// splitMain
			// 
			this->splitMain->Dock = System::Windows::Forms::DockStyle::Top;
			this->splitMain->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitMain->IsSplitterFixed = true;
			this->splitMain->Location = System::Drawing::Point(0, 0);
			this->splitMain->Margin = System::Windows::Forms::Padding(0, 0, 0, 6);
			this->splitMain->Name = L"splitMain";
			// 
			// splitMain.Panel1
			// 
			this->splitMain->Panel1->Controls->Add(this->listLogs);
			this->splitMain->Panel1MinSize = 150;
			// 
			// splitMain.Panel2
			// 
			this->splitMain->Panel2->Controls->Add(this->radioTextMode);
			this->splitMain->Panel2->Controls->Add(this->radioListMode);
			this->splitMain->Panel2->Controls->Add(this->checkDuplicates);
			this->splitMain->Size = System::Drawing::Size(784, 63);
			this->splitMain->SplitterDistance = 604;
			this->splitMain->TabIndex = 2;
			// 
			// radioTextMode
			// 
			this->radioTextMode->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->radioTextMode->AutoSize = true;
			this->radioTextMode->Location = System::Drawing::Point(19, 12);
			this->radioTextMode->Name = L"radioTextMode";
			this->radioTextMode->Size = System::Drawing::Size(72, 17);
			this->radioTextMode->TabIndex = 3;
			this->radioTextMode->TabStop = true;
			this->radioTextMode->Text = L"Text View";
			this->radioTextMode->UseVisualStyleBackColor = true;
			// 
			// radioListMode
			// 
			this->radioListMode->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->radioListMode->AutoSize = true;
			this->radioListMode->Location = System::Drawing::Point(97, 12);
			this->radioListMode->Name = L"radioListMode";
			this->radioListMode->Size = System::Drawing::Size(67, 17);
			this->radioListMode->TabIndex = 2;
			this->radioListMode->TabStop = true;
			this->radioListMode->Text = L"List View";
			this->radioListMode->UseVisualStyleBackColor = true;
			// 
			// checkDuplicates
			// 
			this->checkDuplicates->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkDuplicates->AutoSize = true;
			this->checkDuplicates->Location = System::Drawing::Point(60, 35);
			this->checkDuplicates->Name = L"checkDuplicates";
			this->checkDuplicates->Size = System::Drawing::Size(104, 17);
			this->checkDuplicates->TabIndex = 1;
			this->checkDuplicates->Text = L"Show duplicates";
			this->checkDuplicates->UseVisualStyleBackColor = true;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->splitMain);
			this->Controls->Add(this->logView);
			this->Name = L"Main";
			this->Text = L"Freelancer Developer - Log Reader";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->splitMain->Panel1->ResumeLayout(false);
			this->splitMain->Panel2->ResumeLayout(false);
			this->splitMain->Panel2->PerformLayout();
			this->splitMain->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Main_Load(System::Object^  sender, System::EventArgs^  e) {
				 mainStatus->addStatusText("Parsing error logs", -1, true, true);
			 }
};
}

