#include "Stdafx.h"
#include "includes.h"

using namespace Interfaces;
using namespace System::Text::RegularExpressions;

INIHandler::INIHandler( String ^content ) {
	Init(content);
}

INIHandler::INIHandler( FileStream^ file ) {
	StreamReader^ sr = gcnew StreamReader(file);
	content = sr->ReadToEnd();
	if(content != "") {
		String ^header = content->Substring(0, 4);
		if(String::Equals(header, "bini")) {
			content = "";
			throw gcnew FormatException("Opened file is encrypted with BINI and cannot be parsed.");
		} else
			this->path = file->Name;
	} else {
		this->path = file->Name;
	}
	Init(content);
}

void INIHandler::Init(String^ content) {
	if(content != "") {
		array<String ^>^ rawBlocks = getRawBlocks();
		array<Block ^> ^ blocksArray = gcnew array<Block ^>(rawBlocks->Length);

		blocksArray[0] = gcnew HeadlessBlock( rawBlocks[0] );
		for(int a = 1; a < blocksArray->Length; a++) {
			blocksArray[a] = gcnew Block( rawBlocks[a] );
		}

		parsedContent = blocksArray;
	} else {
		parsedContent = gcnew array<Block ^>(0);
	}
}

array<String ^> ^ INIHandler::getRawBlocks() {
	Regex^ reg = Block::BlockHeaderRegexp;
	MatchCollection^ mtch = reg->Matches(content);
	int totalBlocks = mtch->Count;
	array<String ^> ^ blocks = gcnew array<String ^>(totalBlocks+1);
	
	//Regex^ reg2 = gcnew Regex(Comment::CommentRegexp, RegexOptions::Multiline | RegexOptions::Compiled);
	//MatchCollection^ mtch2 = reg2->Matches(content);
	//comments = gcnew array<Comment^>(mtch2->Count);
	
	//int commentAt = 0;
	if(mtch->Count > 0 && (mtch[0]->Index - Environment::NewLine->Length) > 0)
		blocks[0] = content->Substring(0, mtch[0]->Index - Environment::NewLine->Length);
	else if(mtch->Count > 0)
		blocks[0] = "";
	else
		blocks[0] = content;
	for(int a = 0; a < totalBlocks; a++) //{
		blocks[a+1] = (a+1) < totalBlocks ? content->Substring(mtch[a]->Index, mtch[a+1]->Index - mtch[a]->Index - Environment::NewLine->Length) : content->Substring(mtch[a]->Index);
		/*for(int b = 0; mtch2[b]->Index < mtch[a]->Index; b++) {
			if(mtch2[b]->Index > (a > 0 ? mtch[a-1]->Index : -1)) {
				comments[commentAt] = gcnew Comment(mtch2[b]->Groups["comment"]->Value, a);
				commentAt++;
			}
		}*/
	//}
	
	/*commentAt = comments->Length - 1;
	for(int a = mtch2->Count-1; mtch2[a]->Index > mtch[mtch->Count-1]->Index; a--) {
		comments[commentAt] = gcnew Comment(mtch2[a]->Groups["comment"]->Value, -1);
		commentAt--;
	}*/

	return blocks;
}

void INIHandler::updateContent() {
	content = this->ToString();
}

void INIHandler::updateFile(FileStream^ file) {
	this->updateContent();
	StreamWriter^ sw = gcnew StreamWriter(file);
	sw->Write(content);
	sw->Close();
}

void INIHandler::updateFile() {
	updateFile(gcnew FileStream(this->path, FileMode::OpenOrCreate));
}

String^ INIHandler::ToString() {
	StringBuilder^ sb = gcnew StringBuilder();
	int a = 0;
	/*for each(Block^ blck in parsedContent) {
		sb->Append(getComments(a));
		sb->Append(blck->ToString());
		a++;
	}*/
	for each(Block^ blck in parsedContent)
		sb->Append(blck->ToString());
	//sb->Append(getComments(-1));
	return sb->ToString()->TrimEnd(gcnew array<wchar_t>{'\n', '\r'});
}

