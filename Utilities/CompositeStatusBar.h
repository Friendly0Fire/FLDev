#pragma once

#include "Misc.h"

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace Utilities {
	public ref class CompositeStatusBar : System::Windows::Forms::StatusStrip {
	private: System::Windows::Forms::ToolStripProgressBar^  mainProgressBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  mainStatusText;
	private: System::Windows::Forms::Timer^  statusBarTimer;
	private: System::ComponentModel::IContainer^  components;
			 List<ProcessBarItem^>^ progressStatusTexts;

	public:
		CompositeStatusBar() {
			progressStatusTexts = gcnew List<ProcessBarItem^>();

			this->components = (gcnew System::ComponentModel::Container());
			this->mainProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->mainStatusText = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->statusBarTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();

			// 
			// mainStatusStrip
			// 
			this->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->mainProgressBar, 
				this->mainStatusText});
			this->Location = System::Drawing::Point(0, 540);
			this->Name = L"mainStatusStrip";
			this->Size = System::Drawing::Size(784, 22);
			this->TabIndex = 7;
			this->Text = L"statusStrip1";

			// 
			// mainProgressBar
			// 
			this->mainProgressBar->MarqueeAnimationSpeed = 0;
			this->mainProgressBar->Name = L"mainProgressBar";
			this->mainProgressBar->Size = System::Drawing::Size(200, 16);
			this->mainProgressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			// 
			// mainStatusText
			// 
			this->mainStatusText->Name = L"mainStatusText";
			this->mainStatusText->Size = System::Drawing::Size(567, 17);
			this->mainStatusText->Spring = true;
			this->mainStatusText->Text = L"Ready";
			this->mainStatusText->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// statusBarTimer
			// 
			this->statusBarTimer->Enabled = true;
			this->statusBarTimer->Interval = 1000;
			this->statusBarTimer->Tick += gcnew System::EventHandler(this, &CompositeStatusBar::statusBarTimer_Tick);

			this->ResumeLayout();
		}

		void addStatusText(String^ text, int ticks, bool progress) {
			 addStatusText(text, ticks, progress, true);
		 }
		 void addStatusText(String^ text, int ticks, bool progress, bool duplicate) {
			 if(duplicate) {
				 for each(ProcessBarItem^ t in progressStatusTexts) {
					 if(text->Equals(t))
						 return updateStatusText();
				 }
			 }
			 progressStatusTexts->Add(gcnew ProcessBarItem(text, ticks, progress));
			 updateStatusText();
		 }

		 void removeStatusText(String^ text) {
			 for each(ProcessBarItem^ t in progressStatusTexts) {
				 if(t->Equals(text)) {
					 progressStatusTexts->Remove(t);
					 break;
				 }
			 }
			 updateStatusText();
		 }

		 void updateStatusText() {
			 bool progress = false;
			 for each(ProcessBarItem^ t in progressStatusTexts) {
				 if(t->Progress) {
					 progress = true;
					 break;
				 }
			 }

			 if(progress) {
				 if(mainProgressBar->Style != ProgressBarStyle::Marquee || mainProgressBar->MarqueeAnimationSpeed != 20) {
					 mainProgressBar->Style = ProgressBarStyle::Marquee;
					 mainProgressBar->MarqueeAnimationSpeed = 20;
				 }
			 } else {
				 mainProgressBar->MarqueeAnimationSpeed = 0;
				 mainProgressBar->Style = ProgressBarStyle::Blocks;
			 }

			 mainStatusText->Text = "";
			 if(progressStatusTexts->Count > 0) {
				 for each(ProcessBarItem^ t in progressStatusTexts)
					mainStatusText->Text += t + ", ";
				 mainStatusText->Text = mainStatusText->Text->Remove(mainStatusText->Text->Length-2);
				 if(progress)
					mainStatusText->Text += "...";
				 else
					 mainStatusText->Text += ".";
			 } else
				 mainStatusText->Text = "Ready";
		 }

		 private: System::Void statusBarTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 updateStatusText();
			 List<ProcessBarItem^>^ remove = gcnew List<ProcessBarItem^>();
			 for each(ProcessBarItem^ t in progressStatusTexts) {
				 t->Decrement();
				 if(t->TimeLeft == 0) remove->Add(t);
			 }
			 for each(ProcessBarItem^ t in remove)
				 progressStatusTexts->Remove(t);
		 }

	protected:
		~CompositeStatusBar()
		{
			if (components)
			{
				delete components;
			}
		}
	};
}