#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Interfaces {

	/// <summary>
	/// Displays a loading bar which can be used for virtually anything.
	/// </summary>
	public ref class ProgressPopup : public System::Windows::Forms::Form
	{
	public:
		ProgressPopup(String^ work, String^ desc, int step, int max)
		{
			InitializeComponent();
			this->lblDesc->Text = desc;
			this->lblWork->Text = work;
			if(step != 0 && max != 0) {
				this->progressBar->Value = 1;
				this->progressBar->Step = step;
				this->progressBar->Maximum = max;
			} else {
				this->progressBar->Visible = false;
			}
			counter = 49;
			this->Refresh();
		}
		void ProgressStep() {
			this->progressBar->PerformStep();
			counter++;
			if(counter >= 50) {
				this->Refresh();
				counter = 0;
			}
			if(this->progressBar->Value == this->progressBar->Maximum)
				this->Close();
		}
		void UpdateDesc(String^ desc) {
			this->lblDesc->Text = desc;
			this->Refresh();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ProgressPopup()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblDesc;
	protected: 
	private: System::Windows::Forms::Label^  lblWork;
	private: System::Windows::Forms::ProgressBar^  progressBar;
	private: int counter;

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
			this->lblDesc = (gcnew System::Windows::Forms::Label());
			this->lblWork = (gcnew System::Windows::Forms::Label());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->SuspendLayout();
			// 
			// lblDesc
			// 
			this->lblDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblDesc->Location = System::Drawing::Point(12, 67);
			this->lblDesc->Name = L"lblDesc";
			this->lblDesc->Size = System::Drawing::Size(507, 29);
			this->lblDesc->TabIndex = 5;
			this->lblDesc->Text = L"label1";
			this->lblDesc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblWork
			// 
			this->lblWork->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblWork->Location = System::Drawing::Point(12, 9);
			this->lblWork->Name = L"lblWork";
			this->lblWork->Size = System::Drawing::Size(519, 23);
			this->lblWork->TabIndex = 4;
			this->lblWork->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(15, 35);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(504, 23);
			this->progressBar->TabIndex = 3;
			// 
			// ProgressPopup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(527, 132);
			this->ControlBox = false;
			this->Controls->Add(this->lblDesc);
			this->Controls->Add(this->lblWork);
			this->Controls->Add(this->progressBar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ProgressPopup";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Working...";
			this->TopMost = true;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
