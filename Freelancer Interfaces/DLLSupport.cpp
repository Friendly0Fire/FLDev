#include "Stdafx.h"
#include "includes.h"

using namespace Interfaces;
using namespace System::IO;

DLLInterface::DLLInterface(String ^dllPath, int id) {
	dllID = id;
	LastEmpty = -1;
	if(Path::IsPathRooted(dllPath))
		dllName = dllPath;
	else
		dllName = Path::Combine(Directory::GetCurrentDirectory(), dllPath);
	names = gcnew array<IDSItem ^>(0x10000);
	infocards = gcnew array<IDSItem ^>(0x10000);
	LastUpdateResult = false;
	nameCount = 0;
	infoCount = 0;
	bothCount = 0;
}

void DLLInterface::Parse() {
	String^ fullDLLPath = String::Copy(dllName);
	SetLastError((DWORD) 0);
	hinst = LoadLibraryW( (LPWSTR) (char*) (void*) Marshal::StringToHGlobalAuto(fullDLLPath) );
	DWORD lasterr = GetLastError();
	bool hasCheckedLang = false;
	if(lasterr == 0) {
		loaded = true;
		StringBuilder ^sb;
		for(int a = 0; a < 0x10000; a++) {
			LPWSTR nameContent = new WCHAR[65536];
			int result = LoadStringW(hinst, (UINT) a, nameContent, 65536);
			if(result) {
				names[a] = gcnew IDSItem(Marshal::PtrToStringUni( (IntPtr) nameContent ));
				infocards[a] = gcnew IDSItem( "" );
				nameCount++;
			} else names[a] = gcnew IDSItem( "" );
			HRSRC resource = FindResourceW( hinst, MAKEINTRESOURCEW(a), MAKEINTRESOURCEW(23) );

			LPWSTR resContent;
			if(resource) {
				resContent = (LPWSTR) (LockResource( LoadResource( hinst, resource ) ));
				if(resContent) {
					int resSize = SizeofResource(hinst, resource) / 2;
					sb = gcnew StringBuilder();
					for(int b = 0; b < resSize; b++) {
						sb->Append(resContent[b].ToString());
					}
					String^ sbs = sb->ToString();
					sbs = sbs->TrimEnd(gcnew array<wchar_t>{ '\n', ' ' });
					infocards[a] = gcnew IDSItem(sbs);
					infoCount++;
				}
			} else {
				infocards[a] = gcnew IDSItem( "" );
				if(LastEmpty == -1 && a > 1) LastEmpty = a;
			}

			if(result && resource && resContent) {
				nameCount--;
				infoCount--;
				bothCount++;
			}
			
			delete []nameContent;
		}
		FreeLibrary( hinst );
	} else
		loaded = false;
}

