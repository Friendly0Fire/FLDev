#pragma once


namespace Fuser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text::RegularExpressions;
	using namespace System::Collections::Generic;
	using namespace System::Globalization;

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
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::TextBox^  txtHardpoints;
	private: System::Windows::Forms::TextBox^  txtMinTime;
	protected: 

	private: System::Windows::Forms::TextBox^  txtEffects;
	private: System::Windows::Forms::TextBox^  txtMaxTime;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListBox^  lstEffects;
	private: System::Windows::Forms::ListBox^  lstHardpoints;
	private: System::Windows::Forms::TextBox^  txtOutput;


	private: System::Windows::Forms::Button^  btnGenerate;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnLoad;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btnUpdate;
	private: System::Windows::Forms::Button^  btnClear;
	private: System::Windows::Forms::TextBox^  txtGenCount;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;


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
			this->txtHardpoints = (gcnew System::Windows::Forms::TextBox());
			this->txtMinTime = (gcnew System::Windows::Forms::TextBox());
			this->txtEffects = (gcnew System::Windows::Forms::TextBox());
			this->txtMaxTime = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lstEffects = (gcnew System::Windows::Forms::ListBox());
			this->lstHardpoints = (gcnew System::Windows::Forms::ListBox());
			this->txtOutput = (gcnew System::Windows::Forms::TextBox());
			this->btnGenerate = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnLoad = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btnUpdate = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->txtGenCount = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtHardpoints
			// 
			this->txtHardpoints->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtHardpoints->Location = System::Drawing::Point(8, 21);
			this->txtHardpoints->Multiline = true;
			this->txtHardpoints->Name = L"txtHardpoints";
			this->tableLayoutPanel1->SetRowSpan(this->txtHardpoints, 3);
			this->txtHardpoints->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtHardpoints->Size = System::Drawing::Size(148, 530);
			this->txtHardpoints->TabIndex = 0;
			this->txtHardpoints->WordWrap = false;
			// 
			// txtMinTime
			// 
			this->txtMinTime->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtMinTime->Location = System::Drawing::Point(162, 276);
			this->txtMinTime->Name = L"txtMinTime";
			this->txtMinTime->Size = System::Drawing::Size(55, 20);
			this->txtMinTime->TabIndex = 2;
			// 
			// txtEffects
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->txtEffects, 3);
			this->txtEffects->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtEffects->Location = System::Drawing::Point(162, 21);
			this->txtEffects->Multiline = true;
			this->txtEffects->Name = L"txtEffects";
			this->txtEffects->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtEffects->Size = System::Drawing::Size(146, 249);
			this->txtEffects->TabIndex = 4;
			this->txtEffects->WordWrap = false;
			// 
			// txtMaxTime
			// 
			this->txtMaxTime->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtMaxTime->Location = System::Drawing::Point(253, 276);
			this->txtMaxTime->Name = L"txtMaxTime";
			this->txtMaxTime->Size = System::Drawing::Size(55, 20);
			this->txtMaxTime->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(223, 273);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(24, 26);
			this->label1->TabIndex = 6;
			this->label1->Text = L"to";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lstEffects
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->lstEffects, 3);
			this->lstEffects->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lstEffects->FormattingEnabled = true;
			this->lstEffects->Location = System::Drawing::Point(162, 302);
			this->lstEffects->Name = L"lstEffects";
			this->lstEffects->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->lstEffects->Size = System::Drawing::Size(146, 238);
			this->lstEffects->TabIndex = 7;
			// 
			// lstHardpoints
			// 
			this->lstHardpoints->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lstHardpoints->FormattingEnabled = true;
			this->lstHardpoints->Location = System::Drawing::Point(314, 21);
			this->lstHardpoints->Name = L"lstHardpoints";
			this->tableLayoutPanel1->SetRowSpan(this->lstHardpoints, 3);
			this->lstHardpoints->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->lstHardpoints->Size = System::Drawing::Size(148, 524);
			this->lstHardpoints->TabIndex = 8;
			// 
			// txtOutput
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->txtOutput, 3);
			this->txtOutput->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtOutput->Location = System::Drawing::Point(468, 21);
			this->txtOutput->Multiline = true;
			this->txtOutput->Name = L"txtOutput";
			this->txtOutput->ReadOnly = true;
			this->tableLayoutPanel1->SetRowSpan(this->txtOutput, 3);
			this->txtOutput->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtOutput->Size = System::Drawing::Size(308, 530);
			this->txtOutput->TabIndex = 9;
			this->txtOutput->WordWrap = false;
			// 
			// btnGenerate
			// 
			this->btnGenerate->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnGenerate->Location = System::Drawing::Point(468, 557);
			this->btnGenerate->Name = L"btnGenerate";
			this->btnGenerate->Size = System::Drawing::Size(110, 23);
			this->btnGenerate->TabIndex = 10;
			this->btnGenerate->Text = L"Generate";
			this->btnGenerate->UseVisualStyleBackColor = true;
			this->btnGenerate->Click += gcnew System::EventHandler(this, &Main::btnGenerate_Click);
			// 
			// btnSave
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->btnSave, 3);
			this->btnSave->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnSave->Location = System::Drawing::Point(162, 557);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(146, 23);
			this->btnSave->TabIndex = 11;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = true;
			// 
			// btnLoad
			// 
			this->btnLoad->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnLoad->Location = System::Drawing::Point(314, 557);
			this->btnLoad->Name = L"btnLoad";
			this->btnLoad->Size = System::Drawing::Size(148, 23);
			this->btnLoad->TabIndex = 12;
			this->btnLoad->Text = L"Load";
			this->btnLoad->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(8, 5);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(148, 13);
			this->label2->TabIndex = 13;
			this->label2->Text = L"Hardpoints";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->tableLayoutPanel1->SetColumnSpan(this->label3, 3);
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Location = System::Drawing::Point(162, 5);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(146, 13);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Effects";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->tableLayoutPanel1->SetColumnSpan(this->label4, 3);
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Location = System::Drawing::Point(468, 5);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(308, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"Output";
			// 
			// btnUpdate
			// 
			this->btnUpdate->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnUpdate->Location = System::Drawing::Point(8, 557);
			this->btnUpdate->Name = L"btnUpdate";
			this->btnUpdate->Size = System::Drawing::Size(148, 23);
			this->btnUpdate->TabIndex = 16;
			this->btnUpdate->Text = L"Update";
			this->btnUpdate->UseVisualStyleBackColor = true;
			this->btnUpdate->Click += gcnew System::EventHandler(this, &Main::btnUpdate_Click);
			// 
			// btnClear
			// 
			this->btnClear->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnClear->Location = System::Drawing::Point(661, 557);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(115, 23);
			this->btnClear->TabIndex = 17;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &Main::btnClear_Click);
			// 
			// txtGenCount
			// 
			this->txtGenCount->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtGenCount->Location = System::Drawing::Point(584, 557);
			this->txtGenCount->Name = L"txtGenCount";
			this->txtGenCount->Size = System::Drawing::Size(71, 20);
			this->txtGenCount->TabIndex = 18;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 8;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				20)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				8)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				4)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				8)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				20)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				15)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				10)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				15)));
			this->tableLayoutPanel1->Controls->Add(this->txtHardpoints, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->btnClear, 7, 4);
			this->tableLayoutPanel1->Controls->Add(this->txtGenCount, 6, 4);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label4, 5, 0);
			this->tableLayoutPanel1->Controls->Add(this->btnGenerate, 5, 4);
			this->tableLayoutPanel1->Controls->Add(this->btnLoad, 4, 4);
			this->tableLayoutPanel1->Controls->Add(this->lstEffects, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->label3, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->txtMaxTime, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->label1, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->btnSave, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->txtEffects, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->txtMinTime, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->lstHardpoints, 4, 1);
			this->tableLayoutPanel1->Controls->Add(this->txtOutput, 5, 1);
			this->tableLayoutPanel1->Controls->Add(this->btnUpdate, 0, 4);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->Padding = System::Windows::Forms::Padding(5);
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(784, 588);
			this->tableLayoutPanel1->TabIndex = 19;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 588);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"Main";
			this->Text = L"Fuser";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		static Regex^ multiHp = gcnew Regex("^(?<name>[^\\.]*)(?<start>[0-9]{2})\\.\\.(?<end>[0-9]{2})$", RegexOptions::Compiled | RegexOptions::Singleline);
		static Regex^ countHp = gcnew Regex("^(?<name>.*)(?<num>[0-9]{2})$", RegexOptions::Compiled | RegexOptions::Singleline);
	private: System::Void btnUpdate_Click(System::Object^  sender, System::EventArgs^  e) {
				lstEffects->Items->Clear();
				lstHardpoints->Items->Clear();
				
				for each(String^ hp in txtHardpoints->Lines) {
					if(hp->Trim()->Length > 0) {
						if(hp->Contains(".")) {
							Match^ m = multiHp->Match(hp);
							try {
								String^ name = m->Groups["name"]->Value; int start = Int32::Parse(m->Groups["start"]->Value); int end = Int32::Parse(m->Groups["end"]->Value);
								for(int a = start; a <= end; a++)
									lstHardpoints->Items->Add(name + a.ToString("d2"));
							} catch(...) {}
						} else {
							lstHardpoints->Items->Add(hp);
						}
					}
				}
				
				for each(String^ eff in txtEffects->Lines) {
					if(eff->Trim()->Length > 0) {
						lstEffects->Items->Add(eff);
					}
				}
			 }
			 static Random^ rand = gcnew Random();
			 static CultureInfo^ ci = CultureInfo::CreateSpecificCulture("en-US");
