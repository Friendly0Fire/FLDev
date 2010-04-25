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
	using namespace Utilities;
	using namespace System::Text::RegularExpressions;
	using namespace System::IO;
	using namespace System::Text;

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
			mainStatus = gcnew CompositeStatusBar();
			this->Controls->Add(this->mainStatus);

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
	private:
		Utilities::CompositeStatusBar^ mainStatus;
		System::Windows::Forms::TabControl^  mainTab;
		System::Windows::Forms::TabPage^  tabSettings;
		System::Windows::Forms::TabPage^  editTab;
		System::Windows::Forms::Button^  btnBrowseINI;

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

	private: System::Windows::Forms::RadioButton^  radioSInfocard;
	private: System::Windows::Forms::Label^  lblIDSInfo;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  txtLocalIDS;
	private: System::Windows::Forms::Timer^  undoTimer;
private: System::Windows::Forms::ToolStrip^  toolsEntry;
private: System::Windows::Forms::ToolStripButton^  entrySuperundo;
private: System::Windows::Forms::ToolStripButton^  entryUndo;
private: System::Windows::Forms::ToolStripButton^  entryRedo;
private: System::Windows::Forms::ToolStripButton^  entrySave;
private: System::Windows::Forms::TabPage^  tabSearch;
private: System::Windows::Forms::CheckBox^  chkWhole;
private: System::Windows::Forms::CheckBox^  chkCaseSensitive;
private: System::Windows::Forms::CheckBox^  chkRegex;
private: System::Windows::Forms::Button^  btnSearch;
private: System::Windows::Forms::TextBox^  txtSearch;
private: System::Windows::Forms::ListView^  lstSearch;

private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
private: System::Windows::Forms::SplitContainer^  splitSearch;
private: System::Windows::Forms::ColumnHeader^  colSearchID;
private: System::Windows::Forms::ColumnHeader^  colSearchDLL;
private: System::Windows::Forms::ColumnHeader^  colSearchLocal;
private: System::Windows::Forms::ColumnHeader^  colSearchType;
private: System::Windows::Forms::ColumnHeader^  colSearchContent;
private: System::Windows::Forms::Label^  lblSearchInput;
private: System::ComponentModel::BackgroundWorker^  backgroundWorkerSearch;
private: System::Windows::Forms::TextBox^  txtRegexTest;
private: System::Windows::Forms::TabPage^  tabImportExport;
private: System::Windows::Forms::SplitContainer^  splitContainer1;
private: System::Windows::Forms::GroupBox^  grpImport;
private: System::Windows::Forms::TextBox^  txtPathImport;






private: System::Windows::Forms::Button^  btnBrowseImport;
private: System::Windows::Forms::GroupBox^  grpExport;
private: System::Windows::Forms::Button^  btnBrowseExport;
private: System::Windows::Forms::TextBox^  txtPathExport;



private: System::Windows::Forms::Button^  btnExport;

private: System::Windows::Forms::RadioButton^  radioExportChanges;

private: System::Windows::Forms::RadioButton^  radioExportAll;
private: System::Windows::Forms::Button^  btnImportLoad;