void DLLInterface::Apply() {
	String^ filepath = String::Copy(dllName);
	LastUpdateResult = false;

	if(loaded == true) {
		bool hasModified = false;
		for(int z = 0; z < infocards->Length; z++) {
			if(infocards[z]->modified == true || names[z]->modified == true) {
				hasModified = true;
				break;
			}
		}

		if(hasModified == true) {
			HANDLE resUpdate;
			String^ dllshortname = dllName->Substring(dllName->LastIndexOf("\\")+1, dllName->Length-1-dllName->LastIndexOf("\\"));
			String^ dllshortpath = dllName->Substring(0, dllName->LastIndexOf("\\"));
			filepath = filepath->Trim(gcnew array<wchar_t>{'\\', ' '});
			String^ finalpath = "";
			int overwrite = 0;
			if(filepath == "") filepath = dllshortpath;
			else if(Directory::Exists(filepath) == false)
				Directory::CreateDirectory(filepath);
			finalpath = String::Concat(filepath, "\\", dllshortname);
			if(File::Exists(finalpath)) {
				int bakNum = 1;
				for(; File::Exists(String::Concat(finalpath, ".bak", bakNum.ToString())); bakNum++) {}
				File::Copy(finalpath, String::Concat(finalpath, ".bak", bakNum.ToString()), true);
				if(dllName != finalpath)
					File::Copy(dllName, finalpath, true);
			} else
				File::Copy(dllName, finalpath, true);
			resUpdate = BeginUpdateResourceW( (LPCWSTR) (char*) (void*) Marshal::StringToHGlobalUni(finalpath), FALSE);
			int addedLength = 0;
			for(int a = 0; a < 0x10000; a++) {
				if(infocards[a]->modified == true) {
					infocards[a]->Update();
					if(infocards[a]->text != "") {
						String^ info = String::Concat("a", infocards[a]->text, "  ");
						IntPtr cnt = Marshal::StringToHGlobalUni(info);
						Byte *infopnt = (Byte*) (LPVOID) cnt;
						*infopnt = 0xFF;
						infopnt++;
						*infopnt = 0xFE;
						addedLength += info->Length*2 + 1;
						UpdateResourceW(resUpdate, MAKEINTRESOURCEW(23), MAKEINTRESOURCEW(a), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPVOID) cnt, (DWORD) (info->Length*2 + 1));
					} else
						UpdateResourceW(resUpdate, MAKEINTRESOURCEW(23), MAKEINTRESOURCEW(a), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPVOID) nullptr, (DWORD) (0));
				}
				if(a % 16 == 0) {
					bool update = false;
					int length = 0;
					for(int b = 0; b < 16; b++) {
						if(names[a+b]->modified == true) {
							update = true;
							names[a+b]->Update();
						}
						length += names[a+b]->text->Length + 1;
					}
					if(update == true) {
						short *buffer = new short[length];
						int count = 0;
						bool not_empty = false;
						for(int z = 0; z < length; count++) {
							buffer[z] = names[a+count]->text->Length;
							for(int y = 0; y < buffer[z]; y++) {
								buffer[z+1+y] = (names[a+count]->text->ToCharArray(y, 1))[0];
								if(buffer[z+1+y] != 0)
									not_empty = true;
							}
							z += buffer[z] + 1;
						}

						if(count == 16) {
							if(not_empty)
								UpdateResourceW(resUpdate, MAKEINTRESOURCEW(6), MAKEINTRESOURCEW(a/16+1), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPVOID) buffer, (DWORD) (length*2));
							else
								UpdateResourceW(resUpdate, MAKEINTRESOURCEW(6), MAKEINTRESOURCEW(a/16+1), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPVOID) NULL, (DWORD) (0));
						}

						delete buffer;
					}
					if(addedLength >= 2048) {
						EndUpdateResource(resUpdate, FALSE);
						resUpdate = BeginUpdateResourceW( (LPCWSTR) (char*) (void*) Marshal::StringToHGlobalUni(finalpath), FALSE);
						addedLength = 0;
					}
				}
			}

			EndUpdateResource(resUpdate, FALSE);
		}
	}
	LastUpdateResult = true;
}

int DLLInterface::EntriesCount() {
	return nameCount + infoCount + bothCount;
}

int DLLInterface::Localize(int id, bool local) {
	if(!local)
		return id - 0x10000 * dllID;
	else
		return id;
}

String^ DLLInterface::GetEntry( int id, bool infocard, bool local ) {
	id = Localize(id, local);
	if(!infocard)
		return names[id]->text;
	else
		return infocards[id]->text;
}

DLLEntry DLLInterface::GetEntryType( int id, bool local ) {
	id = Localize(id, local);
	if(names[id]->text != "" && infocards[id]->text == "")
		return DLLEntry::Name;
	else if(names[id]->text == "" && infocards[id]->text != "")
		return DLLEntry::Infocard;
	else if(names[id]->text != "" && infocards[id]->text != "")
		return DLLEntry::Both;
	else
		return DLLEntry::None;
}

void DLLInterface::SetEntry( int id, String^ text, bool infocard, bool local ) {
	DLLEntry orgEntry = GetEntryType(id, local);
	id = Localize(id, local);
	if(infocard == false)
		names[id]->text = text;
	else
		infocards[id]->text = text;
	UpdateCounts(id, local, orgEntry);
}