void INIHandler::insertBlock(Block ^blck, int index) {
	Array::Resize(parsedContent, parsedContent->Length+1);
	for(int a = parsedContent->Length-1; a > index; a--) {
		parsedContent[a] = parsedContent[a-1];
		//moveComments(a-1, a);
	}
	parsedContent[index] = blck;
}

void INIHandler::moveBlock(int index, int newindex, bool relative) {
	Block^ blck = parsedContent[index];
	if(index < newindex) {
		for(int a = index+1; a <= newindex; a++) {
			parsedContent[a-1] = parsedContent[a];
			//moveComments(a, a-1);
		}
		parsedContent[newindex] = blck;
	} else {
		for(int a = index-1; a >= newindex; a--) {
			parsedContent[a+1] = parsedContent[a];
			//moveComments(a, a+1);
		}
		parsedContent[newindex] = blck;
	}
}

array<Block^>^ INIHandler::matchBlocks(PartialBlock^ blck, bool matchcase) {
	int countMatch = 0;
	for each(Block^ bl in parsedContent) {
		if(bl->IsMatch(blck, matchcase))
			countMatch++;
	}
	array<Block^>^ blcks = gcnew array<Block^>(countMatch);
	countMatch = 0;
	for each(Block^ bl in parsedContent) {
		if(bl->IsMatch(blck, matchcase)) {
			blcks[countMatch] = bl;
			countMatch++;
		}
	}
	
	return blcks;
}

Block^ INIHandler::getDefaultInt(int index, bool createifundef) {
	if(index < parsedContent->Length)
		return parsedContent[index];
	else
		throw gcnew ArgumentOutOfRangeException("Could not get value, block does not exist.");
}

void INIHandler::setDefaultInt(int index, bool createifundef, Block^ param) {
	if(index < parsedContent->Length)
		parsedContent[index] = param;
	else if(createifundef) {
		Array::Resize(parsedContent, parsedContent->Length+1);
		parsedContent[parsedContent->Length-1] = param;
	} else
		throw gcnew ArgumentOutOfRangeException("Could not set value, block does not exist.");
}

Block^ INIHandler::getDefaultString(String^ index, int index2, bool createifundef) {
	if(index->IndexOf("[") == -1)
		index = "[" + index;
	if(index->IndexOf("]") == -1)
		index = index + "]";
	for each(Block^ blck in parsedContent) {
		if(blck->Header == index) {
			if(index2 > 0)
				index2--;
			else
				return blck;
		}
	}
	if(createifundef) {
		Array::Resize(parsedContent, parsedContent->Length+1);
		parsedContent[parsedContent->Length-1] = gcnew Block(index);
		return parsedContent[parsedContent->Length-1];
	} else throw gcnew ArgumentOutOfRangeException("Could not get value, block does not exist.");
}

void INIHandler::setDefaultString(String^ index, int index2, bool createifundef, Block^ param) {
	if(index->IndexOf("[") == -1)
		index = "[" + index;
	if(index->IndexOf("]") == -1)
		index = "]" + index;
	if(index2 >= 0) {
		for each(Block^ blck in parsedContent) {
			if(blck->Header == index) {
				if(index2 > 0)
					index2--;
				else {
					blck = param;
					return;
				}
			}
		}
	}
	if(createifundef) {
		Array::Resize(parsedContent, parsedContent->Length+1);
		parsedContent[parsedContent->Length-1] = param;
	} else
		throw gcnew ArgumentOutOfRangeException("Could not set value, block does not exist.");
}

//void INIHandler::moveComments(int oldblockID, int newblockID) {
//	for each(Comment^ c in comments) {
//		if(c->BlockID == oldblockID)
//			c->BlockID = newblockID;
//	}
//}
//
//String^ INIHandler::getComments(int id) {
//	StringBuilder^ sb = gcnew StringBuilder;
//	for each(Comment^ c in comments) {
//		if(c->BlockID == id)
//			sb->Append(c->Value);
//	}
//	sb->Append(Environment::NewLine);
//	return sb->ToString();
//}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

//Comment::Comment( String^ content, int bID ) {
//	comment = content;
//	blockID = bID;
//}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

Block::Block( String ^blockContent, Regex^ regexp ) {
	Init( blockContent, regexp );
}

Block::Block( String ^blockContent ) {
	Init( blockContent, BlockHeaderRegexp );
}