private: System::Windows::Forms::ListView^  lstImportResults;
private: System::Windows::Forms::ColumnHeader^  colImportID;
private: System::Windows::Forms::ColumnHeader^  colImportType;
private: System::Windows::Forms::ColumnHeader^  colImportResult;
private: System::Windows::Forms::TextBox^  txtImportMessage;
private: System::Windows::Forms::TextBox^  txtExportSpecific;
private: System::Windows::Forms::RadioButton^  radioExportSpecific;
private: System::Windows::Forms::Button^  btnImport;
private: System::Windows::Forms::OpenFileDialog^  openImport;








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
			this->lblIDSInfo = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtLocalIDS = (gcnew System::Windows::Forms::TextBox());
			this->toolsEntry = (gcnew System::Windows::Forms::ToolStrip());
			this->entrySuperundo = (gcnew System::Windows::Forms::ToolStripButton());
			this->entryUndo = (gcnew System::Windows::Forms::ToolStripButton());
			this->entryRedo = (gcnew System::Windows::Forms::ToolStripButton());
			this->entrySave = (gcnew System::Windows::Forms::ToolStripButton());
			this->txtEntry = (gcnew System::Windows::Forms::TextBox());
			this->tabSearch = (gcnew System::Windows::Forms::TabPage());
			this->lstSearch = (gcnew System::Windows::Forms::ListView());
			this->colSearchID = (gcnew System::Windows::Forms::ColumnHeader());
			this->colSearchDLL = (gcnew System::Windows::Forms::ColumnHeader());
			this->colSearchLocal = (gcnew System::Windows::Forms::ColumnHeader());
			this->colSearchType = (gcnew System::Windows::Forms::ColumnHeader());
			this->colSearchContent = (gcnew System::Windows::Forms::ColumnHeader());
			this->splitSearch = (gcnew System::Windows::Forms::SplitContainer());
			this->txtSearch = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->chkRegex = (gcnew System::Windows::Forms::CheckBox());
			this->chkCaseSensitive = (gcnew System::Windows::Forms::CheckBox());
			this->chkWhole = (gcnew System::Windows::Forms::CheckBox());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->txtRegexTest = (gcnew System::Windows::Forms::TextBox());
			this->lblSearchInput = (gcnew System::Windows::Forms::Label());
			this->tabImportExport = (gcnew System::Windows::Forms::TabPage());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->grpImport = (gcnew System::Windows::Forms::GroupBox());
			this->btnImport = (gcnew System::Windows::Forms::Button());
			this->txtImportMessage = (gcnew System::Windows::Forms::TextBox());
			this->lstImportResults = (gcnew System::Windows::Forms::ListView());
			this->colImportID = (gcnew System::Windows::Forms::ColumnHeader());
			this->colImportType = (gcnew System::Windows::Forms::ColumnHeader());
			this->colImportResult = (gcnew System::Windows::Forms::ColumnHeader());
			this->btnImportLoad = (gcnew System::Windows::Forms::Button());
			this->txtPathImport = (gcnew System::Windows::Forms::TextBox());
			this->btnBrowseImport = (gcnew System::Windows::Forms::Button());
			this->grpExport = (gcnew System::Windows::Forms::GroupBox());
			this->txtExportSpecific = (gcnew System::Windows::Forms::TextBox());
			this->radioExportSpecific = (gcnew System::Windows::Forms::RadioButton());
			this->radioExportChanges = (gcnew System::Windows::Forms::RadioButton());
			this->radioExportAll = (gcnew System::Windows::Forms::RadioButton());
			this->btnExport = (gcnew System::Windows::Forms::Button());
			this->btnBrowseExport = (gcnew System::Windows::Forms::Button());
			this->txtPathExport = (gcnew System::Windows::Forms::TextBox());
			this->helpProvider = (gcnew System::Windows::Forms::HelpProvider());
			this->openFLINI = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openDLL = (gcnew System::Windows::Forms::OpenFileDialog());
			this->backgroundWorkerFLINI = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerApply = (gcnew System::ComponentModel::BackgroundWorker());
			this->undoTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorkerSearch = (gcnew System::ComponentModel::BackgroundWorker());
			this->openImport = (gcnew System::Windows::Forms::OpenFileDialog());
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
			this->tabSearch->SuspendLayout();
			this->splitSearch->Panel1->SuspendLayout();
			this->splitSearch->Panel2->SuspendLayout();
			this->splitSearch->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tabImportExport->SuspendLayout();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->grpImport->SuspendLayout();
			this->grpExport->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainTab
			// 
			this->mainTab->Controls->Add(this->tabSettings);
			this->mainTab->Controls->Add(this->editTab);
			this->mainTab->Controls->Add(this->tabSearch);
			this->mainTab->Controls->Add(this->tabImportExport);
			this->mainTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainTab->Location = System::Drawing::Point(0, 0);
			this->mainTab->Name = L"mainTab";
			this->mainTab->SelectedIndex = 0;
			this->mainTab->Size = System::Drawing::Size(784, 562);
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
			this->tabSettings->Size = System::Drawing::Size(776, 536);
			this->tabSettings->TabIndex = 0;
			this->tabSettings->Text = L"Primary Settings";
			// 
			// btnApply
			// 
			this->btnApply->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnApply->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnApply->Location = System::Drawing::Point(284, 490);
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
			this->editTab->Size = System::Drawing::Size(776, 536);
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
			this->splitDLLEditor->Size = System::Drawing::Size(770, 530);
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
			this->grpDLLExplorer->Size = System::Drawing::Size(254, 528);
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
			this->lstDLLExplorer->HideSelection = false;
			this->lstDLLExplorer->LabelWrap = false;
			this->lstDLLExplorer->Location = System::Drawing::Point(3, 37);
			this->lstDLLExplorer->MultiSelect = false;
			this->lstDLLExplorer->Name = L"lstDLLExplorer";
			this->lstDLLExplorer->Size = System::Drawing::Size(231, 471);
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
			this->lstScroll->Size = System::Drawing::Size(17, 471);
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
			this->chkDLLExplorerShowEmpty->Location = System::Drawing::Point(3, 508);
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
			this->tableLayoutPanel1->Controls->Add(this->lblIDSInfo, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label3, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->txtLocalIDS, 2, 4);
			this->tableLayoutPanel1->Controls->Add(this->toolsEntry, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->txtEntry, 0, 3);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(508, 528);
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
			// 
			// lblIDSInfo
			// 
			this->lblIDSInfo->AutoSize = true;
			this->lblIDSInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblIDSInfo->Location = System::Drawing::Point(3, 502);
			this->lblIDSInfo->Name = L"lblIDSInfo";
			this->lblIDSInfo->Size = System::Drawing::Size(197, 26);
			this->lblIDSInfo->TabIndex = 11;
			this->lblIDSInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Location = System::Drawing::Point(206, 502);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(146, 26);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Local ID";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// txtLocalIDS
			// 
			this->txtLocalIDS->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtLocalIDS->Location = System::Drawing::Point(358, 505);
			this->txtLocalIDS->Name = L"txtLocalIDS";
			this->txtLocalIDS->Size = System::Drawing::Size(147, 20);
			this->txtLocalIDS->TabIndex = 10;
			this->txtLocalIDS->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::txtLocalIDS_KeyUp);
			// 
			// toolsEntry
			// 
			this->toolsEntry->AllowMerge = false;
			this->tableLayoutPanel1->SetColumnSpan(this->toolsEntry, 3);
			this->toolsEntry->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolsEntry->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolsEntry->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->entrySuperundo, this->entryUndo, 
				this->entryRedo, this->entrySave});
			this->toolsEntry->Location = System::Drawing::Point(10, 55);
			this->toolsEntry->Margin = System::Windows::Forms::Padding(10, 0, 10, 0);
			this->toolsEntry->Name = L"toolsEntry";
			this->toolsEntry->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolsEntry->Size = System::Drawing::Size(488, 25);
			this->toolsEntry->Stretch = true;
			this->toolsEntry->TabIndex = 5;
			this->toolsEntry->Text = L"Entry Tools";
			// 
			// entrySuperundo
			// 
			this->entrySuperundo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->entrySuperundo->Enabled = false;
			this->entrySuperundo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"entrySuperundo.Image")));
			this->entrySuperundo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->entrySuperundo->Name = L"entrySuperundo";
			this->entrySuperundo->Size = System::Drawing::Size(23, 22);
			this->entrySuperundo->Text = L"Super Undo";
			this->entrySuperundo->Click += gcnew System::EventHandler(this, &Main::entrySuperundo_Click);
			// 
			// entryUndo
			// 
			this->entryUndo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->entryUndo->Enabled = false;
			this->entryUndo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"entryUndo.Image")));
			this->entryUndo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->entryUndo->Name = L"entryUndo";
			this->entryUndo->Size = System::Drawing::Size(23, 22);
			this->entryUndo->Text = L"Undo";
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
			this->entryRedo->Text = L"Redo";
			this->entryRedo->Click += gcnew System::EventHandler(this, &Main::entryRedo_Click);
			// 
			// entrySave
			// 
			this->entrySave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->entrySave->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"entrySave.Image")));
			this->entrySave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->entrySave->Name = L"entrySave";
			this->entrySave->Size = System::Drawing::Size(23, 22);
			this->entrySave->Text = L"Save";
			this->entrySave->Click += gcnew System::EventHandler(this, &Main::entrySave_Click);
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
			this->txtEntry->Size = System::Drawing::Size(488, 412);
			this->txtEntry->TabIndex = 2;
			this->txtEntry->TextChanged += gcnew System::EventHandler(this, &Main::txtEntry_TextChanged);
			// 
			// tabSearch
			// 
			this->tabSearch->BackColor = System::Drawing::SystemColors::Control;
			this->tabSearch->Controls->Add(this->lstSearch);
			this->tabSearch->Controls->Add(this->splitSearch);
			this->tabSearch->Location = System::Drawing::Point(4, 22);
			this->tabSearch->Margin = System::Windows::Forms::Padding(0);
			this->tabSearch->Name = L"tabSearch";
			this->tabSearch->Padding = System::Windows::Forms::Padding(3);
			this->tabSearch->Size = System::Drawing::Size(776, 536);
			this->tabSearch->TabIndex = 2;
			this->tabSearch->Text = L"Search";
			// 
			// lstSearch
			// 
			this->lstSearch->Activation = System::Windows::Forms::ItemActivation::TwoClick;
			this->lstSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lstSearch->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->colSearchID, this->colSearchDLL, 
				this->colSearchLocal, this->colSearchType, this->colSearchContent});
			this->lstSearch->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lstSearch->FullRowSelect = true;
			this->lstSearch->GridLines = true;
			this->lstSearch->Location = System::Drawing::Point(3, 61);
			this->lstSearch->MultiSelect = false;
			this->lstSearch->Name = L"lstSearch";
			this->lstSearch->Size = System::Drawing::Size(770, 472);
			this->lstSearch->TabIndex = 6;
			this->lstSearch->UseCompatibleStateImageBehavior = false;
			this->lstSearch->View = System::Windows::Forms::View::Details;
			this->lstSearch->ItemActivate += gcnew System::EventHandler(this, &Main::lstSearch_ItemActivate);
			// 
			// colSearchID
			// 
			this->colSearchID->Text = L"ID";
			// 
			// colSearchDLL
			// 
			this->colSearchDLL->Text = L"DLL";
			this->colSearchDLL->Width = 79;
			// 
			// colSearchLocal
			// 
			this->colSearchLocal->Text = L"Local ID";
			// 
			// colSearchType
			// 
			this->colSearchType->Text = L"Type";
			this->colSearchType->Width = 68;
			// 
			// colSearchContent
			// 
			this->colSearchContent->Text = L"Content";
			this->colSearchContent->Width = 502;
			// 
			// splitSearch
			// 
			this->splitSearch->Dock = System::Windows::Forms::DockStyle::Top;
			this->splitSearch->Location = System::Drawing::Point(3, 3);
			this->splitSearch->Name = L"splitSearch";
			// 
			// splitSearch.Panel1
			// 
			this->splitSearch->Panel1->Controls->Add(this->txtSearch);
			this->splitSearch->Panel1MinSize = 300;
			// 
			// splitSearch.Panel2
			// 
			this->splitSearch->Panel2->Controls->Add(this->flowLayoutPanel1);
			this->splitSearch->Size = System::Drawing::Size(770, 58);
			this->splitSearch->SplitterDistance = 327;
			this->splitSearch->TabIndex = 7;
			// 
			// txtSearch
			// 
			this->txtSearch->AcceptsReturn = true;
			this->txtSearch->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtSearch->Location = System::Drawing::Point(0, 0);
			this->txtSearch->Multiline = true;
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->Size = System::Drawing::Size(327, 58);
			this->txtSearch->TabIndex = 0;
			this->txtSearch->TextChanged += gcnew System::EventHandler(this, &Main::txtSearch_TextChanged);
			this->txtSearch->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::txtSearch_KeyDown);
			this->txtSearch->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Main::txtSearch_KeyPress);
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->AutoSize = true;
			this->flowLayoutPanel1->Controls->Add(this->chkRegex);
			this->flowLayoutPanel1->Controls->Add(this->chkCaseSensitive);
			this->flowLayoutPanel1->Controls->Add(this->chkWhole);
			this->flowLayoutPanel1->Controls->Add(this->btnSearch);
			this->flowLayoutPanel1->Controls->Add(this->txtRegexTest);
			this->flowLayoutPanel1->Controls->Add(this->lblSearchInput);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel1->Margin = System::Windows::Forms::Padding(0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(439, 58);
			this->flowLayoutPanel1->TabIndex = 5;
			// 
			// chkRegex
			// 
			this->chkRegex->Location = System::Drawing::Point(3, 3);
			this->chkRegex->Name = L"chkRegex";
			this->chkRegex->Size = System::Drawing::Size(144, 23);
			this->chkRegex->TabIndex = 2;
			this->chkRegex->Text = L"Use Regular Expressions";
			this->chkRegex->UseVisualStyleBackColor = true;
			this->chkRegex->CheckedChanged += gcnew System::EventHandler(this, &Main::chkRegex_CheckedChanged);
			// 
			// chkCaseSensitive
			// 
			this->chkCaseSensitive->Location = System::Drawing::Point(153, 3);
			this->chkCaseSensitive->Name = L"chkCaseSensitive";
			this->chkCaseSensitive->Size = System::Drawing::Size(96, 23);
			this->chkCaseSensitive->TabIndex = 3;
			this->chkCaseSensitive->Text = L"Case Sensitive";
			this->chkCaseSensitive->UseVisualStyleBackColor = true;
			// 
			// chkWhole
			// 
			this->chkWhole->Location = System::Drawing::Point(255, 3);
			this->chkWhole->Name = L"chkWhole";
			this->chkWhole->Size = System::Drawing::Size(92, 23);
			this->chkWhole->TabIndex = 4;
			this->chkWhole->Text = L"Whole Strings";
			this->chkWhole->UseVisualStyleBackColor = true;
			// 
			// btnSearch
			// 
			this->btnSearch->Enabled = false;
			this->btnSearch->Location = System::Drawing::Point(353, 3);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(75, 23);
			this->btnSearch->TabIndex = 1;
			this->btnSearch->Text = L"Search";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &Main::btnSearch_Click);
			// 
			// txtRegexTest
			// 
			this->txtRegexTest->Location = System::Drawing::Point(3, 32);
			this->txtRegexTest->Name = L"txtRegexTest";
			this->txtRegexTest->Size = System::Drawing::Size(100, 20);
			this->txtRegexTest->TabIndex = 6;
			this->txtRegexTest->Visible = false;
			this->txtRegexTest->TextChanged += gcnew System::EventHandler(this, &Main::txtRegexTest_TextChanged);
			// 
			// lblSearchInput
			// 
			this->lblSearchInput->AutoSize = true;
			this->lblSearchInput->Location = System::Drawing::Point(109, 29);
			this->lblSearchInput->MinimumSize = System::Drawing::Size(0, 23);
			this->lblSearchInput->Name = L"lblSearchInput";
			this->lblSearchInput->Size = System::Drawing::Size(0, 23);
			this->lblSearchInput->TabIndex = 5;
			this->lblSearchInput->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tabImportExport
			// 
			this->tabImportExport->BackColor = System::Drawing::SystemColors::Control;
			this->tabImportExport->Controls->Add(this->splitContainer1);
			this->tabImportExport->Location = System::Drawing::Point(4, 22);
			this->tabImportExport->Name = L"tabImportExport";
			this->tabImportExport->Padding = System::Windows::Forms::Padding(3);
			this->tabImportExport->Size = System::Drawing::Size(776, 536);
			this->tabImportExport->TabIndex = 3;
			this->tabImportExport->Text = L"Import/Export";
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->Location = System::Drawing::Point(3, 3);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->grpImport);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->grpExport);
			this->splitContainer1->Size = System::Drawing::Size(770, 530);
			this->splitContainer1->SplitterDistance = 449;
			this->splitContainer1->TabIndex = 3;
			// 
			// grpImport
			// 
			this->grpImport->Controls->Add(this->btnImport);
			this->grpImport->Controls->Add(this->txtImportMessage);
			this->grpImport->Controls->Add(this->lstImportResults);
			this->grpImport->Controls->Add(this->btnImportLoad);
			this->grpImport->Controls->Add(this->txtPathImport);
			this->grpImport->Controls->Add(this->btnBrowseImport);
			this->grpImport->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grpImport->Location = System::Drawing::Point(0, 0);
			this->grpImport->Name = L"grpImport";
			this->grpImport->Size = System::Drawing::Size(770, 449);
			this->grpImport->TabIndex = 2;
			this->grpImport->TabStop = false;
			this->grpImport->Text = L"Import";
			// 
			// btnImport
			// 
			this->btnImport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnImport->Location = System::Drawing::Point(674, 424);
			this->btnImport->Name = L"btnImport";
			this->btnImport->Size = System::Drawing::Size(90, 23);
			this->btnImport->TabIndex = 9;
			this->btnImport->Text = L"Import";
			this->btnImport->UseVisualStyleBackColor = true;
			// 
			// txtImportMessage
			// 
			this->txtImportMessage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtImportMessage->Location = System::Drawing::Point(6, 426);
			this->txtImportMessage->Name = L"txtImportMessage";
			this->txtImportMessage->ReadOnly = true;
			this->txtImportMessage->Size = System::Drawing::Size(662, 20);
			this->txtImportMessage->TabIndex = 8;
			// 
			// lstImportResults
			// 
			this->lstImportResults->Activation = System::Windows::Forms::ItemActivation::TwoClick;
			this->lstImportResults->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstImportResults->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lstImportResults->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->colImportID, 
				this->colImportType, this->colImportResult});
			this->lstImportResults->FullRowSelect = true;
			this->lstImportResults->GridLines = true;
			this->lstImportResults->Location = System::Drawing::Point(6, 46);
			this->lstImportResults->MultiSelect = false;
			this->lstImportResults->Name = L"lstImportResults";
			this->lstImportResults->Size = System::Drawing::Size(758, 374);
			this->lstImportResults->TabIndex = 7;
			this->lstImportResults->UseCompatibleStateImageBehavior = false;
			this->lstImportResults->View = System::Windows::Forms::View::Details;
			// 
			// colImportID
			// 
			this->colImportID->Text = L"ID";
			// 
			// colImportType
			// 
			this->colImportType->Text = L"Type";
			this->colImportType->Width = 68;
			// 
			// colImportResult
			// 
			this->colImportResult->Text = L"Result";
			this->colImportResult->Width = 620;
			// 
			// btnImportLoad
			// 
			this->btnImportLoad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnImportLoad->Location = System::Drawing::Point(689, 17);
			this->btnImportLoad->Name = L"btnImportLoad";
			this->btnImportLoad->Size = System::Drawing::Size(75, 23);
			this->btnImportLoad->TabIndex = 6;
			this->btnImportLoad->Text = L"Load";
			this->btnImportLoad->UseVisualStyleBackColor = true;
			this->btnImportLoad->Click += gcnew System::EventHandler(this, &Main::btnImportLoad_Click);
			// 
			// txtPathImport
			// 
			this->txtPathImport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtPathImport->Location = System::Drawing::Point(6, 19);
			this->txtPathImport->Name = L"txtPathImport";
			this->txtPathImport->Size = System::Drawing::Size(596, 20);
			this->txtPathImport->TabIndex = 5;
			// 
			// btnBrowseImport
			// 
			this->btnBrowseImport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnBrowseImport->Location = System::Drawing::Point(608, 17);
			this->btnBrowseImport->Name = L"btnBrowseImport";
			this->btnBrowseImport->Size = System::Drawing::Size(75, 23);
			this->btnBrowseImport->TabIndex = 0;
			this->btnBrowseImport->Text = L"Browse";
			this->btnBrowseImport->UseVisualStyleBackColor = true;
			this->btnBrowseImport->Click += gcnew System::EventHandler(this, &Main::btnBrowseImport_Click);
			// 
			// grpExport
			// 
			this->grpExport->Controls->Add(this->txtExportSpecific);
			this->grpExport->Controls->Add(this->radioExportSpecific);
			this->grpExport->Controls->Add(this->radioExportChanges);
			this->grpExport->Controls->Add(this->radioExportAll);
			this->grpExport->Controls->Add(this->btnExport);
			this->grpExport->Controls->Add(this->btnBrowseExport);
			this->grpExport->Controls->Add(this->txtPathExport);
			this->grpExport->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grpExport->Location = System::Drawing::Point(0, 0);
			this->grpExport->Name = L"grpExport";
			this->grpExport->Size = System::Drawing::Size(770, 77);
			this->grpExport->TabIndex = 3;
			this->grpExport->TabStop = false;
			this->grpExport->Text = L"Export";
			// 
			// txtExportSpecific
			// 
			this->txtExportSpecific->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtExportSpecific->Location = System::Drawing::Point(376, 48);
			this->txtExportSpecific->Name = L"txtExportSpecific";
			this->txtExportSpecific->Size = System::Drawing::Size(388, 20);
			this->txtExportSpecific->TabIndex = 9;
			// 
			// radioExportSpecific
			// 
			this->radioExportSpecific->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->radioExportSpecific->AutoSize = true;
			this->radioExportSpecific->Location = System::Drawing::Point(246, 49);
			this->radioExportSpecific->Name = L"radioExportSpecific";
			this->radioExportSpecific->Size = System::Drawing::Size(124, 17);
			this->radioExportSpecific->TabIndex = 8;
			this->radioExportSpecific->TabStop = true;
			this->radioExportSpecific->Text = L"Export Following IDs:";
			this->radioExportSpecific->UseVisualStyleBackColor = true;
			// 
			// radioExportChanges
			// 
			this->radioExportChanges->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->radioExportChanges->AutoSize = true;
			this->radioExportChanges->Location = System::Drawing::Point(116, 49);
			this->radioExportChanges->Name = L"radioExportChanges";
			this->radioExportChanges->Size = System::Drawing::Size(124, 17);
			this->radioExportChanges->TabIndex = 7;
			this->radioExportChanges->TabStop = true;
			this->radioExportChanges->Text = L"Export Changes Only";
			this->radioExportChanges->UseVisualStyleBackColor = true;
			// 
			// radioExportAll
			// 
			this->radioExportAll->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->radioExportAll->AutoSize = true;
			this->radioExportAll->Location = System::Drawing::Point(6, 49);
			this->radioExportAll->Name = L"radioExportAll";
			this->radioExportAll->Size = System::Drawing::Size(104, 17);
			this->radioExportAll->TabIndex = 6;
			this->radioExportAll->TabStop = true;
			this->radioExportAll->Text = L"Export All Entries";
			this->radioExportAll->UseVisualStyleBackColor = true;
			// 
			// btnExport
			// 
			this->btnExport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnExport->Location = System::Drawing::Point(689, 19);
			this->btnExport->Name = L"btnExport";
			this->btnExport->Size = System::Drawing::Size(75, 23);
			this->btnExport->TabIndex = 5;
			this->btnExport->Text = L"Export";
			this->btnExport->UseVisualStyleBackColor = true;
			// 
			// btnBrowseExport
			// 
			this->btnBrowseExport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnBrowseExport->Location = System::Drawing::Point(608, 19);
			this->btnBrowseExport->Name = L"btnBrowseExport";
			this->btnBrowseExport->Size = System::Drawing::Size(75, 23);
			this->btnBrowseExport->TabIndex = 4;
			this->btnBrowseExport->Text = L"Browse";
			this->btnBrowseExport->UseVisualStyleBackColor = true;
			// 
			// txtPathExport
			// 
			this->txtPathExport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtPathExport->Location = System::Drawing::Point(6, 19);
			this->txtPathExport->Name = L"txtPathExport";
			this->txtPathExport->Size = System::Drawing::Size(596, 20);
			this->txtPathExport->TabIndex = 1;
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
			// undoTimer
			// 
			this->undoTimer->Interval = 2000;
			this->undoTimer->Tick += gcnew System::EventHandler(this, &Main::undoTimer_Tick);
			// 
			// backgroundWorkerSearch
			// 
			this->backgroundWorkerSearch->WorkerReportsProgress = true;
			this->backgroundWorkerSearch->WorkerSupportsCancellation = true;
			this->backgroundWorkerSearch->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Main::backgroundWorkerSearch_DoWork);
			this->backgroundWorkerSearch->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::backgroundWorkerSearch_RunWorkerCompleted);
			this->backgroundWorkerSearch->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Main::backgroundWorkerSearch_ProgressChanged);
			// 
			// openImport
			// 
			this->openImport->RestoreDirectory = true;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->mainTab);
			this->HelpButton = true;
			this->Name = L"Main";
			this->Text = L"Freelancer Developer - DLL Editor";
			this->TransparencyKey = System::Drawing::Color::Magenta;
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
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
			this->tabSearch->ResumeLayout(false);
			this->splitSearch->Panel1->ResumeLayout(false);
			this->splitSearch->Panel1->PerformLayout();
			this->splitSearch->Panel2->ResumeLayout(false);
			this->splitSearch->Panel2->PerformLayout();
			this->splitSearch->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->tabImportExport->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->ResumeLayout(false);
			this->grpImport->ResumeLayout(false);
			this->grpImport->PerformLayout();
			this->grpExport->ResumeLayout(false);
			this->grpExport->PerformLayout();
			this->ResumeLayout(false);

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
					 mainStatus->addStatusText("Applying changes", -1, true);
					 backgroundWorkerApply->RunWorkerAsync(txtOutPath->Text);
					 this->Cursor = Cursors::WaitCursor;
				 }
			 }
	private: System::Void backgroundWorkerFLINI_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 dlls = gcnew Interfaces::DLLManager(dllNames);
			 }
	private: System::Void backgroundWorkerApply_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 dlls->mApply((String^) e->Argument);
			 }
	private: System::Void backgroundWorkerGeneric_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 this->Cursor = Cursors::Default;
			 }
	private: System::Void backgroundWorkerFLINI_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 mainStatus->removeStatusText("Reading INI");
				 updateDLLList();
			 }
	private: System::Void backgroundWorkerApply_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 mainStatus->removeStatusText("Applying changes");
			 }

			 void RefreshList(int dllID);
			 void RefreshList(int start, int overwrite);
			 void showNewEntry(int id);
			 void refreshEntry();
			 void radioType(DLLEntry type);
			 void addUndo();
			 void lstScroll_ValueChanged(Object^  sender, System::EventArgs^ e) {
				RefreshList(lstScroll->Value, 0);
			 }
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
	private: System::Void txtEntry_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(currentEntry >= 0) {
					 IDSItem^ i = dlls->mGetEntryObj(currentEntry, radioInfocard->Checked || radioSInfocard->Checked);
					 entrySuperundo->Enabled = (radioSInfocard->Checked ? SimpleInfocards::XMLToSimple(i->Original) : i->Original) != txtEntry->Text;
				 }
				 
				 if(changingSelectedIDS) return;

				 undoTimer->Stop();
				 undoTimer->Enabled = false;
				 undoTimer->Enabled = true;
				 undoTimer->Start();
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
	private: System::Void entrySuperundo_Click(System::Object^  sender, System::EventArgs^  e) {
				 addUndo();
				 IDSItem^ i = dlls->mGetEntryObj(currentEntry, radioInfocard->Checked || radioSInfocard->Checked);
				 i->Revert(false);
				 refreshEntry();
				 RefreshList(lstScroll->Value, 0);
				 entrySuperundo->Enabled = false;
			 }