private: System::Void btnGenerate_Click(System::Object^  sender, System::EventArgs^  e) {
			if(txtGenCount->Text->Trim()->Length > 0) {
				try {
					int count = Int32::Parse(txtGenCount->Text);
					for(int a = 0; a < count; a++) Generate();
				} catch(...) { Generate(); }
			} else Generate();
		 }
		 void Generate() {
			try {
				double timeFrom = txtMinTime->Text->Trim()->Length > 0 ? Double::Parse(txtMinTime->Text, ci) : 0;
				double timeTo = txtMaxTime->Text->Trim()->Length > 0 ? Double::Parse(txtMaxTime->Text, ci) : 1;
				double time = rand->NextDouble() * (timeTo - timeFrom) + timeFrom;
				
				System::Collections::IList^ lstHp = lstHardpoints->SelectedItems->Count > 0 ? (System::Collections::IList^) lstHardpoints->SelectedItems : (System::Collections::IList^) lstHardpoints->Items;
				System::Collections::IList^ lstEff = lstEffects->SelectedItems->Count > 0 ? (System::Collections::IList^) lstEffects->SelectedItems : (System::Collections::IList^) lstEffects->Items;
				
				int hpStart = rand->Next(0, lstHp->Count-1); int hpCount = rand->Next(0, lstHp->Count-hpStart);
				String^ eff = (String^) lstEff[rand->Next(0, lstEff->Count-1)];
				
				Match^ m = countHp->Match((String^) lstHp[hpStart]);
				String^ name = m->Groups["name"]->Value;
				
				List<String^>^ hps = gcnew List<String^>();
				for(int a = 0; a < hpCount; a++) {
					m = countHp->Match((String^) lstHp[hpStart+a]);
					if(m->Groups["name"]->Value == name)
						hps->Add((String^) lstHp[hpStart+a]);
					else break;
				}
				
				txtOutput->Text += "[start_effect]" + Environment::NewLine +
									"effect = " + eff + Environment::NewLine;
				for each(String^ hp in hps) txtOutput->Text += "hardpoint = " + hp + Environment::NewLine;
				txtOutput->Text += "attached = true" + Environment::NewLine +
									"at_t = " + time.ToString("0.###", ci) + Environment::NewLine + Environment::NewLine;
			} catch(...) { MessageBox::Show("Error!"); }
		 }
private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e) {
			txtOutput->Text = "";
		 }
};
}

