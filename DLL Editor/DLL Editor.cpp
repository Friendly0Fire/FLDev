// DLL Editor.cpp : main project file.

#include "stdafx.h"
#include "Main.h"

using namespace DLLEditor;
using namespace Interfaces;
using namespace System::IO;
using namespace System::Threading;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Main());
	return 0;
}

void Main::browseAndLoadINI() {
	if(openFLINI->ShowDialog() == Windows::Forms::DialogResult::OK) {
		txtINIPath->Text = openFLINI->FileName;
		loadINI();
	}
}

void Main::loadINI() {
	if(File::Exists(txtINIPath->Text)) {
		lstDLLs->Items->Clear();
		INIHandler^ flini = gcnew INIHandler(gcnew FileStream(txtINIPath->Text, FileMode::Open, FileAccess::Read));
		
		dllNames = gcnew array<String^>(flini["Resources"]->CountParam["DLL"]+1);
		for(int a = 1; a < dllNames->Length; a++)
			dllNames[a] = flini["Resources"]["DLL", a-1]->Value[0];
		
		if(File::Exists(Path::Combine(Path::GetDirectoryName(flini->FilePath), "Resources.dll")))
			dllNames[0] = "Resources.dll";
		else
			dllNames[0] = "";

		flINIPath = txtINIPath->Text;
		Directory::SetCurrentDirectory(Path::GetDirectoryName(flINIPath));
		addStatusText("Reading INI");
		backgroundWorkerFLINI->RunWorkerAsync();
		this->Cursor = Cursors::WaitCursor;
	}
}

void Main::updateDLLList(Object^ sender, RunWorkerCompletedEventArgs^ e) {
	updateDLLList();
}
void Main::updateDLLList() {
	lstDLLs->Items->Clear();
	comboDLLExplorer->Items->Clear();

	int at = 0;
	for each(String^ dll in dllNames) {
		ListViewItem^ i = gcnew ListViewItem(dll);
		i->SubItems->Add(Path::GetFullPath(dll));
		i->SubItems->Add(dlls->mIsLoaded(at) ? "Loaded" : "Error");
		lstDLLs->Items->Add(i);
		comboDLLExplorer->Items->Add(dll);
		at++;
	}
}

void Main::reloadDLL() {
	if(File::Exists(txtSelectedDLLPath->Text)) {
		for each(String^ dll in dllNames) {
			if(dll->Equals(txtSelectedDLLPath->Text, StringComparison::InvariantCultureIgnoreCase))
				return;
		}
		dlls->updateDLLPath(txtSelectedDLLPath->Text, lstDLLs->SelectedIndices[0]);
		dllNames[lstDLLs->SelectedIndices[0]] = txtSelectedDLLPath->Text;
		updateDLLList();
	}
}