private: System::Void entrySave_Click(System::Object^  sender, System::EventArgs^  e) {
				addUndo();
		 }
private: System::Void txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				checkRegex();
		 }
private: System::Void chkRegex_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				bool regValid = false;
				if(chkRegex->Checked) {
					regValid = checkRegex();
					chkCaseSensitive->Enabled = false;
					chkWhole->Enabled = false;
				} else {
					lblSearchInput->Text = "";
					chkCaseSensitive->Enabled = true;
					chkWhole->Enabled = true;
				}
				if(regValid) {
					txtRegexTest->Text = "Test regex here!";
					txtRegexTest->Visible = true;
				} else
					txtRegexTest->Visible = false;
		 }
		 
		 bool checkRegex() {
			if(chkRegex->Checked) {
				try {
					if(txtSearch->Text->Length == 0) throw gcnew ArgumentException("No expression.");
					Regex^ r = gcnew Regex(txtSearch->Text);
					
					lblSearchInput->ForeColor = Color::DarkGreen;
					lblSearchInput->Text = "Regex OK!";
					
					if(!txtRegexTest->Visible)
						txtRegexTest->Text = "Test regex here!";
					txtRegexTest->Visible = true;
					
					return true;
				} catch(ArgumentException^ e) {
					lblSearchInput->ForeColor = Color::DarkRed;
					lblSearchInput->Text = "Parse error: " + e->Message;
					
					txtRegexTest->Visible = false;
					
					return false;
				}
			}
			return false;
		}