Block::Block() {}

void Block::Init( String ^blockContent, Regex^ regexp) {
	Regex^ reg = regexp;
	Match^ match = reg->Match(blockContent);
	//Regex^ reg2 = gcnew Regex(Comment::CommentRegexp, RegexOptions::Compiled | RegexOptions::Multiline);
	//blockContent = reg2->Replace(blockContent, "");
	if(match->Success) {
		headerpadding = match->Groups["padding"]->Value;
		header = match->Groups["header"]->Value;
		headercomment = match->Groups["comment"]->Value;
		if(!match->NextMatch()->Success) {
			array<String^>^ lines = blockContent->Split(gcnew array<String^>{Environment::NewLine}, StringSplitOptions::None);
			int lineC = lines->Length-1;
			/*for(int x = lines->Length-1; lines[x]->Trim() == ""; x--) {
				lines[x] = lines[x]->Trim(gcnew array<wchar_t>{'\n', '\r'});
				if(lines[x] == "") lineC--;
			}*/
			params = gcnew array<BlockParam^>(lineC);
			for(int a = 0; a < lineC; a++) {
				params[a] = gcnew BlockParam(lines[a+1]);
			}
		} else
			throw gcnew ArgumentException("There appears to be more than one block in the content given!");
	} else
		throw gcnew ArgumentException("The given block does not match standard formatting!");
}

String^ Block::ToString() {
	StringBuilder^ sb = gcnew StringBuilder();
	sb->AppendLine((headerpadding + header + headercomment)->Trim());
	for each(BlockParam^ param in params) {
		//if(param->Empty)
		//	sb->Append(param->ToString());
		//else
			sb->AppendLine(param->ToString());
	}
	return sb->ToString();
}

bool Block::IsMatch(PartialBlock^ test, bool matchcase) {
	if(test->Header != PartialBlock::EmptyHeader && test->Header != header) return false;
	for(int a = 0; a < test->Count; a++) {
		bool matched = false;
		for(int b = 0; b < params->Length; b++) {
			if(params[b]->Equals(test[a, 0], matchcase)) {
				matched = true;
				break;
			}
		}
		if(!matched) return false;
	}
	return true;
}

BlockParam^ Block::getDefaultInt(int index, bool createifundef) {
	if(index < params->Length)
		return params[index];
	else
		throw gcnew ArgumentOutOfRangeException("Could not get value, parameter does not exist.");
}

void Block::setDefaultInt(int index, bool createifundef, BlockParam^ param) {
	if(index < params->Length)
		params[index] = param;
	else if(createifundef) {
		Array::Resize(params, params->Length+1);
		params[params->Length-1] = param;
	} else
		throw gcnew ArgumentOutOfRangeException("Could not set value, parameter does not exist.");
}

BlockParam^ Block::getDefaultString(String^ index, int index2, bool createifundef) {
	for each(BlockParam^ param in params) {
		if(param->Parameter == index) {
			if(index2 > 0)
				index2--;
			else
				return param;
		}
	}
	if(createifundef) {
		Array::Resize(params, params->Length+1);
		params[params->Length-1] = gcnew BlockParam(index, gcnew BlockParamValue(""));
		return params[params->Length-1];
	} else throw gcnew ArgumentOutOfRangeException("Could not get value, parameter does not exist.");
}

