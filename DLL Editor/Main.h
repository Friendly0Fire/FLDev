#pragma once


namespace DLLEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace Interfaces;

	/// <summary>
	/// Summary for Main
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

			progressStatusTexts = gcnew List<ProcessBarItem^>();
			this->backgroundWorkerFLINI->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::backgroundWorkerFLINI_RunWorkerCompleted);
			this->backgroundWorkerApply->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::backgroundWorkerApply_RunWorkerCompleted);
			this->lstDLLExplorer->MouseWheel += gcnew MouseEventHandler(this, &Main::lstDLLExplorer_MouseWheel);

			activeDll = -1;
			RefreshList(lstScroll->Value, 0);
			oldScroll = 0;
			changingSelectedIDS = false;
			currentEntry = -1;
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
	private: System::Windows::Forms::TabControl^  mainTab;
	private: System::Windows::Forms::TabPage^  tabSettings;
	private: System::Windows::Forms::TabPage^  editTab;
	protected: 


	private: System::Windows::Forms::Button^  btnBrowseINI;

	private: System::Windows::Forms::TextBox^  txtINIPath;


	private: System::Windows::Forms::GroupBox^  grpDLLs;
	private: System::Windows::Forms::Button^  btnResetDLLs;


	private: System::Windows::Forms::Button^  btnBrowseDLL;

	private: System::Windows::Forms::ListView^  lstDLLs;

	private: System::Windows::Forms::GroupBox^  grpFLINI;
	private: System::Windows::Forms::GroupBox^  grpOut;
	private: System::Windows::Forms::Button^  btnOutOpen;



	private: System::Windows::Forms::TextBox^  txtOutPath;
	private: System::Windows::Forms::Button^  btnBrowseOut;
	private: System::Windows::Forms::Button^  btnApply;



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  btnReloadDLL;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ColumnHeader^  colDLL;
	private: System::Windows::Forms::ColumnHeader^  colStatus;
	private: System::Windows::Forms::HelpProvider^  helpProvider;
	private: System::Windows::Forms::Button^  btnReloadINI;
	private: System::Windows::Forms::OpenFileDialog^  openFLINI;
	private: System::Windows::Forms::ColumnHeader^  colDLLAbs;
	private: System::Windows::Forms::TextBox^  txtSelectedDLLPath;
	private: System::Windows::Forms::OpenFileDialog^  openDLL;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerFLINI;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerApply;
	private: System::Windows::Forms::StatusStrip^  mainStatusStrip;
	private: System::Windows::Forms::ToolStripProgressBar^  mainProgressBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  mainStatusText;

	private:
		int										oldScroll,
												activeDll;
		System::Windows::Forms::ListView^			lstDLLExplorer;
		System::Windows::Forms::ColumnHeader^	lstDLLExplorerID;
		System::Windows::Forms::ColumnHeader^	lstDLLExplorerLID;
		System::Windows::Forms::ColumnHeader^	lstDLLExplorerType;
		System::Windows::Forms::ColumnHeader^	lstDLLExplorerPreview;
		System::Windows::Forms::VScrollBar^  lstScroll;
	private: System::Windows::Forms::GroupBox^  grpDLLExplorer;
	private: System::Windows::Forms::ComboBox^  comboDLLExplorer;
	private: System::Windows::Forms::CheckBox^  chkDLLExplorerShowEmpty;
	private: System::Windows::Forms::SplitContainer^  splitDLLEditor;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::RadioButton^  radioName;
	private: System::Windows::Forms::RadioButton^  radioInfocard;
	private: System::Windows::Forms::TextBox^  txtEntry;



	private: System::Windows::Forms::ComboBox^  comboIDS;
	private: System::Windows::Forms::ToolStrip^  toolsEntry;
	private: System::Windows::Forms::RadioButton^  radioSInfocard;
private: System::Windows::Forms::Label^  lblIDSInfo;