private: System::Void txtRegexTest_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			if(checkRegex() && txtRegexTest->Text != "Test regex here!") {
				Regex^ r = gcnew Regex(txtSearch->Text);
				MatchCollection^ mc = r->Matches(txtRegexTest->Text);
				lblSearchInput->Text = mc->Count + " match" + (mc->Count == 1 ? "" : "es") + " found.";
			}
		 }
private: System::Void txtSearch_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if(e->Control && e->KeyCode == Keys::Enter) {
				if(backgroundWorkerSearch->IsBusy)
					cancelSearch();
				beginSearch();
				e->Handled = true;
			}
		 }
private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e) {
			if(backgroundWorkerSearch->IsBusy)
				cancelSearch();
			else
				beginSearch();
		 }
		 
		void beginSearch() {
			mainStatus->addStatusText("Search in progress", -1, true, true);
			lstSearch->Items->Clear();
			lstSearch->BeginUpdate();
			backgroundWorkerSearch->RunWorkerAsync(gcnew SearchRequest(txtSearch->Text, chkRegex->Checked, chkCaseSensitive->Checked, chkWhole->Checked));
		}
		
		void cancelSearch() {
			mainStatus->removeStatusText("Search in progress");
			mainStatus->addStatusText("Search cancelled", 5, false, true);
			backgroundWorkerSearch->CancelAsync();
		}
		 
		 void testEntry(IDSItem^ eN, BackgroundWorker^ bw, SearchRequest^ sr, Regex^ r, int a, DLLInterface^ dll, bool infocard) {
			if(eN->text != "") {
				if(sr->Regex) {
					if(r->IsMatch(eN->text))
						bw->ReportProgress(a % 100, gcnew SearchResult(eN, infocard, a, dll));
				} else {
					if(sr->WholeStrings && eN->text->Equals(sr->Query, sr->CaseSensitive ? StringComparison::InvariantCulture : StringComparison::InvariantCultureIgnoreCase))
						bw->ReportProgress(0, gcnew SearchResult(eN, infocard, a, dll));
					else if(!sr->WholeStrings && eN->text->IndexOf(sr->Query, sr->CaseSensitive ? StringComparison::InvariantCulture : StringComparison::InvariantCultureIgnoreCase) != -1)
						bw->ReportProgress(0, gcnew SearchResult(eN, infocard, a, dll));
				}
			}
		 }
		 
