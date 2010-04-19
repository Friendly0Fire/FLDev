#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Threading;

namespace Interfaces
{
	public ref class ProcessingClass {
		public:
			delegate void ProcessingHandler(int current, int total);
			event ProcessingHandler^ Processing;
		protected:
			void OnProcessing(int current, int total);
	};

	public ref class SimpleListItem {
		public:
			SimpleListItem( String ^name, String ^value);
			virtual String ^ToString() override;

			property String^ value {
				String^ get() {
					return trueVal;
				}
				void set(String^ param) {
					trueVal = param;
				}
			}
			property String^ display {
				String^ get() {
					return displayName;
				}
				void set(String^ param) {
					displayName = param;
				}
			}

		private:
			String ^displayName;
			String ^trueVal;
		public:
			array<String^>^ miscInfoString;
			array<int>^ miscInfoInt;
	};

	public ref class CSVParser : ProcessingClass {
		public:
			CSVParser( String ^text, String^ filename );
			CSVParser( CSVParser^ oldcsv );
			bool Parse();
			int getCol( String^ name );
			property array<String ^, 2>^ objects {
				array<String ^, 2>^ get() {
					return objs;
				}
				void set(array<String ^, 2>^ param) {}
			}
			property int lineCount {
				int get() {
					return lines;
				}
				void set(int param) {}
			}
			property int columnCount {
				int get() {
					return cols;
				}
				void set(int param) {}
			}
			property String^ fileName {
				String^ get() {
					return file->Substring(file->LastIndexOf("\\")+1);
				}
				void set(String^ param) {}
			}
			property String^ filePath {
				String^ get() {
					return file->Substring(0, file->LastIndexOf("\\")+1);
				}
				void set(String^ param) {}
			}
			property int nameIndex {
				int get() {
					return nameCol;
				}
				void set(int param) {
					if(param < cols && param >= 0)
						nameCol = param;
				}
			}
			property String^ csvcontent {
				String^ get() {
					return content;
				}
				void set(String^ param) {}
			}
			int start_eff, end_eff;
			
		private:
			array<String ^, 2>^ objs;
			int lines, cols, nameCol;
			String^ file,^ content;
	};
}