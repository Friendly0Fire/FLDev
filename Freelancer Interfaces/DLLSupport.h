#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Text::RegularExpressions;
using namespace System::Collections::Generic;

namespace Interfaces
{
	public enum class DLLEntry {
		Name = 0,
		Infocard = 1,
		Both = 2,
		None = -1
	};

	public ref class IDSItem {
		public:
			IDSItem( String^ value );

			property String^ text {
				String^ get() {
					return txt;
				}
				void set(String^ param) {
					if(param == txt) return;

					undo->Push(txt);
					redo->Clear();
					txt = param;
				}
			}
			property bool modified {
				bool get() {
					if(txt != org) return true;
					else return false;
				}
			}
			property String^ Original {
				String^ get() {
					return org;
				}
			}

			void Undo();
			void Redo();
			int canRedo();
			int canUndo();
			void Update();
			void Revert();
			void Revert(bool clear);
		private:
			String^ txt, ^ org;
			Stack<String^>^ undo, ^ redo;
			
	};

	public ref class DLLInterface : ProcessingClass {
		public:
			DLLInterface(String ^dllPath, int id);
			void Apply();
			void Apply(String^ filepath);
			void Parse();
			void CancelSetEntry(int id, bool infocard, bool local);
			int GetNextEmptyEntry();
			void ResetNextEmpty();
			int GetEmpty(int id, bool local);
			array<int>^ Search(String^ needle, bool case_sensitive, bool whole);
			array<int>^ Search(String^ needle, bool case_sensitive, bool whole, int type_excl);
			array<int>^ Search(String^ needle, int offset, bool case_sensitive, bool whole);
			array<int>^ Search(String^ needle, int offset, bool case_sensitive, bool whole, int type_excl);
			int EntriesCount();

			property String^ DllFile {
				String^ get() {
					return dllName;
				}
			}
			property bool Loaded {
				bool get() {
					return loaded;
				}
			}
			property bool LastUpdateResult {
				bool get() {
					return lastupdateres;
				}
				void set(bool param) {
					lastupdateres = param;
				}
			}
			property int LangID {
				int get() {
					return languageid;
				}
				void set(int param) {
					languageid = param;
				}
			}
			property int ID {
				int get() {
					return dllID;
				}
			}

			property String^ EntryL[int, bool] {
				String^ get(int id, bool infocard) {
					return GetEntry(id, infocard, true);
				}
				void set(int id, bool infocard, String^ text) {
					SetEntry(id, text, infocard, true);
				}
			}

			property String^ default[int] {
				String^ get(int id) {
					return GetEntry(id, false, false);
				}
				void set(int id, String^ text) {
					SetEntry(id, text, false, false);
				}
			}

			property IDSItem^ Obj[int, bool] {
				IDSItem^ get(int id, bool infocard) {
					if(!infocard) return names[Localize(id, false)];
					else return infocards[Localize(id, false)];
				}
			}

			property IDSItem^ ObjL[int, bool] {
				IDSItem^ get(int id, bool infocard) {
					if(!infocard) return names[id];
					else return infocards[id];
				}
			}

			property String^ default[int, bool] {
				String^ get(int id, bool infocard) {
					return GetEntry(id, infocard, false);
				}
				void set(int id, bool infocard, String^ text) {
					SetEntry(id, text, infocard, false);
				}
			}

			property bool Modified[int, bool] {
				bool get(int id, bool infocard) {
					return IsModified(id, infocard, false);
				}
			}
			property bool ModifiedL[int, bool] {
				bool get(int id, bool infocard) {
					return IsModified(id, infocard, true);
				}
			}

			property DLLEntry Type[int] {
				DLLEntry get(int id) {
					return GetEntryType(id, false);
				}
			}
			property DLLEntry TypeL[int] {
				DLLEntry get(int id) {
					return GetEntryType(id, true);
				}
			}
		private:
			String^ GetEntry(int id, bool infocard, bool local);
			void SetEntry(int id, String^ text, bool infocard, bool local);
			bool IsModified(int id, bool infocard, bool local);
			DLLEntry GetEntryType(int id, bool local);
			int Localize(int id, bool local);
			void UpdateCounts(int id, bool local, DLLEntry orgEntry);

			HINSTANCE hinst;
			String^ dllName, ^dll_needle;
			array<IDSItem ^>^ names,^ infocards;
			int LastEmpty, languageid;
			bool loaded, lastupdateres;
			int dllID;
			int nameCount, infoCount, bothCount;
	};

	public ref class SimpleInfocards {
	public:
		static String^ XMLToSimple(String^ content);
		static String^ SimpleToXML(String^ content);
		static String^ StripTags(String^ content);
		
	private:
		static String^ dec2Bin(int i);
		static unsigned int reverseByteOrder(unsigned int i);
		
		static Regex^ justMatch = gcnew Regex("loc=\"(?<value>[^\"]+)\"", RegexOptions::Compiled | RegexOptions::IgnoreCase);
		static Regex^ traMatch = gcnew Regex("((?<data>data)|(?<mask>mask)|(?<def>def))=\"(?<value>[^\"]+)\"", RegexOptions::Compiled | RegexOptions::IgnoreCase);
		// Add whitespace shifting refex
		
		const static short JUST = 0, TRA = 1;
		const static short Left = -1, Center = 0, Right = 1;
		
		static array<String^>^ Alignments = gcnew array<String^> {"center", "right"};
	};

	public ref class DLLManager : ProcessingClass, Collections::IEnumerable {
		public:
			DLLManager( array<String ^> ^ dllpaths );
			void mApply();
			void mApply(String^ folderpath);
			void updateDLLPath( String^ dllpath, int id );
			void mCancelSetEntry(int id, bool infocard);
			bool mIsModified(int id, bool infocard);
			bool mIsLoaded(int dllID);
			String^ mGetEntry(int id, bool infocard);
			String^ mGetEntry(int id, int dll, bool infocard);
			IDSItem^ mGetEntryObj(int id, bool infocard);
			IDSItem^ mGetEntryObj(int id, int dll, bool infocard);
			void mSetEntry(int id, String^ text, bool infocard);
			void mSetEntry(int id, int dll, String^ text, bool infocard);
			int mGetNextEmptyEntry( String^ dllPath );
			int mGetNextEmptyEntry( int dllID );
			DLLEntry mGetEntryType(int id);
			DLLEntry mGetEntryType(int id, int dll);
			int mGetEmpty(int id);
			int getDLLCount();
			String^ mGetPath( int id );
			array<int>^ mSearch(String^ needle, bool case_sensitive, bool whole);
			array<int>^ mSearch(String^ needle, bool case_sensitive, bool whole, int type_excl);
			array<int>^ mSearch(String^ needle, int dll, bool case_sensitive, bool whole);
			array<int>^ mSearch(String^ needle, int dll, bool case_sensitive, bool whole, int type_excl);
			int localize(int id);
			int getDllId(int id);

			property DLLInterface^ default[int] {
				DLLInterface^ get(int id) {
					return dlls[id];
				}
			}
			
			virtual Collections::IEnumerator^ GetEnumerator() {
				return dlls->GetEnumerator();
			}
		private:
			array<DLLInterface ^> ^ dlls;
			array<String ^>^ dllPaths;
	};
}