private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::TextBox^  txtLocalIDS;
private: System::Windows::Forms::Timer^  undoTimer;
private: System::Windows::Forms::ToolStripButton^  entryUndo;
private: System::Windows::Forms::ToolStripButton^  entryRedo;
private: System::Windows::Forms::Timer^  statusBarTimer;
private: System::ComponentModel::IContainer^  components;








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->mainTab = (gcnew System::Windows::Forms::TabControl());
			this->tabSettings = (gcnew System::Windows::Forms::TabPage());
			this->btnApply = (gcnew System::Windows::Forms::Button());
			this->grpOut = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnOutOpen = (gcnew System::Windows::Forms::Button());
			this->txtOutPath = (gcnew System::Windows::Forms::TextBox());
			this->btnBrowseOut = (gcnew System::Windows::Forms::Button());
			this->grpDLLs = (gcnew System::Windows::Forms::GroupBox());
			this->txtSelectedDLLPath = (gcnew System::Windows::Forms::TextBox());
			this->btnReloadDLL = (gcnew System::Windows::Forms::Button());
			this->btnResetDLLs = (gcnew System::Windows::Forms::Button());
			this->btnBrowseDLL = (gcnew System::Windows::Forms::Button());
			this->lstDLLs = (gcnew System::Windows::Forms::ListView());
			this->colDLL = (gcnew System::Windows::Forms::ColumnHeader());
			this->colDLLAbs = (gcnew System::Windows::Forms::ColumnHeader());
			this->colStatus = (gcnew System::Windows::Forms::ColumnHeader());
			this->grpFLINI = (gcnew System::Windows::Forms::GroupBox());
			this->btnReloadINI = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtINIPath = (gcnew System::Windows::Forms::TextBox());
			this->btnBrowseINI = (gcnew System::Windows::Forms::Button());
			this->editTab = (gcnew System::Windows::Forms::TabPage());
			this->splitDLLEditor = (gcnew System::Windows::Forms::SplitContainer());
			this->grpDLLExplorer = (gcnew System::Windows::Forms::GroupBox());
			this->lstDLLExplorer = (gcnew System::Windows::Forms::ListView());
			this->lstDLLExplorerID = (gcnew System::Windows::Forms::ColumnHeader());
			this->lstDLLExplorerLID = (gcnew System::Windows::Forms::ColumnHeader());
			this->lstDLLExplorerType = (gcnew System::Windows::Forms::ColumnHeader());
			this->lstDLLExplorerPreview = (gcnew System::Windows::Forms::ColumnHeader());
			this->lstScroll = (gcnew System::Windows::Forms::VScrollBar());
			this->comboDLLExplorer = (gcnew System::Windows::Forms::ComboBox());
			this->chkDLLExplorerShowEmpty = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->radioSInfocard = (gcnew System::Windows::Forms::RadioButton());
			this->comboIDS = (gcnew System::Windows::Forms::ComboBox());
			this->radioName = (gcnew System::Windows::Forms::RadioButton());
			this->radioInfocard = (gcnew System::Windows::Forms::RadioButton());
			this->txtEntry = (gcnew System::Windows::Forms::TextBox());
			this->toolsEntry = (gcnew System::Windows::Forms::ToolStrip());
			this->entryUndo = (gcnew System::Windows::Forms::ToolStripButton());
			this->entryRedo = (gcnew System::Windows::Forms::ToolStripButton());
			this->lblIDSInfo = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtLocalIDS = (gcnew System::Windows::Forms::TextBox());
			this->helpProvider = (gcnew System::Windows::Forms::HelpProvider());
			this->openFLINI = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openDLL = (gcnew System::Windows::Forms::OpenFileDialog());
			this->backgroundWorkerFLINI = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerApply = (gcnew System::ComponentModel::BackgroundWorker());
			this->mainStatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->mainProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->mainStatusText = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->undoTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusBarTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->mainTab->SuspendLayout();
			this->tabSettings->SuspendLayout();
			this->grpOut->SuspendLayout();
			this->grpDLLs->SuspendLayout();
			this->grpFLINI->SuspendLayout();
			this->editTab->SuspendLayout();
			this->splitDLLEditor->Panel1->SuspendLayout();
			this->splitDLLEditor->Panel2->SuspendLayout();
			this->splitDLLEditor->SuspendLayout();
			this->grpDLLExplorer->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->toolsEntry->SuspendLayout();
			this->mainStatusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainTab
			// 
			this->mainTab->Controls->Add(this->tabSettings);
			this->mainTab->Controls->Add(this->editTab);
			this->mainTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainTab->Location = System::Drawing::Point(0, 0);
			this->mainTab->Name = L"mainTab";
			this->mainTab->SelectedIndex = 0;
			this->mainTab->Size = System::Drawing::Size(784, 540);
			this->mainTab->TabIndex = 0;
			// 
			// tabSettings
			// 
			this->tabSettings->BackColor = System::Drawing::SystemColors::Control;
			this->tabSettings->Controls->Add(this->btnApply);
			this->tabSettings->Controls->Add(this->grpOut);
			this->tabSettings->Controls->Add(this->grpDLLs);
			this->tabSettings->Controls->Add(this->grpFLINI);
			this->tabSettings->Location = System::Drawing::Point(4, 22);
			this->tabSettings->Name = L"tabSettings";
			this->tabSettings->Padding = System::Windows::Forms::Padding(3);
			this->tabSettings->Size = System::Drawing::Size(776, 514);
			this->tabSettings->TabIndex = 0;
			this->tabSettings->Text = L"Primary Settings";
			// 
			// btnApply
			// 
			this->btnApply->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnApply->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnApply->Location = System::Drawing::Point(284, 468);
			this->btnApply->MinimumSize = System::Drawing::Size(100, 25);
			this->btnApply->Name = L"btnApply";
			this->btnApply->Size = System::Drawing::Size(209, 38);
			this->btnApply->TabIndex = 5;
			this->btnApply->Text = L"Apply Changes";
			this->btnApply->UseVisualStyleBackColor = true;
			this->btnApply->Click += gcnew System::EventHandler(this, &Main::btnApply_Click);
			// 
			// grpOut
			// 
			this->grpOut->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpOut->Controls->Add(this->label2);
			this->grpOut->Controls->Add(this->btnOutOpen);
			this->grpOut->Controls->Add(this->txtOutPath);
			this->grpOut->Controls->Add(this->btnBrowseOut);
			this->grpOut->Location = System::Drawing::Point(8, 291);
			this->grpOut->Name = L"grpOut";
			this->grpOut->Size = System::Drawing::Size(760, 98);
			this->grpOut->TabIndex = 4;
			this->grpOut->TabStop = false;
			this->grpOut->Text = L"Output Settings";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Output Path:";
			// 
			// btnOutOpen
			// 
			this->btnOutOpen->Location = System::Drawing::Point(6, 61);
			this->btnOutOpen->Name = L"btnOutOpen";
			this->btnOutOpen->Size = System::Drawing::Size(123, 23);
			this->btnOutOpen->TabIndex = 2;
			this->btnOutOpen->Text = L"Open Directory";
			this->btnOutOpen->UseVisualStyleBackColor = true;
			this->btnOutOpen->Click += gcnew System::EventHandler(this, &Main::btnOutOpen_Click);
			// 
			// txtOutPath
			// 
			this->txtOutPath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutPath->Location = System::Drawing::Point(6, 35);
			this->txtOutPath->Name = L"txtOutPath";
			this->txtOutPath->Size = System::Drawing::Size(619, 20);
			this->txtOutPath->TabIndex = 0;
			// 
			// btnBrowseOut
			// 
			this->btnBrowseOut->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnBrowseOut->Location = System::Drawing::Point(631, 33);
			this->btnBrowseOut->Name = L"btnBrowseOut";
			this->btnBrowseOut->Size = System::Drawing::Size(123, 23);
			this->btnBrowseOut->TabIndex = 1;
			this->btnBrowseOut->Text = L"Browse";
			this->btnBrowseOut->UseVisualStyleBackColor = true;
			// 
			// grpDLLs
			// 
			this->grpDLLs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpDLLs->Controls->Add(this->txtSelectedDLLPath);
			this->grpDLLs->Controls->Add(this->btnReloadDLL);
			this->grpDLLs->Controls->Add(this->btnResetDLLs);
			this->grpDLLs->Controls->Add(this->btnBrowseDLL);
			this->grpDLLs->Controls->Add(this->lstDLLs);
			this->grpDLLs->Location = System::Drawing::Point(8, 84);
			this->grpDLLs->Name = L"grpDLLs";
			this->grpDLLs->Size = System::Drawing::Size(760, 201);
			this->grpDLLs->TabIndex = 4;
			this->grpDLLs->TabStop = false;
			this->grpDLLs->Text = L"DLLs Loaded";
			// 
			// txtSelectedDLLPath
			// 
			this->txtSelectedDLLPath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->helpProvider->SetHelpString(this->txtSelectedDLLPath, L"Browse to the path of your freelancer.ini file. This will allow FLDev to parse th" 
				L"e required DLLs for editing and viewing.");
			this->txtSelectedDLLPath->Location = System::Drawing::Point(6, 163);
			this->txtSelectedDLLPath->Name = L"txtSelectedDLLPath";
			this->helpProvider->SetShowHelp(this->txtSelectedDLLPath, true);
			this->txtSelectedDLLPath->Size = System::Drawing::Size(414, 20);
			this->txtSelectedDLLPath->TabIndex = 7;
			// 
			// btnReloadDLL
			// 
			this->btnReloadDLL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnReloadDLL->Location = System::Drawing::Point(537, 161);
			this->btnReloadDLL->Name = L"btnReloadDLL";
			this->btnReloadDLL->Size = System::Drawing::Size(105, 23);
			this->btnReloadDLL->TabIndex = 5;
			this->btnReloadDLL->Text = L"(Re)Load";
			this->btnReloadDLL->UseVisualStyleBackColor = true;
			this->btnReloadDLL->Click += gcnew System::EventHandler(this, &Main::btnReloadDLL_Click);
			// 
			// btnResetDLLs
			// 
			this->btnResetDLLs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnResetDLLs->Location = System::Drawing::Point(667, 161);
			this->btnResetDLLs->Name = L"btnResetDLLs";
			this->btnResetDLLs->Size = System::Drawing::Size(87, 23);
			this->btnResetDLLs->TabIndex = 4;
			this->btnResetDLLs->Text = L"Reset All";
			this->btnResetDLLs->UseVisualStyleBackColor = true;
			// 
			// btnBrowseDLL
			// 
			this->btnBrowseDLL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnBrowseDLL->Location = System::Drawing::Point(426, 161);
			this->btnBrowseDLL->Name = L"btnBrowseDLL";
			this->btnBrowseDLL->Size = System::Drawing::Size(105, 23);
			this->btnBrowseDLL->TabIndex = 3;
			this->btnBrowseDLL->Text = L"Browse";
			this->btnBrowseDLL->UseVisualStyleBackColor = true;
			this->btnBrowseDLL->Click += gcnew System::EventHandler(this, &Main::btnBrowseDLL_Click);
			// 
			// lstDLLs
			// 
			this->lstDLLs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstDLLs->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->colDLL, this->colDLLAbs, 
				this->colStatus});
			this->lstDLLs->FullRowSelect = true;
			this->lstDLLs->GridLines = true;
			this->lstDLLs->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lstDLLs->HideSelection = false;
			this->lstDLLs->Location = System::Drawing::Point(6, 19);
			this->lstDLLs->MultiSelect = false;
			this->lstDLLs->Name = L"lstDLLs";
			this->lstDLLs->Size = System::Drawing::Size(748, 136);
			this->lstDLLs->TabIndex = 2;
			this->lstDLLs->UseCompatibleStateImageBehavior = false;
			this->lstDLLs->View = System::Windows::Forms::View::Details;
			this->lstDLLs->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::lstDLLs_SelectedIndexChanged);
			// 
			// colDLL
			// 
			this->colDLL->Text = L"DLL Path";
			this->colDLL->Width = 208;
			// 
			// colDLLAbs
			// 
			this->colDLLAbs->Text = L"DLL Absolute Path";
			this->colDLLAbs->Width = 411;
			// 
			// colStatus
			// 
			this->colStatus->Text = L"Status";
			this->colStatus->Width = 118;
			// 
			// grpFLINI
			// 
			this->grpFLINI->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpFLINI->Controls->Add(this->btnReloadINI);
			this->grpFLINI->Controls->Add(this->label1);
			this->grpFLINI->Controls->Add(this->txtINIPath);
			this->grpFLINI->Controls->Add(this->btnBrowseINI);
			this->grpFLINI->Location = System::Drawing::Point(8, 6);
			this->grpFLINI->Name = L"grpFLINI";
			this->grpFLINI->Size = System::Drawing::Size(760, 72);
			this->grpFLINI->TabIndex = 3;
			this->grpFLINI->TabStop = false;
			this->grpFLINI->Text = L"Freelancer.ini Settings";
			// 
			// btnReloadINI
			// 
			this->btnReloadINI->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnReloadINI->Location = System::Drawing::Point(649, 33);
			this->btnReloadINI->Name = L"btnReloadINI";
			this->btnReloadINI->Size = System::Drawing::Size(105, 23);
			this->btnReloadINI->TabIndex = 6;
			this->btnReloadINI->Text = L"(Re)Load";
			this->btnReloadINI->UseVisualStyleBackColor = true;
			this->btnReloadINI->Click += gcnew System::EventHandler(this, &Main::btnReloadINI_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Freelancer.ini Path:";
			// 
			// txtINIPath
			// 
			this->txtINIPath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->helpProvider->SetHelpString(this->txtINIPath, L"Browse to the path of your freelancer.ini file. This will allow FLDev to parse th" 
				L"e required DLLs for editing and viewing.");
			this->txtINIPath->Location = System::Drawing::Point(6, 35);
			this->txtINIPath->Name = L"txtINIPath";
			this->helpProvider->SetShowHelp(this->txtINIPath, true);
			this->txtINIPath->Size = System::Drawing::Size(508, 20);
			this->txtINIPath->TabIndex = 0;
			// 
			// btnBrowseINI
			// 
			this->btnBrowseINI->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnBrowseINI->Location = System::Drawing::Point(520, 33);
			this->btnBrowseINI->Name = L"btnBrowseINI";
			this->btnBrowseINI->Size = System::Drawing::Size(123, 23);
			this->btnBrowseINI->TabIndex = 1;
			this->btnBrowseINI->Text = L"Browse";
			this->btnBrowseINI->UseVisualStyleBackColor = true;
			this->btnBrowseINI->Click += gcnew System::EventHandler(this, &Main::btnBrowseINI_Click);
			// 
			// editTab
			// 
			this->editTab->BackColor = System::Drawing::SystemColors::Control;
			this->editTab->Controls->Add(this->splitDLLEditor);
			this->editTab->Location = System::Drawing::Point(4, 22);
			this->editTab->Name = L"editTab";
			this->editTab->Padding = System::Windows::Forms::Padding(3);
			this->editTab->Size = System::Drawing::Size(776, 514);
			this->editTab->TabIndex = 1;
			this->editTab->Text = L"Edition";
			// 
			// splitDLLEditor
			// 
			this->splitDLLEditor->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->splitDLLEditor->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitDLLEditor->Location = System::Drawing::Point(3, 3);
			this->splitDLLEditor->Name = L"splitDLLEditor";
			// 
			// splitDLLEditor.Panel1
			// 
			this->splitDLLEditor->Panel1->Controls->Add(this->grpDLLExplorer);
			// 
			// splitDLLEditor.Panel2
			// 
			this->splitDLLEditor->Panel2->Controls->Add(this->tableLayoutPanel1);
			this->splitDLLEditor->Size = System::Drawing::Size(770, 508);
			this->splitDLLEditor->SplitterDistance = 256;
			this->splitDLLEditor->TabIndex = 1;
			// 
			// grpDLLExplorer
			// 
			this->grpDLLExplorer->Controls->Add(this->lstDLLExplorer);
			this->grpDLLExplorer->Controls->Add(this->lstScroll);
			this->grpDLLExplorer->Controls->Add(this->comboDLLExplorer);
			this->grpDLLExplorer->Controls->Add(this->chkDLLExplorerShowEmpty);
			this->grpDLLExplorer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grpDLLExplorer->Location = System::Drawing::Point(0, 0);
			this->grpDLLExplorer->Name = L"grpDLLExplorer";
			this->grpDLLExplorer->Size = System::Drawing::Size(254, 506);
			this->grpDLLExplorer->TabIndex = 0;
			this->grpDLLExplorer->TabStop = false;
			this->grpDLLExplorer->Text = L"DLL Explorer";
			// 
			// lstDLLExplorer
			// 
			this->lstDLLExplorer->Activation = System::Windows::Forms::ItemActivation::TwoClick;
			this->lstDLLExplorer->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lstDLLExplorer->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->lstDLLExplorerID, 
				this->lstDLLExplorerLID, this->lstDLLExplorerType, this->lstDLLExplorerPreview});
			this->lstDLLExplorer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lstDLLExplorer->FullRowSelect = true;
			this->lstDLLExplorer->GridLines = true;
			this->lstDLLExplorer->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lstDLLExplorer->LabelWrap = false;
			this->lstDLLExplorer->Location = System::Drawing::Point(3, 37);
			this->lstDLLExplorer->MultiSelect = false;
			this->lstDLLExplorer->Name = L"lstDLLExplorer";
			this->lstDLLExplorer->Size = System::Drawing::Size(231, 449);
			this->lstDLLExplorer->TabIndex = 0;
			this->lstDLLExplorer->UseCompatibleStateImageBehavior = false;
			this->lstDLLExplorer->View = System::Windows::Forms::View::Details;
			this->lstDLLExplorer->ItemActivate += gcnew System::EventHandler(this, &Main::lstDLLExplorer_ItemActivate);
			this->lstDLLExplorer->Resize += gcnew System::EventHandler(this, &Main::lstDLLExplorer_Resize);
			// 
			// lstDLLExplorerID
			// 
			this->lstDLLExplorerID->Text = L"ID";
			this->lstDLLExplorerID->Width = 55;
			// 
			// lstDLLExplorerLID
			// 
			this->lstDLLExplorerLID->Text = L"Local ID";
			this->lstDLLExplorerLID->Width = 55;
			// 
			// lstDLLExplorerType
			// 
			this->lstDLLExplorerType->Text = L"Type";
			// 
			// lstDLLExplorerPreview
			// 
			this->lstDLLExplorerPreview->Text = L"Preview";
			this->lstDLLExplorerPreview->Width = 160;
			// 
			// lstScroll
			// 
			this->lstScroll->Dock = System::Windows::Forms::DockStyle::Right;
			this->lstScroll->Location = System::Drawing::Point(234, 37);
			this->lstScroll->Maximum = 65536;
			this->lstScroll->Name = L"lstScroll";
			this->lstScroll->Size = System::Drawing::Size(17, 449);
			this->lstScroll->TabIndex = 1;
			this->lstScroll->ValueChanged += gcnew System::EventHandler(this, &Main::lstScroll_ValueChanged);
			// 
			// comboDLLExplorer
			// 
			this->comboDLLExplorer->Dock = System::Windows::Forms::DockStyle::Top;
			this->comboDLLExplorer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboDLLExplorer->FormattingEnabled = true;
			this->comboDLLExplorer->Location = System::Drawing::Point(3, 16);
			this->comboDLLExplorer->Name = L"comboDLLExplorer";
			this->comboDLLExplorer->Size = System::Drawing::Size(248, 21);
			this->comboDLLExplorer->TabIndex = 2;
			this->comboDLLExplorer->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::comboDLLExplorer_SelectedIndexChanged);
			// 
			// chkDLLExplorerShowEmpty
			// 
			this->chkDLLExplorerShowEmpty->AutoSize = true;
			this->chkDLLExplorerShowEmpty->Checked = true;
			this->chkDLLExplorerShowEmpty->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkDLLExplorerShowEmpty->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->chkDLLExplorerShowEmpty->Location = System::Drawing::Point(3, 486);
			this->chkDLLExplorerShowEmpty->Name = L"chkDLLExplorerShowEmpty";
			this->chkDLLExplorerShowEmpty->Size = System::Drawing::Size(248, 17);
			this->chkDLLExplorerShowEmpty->TabIndex = 3;
			this->chkDLLExplorerShowEmpty->Text = L"Show empty entries";
			this->chkDLLExplorerShowEmpty->UseVisualStyleBackColor = true;
			this->chkDLLExplorerShowEmpty->CheckedChanged += gcnew System::EventHandler(this, &Main::chkDLLExplorerShowEmpty_CheckedChanged);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				40)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				30)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				30)));
			this->tableLayoutPanel1->Controls->Add(this->radioSInfocard, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->comboIDS, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->radioName, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->radioInfocard, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->txtEntry, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->toolsEntry, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblIDSInfo, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label3, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->txtLocalIDS, 2, 4);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(508, 506);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// radioSInfocard
			// 
			this->radioSInfocard->AutoSize = true;
			this->radioSInfocard->Dock = System::Windows::Forms::DockStyle::Right;
			this->radioSInfocard->Location = System::Drawing::Point(390, 35);
			this->radioSInfocard->Margin = System::Windows::Forms::Padding(3, 3, 20, 3);
			this->radioSInfocard->Name = L"radioSInfocard";
			this->radioSInfocard->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->radioSInfocard->Size = System::Drawing::Size(98, 17);
			this->radioSInfocard->TabIndex = 8;
			this->radioSInfocard->TabStop = true;
			this->radioSInfocard->Text = L"Simple Infocard";
			this->radioSInfocard->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->radioSInfocard->UseVisualStyleBackColor = true;
			this->radioSInfocard->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::radioSInfocard_MouseClick);
			this->radioSInfocard->CheckedChanged += gcnew System::EventHandler(this, &Main::radioSInfocard_CheckedChanged);
			// 
			// comboIDS
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->comboIDS, 3);
			this->comboIDS->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comboIDS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboIDS->FormattingEnabled = true;
			this->comboIDS->Location = System::Drawing::Point(120, 3);
			this->comboIDS->Margin = System::Windows::Forms::Padding(120, 3, 120, 3);
			this->comboIDS->Name = L"comboIDS";
			this->comboIDS->Size = System::Drawing::Size(268, 26);
			this->comboIDS->TabIndex = 4;
			this->comboIDS->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::comboIDS_SelectedIndexChanged);
			this->comboIDS->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::comboIDS_KeyUp);
			this->comboIDS->TextUpdate += gcnew System::EventHandler(this, &Main::comboIDS_TextUpdate);
			// 
			// radioName
			// 
			this->radioName->AutoSize = true;
			this->radioName->Dock = System::Windows::Forms::DockStyle::Left;
			this->radioName->Location = System::Drawing::Point(20, 35);
			this->radioName->Margin = System::Windows::Forms::Padding(20, 3, 3, 3);
			this->radioName->Name = L"radioName";
			this->radioName->Size = System::Drawing::Size(53, 17);
			this->radioName->TabIndex = 0;
			this->radioName->TabStop = true;
			this->radioName->Text = L"Name";
			this->radioName->UseVisualStyleBackColor = true;
			this->radioName->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::radioName_MouseClick);
			this->radioName->CheckedChanged += gcnew System::EventHandler(this, &Main::radioName_CheckedChanged);
			// 
			// radioInfocard
			// 
			this->radioInfocard->AutoSize = true;
			this->radioInfocard->Dock = System::Windows::Forms::DockStyle::Right;
			this->radioInfocard->Location = System::Drawing::Point(271, 35);
			this->radioInfocard->Margin = System::Windows::Forms::Padding(3, 3, 20, 3);
			this->radioInfocard->Name = L"radioInfocard";
			this->radioInfocard->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->radioInfocard->Size = System::Drawing::Size(64, 17);
			this->radioInfocard->TabIndex = 1;
			this->radioInfocard->TabStop = true;
			this->radioInfocard->Text = L"Infocard";
			this->radioInfocard->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->radioInfocard->UseVisualStyleBackColor = true;
			this->radioInfocard->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::radioInfocard_MouseClick);
			this->radioInfocard->CheckedChanged += gcnew System::EventHandler(this, &Main::radioInfocard_CheckedChanged);
			// 
			// txtEntry
			// 
			this->txtEntry->AcceptsTab = true;
			this->tableLayoutPanel1->SetColumnSpan(this->txtEntry, 3);
			this->txtEntry->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtEntry->Location = System::Drawing::Point(10, 80);
			this->txtEntry->Margin = System::Windows::Forms::Padding(10, 0, 10, 10);
			this->txtEntry->MaxLength = 65536;
			this->txtEntry->Multiline = true;
			this->txtEntry->Name = L"txtEntry";
			this->txtEntry->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtEntry->Size = System::Drawing::Size(488, 390);
			this->txtEntry->TabIndex = 2;
			this->txtEntry->TextChanged += gcnew System::EventHandler(this, &Main::txtEntry_TextChanged);
			// 
			// toolsEntry
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->toolsEntry, 3);
			this->toolsEntry->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolsEntry->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->entryUndo, this->entryRedo});
			this->toolsEntry->Location = System::Drawing::Point(10, 55);
			this->toolsEntry->Margin = System::Windows::Forms::Padding(10, 0, 10, 0);
			this->toolsEntry->Name = L"toolsEntry";
			this->toolsEntry->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolsEntry->Size = System::Drawing::Size(488, 25);
			this->toolsEntry->TabIndex = 5;
			this->toolsEntry->Text = L"toolStrip1";
			// 
			// entryUndo
			// 
			this->entryUndo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->entryUndo->Enabled = false;
			this->entryUndo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"entryUndo.Image")));
			this->entryUndo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->entryUndo->Name = L"entryUndo";
			this->entryUndo->Size = System::Drawing::Size(23, 22);
			this->entryUndo->Text = L"toolStripButton1";
			this->entryUndo->Click += gcnew System::EventHandler(this, &Main::entryUndo_Click);
			// 
			// entryRedo
			// 
			this->entryRedo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->entryRedo->Enabled = false;
			this->entryRedo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"entryRedo.Image")));
			this->entryRedo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->entryRedo->Name = L"entryRedo";
			this->entryRedo->Size = System::Drawing::Size(23, 22);
			this->entryRedo->Text = L"toolStripButton1";
			this->entryRedo->Click += gcnew System::EventHandler(this, &Main::entryRedo_Click);
			// 
			// lblIDSInfo
			// 
			this->lblIDSInfo->AutoSize = true;
			this->lblIDSInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblIDSInfo->Location = System::Drawing::Point(3, 480);
			this->lblIDSInfo->Name = L"lblIDSInfo";
			this->lblIDSInfo->Size = System::Drawing::Size(197, 26);
			this->lblIDSInfo->TabIndex = 11;
			this->lblIDSInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Location = System::Drawing::Point(206, 480);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(146, 26);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Local ID";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// txtLocalIDS
			// 
			this->txtLocalIDS->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtLocalIDS->Location = System::Drawing::Point(358, 483);
			this->txtLocalIDS->Name = L"txtLocalIDS";
			this->txtLocalIDS->Size = System::Drawing::Size(147, 20);
			this->txtLocalIDS->TabIndex = 10;
			this->txtLocalIDS->TextChanged += gcnew System::EventHandler(this, &Main::txtLocalIDS_TextChanged);
			this->txtLocalIDS->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::txtLocalIDS_KeyUp);
			// 
			// openFLINI
			// 
			this->openFLINI->DefaultExt = L"ini";
			this->openFLINI->FileName = L"freelancer.ini";
			this->openFLINI->Filter = L"INI files|*.ini|All files|*.*";
			// 
			// openDLL
			// 
			this->openDLL->DefaultExt = L"dll";
			this->openDLL->Filter = L"DLL files|*.dll|All files|*.*";
			// 
			// backgroundWorkerFLINI
			// 
			this->backgroundWorkerFLINI->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Main::backgroundWorkerFLINI_DoWork);
			this->backgroundWorkerFLINI->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::backgroundWorkerGeneric_RunWorkerCompleted);
			// 
			// backgroundWorkerApply
			// 
			this->backgroundWorkerApply->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Main::backgroundWorkerApply_DoWork);
			this->backgroundWorkerApply->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::backgroundWorkerGeneric_RunWorkerCompleted);
			// 
			// mainStatusStrip
			// 
			this->mainStatusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->mainProgressBar, 
				this->mainStatusText});
			this->mainStatusStrip->Location = System::Drawing::Point(0, 540);
			this->mainStatusStrip->Name = L"mainStatusStrip";
			this->mainStatusStrip->Size = System::Drawing::Size(784, 22);
			this->mainStatusStrip->TabIndex = 7;
			this->mainStatusStrip->Text = L"statusStrip1";
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
			// undoTimer
			// 
			this->undoTimer->Interval = 2000;
			this->undoTimer->Tick += gcnew System::EventHandler(this, &Main::undoTimer_Tick);
			// 
			// statusBarTimer
			// 
			this->statusBarTimer->Enabled = true;
			this->statusBarTimer->Interval = 1000;
			this->statusBarTimer->Tick += gcnew System::EventHandler(this, &Main::statusBarTimer_Tick);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->mainTab);
			this->Controls->Add(this->mainStatusStrip);
			this->HelpButton = true;
			this->Name = L"Main";
			this->Text = L"Freelancer Developer - DLL Editor";
			this->TransparencyKey = System::Drawing::Color::Magenta;
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->Resize += gcnew System::EventHandler(this, &Main::Main_Resize);
			this->mainTab->ResumeLayout(false);
			this->tabSettings->ResumeLayout(false);
			this->grpOut->ResumeLayout(false);
			this->grpOut->PerformLayout();
			this->grpDLLs->ResumeLayout(false);
			this->grpDLLs->PerformLayout();
			this->grpFLINI->ResumeLayout(false);
			this->grpFLINI->PerformLayout();
			this->editTab->ResumeLayout(false);
			this->splitDLLEditor->Panel1->ResumeLayout(false);
			this->splitDLLEditor->Panel2->ResumeLayout(false);
			this->splitDLLEditor->ResumeLayout(false);
			this->grpDLLExplorer->ResumeLayout(false);
			this->grpDLLExplorer->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->toolsEntry->ResumeLayout(false);
			this->toolsEntry->PerformLayout();
			this->mainStatusStrip->ResumeLayout(false);
			this->mainStatusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	void loadINI();
	void browseAndLoadINI();
	void updateDLLList(Object^ sender, RunWorkerCompletedEventArgs^ e);
	void updateDLLList();
	void reloadDLL();
	bool confirmApply();
	bool dataLossAsk();

	array<String^>^ dllNames;
	Interfaces::DLLManager^ dlls;
	String^ flINIPath;
	List<ProcessBarItem^>^ progressStatusTexts;
	bool changingSelectedIDS;
	int currentEntry;

