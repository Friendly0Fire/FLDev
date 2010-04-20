#pragma once

namespace LogReader {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Utilities;
	using namespace System::IO;
	using namespace System::Text::RegularExpressions;

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

			errors = gcnew List<String^>();
			parsedErrs = gcnew List<Error^>();
			logView->ListViewItemSorter = gcnew ListViewItemComparer();
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


	private: System::Windows::Forms::SplitContainer^  splitMain;
	protected: 


	private: System::Windows::Forms::RadioButton^  radioTextMode;
	private: System::Windows::Forms::RadioButton^  radioListMode;
	private: System::Windows::Forms::CheckBox^  checkDuplicates;

	private: CompositeStatusBar^ mainStatus;
	private: System::Windows::Forms::ColumnHeader^  colMessage;
	private: System::Windows::Forms::ColumnHeader^  colType;
	private: System::Windows::Forms::ColumnHeader^  colCount;
	private: System::ComponentModel::BackgroundWorker^  backgroundLoad;






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
			this->colMessage = (gcnew System::Windows::Forms::ColumnHeader());
			this->colType = (gcnew System::Windows::Forms::ColumnHeader());
			this->colCount = (gcnew System::Windows::Forms::ColumnHeader());
			this->splitMain = (gcnew System::Windows::Forms::SplitContainer());
			this->radioTextMode = (gcnew System::Windows::Forms::RadioButton());
			this->radioListMode = (gcnew System::Windows::Forms::RadioButton());
			this->checkDuplicates = (gcnew System::Windows::Forms::CheckBox());
			this->backgroundLoad = (gcnew System::ComponentModel::BackgroundWorker());
			this->splitMain->Panel2->SuspendLayout();
			this->splitMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// logView
			// 
			this->logView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->colMessage, this->colType, 
				this->colCount});
			this->logView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->logView->FullRowSelect = true;
			this->logView->GridLines = true;
			this->logView->Location = System::Drawing::Point(0, 63);
			this->logView->Margin = System::Windows::Forms::Padding(5);
			this->logView->Name = L"logView";
			this->logView->ShowGroups = false;
			this->logView->Size = System::Drawing::Size(784, 499);
			this->logView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->logView->TabIndex = 0;
			this->logView->UseCompatibleStateImageBehavior = false;
			this->logView->View = System::Windows::Forms::View::Details;
			this->logView->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &Main::logView_ColumnClick);
			// 
			// colMessage
			// 
			this->colMessage->DisplayIndex = 2;
			this->colMessage->Text = L"Message";
			this->colMessage->Width = 500;
			// 
			// colType
			// 
			this->colType->DisplayIndex = 0;
			this->colType->Text = L"Type";
			this->colType->Width = 100;
			// 
			// colCount
			// 
			this->colCount->DisplayIndex = 1;
			this->colCount->Text = L"Count";
			// 
			// splitMain
			// 
			this->splitMain->Dock = System::Windows::Forms::DockStyle::Top;
			this->splitMain->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitMain->IsSplitterFixed = true;
			this->splitMain->Location = System::Drawing::Point(0, 0);
			this->splitMain->Margin = System::Windows::Forms::Padding(0, 0, 0, 6);
			this->splitMain->Name = L"splitMain";
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
			// backgroundLoad
			// 
			this->backgroundLoad->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Main::backgroundLoad_DoWork);
			this->backgroundLoad->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::backgroundLoad_RunWorkerCompleted);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->logView);
			this->Controls->Add(this->splitMain);
			this->Name = L"Main";
			this->Text = L"Freelancer Developer - Log Reader";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->splitMain->Panel2->ResumeLayout(false);
			this->splitMain->Panel2->PerformLayout();
			this->splitMain->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		private: static array<String^>^ fileLocations = gcnew array<String^>
				 {
					 Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData), "Freelancer\\FLSpew.txt")
				 };
				 List<String^>^ errors;
				 List<Error^>^ parsedErrs;

	private: System::Void Main_Load(System::Object^  sender, System::EventArgs^  e) {
				 mainStatus->addStatusText("Parsing error logs", -1, true, true);

				 backgroundLoad->RunWorkerAsync();
			 }

			 void LoadFile(String^ path) {
				 StreamReader^ sr = gcnew StreamReader(path);
				 String^ line;
				 while(line = sr->ReadLine())
					 errors->Add(line);
			 }

			 void ParseErrors() {
				 for each(String^ l in errors) {
					 try {
						 Error^ n = gcnew Error(l);
						 if(n->Message != "") {
							 bool exists = false;
							 for each(Error^ err in parsedErrs) {
								 if(err->Equals(n)) {
									 exists = true;
									 err->Increment();
									 break;
								 }
							 }
							 if(!exists)
								 parsedErrs->Add(n);
						 }
					 } catch(...) {}
				 }
			 }

			 void PopulateList() {
				 logView->Items->Clear();
				 logView->BeginUpdate();
				 for each(Error^ e in parsedErrs) {
					 ListViewItem^ i = gcnew ListViewItem(e->Message);
					 switch(e->Type) {
						 case ErrorType::Error:
							 i->SubItems->Add("Error");
							 i->ForeColor = Color::DarkRed;
							 i->Font = gcnew System::Drawing::Font(i->Font, System::Drawing::FontStyle::Bold);
							 break;
						 case ErrorType::Warning:
							 i->SubItems->Add("Warning");
							 i->ForeColor = Color::FromArgb(255, 212,117,0);
							 i->Font = gcnew System::Drawing::Font(i->Font, System::Drawing::FontStyle::Bold);
							 break;
						 case ErrorType::Notice:
							 i->SubItems->Add("Notice");
							 break;
						 default:
							 i->SubItems->Add("Unknown");
							 i->ForeColor = Color::DarkSlateBlue;
					 }
					 i->SubItems->Add("" + e->Count);
					 logView->Items->Add(i);
				 }
				 logView->EndUpdate();
			 }
	private: System::Void backgroundLoad_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 for each(String^ p in fileLocations) {
					 if(File::Exists(p)) {
						 LoadFile(p);
					 }
				 }

				 ParseErrors();
			 }
private: System::Void backgroundLoad_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 PopulateList();
			 mainStatus->removeStatusText("Parsing error logs");
			 mainStatus->addStatusText("Parsed logs", 5, false, true);
		 }
private: System::Void logView_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
			 bool numeric = e->Column == 2 ? true : false;
			 bool desc = true;
			 try {
				 ListViewItemComparer^ c = (ListViewItemComparer^) logView->ListViewItemSorter;
				 if(e->Column == c->Column)
					 desc = !c->Descending;
			 } catch(...) {} finally {
				 logView->ListViewItemSorter = gcnew ListViewItemComparer(e->Column, numeric, desc);

				 logView->Sort();
			 }
		 }
};
}