void DLLInterface::UpdateCounts(int id, bool local, DLLEntry orgEntry) {
	DLLEntry newEntry = GetEntryType(id, local);
	switch(orgEntry) {
		case DLLEntry::Name:
			nameCount--;
			break;
		case DLLEntry::Infocard:
			infoCount--;
			break;
		case DLLEntry::Both:
			bothCount--;
			break;
	}
	switch(newEntry) {
		case DLLEntry::Name:
			nameCount++;
			break;
		case DLLEntry::Infocard:
			infoCount++;
			break;
		case DLLEntry::Both:
			bothCount++;
			break;
	}
}

// Add Clear functions

void DLLInterface::CancelSetEntry( int id, bool infocard, bool local ) {
	DLLEntry orgEntry = GetEntryType(id, local);
	id = Localize(id, local);
	if(!infocard)
		names[id]->Revert();
	else
		infocards[id]->Revert();
	UpdateCounts(id, local, orgEntry);
}

bool DLLInterface::IsModified( int id, bool infocard, bool local ) {
	id = Localize(id, local);
	if((names[id]->modified == true && !infocard) || (infocards[id]->modified == true && infocard))
		return true;
	else
		return false;
}

int DLLInterface::GetNextEmptyEntry() {
	for(int a = 0; a < 0x10000; a++) {
		if( names[LastEmpty+a]->text == "" && infocards[LastEmpty+a]->text == "") {
			LastEmpty += a;
			return LastEmpty;
		}
	}
	return -1;
}

void DLLInterface::ResetNextEmpty() {
	LastEmpty = 0;
	GetNextEmptyEntry();
}

int DLLInterface::GetEmpty(int id, bool local) {
	id = Localize(id, local);
	for(int a = id+1; a < 0x10000; a++) {
		if( names[a]->text == "" && infocards[a]->text == "") {
			return a;
		}
	}
	return -1;
}

array<int>^ DLLInterface::Search(String^ needle, bool case_sensitive, bool whole) {
	return this->Search(needle, 0, case_sensitive, whole, -1);
}

array<int>^ DLLInterface::Search(String^ needle, bool case_sensitive, bool whole, int type_excl) {
	return this->Search(needle, 0, case_sensitive, whole, type_excl);
}

array<int>^ DLLInterface::Search(String^ needle, int offset, bool case_sensitive, bool whole) {
	return this->Search(needle, offset, case_sensitive, whole, -1);
}

