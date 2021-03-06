#include "Stdafx.h"
#include "includes.h"

using namespace Interfaces;

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

#pragma region SimpleListItem
SimpleListItem::SimpleListItem( String ^name, String ^value) {

	this->displayName = name;
	this->trueVal = value;

}

String ^SimpleListItem::ToString() {
	return displayName;
}
#pragma endregion

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

#pragma region CSVParser
CSVParser::CSVParser(String ^text, String^ filename) {
	start_eff = 1;
	end_eff = -1;
	content = text;
	file = filename;
	if(!this->Parse())
		throw gcnew Exception();
}
CSVParser::CSVParser(CSVParser^ oldCSV) {
	nameCol = oldCSV->nameIndex;
	content = oldCSV->csvcontent;
	file = String::Concat(oldCSV->filePath, oldCSV->fileName);
	cols = oldCSV->columnCount;
	lines = oldCSV->lineCount;
	objs = gcnew array<String^, 2>(lines, cols);
	Array::Copy(oldCSV->objects, objs, lines*cols);
}

int CSVParser::getCol( String^ name ) {
	for(int a = 0; a < objects->GetLength(1); a++) {
		if(objects[0, a]->Equals(name, StringComparison::OrdinalIgnoreCase))
			return a;
	}
	return -1;
}

bool CSVParser::Parse() {
	String^ split_char, ^escape_char = Environment::NewLine;
	
	//Gets the escaping character, usually \n, \r or Environment::NewLine
	int count_nl = 0, count_cr = 0;
	int at_nl = -1, at_cr = -1;
	for(int a = 0; a < 30; a++) {
		at_nl = content->IndexOf("\n", at_nl+1);
		if(at_nl != -1)
			count_nl++;
		at_cr = content->IndexOf("\r", at_cr+1);
		if(at_cr != -1)
			count_cr++;
		if(at_cr == -1 && at_nl == -1)
			break;
	}
	if(count_nl > count_cr)
		escape_char = "\n";
	else if(count_cr > count_nl)
		escape_char = "\r";

	//Gets the splitting character, usually a "," or a ";"
	if(content->Substring(0, 1) == "\"") {
		for(int a = 1; a < content->Length; a++) {
			a = content->IndexOf("\"", a) + 1;
			if(a < content->Length) {
				String^ tmp1 = content->Substring(a, 1);
				if(tmp1 != "\"") {
					split_char = tmp1;
					break;
				}
			} else {
				throw gcnew Exception("Selected CSV does not seem to contain more than one entry. Aborted.");
				return false;
			}
		}
	} else {
		int comma = content->IndexOf(",");
		int semicolon = content->IndexOf(";");
		if( (comma < semicolon && comma != -1 && semicolon != -1) || (comma != -1 && semicolon == -1) )
			split_char = ",";
		else if( (comma > semicolon && comma != -1 && semicolon != -1) || (comma == -1 && semicolon != -1) )
			split_char = ";";
		else {
			throw gcnew Exception("Selected CSV does not seem to contain more than one entry. Aborted.");
			return false;
		}
	}

	int linesNum = 1, columnsNum = 1;
	int cntlen = content->Length;
	int total_separators = 0;

	//Counts the number of lines and of columns
	for(int r = 0; r < cntlen; r++) {
		int quote = content->IndexOf("\"", r);
		int separator = content->IndexOf(split_char, r);
		int linebreak = content->IndexOf(escape_char, r);

		if( (quote < separator && separator != -1 || separator == -1) && (quote < linebreak && linebreak != -1 || linebreak == -1) && quote != -1 ) {
			while(true) {
				int temp1 = content->IndexOf("\"", ++r);
				r = temp1 + 1;
				if(cntlen <= (r+1) || content->Substring(r, 1) != "\"")
					break;
				total_separators++;
			}
			if(cntlen <= (r+1) || (content->Substring(r, 1) != split_char && content->Substring(r, escape_char->Length) != escape_char))
				break;
		}
		quote = content->IndexOf("\"", r);
		separator = content->IndexOf(split_char, r);
		linebreak = content->IndexOf(escape_char, r);

		if( (separator < quote && quote != -1 || quote == -1) && (separator < linebreak && linebreak != -1 || linebreak == -1) && separator != -1 ) {
			if(linesNum == 1)
				columnsNum++;
			r = separator;
			total_separators++;
		} else if( (linebreak < quote && quote != -1 || quote == -1) && (linebreak < separator && separator != -1 || separator == -1) && linebreak != -1 ) {
			linesNum++;
			r = linebreak + escape_char->Length - 1;
			total_separators++;
		} else
			break;
	}
	lines = linesNum;
	cols = columnsNum;
	objs = gcnew array<String^, 2>(lines, cols);

	int old_a = 0, new_a = 0, temp_a = 0;
	linesNum = 0;
	columnsNum = 0;
	int counter = 0;
	for(int a = 0; a < cntlen; a++) {
		int quote = content->IndexOf("\"", a);
		int separator = content->IndexOf(split_char, a);
		int linebreak = content->IndexOf(escape_char, a);
		int quoted = 0;
		temp_a = a;

		if( (quote < separator && separator != -1 || separator == -1) && (quote < linebreak && linebreak != -1 || linebreak == -1) && quote != -1 ) {
			quoted = 1;
			while(true) {
				int temp1 = content->IndexOf("\"", ++a);
				a = temp1 + 1;
				if(cntlen <= (a+1) || content->Substring(a, 1) != "\"")
					break;
			}
			if(cntlen > (a+1) && content->Substring(a, 1) != split_char && content->Substring(a, escape_char->Length) != escape_char) {
				break;
			}
		}

		quote = content->IndexOf("\"", a);
		separator = content->IndexOf(split_char, a);
		linebreak = content->IndexOf(escape_char, a);

		if( (separator < quote && quote != -1 || quote == -1) && (separator < linebreak && linebreak != -1 || linebreak == -1) && separator != -1 ) {
			old_a = temp_a;
			a = separator;
			new_a = a;
			objs[linesNum, columnsNum] = content->Substring(old_a+quoted, new_a-old_a-quoted*2)->Replace("\"\"", "\"");
			columnsNum++;
		} else if( (linebreak < quote && quote != -1 || quote == -1) && (linebreak < separator && separator != -1 || separator == -1) && linebreak != -1 ) {
			old_a = temp_a;
			a = linebreak - 1 + escape_char->Length;
			new_a = a;
			objs[linesNum, columnsNum] = content->Substring(old_a+quoted, new_a-old_a-quoted+1-escape_char->Length)->Replace("\"\"", "\"");
			columnsNum = 0;
			linesNum++;
		} else {
			old_a = temp_a;
			objs[linesNum, columnsNum] = content->Substring(old_a+quoted, content->Length-old_a-quoted)->Replace("\"\"", "\"");
			break;
		}
		OnProcessing(counter, total_separators);
		counter++;
	}
	OnProcessing(total_separators, total_separators);
	return true;
}
void ProcessingClass::OnProcessing(int current, int total) {
	if(total > 0)
		Processing(current, total);
}
#pragma endregion