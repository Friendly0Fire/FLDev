#pragma once

using namespace System;
using namespace System::Text::RegularExpressions;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace Interfaces;

namespace Utilities {
	public ref class ProcessBarItem {
		public:
			ProcessBarItem(String^ text, int initTicks, bool prog);

			property int TimeLeft {
				int get() {
					return timeleft;
				}
			}
			property String^ Text {
				String^ get() {
					return txt;
				}
			}
			property bool Progress {
				bool get() {
					return progress;
				}
			}
			void Decrement();
			virtual bool Equals(Object^ obj) override;
			virtual String^ ToString() override;
		private:
			int timeleft;
			bool progress;
			String^ txt;
	};

	public enum class ErrorType {
		Unknown = -1,
		Notice = 0,
		Warning = 1,
		Error = 2
	};

	public ref class Error {
	private:
		ErrorType type;
		String^ msg;
		static Regex^ messageMatch = gcnew Regex("^.+ : (?<type>(WARNING)|(NOTICE)|(ERROR)):(?<message>.+)$");
		int count;
	public:
		Error(String^ message) {
			Match^ m = messageMatch->Match(message);
			try {
				if(m->Groups["type"]->Value == "NOTICE") type = ErrorType::Notice;
				else if(m->Groups["type"]->Value == "WARNING") type = ErrorType::Warning;
				else if(m->Groups["type"]->Value == "ERROR") type = ErrorType::Error;
				else type = ErrorType::Unknown;
				msg = m->Groups["message"]->Value;

				count = 1;
			} catch(...) {
				throw gcnew ArgumentException();
			}
		}

		property ErrorType Type {
			ErrorType get() {
				return type;
			}
		}

		property String^ Message {
			String^ get() {
				return msg;
			}
		}

		property int Count {
			int get() {
				return count;
			}
		}

		int Increment() {
			return ++count;
		}

		virtual bool Equals(Object^ obj) override {
			if( this->GetType()->Equals(obj->GetType()) ) {
				Error^ o = (Error^) obj;
				if(o->Message == this->Message && o->Type == this->Type)
					return true;
			}
			return false;
		}
	};

	public ref class ListViewItemComparer : public IComparer {
	private:
	   int col;
	   bool descending, numeral;

	public:
	   ListViewItemComparer()
	   {
		  col = 0;
		  numeral = false;
		  descending = true;
	   }

	   ListViewItemComparer( int column, bool numeric, bool desc )
	   {
		  col = column;
		  numeral = numeric;
		  descending = desc;
	   }

	   virtual int Compare( Object^ x, Object^ y )
	   {
		   if(numeral) {
			   int a = Int32::Parse((dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text);
			   int b = Int32::Parse((dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text);
			   return (descending ? 1 : -1) * (b - a);
		   } else
				return (descending ? 1 : -1) * String::Compare( (dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text,
														 (dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text );
	   }

	   property int Column {
		   int get() {
			   return col;
		   }
	   }

	   property bool Descending {
		   bool get() {
			   return descending;
		   }
	   }
	};
	
	public ref class SearchRequest {
		public:
			SearchRequest(String^ q, bool rg, bool cs, bool ws) {
				query = q;
				regex = rg;
				caseSensitive = cs;
				wholeStrings = ws;
			}
			
			property String^ Query {
				String^ get() { return query; }
			}
			
			property bool Regex {
				bool get() { return regex; }
			}
			
			property bool CaseSensitive {
				bool get() { return caseSensitive; }
			}
			
			property bool WholeStrings {
				bool get() { return wholeStrings; }
			}
		private:
			String^ query;
			bool regex, caseSensitive, wholeStrings;
	};
	
	public ref class SearchResult {
		public:
			SearchResult(IDSItem^ item, bool infocard, int index, DLLInterface^ dll) {
				i = item;
				ix = index;
				info = infocard;
				dllName = IO::Path::GetFileName(dll->DllFile);
				dllId = dll->ID;
			}
			
			property IDSItem^ Item {
				IDSItem^ get() { return i; }
			}
			
			property bool Infocard {
				bool get() { return info; }
			}
			
			property int Index {
				int get() { return ix; }
			}
			
			property int ID {
				int get() { return dllId; }
			}
			
			property String^ DllName {
				String^ get() { return dllName; }
			}
		private:
			IDSItem^ i;
			bool info;
			int ix, dllId;
			String^ dllName;
	};
}