private: System::Void btnReloadINI_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(dataLossAsk())
				loadINI();
		 }

private: System::Void btnBrowseINI_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(dlls == nullptr || dataLossAsk())
				browseAndLoadINI();
		 }

private: System::Void lstDLLs_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(lstDLLs->SelectedIndices->Count > 0)
				 txtSelectedDLLPath->Text = lstDLLs->SelectedItems[0]->SubItems[1]->Text;
		 }
private: System::Void btnReloadDLL_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(dlls != nullptr && System::IO::File::Exists(txtSelectedDLLPath->Text)) {
				 if(!dlls->mIsLoaded(lstDLLs->SelectedIndices[0]) || dataLossAsk())
					reloadDLL();
			 }
		 }
private: System::Void btnBrowseDLL_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstDLLs->SelectedIndices->Count > 0) {
				 openDLL->FileName = System::IO::Path::GetFileName(txtSelectedDLLPath->Text);
				 if(openDLL->ShowDialog() == Windows::Forms::DialogResult::OK) {
					 txtSelectedDLLPath->Text = openDLL->FileName;
					 reloadDLL();
				 }
			 }
		 }
private: System::Void Main_Load(System::Object^  sender, System::EventArgs^  e) {
			 RefreshList(lstScroll->Value, 0);
			 txtOutPath->Text = System::IO::Path::Combine(Application::StartupPath, "Output\\DLL");
			 if(!System::IO::Directory::Exists(txtOutPath->Text))
				 System::IO::Directory::CreateDirectory(txtOutPath->Text);
		 }