void Block::setDefaultString(String^ index, int index2, bool createifundef, BlockParam^ param) {
	if(index2 >= 0) {
		for each(BlockParam^ par in params) {
			if(par->Parameter == index) {
				if(index2 > 0)
					index2--;
				else {
					par = param;
					return;
				}
			}
		}
	}
	if(createifundef) {
		Array::Resize(params, params->Length+1);
		params[params->Length-1] = param;
	} else
		throw gcnew ArgumentOutOfRangeException("Could not set value, parameter does not exist.");
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

PartialBlock::PartialBlock( String ^blockContent ) : Block(blockContent, PartialBlockHeaderRegexp) {}

PartialBlock::PartialBlock() {
	headerpadding = "";
	header = PartialBlock::EmptyHeader;
	headercomment = "\r";
	params = gcnew array<BlockParam^>(0);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

HeadlessBlock::HeadlessBlock( String ^blockContent ) {
	headerpadding = "";
	header = "";
	headercomment = "";
	
	array<String^>^ lines = blockContent->Split(gcnew array<String^>{Environment::NewLine}, StringSplitOptions::None);
	int lineC = lines->Length;
	/*for(int x = lines->Length-1; lines[x]->Trim() == ""; x--) {
		lines[x] = lines[x]->Trim(((String^) "\n\r ")->ToCharArray());
		if(lines[x] == "") lineC--;
	}*/
	params = gcnew array<BlockParam^>(lineC);
	for(int a = 0; a < lines->Length; a++)
		params[a] = gcnew BlockParam(lines[a]);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

BlockParam::BlockParam(String^ content) {
	Regex^ reg = ParamRegexp;
	Regex^ reg2 = EmptyRegexp;
	Regex^ reg3 = ParamOnlyRegexp;
	Match^ match = reg->Match(content);
	Match^ match2 = reg2->Match(content);
	Match^ match3 = reg3->Match(content);
	if(match2->Success) {
		padding = match2->Groups["padding"]->Value;
		parameter = "";
		equal = "";
		value = gcnew BlockParamValue("");
		comment = match2->Groups["comment"]->Value->TrimEnd(gcnew array<wchar_t>{'\r', '\n'});
		empty = true;
	} else if(match->Success) {
		padding = match->Groups["padding"]->Value;
		parameter = match->Groups["param"]->Value;
		equal = match->Groups["equal"]->Value;
		value = gcnew BlockParamValue(match->Groups["value"]->Value);
		comment = match->Groups["comment"]->Value->TrimEnd(gcnew array<wchar_t>{'\r', '\n'});
		empty = false;
	} else if(match3->Success) {
		padding = match->Groups["padding"]->Value;
		parameter = match->Groups["param"]->Value;
		equal = "";
		value = gcnew BlockParamValue(gcnew array<String^>{});
		comment = match->Groups["comment"]->Value->TrimEnd(gcnew array<wchar_t>{'\r', '\n'});
		empty = true;
	} else
		throw gcnew ArgumentException("The given parameter does not match standard formatting!");
}

BlockParam::BlockParam(String^ param, BlockParamValue^ values) {
	padding = "";
	parameter = param;
	equal = " = ";
	value = values;
	comment = "";
	if(param == "" && (values->Count == 0 || (values->Count == 1 && values[0] == "")))
		empty = true;
	else
		empty = false;
}

bool BlockParam::IsEmpty() {
	if(parameter == "" && equal == "" && value->Count == 0)
		return true;
	return false;
}

String^ BlockParam::ToString() {
	if(!this->empty)
		return padding + parameter + equal + value + comment;
	else return "";
}

bool BlockParam::Equals(BlockParam^ test, bool matchcase) {
	if(parameter->Equals(test->Parameter, matchcase ? StringComparison::Ordinal : StringComparison::OrdinalIgnoreCase) && value->Equals(test->Value, matchcase))
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

BlockParamValue::BlockParamValue(String^ values) {
	Init(values->Split(((String^)",")->ToCharArray()));
}
BlockParamValue::BlockParamValue(array<String^>^ values) {
	Init(values);
}

void BlockParamValue::Init(array<String^>^ values) {
	subvalues = gcnew array<String^>(values->Length);
	Regex^ reg = ValueRegexp;
	for(int a = 0; a < values->Length; a++) {
		if(reg->IsMatch(values[a]))
			subvalues[a] = values[a]->Trim();
		else
			subvalues[a] = "";
	}
}

bool BlockParamValue::Equals(BlockParamValue^ test, bool matchcase) {
	if(test->Count <= subvalues->Length) {
		for(int a = 0; a < test->Count; a++) {
			if(test[a] != "") {
				if(!subvalues[a]->Equals(test[a], matchcase ? StringComparison::InvariantCulture : StringComparison::InvariantCultureIgnoreCase))
					return false;
			}
		}
		return true;
	} else
		return false;
}

String^ BlockParamValue::ToString() {
	String^ final = "";
	for each(String^ element in subvalues)
		final += element + ", ";
	return final->Substring(0, final->Length-2);
}