bool Main::dataLossAsk() {
	if(MessageBox::Show("Continuing with the current action may result in data loss. Proceed?", "Data Loss Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button2) == Windows::Forms::DialogResult::Yes)
		return true;
	return false;
}

bool Main::confirmApply() {
	if(MessageBox::Show("Are you sure you want to apply all selected changes?", "Applying Changes", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2) == Windows::Forms::DialogResult::Yes)
		return true;
	return false;
}

void Main::RefreshList(int dllID) {
	activeDll = dllID;
	lstScroll->Value = 1;
	RefreshList(0, 0);
}

void Main::RefreshList(int start, int overwrite) {

	if(activeDll >= 0) {
		this->lstDLLExplorer->SuspendLayout();
		this->lstScroll->Maximum = chkDLLExplorerShowEmpty->Checked ? 0x10000 : dlls[activeDll]->EntriesCount();

		List<String^>^ selected = gcnew List<String^>();
		for each(ListViewItem^ i in lstDLLExplorer->SelectedItems) {
			selected->Add(i->Text);
		}
		lstDLLExplorer->BeginUpdate();
		if(overwrite == 0) lstDLLExplorer->Items->Clear();
		DLLInterface^ dllFile = dlls[activeDll];
		array<ListViewItem^>^ lvic = gcnew array<ListViewItem^>(0x10000);
		bool repeat = false;
		int pass = 0;
		for(int a = start; (a-pass-start <= 1 || lstDLLExplorer->Items[a-pass-start-1]->Bounds.Bottom <= lstDLLExplorer->ClientRectangle.Bottom) && a < 0x10000; a++) {
			ListViewItem^ i = gcnew ListViewItem((a + dllFile->ID*0x10000).ToString());
			i->SubItems->Add(a.ToString());
			switch(dllFile->TypeL[a]) {
			case DLLEntry::Name:
				i->SubItems->Add("Name");
				i->SubItems->Add(dllFile->EntryL[a, false]);
				break;
			case DLLEntry::Infocard:
				i->SubItems->Add("Infocard");
				i->SubItems->Add(SimpleInfocards::StripTags(dllFile->EntryL[a, true]));
				break;
			case DLLEntry::Both:
				i->SubItems->Add("Both");
				if(!repeat) {
					i->SubItems->Add(dllFile->EntryL[a, false]);
					repeat = true;
				} else {
					i->SubItems->Add(SimpleInfocards::StripTags(dllFile->EntryL[a, true]));
					repeat = false;
				}
				break;
			case DLLEntry::None:
				if(!chkDLLExplorerShowEmpty->Checked) {
					i = nullptr;
					pass++;
				} else
					i->SubItems->Add("None");
			}
			if(i != nullptr) {
				if(overwrite == 1 || overwrite == 0) {
					lstDLLExplorer->Items->Add(i);
				} else if(overwrite == -1) {
					lstDLLExplorer->Items->Insert(0, i);
				}
			}
			if(repeat) a--;
		}
		while(lstDLLExplorer->Items->Count > 0 && lstDLLExplorer->Items[lstDLLExplorer->Items->Count-1]->Bounds.Bottom > lstDLLExplorer->ClientRectangle.Bottom)
			lstDLLExplorer->Items->RemoveAt(lstDLLExplorer->Items->Count-1);

		lstDLLExplorer->EndUpdate();
		for each(ListViewItem^ i in lstDLLExplorer->Items) {
			for each(String^ j in selected) {
				if(i->Text == j)
					i->Selected = true;
			}
		}
		this->lstDLLExplorer->ResumeLayout();
	} else {
		lstDLLExplorer->Items->Clear();
		lstDLLExplorer->Items->Add("");
	}
}

void Main::lstScroll_ValueChanged(Object^  sender, System::EventArgs^ e) {
	RefreshList(lstScroll->Value, 0);
}

System::Void Main::lstDLLExplorer_MouseWheel(System::Object^  sender, MouseEventArgs^  e) {
	if(e->Delta != 0) {
		int t = lstScroll->Value - e->Delta / 10;
		if(t < lstScroll->Minimum) t = lstScroll->Minimum;
		else if(t > lstScroll->Maximum) t = lstScroll->Maximum;
		lstScroll->Value = t;

		RefreshList(lstScroll->Value, 0);

		HandledMouseEventArgs^ he = (HandledMouseEventArgs^)e;
		he->Handled = true;
	}
}

void Main::lstDLLExplorer_ItemActivate(System::Object^  sender, System::EventArgs^  e) {
	if(lstDLLExplorer->SelectedItems->Count == 1) {
		int index = -1;
		if(Int32::TryParse(lstDLLExplorer->SelectedItems[0]->SubItems[0]->Text, index))
			showNewEntry(index);
	}
}

void Main::showNewEntry(int id) {
	changingSelectedIDS = true;

	addUndo();

	String^ e;
	DLLEntry ent = dlls->mGetEntryType(id);

	if(ent == DLLEntry::Name || ent == DLLEntry::Both)
		e = dlls->mGetEntry(id, false);
	else if(ent == DLLEntry::Infocard)
		e = dlls->mGetEntry(id, true);
	else
		e = "";

	radioType(ent);
	if(radioSInfocard->Checked) e = SimpleInfocards::XMLToSimple(e);
	txtEntry->Text = e;
	comboIDS->Text = "" + id;
	txtLocalIDS->Text = "" + dlls->localize(id);
	lblIDSInfo->Text = "DLL " + dlls->getDllId(id) + " of " + dlls->getDLLCount() + ".";
	changingSelectedIDS = false;
}

// TODO: Force changing when selected by user
void Main::radioType(DLLEntry type) {
	changingSelectedIDS = true;

	bool wasSInfo = radioSInfocard->Checked;
	switch(type) {
		case DLLEntry::Both:
		case DLLEntry::None:
			break;
		case DLLEntry::Name:
		case DLLEntry::Infocard:
			radioName->Checked = false;
			radioInfocard->Checked = false;
			radioSInfocard->Checked = false;
	}

	if(type == DLLEntry::Name) radioName->Checked = true;
	if(type == DLLEntry::Infocard) {
		if(wasSInfo)
			radioSInfocard->Checked = true;
		else
			radioInfocard->Checked = true;
	}
	changingSelectedIDS = false;
}

void Main::addUndo() {
	undoTimer->Stop();
	undoTimer->Enabled = false;

	addStatusText("Saved changes to entry", false);
	updateStatusText(false);
	int ids;
	if(!Int32::TryParse(comboIDS->Text, ids)) return;

	String^ t = txtEntry->Text;
	if(radioSInfocard->Checked) t = SimpleInfocards::SimpleToXML(t);

	dlls->mSetEntry(ids, t, radioInfocard->Checked || radioSInfocard->Checked);

	entryUndo->Enabled = true;
	entryRedo->Enabled = false;
}