private: System::Void btnOutOpen_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start("explorer", "\"" + txtOutPath->Text + "\"");
		 }
private: System::Void btnApply_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(dlls != nullptr && confirmApply()) {
				 addStatusText("Applying changes", -1, true);
				 backgroundWorkerApply->RunWorkerAsync();
				 this->Cursor = Cursors::WaitCursor;
			 }
		 }
private: System::Void backgroundWorkerFLINI_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 dlls = gcnew Interfaces::DLLManager(dllNames);
		 }
private: System::Void backgroundWorkerApply_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 dlls->mApply(txtOutPath->Text);
		 }
private: System::Void backgroundWorkerGeneric_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 this->Cursor = Cursors::Default;
		 }
private: System::Void backgroundWorkerFLINI_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 removeStatusText("Reading INI");
			 updateDLLList();
		 }
private: System::Void backgroundWorkerApply_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 removeStatusText("Applying changes");
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
				 if(mainProgressBar->Style != ProgressBarStyle::Marquee) {
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
				 mainStatusText->Text += "...";
			 } else
				 mainStatusText->Text = "Ready";
		 }

		void RefreshList(int dllID);
		void RefreshList(int start, int overwrite);
		void showNewEntry(int id);
		void refreshEntry();
		void radioType(DLLEntry type);
		void addUndo();

		System::Void Main_Resize(System::Object^  sender, System::EventArgs^  e) {
			
		}
		void lstScroll_ValueChanged(Object^  sender, System::EventArgs^ e);
		System::Void lstDLLExplorer_MouseWheel(System::Object^  sender, MouseEventArgs^  e);
		void lstDLLExplorer_ItemActivate(System::Object^  sender, System::EventArgs^  e);