array<int>^ DLLInterface::Search(String^ needle, int offset, bool case_sensitive, bool whole, int type_excl) {
	array<int>^ find_vals = gcnew array<int>(0x10000);
	int find_count = 0;
	StringComparison case_s = StringComparison::Ordinal;
	if(case_sensitive == false) case_s = StringComparison::OrdinalIgnoreCase;
	for(int a = 0; a < 0x10000; a++) {
		if(whole == false) {
			if( (names[a]->text->IndexOf(needle, case_s) >= 0 && (type_excl == -1 || type_excl == 0)) || (infocards[a]->text->IndexOf(needle, case_s) >= 0 && (type_excl == -1 || type_excl == 1)) ) {
				find_vals[find_count] = a + offset * 0x10000;
				find_count++;
			}
		} else {
			if( (names[a]->text->Equals(needle, case_s) && (type_excl == -1 || type_excl == 0)) || (infocards[a]->text->Equals(needle, case_s) && (type_excl == -1 || type_excl == 1)) ) {
				find_vals[find_count] = a + offset * 0x10000;
				find_count++;
			}
		}
	}
	array<int>^ final = gcnew array<int>(find_count);
	Array::Copy(find_vals, final, find_count);
	return final;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

DLLManager::DLLManager( array<String ^> ^ dllpaths ) {
	dlls = gcnew array<DLLInterface ^>(dllpaths->Length);
	
	for(int a = 0; a < dllpaths->Length; a++) {
		dlls[a] = gcnew DLLInterface( dllpaths[a], a );
		dlls[a]->Parse();
	}

	dllPaths = dllpaths;
}

int DLLManager::getDLLCount() {
	return dlls->Length;
}

void DLLManager::updateDLLPath( String^ dllpath, int id ) {
	dlls[id] = gcnew DLLInterface( dllpath, id );
	dlls[id]->Parse();
}

void DLLManager::mApply(String^ folderpath) {
	bool result_state = true;
	String^ erroneous_dlls = "";
	for(int a = 0; a < dlls->Length; a++) {
		dlls[a]->Apply();
		if(dlls[a]->LastUpdateResult == false) {
			result_state = false;
			erroneous_dlls = String::Concat(erroneous_dlls, ", ", dlls[a]->DllFile->Substring(dlls[a]->DllFile->LastIndexOf("\\")+1));
		}
	}

	if(!result_state)
		throw gcnew Exception(String::Concat("There were errors during update. The following DLLs have not been updated successfully: ", erroneous_dlls->Trim(gcnew array<wchar_t>{' ', ','})));
}

void DLLManager::mApply() {
	this->mApply("");
}

String ^DLLManager::mGetEntry( int id, bool infocard ) {
	return dlls[id / 0x10000][ id, infocard ];
}

String ^DLLManager::mGetEntry( int id, int dll, bool infocard ) {
	return dlls[dll]->EntryL[ id, infocard ];
}

IDSItem ^DLLManager::mGetEntryObj( int id, bool infocard ) {
	return dlls[id / 0x10000]->Obj[ id, infocard ];
}

IDSItem ^DLLManager::mGetEntryObj( int id, int dll, bool infocard ) {
	return dlls[dll]->ObjL[ id, infocard ];
}

DLLEntry DLLManager::mGetEntryType( int id ) {
	int b;
	for(int a = 0; a < this->dlls->Length; a++) {
		b = a * 0x10000;
		if(id > b && id < ( b + 0x10000) )
			return mGetEntryType(id - b, a);
	}
	return DLLEntry::None;
}

DLLEntry DLLManager::mGetEntryType( int id, int dll ) {
	return dlls[dll]->TypeL[ id ];
}

int DLLManager::mGetEmpty( int id ) {
	int b, c;
	for(int a = 0; a < this->dlls->Length; a++) {
		b = a * 0x10000;
		if( b >= (Math::Floor(id / 0x10000) * 0x10000) ) {
			c =  dlls[a]->GetEmpty( id - b, true );
			if(c >= 0)
				return c + b;
		}
	}
	return -1;
}

bool DLLManager::mIsModified( int id, bool infocard ) {
	int b;
	for(int a = 0; a < this->dlls->Length; a++) {
		b = a * 0x10000;
		if(id > b && id < ( b + 0x10000) )
			return dlls[a]->ModifiedL[ id - b, infocard ];
	}
	return false;
}

String^ DLLManager::mGetPath( int id ) {
	return dlls[id]->DllFile;
}

array<int>^ DLLManager::mSearch(String^ needle, bool case_sensitive, bool whole) {
	return this->mSearch(needle, case_sensitive, whole, -1);
}

array<int>^ DLLManager::mSearch(String^ needle, bool case_sensitive, bool whole, int type_excl) {
	array<array<int>^>^ arrays = gcnew array<array<int>^>(dlls->Length);
	array<int>^ final_array;
	int final_count = 0, add_count = 0;
	for(int a = 0; a < dlls->Length; a++) {
		arrays[a] = mSearch(needle, a, case_sensitive, whole, type_excl);
		final_count += arrays[a]->Length;
	}
	final_array = gcnew array<int>(final_count);
	for(int a = 0; a < dlls->Length; a++) {
		Array::Copy(arrays[a], 0, final_array, add_count, arrays[a]->Length);
		add_count += arrays[a]->Length;
	}
	return final_array;
}
array<int>^ DLLManager::mSearch(String^ needle, int dll, bool case_sensitive, bool whole) {
	return this->mSearch(needle, dll, case_sensitive, whole, -1);
}
array<int>^ DLLManager::mSearch(String^ needle, int dll, bool case_sensitive, bool whole, int type_excl) {
	if(dlls[dll]->Loaded == true) {
		return dlls[dll]->Search( needle, dll, case_sensitive, whole, type_excl );
	} else {
		array<int>^ empty = { };
		return empty;
	}
}

bool DLLManager::mIsLoaded( int dllID ) {
	return dlls[dllID]->Loaded;
}

void DLLManager::mSetEntry( int id, String^ text, bool infocard ) {
	int b;
	for(int a = 0; a < this->dlls->Length; a++) {
		b = a * 0x10000;
		if(id > b && id < ( b + 0x10000) )
			mSetEntry( (id - b), a, text, infocard);
	}
}

void DLLManager::mSetEntry( int id, int dll, String^ text, bool infocard ) {
	dlls[dll]->EntryL[ id, infocard ] = text;
}

void DLLManager::mCancelSetEntry( int id, bool infocard ) {
	int b;
	for(int a = 0; a < this->dlls->Length; a++) {
		b = a * 0x10000;
		if(id > b && id < ( b + 0x10000) )
			dlls[a]->CancelSetEntry( (id - b), infocard, true );
	}
}

int DLLManager::mGetNextEmptyEntry( String^ dllPath ) {
	for(int a = 0; a < this->dlls->Length; a++) {
		if( dllPath->ToLower() == dlls[a]->DllFile->ToLower() ) {
			int nextID = dlls[a]->GetNextEmptyEntry();
			if(nextID > 0)
				return nextID + a*0x10000;
			else
				return -1;
		}
	}
	return -1;
}

int DLLManager::mGetNextEmptyEntry( int dllID ) {
	int nextID = dlls[dllID]->GetNextEmptyEntry();
	if(nextID > 0)
		return nextID + dllID*0x10000;
	else
		return -1;
}

int DLLManager::localize(int id) {
	while(id > 0x10000)
		id -= 0x10000;
	return id;
}

int DLLManager::getDllId(int id) {
	int a = 0;
	for(; id > 0x10000; a++)
		id -= 0x10000;
	return a;
}

System::String^ SimpleInfocards::XMLToSimple(String^ content) {
	//Make a new StringBuilder; it will hold the final text with BBCode
	StringBuilder^ content_final = gcnew StringBuilder();
	//Replace the basic stuff; either it doesn't code anything worthwhile or it always means the same thing
	content = content->Replace("\n", "");
	content = content->Replace("\r", "");
	content = content->Replace("<PARA/><POP/></RDL>", "");
	content = content->Replace("<?xml version=\"1.0\" encoding=\"UTF-16\"?><RDL><PUSH/>", "");
	content = content->Replace("<TEXT>", "");
	content = content->Replace("</TEXT>", "");
	content = content->Replace("<PARA/>", Environment::NewLine);
	//Store the length of the now stripped-down content
	int clen = content->Length;
	//Store the whole content String as a wchar array
	array<wchar_t>^ cnchar = content->ToCharArray();
	//Those will hold the currently active markers; it is important to keep them as if, for example, the text becomes bold and then italic afterwards, you will find the second opening tag will describe the text as being both italic and bold.
	//XML TRA tags aren't working as masks which can be applied on top of eachother (ala BBCode): each time a TRA tag is opened, all previous styles must be reapplied.
	String^ style_markers = "", ^ align_marker = "", ^ color_marker = "000000";
	//lastc holds the last value of "a"; that is, the last position of a parsed character
	int lastc = 0;
	for(int a = 0; a < clen; a++) {
		if(cnchar[a] == '<') {
			String^ tag = content->Substring(a, content->IndexOf(">", a) - a + 1);
			content = content->Remove(a, tag->Length);
			cnchar = content->ToCharArray();
			clen = content->Length;
			int new_pos = a;
			if(new_pos >= Environment::NewLine->Length) {
				while(content->Substring(new_pos - Environment::NewLine->Length, Environment::NewLine->Length) == Environment::NewLine) {
					new_pos -= Environment::NewLine->Length;
					if(new_pos < Environment::NewLine->Length) break;
				}
			}
			a = new_pos;
			if(a > lastc)
				content_final->Append(content->Substring(lastc, a - lastc));
			if(tag->IndexOf("<TRA") != -1) {
				String^ data_string = tag->Substring(tag->IndexOf("data=\"") + 6, tag->IndexOf("\"", tag->IndexOf("data=\"") + 6) - tag->IndexOf("data=\"") - 6);
				String^ dat = "";
				String^ colordat = "";
				if(data_string->IndexOf("0x") != -1) {
					colordat = data_string->Substring(2, 6);
					dat = dec2Bin(Int32::Parse(data_string->Substring(2, data_string->Length - 2), System::Globalization::NumberStyles::HexNumber));
				} else {
					int data = Int32::Parse(data_string);
					dat = dec2Bin(data);
					colordat = data.ToString("X");
					if(colordat->Length >= 2)
						colordat = colordat->Remove(colordat->Length - 2, 2);
					else
						colordat = "";
				}
				if(colordat->Length > 0) {
					for(int b = colordat->Length; b < 6; b++) {
						colordat = String::Concat("0", colordat);
					}
					String^ reversed_colordat = String::Concat(colordat->Substring(4, 2), colordat->Substring(2, 2), colordat->Substring(0, 2));
					colordat = reversed_colordat;
				} else
					colordat = "000000";
				String^ styledat = dat->Substring(dat->Length - 8, 8);
				String^ prev_style_markers = style_markers;
				style_markers = "";
				String^ style_markers_1 = "", ^ style_markers_2 = "";
				if(prev_style_markers->IndexOf("[b]") != -1)
					style_markers_1 = String::Concat(style_markers_1, "[/b]");
				if(prev_style_markers->IndexOf("[i]") != -1)
					style_markers_1 = String::Concat(style_markers_1, "[/i]");
				if(prev_style_markers->IndexOf("[u]") != -1)
					style_markers_1 = String::Concat(style_markers_1, "[/u]");

				if(color_marker != colordat) {
					if(color_marker != "000000")
						content_final->Append("[/color]");
				}

				content_final->Append(style_markers_1);

				while( (a + Environment::NewLine->Length) < clen && content->Substring(a, Environment::NewLine->Length) == Environment::NewLine) {
					content_final->Append(Environment::NewLine);
					a += Environment::NewLine->Length;
					if(a + Environment::NewLine->Length > content->Length) break;
				}
				lastc = a;
				if(styledat->Substring(7, 1) == "1")
					style_markers_2 = String::Concat(style_markers_2, "[b]");
				if(styledat->Substring(6, 1) == "1")
					style_markers_2 = String::Concat(style_markers_2, "[i]");
				if(styledat->Substring(5, 1) == "1")
					style_markers_2 = String::Concat(style_markers_2, "[u]");

				if(color_marker != colordat) {
					if(colordat != "000000")
						content_final->Append(String::Concat("[color=#", colordat, "]"));
					color_marker = colordat;
				}

				content_final->Append(style_markers_2);
				style_markers = String::Concat(style_markers_1, style_markers_2);

			} else {
				String^ prev_align_marker = align_marker;
				align_marker = "";
				if(prev_align_marker == "[center]")
					align_marker = "[/center]";
				else if(prev_align_marker == "[left]")
					align_marker = "[/left]";
				else if(prev_align_marker == "[right]")
					align_marker = "[/right]";
				content_final->Append(align_marker);
				align_marker = "";

				while( (a + Environment::NewLine->Length) < clen && content->Substring(a, Environment::NewLine->Length) == Environment::NewLine) {
					content_final->Append(Environment::NewLine);
					a += Environment::NewLine->Length;
					if(a + Environment::NewLine->Length > content->Length) break;
				}
				lastc = a;

				if(tag == "<JUST loc=\"center\"/>")
					align_marker = "[center]";
				else if(tag == "<JUST loc=\"left\"/>")
					align_marker = "[left]";
				else if(tag == "<JUST loc=\"right\"/>")
					align_marker = "[right]";

				content_final->Append(align_marker);
			}
			a--;
		}
	}
	content_final->Append(content->Substring(lastc, clen - lastc));

	String^ prev_style_markers2 = style_markers;
	style_markers = "";
	if(prev_style_markers2->IndexOf("[b]") != -1)
		style_markers = String::Concat(style_markers, "[/b]");
	if(prev_style_markers2->IndexOf("[i]") != -1)
		style_markers = String::Concat(style_markers, "[/i]");
	if(prev_style_markers2->IndexOf("[u]") != -1)
		style_markers = String::Concat(style_markers, "[/u]");
	content_final->Append(style_markers);

	if(align_marker == "[center]")
		align_marker = "[/center]";
	else if(align_marker == "[left]")
		align_marker = "[/left]";
	else if(align_marker == "[right]")
		align_marker = "[/right]";
	content_final->Append(align_marker);

	if(color_marker != "000000")
		content_final->Append("[/color]");

	content_final->Replace("&gt;", ">");
	content_final->Replace("&lt;", "<");

	return content_final->ToString();
}
System::String^ SimpleInfocards::SimpleToXML(String^ content) {
	StringBuilder^ content_final = gcnew StringBuilder();
	content = content->Replace(">", "&gt;");
	content = content->Replace("<", "&lt;");
	content = content->Replace(Environment::NewLine, "</TEXT><PARA/><TEXT>");
	content_final->Append("<?xml version=\"1.0\" encoding=\"UTF-16\"?><RDL><PUSH/><TEXT>");
	int clen = content->Length;
	array<wchar_t>^ cnchar = content->ToCharArray();
	String^ color = "000000";
	int align = 0, lastalign = 0; // 0 = left, 1 = center, 2 = right
	int lastc = 0, style_bits = 0, last_style_bits = 0;
	for(int a = 0; a < clen; a++) {
		if(cnchar[a] == '[') {
			last_style_bits = style_bits;
			String^ tag = content->Substring(a, content->IndexOf("]", a) - a + 1);
			content = content->Remove(a, tag->Length);
			cnchar = content->ToCharArray();
			clen = content->Length;
			content_final->Append(content->Substring(lastc, a - lastc));
			lastc = a;
			if(tag->IndexOf("left") != -1 || tag->IndexOf("center") != -1 || tag->IndexOf("right") != -1) {
				if(tag == "[left]" || tag->IndexOf("[/") != -1) {
					content_final->Append("</TEXT><JUST loc=\"left\"/><TEXT>");
					align = 0;
					lastalign = align;
				} else if(tag == "[right]") {
					content_final->Append("</TEXT><JUST loc=\"right\"/><TEXT>");
					align = 2;
					lastalign = align;
				} else if(tag == "[center]") {
					content_final->Append("</TEXT><JUST loc=\"center\"/><TEXT>");
					align = 1;
					lastalign = align;
				}
			} else {
				String^ old_color = color;
				if(tag == "[b]")
					style_bits += 1;
				if(tag == "[/b]")
					style_bits -= 1;
				if(tag == "[i]")
					style_bits += 2;
				if(tag == "[/i]")
					style_bits -= 2;
				if(tag == "[u]")
					style_bits += 4;
				if(tag == "[/u]")
					style_bits -= 4;
				if(tag->IndexOf("color=#") != -1)
					color = tag->Substring(8, tag->Length - 9);
				if(tag == "[/color]")
					color = "000000";
				if(a < cnchar->Length) {
					while(cnchar[a] == '[') {
						String^ tag2 = content->Substring(a, content->IndexOf("]", a) - a + 1);
						content = content->Remove(a, tag2->Length);
						cnchar = content->ToCharArray();
						clen = content->Length;
						if(tag2 == "[b]")
							style_bits += 1;
						if(tag2 == "[/b]")
							style_bits -= 1;
						if(tag2 == "[i]")
							style_bits += 2;
						if(tag2 == "[/i]")
							style_bits -= 2;
						if(tag2 == "[u]")
							style_bits += 4;
						if(tag2 == "[/u]")
							style_bits -= 4;
						if(tag2->IndexOf("color=#") != -1)
							color = tag2->Substring(8, 6);
						if(tag2 == "[/color]")
							color = "000000";
						if(tag2 == "[left]" || tag2->IndexOf("[/") != -1)
							align = 0;
						if(tag2 == "[right]")
							align = 2;
						if(tag2 == "[center]")
							align = 1;
						if(a + 1 >= cnchar->Length) break;
					}
				}
				//
				while(color->Length < 6)
					color = String::Concat("0", color);
				String^ color_reversed = String::Concat(color->Substring(4, 2), color->Substring(2, 2), color->Substring(0, 2));
				color = color_reversed;
				String^ style_bits_s = style_bits.ToString();
				while(style_bits_s->Length < 2)
					style_bits_s = String::Concat("0", style_bits_s);
				style_bits_s = String::Concat(color, style_bits_s);
				int style_mask = 0, style_def = 0;
				style_mask = -1;
				if(color == "000000")
					style_def = style_bits * -1 - 1;
				else
					style_def = 31 - style_bits;
				content_final->Append(String::Concat("</TEXT><TRA data=\"0x", style_bits_s, "\" mask=\"", style_mask.ToString(), "\" def=\"", style_def.ToString(), "\"/><TEXT>"));
				if(align != lastalign) {
					lastalign = align;
					if(align == 0)
						content_final->Append("</TEXT><JUST loc=\"left\"/><TEXT>");
					else if(align == 2)
						content_final->Append("</TEXT><JUST loc=\"right\"/><TEXT>");
					else if(align == 1)
						content_final->Append("</TEXT><JUST loc=\"center\"/><TEXT>");
				}
			}
			a--;
		}
	}
	content_final->Append(content->Substring(lastc));
	content_final->Append("</TEXT><PARA/><POP/></RDL>");
	content_final->Replace("<TEXT></TEXT>", "");
	String^ final_text = System::Text::RegularExpressions::Regex::Replace(content_final->ToString(), "<JUST (?<just>[^<>/]*)/>(?<paras>(<PARA/>)*)", "${paras}<JUST ${just}/>");
	final_text = System::Text::RegularExpressions::Regex::Replace(final_text, "<TRA (?<tra>[^<>/]*)/>(?<paras>(<PARA/>)*)", "${paras}<TRA ${tra}/>");
	return final_text;
}
String^ SimpleInfocards::dec2Bin(int i) {
	String^ b = (i < 0) ? "1" : "0";
	for (int j = 0x40000000; j > 0; j >>= 1)
		b = String::Concat(b, ((i & j) != 0) ? "1" : "0");
	return b;
}

String^ SimpleInfocards::StripTags(String^ content) {
	return Regex::Replace(content,  "<[^>]+>", " ");
}

IDSItem::IDSItem(String^ value) {
	array<wchar_t>^ arr = value->ToCharArray();
	if(arr->Length >= 1) {
		if(arr[0] == 0xFFFE || arr[0] == 0xFEFF)
			value = value->Substring(1, value->Length - 1);
	}
	txt = value;
	org = (String^) txt->Clone();

	undo = gcnew Stack<String^>();
	redo = gcnew Stack<String^>();
}

void IDSItem::Undo() {
	redo->Push(txt);
	txt = undo->Pop();
}
void IDSItem::Redo() {
	undo->Push(txt);
	txt = redo->Pop();
}
int IDSItem::canRedo() {
	return redo->Count;
}
int IDSItem::canUndo() {
	return undo->Count;
}
void IDSItem::Update() {
	undo->Clear();
	redo->Clear();
	org = (String^) txt->Clone();
}
void IDSItem::Revert() {
	undo->Clear();
	redo->Clear();
	txt = (String^) org->Clone();
}