private: System::Void backgroundWorkerSearch_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				BackgroundWorker^ bw = (BackgroundWorker^) sender;
				SearchRequest^ sr = (SearchRequest^) e->Argument;
				Regex^ r;
				if(sr->Regex) r = gcnew Regex(sr->Query);
				for each(DLLInterface^ d in dlls) {
					if(d->Loaded) {
						for(int a = 0; a < 0x10000; a++) {
							IDSItem^ eN = d->ObjL[a, false], ^ eI = d->ObjL[a, true];
							testEntry(eN, bw, sr, r, a, d, false);
							testEntry(eI, bw, sr, r, a, d, true);
						}
					}
				}
		 }
private: System::Void backgroundWorkerSearch_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
			SearchResult^ sr = (SearchResult^) e->UserState;
			
			ListViewItem^ i = gcnew ListViewItem("" + (sr->Index + sr->ID * 0x10000));
			i->SubItems->Add(sr->DllName);
			i->SubItems->Add("" + sr->Index);
			i->SubItems->Add(sr->Infocard ? "Infocard" : "Name");
			i->SubItems->Add(SimpleInfocards::StripTags(sr->Item->text));
			lstSearch->Items->Add(i);
			
			if(e->ProgressPercentage == 0) lstSearch->Update();
		 }