private: System::Void comboDLLExplorer_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(comboDLLExplorer->SelectedIndex >= 0)
				 RefreshList(comboDLLExplorer->SelectedIndex);
		 }
private: System::Void chkDLLExplorerShowEmpty_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 RefreshList(lstScroll->Value, 0);
		 }
private: System::Void lstDLLExplorer_Resize(System::Object^  sender, System::EventArgs^  e) {
			 RefreshList(lstScroll->Value, 0);
		 }
private: System::Void comboIDS_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 int ids;
			 if(Int32::TryParse(comboIDS->Text, ids))
				showNewEntry(ids);
		 }
private: System::Void comboIDS_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void radioName_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void radioInfocard_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void radioSInfocard_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void txtLocalIDS_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void txtEntry_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(changingSelectedIDS) return;

			 if(dlls->mGetEntryType(currentEntry) != DLLEntry::None) {
				undoTimer->Enabled = true;
				undoTimer->Start();
			 }
		 }
private: System::Void undoTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 addUndo();
		 }
private: System::Void entryUndo_Click(System::Object^  sender, System::EventArgs^  e) {
			 IDSItem^ i = dlls->mGetEntryObj(currentEntry, radioInfocard->Checked || radioSInfocard->Checked);
			 if(i->canUndo())
				i->Undo();

			 refreshEntry();

			 if(!i->canUndo()) entryUndo->Enabled = false;
			 entryRedo->Enabled = true;

			 RefreshList(lstScroll->Value, 0);
		 }
private: System::Void entryRedo_Click(System::Object^  sender, System::EventArgs^  e) {
			 IDSItem^ i = dlls->mGetEntryObj(currentEntry, radioInfocard->Checked || radioSInfocard->Checked);
			 if(i->canRedo())
				i->Redo();

			 refreshEntry();

			 if(!i->canRedo()) entryRedo->Enabled = false;
			 entryUndo->Enabled = true;

			 RefreshList(lstScroll->Value, 0);
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
private: System::Void comboIDS_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(changingSelectedIDS) return;
			 int ids;
			 if(Int32::TryParse(comboIDS->Text, ids) && ids != currentEntry)
				showNewEntry(ids);
		 }
private: System::Void txtLocalIDS_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(changingSelectedIDS) return;
			 int ids;
			 if(Int32::TryParse(txtLocalIDS->Text, ids) && ids != currentEntry)
				showNewEntry(comboDLLExplorer->SelectedIndex * 0x10000 + ids);
		 }
private: System::Void radioInfocard_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(changingSelectedIDS) return;
			 refreshEntry();
		 }
private: System::Void radioSInfocard_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(changingSelectedIDS) return;
			 refreshEntry();
		 }
private: System::Void radioName_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(changingSelectedIDS) return;
			 refreshEntry();
		 }
};
}