private: System::Void backgroundWorkerSearch_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			lstSearch->EndUpdate();
			mainStatus->removeStatusText("Search in progress");
			mainStatus->addStatusText("Search completed", 5, false, true);
		 }
private: System::Void txtSearch_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			if(e->KeyChar == (wchar_t) 0xa) {
				e->Handled = true;
			}
		 }
private: System::Void lstSearch_ItemActivate(System::Object^  sender, System::EventArgs^  e) {
			if(lstSearch->SelectedItems->Count == 1) {
				int index = -1;
				if(Int32::TryParse(lstSearch->SelectedItems[0]->SubItems[0]->Text, index)) {
					mainTab->SelectedTab = editTab;
					String^ dll = lstSearch->SelectedItems[0]->SubItems[1]->Text;
					int a = 0;
					for each(Object^ o in comboDLLExplorer->Items) {
						if(((String^) o)->Equals(dll)) {
							comboDLLExplorer->SelectedIndex = a;
							//System::Threading::Thread::Sleep(100);
							break;
						}
						a++;
					}
					showNewEntry(index);
				}
			}
		 }
private: System::Void btnImportLoad_Click(System::Object^  sender, System::EventArgs^  e) {
			if(File::Exists(txtPathImport->Text)) importLoad(txtPathImport->Text);
		 }
		 
		 // Add color coding, reordering by column
		 void importLoad(String^ path) {
			StreamReader^ sr = gcnew StreamReader(txtPathImport->Text);
			lstImportResults->Items->Clear();
			
			int importCount = 0, badCount = 0;
			
			Regex^ stripComments = gcnew Regex("(?<!\\\\);(.*)$", static_cast<RegexOptions>(RegexOptions::IgnoreCase | RegexOptions::Multiline | RegexOptions::CultureInvariant | RegexOptions::Compiled));
			
			String^ l = "";
			int lineID = 0;
			importReadLine(sr, l, lineID, stripComments);
			while(l != nullptr) {
				int id = -1;
				String^ sID = l;
				
				if(Int32::TryParse(sID, id)) {
					importReadLine(sr, l, lineID, stripComments);
					if(l->Trim() == "INFOCARD" || l->Trim() == "NAME") {
						DLLEntry e = l == "INFOCARD" ? DLLEntry::Infocard : DLLEntry::Name;
						
						StringBuilder^ entry = gcnew StringBuilder();
						importReadLine(sr, l, lineID, stripComments, false);
						
						if(l == "///BEGIN///") {
							importReadLine(sr, l, lineID, stripComments);
							for(; l != "///END///" && l != nullptr; importReadLine(sr, l, lineID, stripComments))
								entry->AppendLine(l);
						} else
							entry->Append(l->Replace("\\n", "\n")->Replace("\\r", "\r")->Replace("\\;", ";"));
						
						importReadLine(sr, l, lineID, stripComments);
						
						lstImportResults->Items->Add(gcnew ListViewItem(gcnew array<String^> {"" + id, e == DLLEntry::Infocard ? "Infocard" : "Name", e == DLLEntry::Infocard ? SimpleInfocards::StripTags(entry->ToString()) : entry->ToString()}));
						importCount++;
					} else {
						lstImportResults->Items->Add(gcnew ListViewItem(gcnew array<String^> {"" + id, "Unknown", "ERROR: Unexpected entry at line " + lineID + ". Expected INFOCARD or NAME."}));
						badCount++;
					}
				} else {
					lstImportResults->Items->Add(gcnew ListViewItem(gcnew array<String^> {"" + id, "Unknown", "ERROR: Unexpected entry at line " + lineID + ". Expected integer."}));
					importReadLine(sr, l, lineID, stripComments);
					badCount++;
				}
			}
			
			sr->Close();
			if(badCount == 0)
				txtImportMessage->Text = "Successfully loaded " + importCount + " entries. Press import to integrate in the current DLL set.";
			else
				txtImportMessage->Text = "Loaded " + importCount + " entries with " + badCount + " error" + (badCount == 1 ? "" : "s") + ". Press import to integrate in the current DLL set.";
		 }
		 
		 void importReadLine(StreamReader^ sr, String^ &l, int &ID, Regex^ stripComments) {
			importReadLine(sr, l, ID, stripComments, true);
		 }
		 
		 void importReadLine(StreamReader^ sr, String^ &l, int &ID, Regex^ stripComments, bool ignoreBlankLines) {
			do {
				l = sr->ReadLine();
				if(l != nullptr) {
					l = stripComments->Replace(l, "");
					ID++;
				}
			} while((l == "" && ignoreBlankLines) && l != nullptr);
		 }
private: System::Void btnBrowseImport_Click(System::Object^  sender, System::EventArgs^  e) {
			if(openImport->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				txtPathImport->Text = openImport->FileName;
		 }
};
}