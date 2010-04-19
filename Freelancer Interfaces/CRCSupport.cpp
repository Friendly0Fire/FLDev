#include "Stdafx.h"
#include "includes.h"

/* standard CRC16 polynomial */
#define FLHASH_POLYNOMIAL  0xA001ul

#define LOGICAL_BITS   30
#define PHYSICAL_BITS  32
#define SHIFTED_POLY   (FLHASH_POLYNOMIAL << (LOGICAL_BITS - 16))

using namespace Interfaces;

UnCRCDatabase::UnCRCDatabase(System::String ^path, bool is_folder, String^ workdir) {
	if(is_folder) {
		System::DateTime dt = System::DateTime::Now;
		database_file_path = String::Concat(Path::Combine(workdir, path->Substring(path->LastIndexOf("\\") + 1)), "_", dt.Day, "_", dt.Month, "_", dt.Year, "_", dt.Hour, "h_", dt.Minute, "m_", dt.Second, "s.db");
		dbsw = gcnew StreamWriter(database_file_path);
		OnProcessing(0, 1);
		ParseFolder(path);
		OnProcessing(1, 1);
		dbsw->Close();
		parsed_files_count = 0;
		OpenDB(database_file_path);
	} else {
		database_file_path = path;
		OnProcessing(0, 1);
		OpenDB(database_file_path);
		OnProcessing(1, 1);
	}
}

void UnCRCDatabase::ParseFolder(System::String ^path) {
	array<String^>^ subfolders = Directory::GetDirectories(path);
	array<String^>^ files = Directory::GetFiles(path);
	for(int a = 0; a < files->Length; a++) {
		if(Path::GetExtension(files[a])->Equals(".ini", StringComparison::InvariantCultureIgnoreCase))
			ParseFile(Path::Combine(path, files[a]));
	}
	for(int a = 0; a < subfolders->Length; a++) {
		ParseFolder(Path::Combine(path, subfolders[a]));
	}
}

void UnCRCDatabase::ParseFile(System::String ^path) {
	INIHandler^ ini = gcnew INIHandler(gcnew System::IO::FileStream(path, System::IO::FileMode::Open));
	DWORD dd = 0;
	if(ini->Count > 0) {
		for(int a = 0; a < ini->Count; a++) {
			for(int b = 0; b < ini[a]->Count; b++) {
				if(!ini[a][b]->Empty) {
					for(int c = 0; c < ini[a][b]->Value->Count; c++) {
						double dummy = -1;
						if(!Double::TryParse(ini[a][b]->Value[c], dummy) && dummy == 0 && ini[a][b]->Value[c] != "" && ini[a][b]->Value[c] != nullptr && ini[a][b]->Value[c] != "true" && ini[a][b]->Value[c] != "false") {
							dbsw->WriteLine(ini[a][b]->Value[c]);
							dbsw->WriteLine(FLCRC32::fl_crc32(ini[a][b]->Value[c]));
							char* currc = new char[ini[a][b]->Value[c]->Length];
							array<wchar_t>^ wcurrc = ini[a][b]->Value[c]->ToLower()->ToCharArray();
							for(int z = 0; z < ini[a][b]->Value[c]->Length; z++)
								currc[z] = (char) wcurrc[z];
							dd = FLHash(&global_context, currc, ini[a][b]->Value[c]->Length);
							dbsw->WriteLine(dd.ToString());
							delete currc;
						}
					}
				}
			}
		}
	}
	parsed_files_count++;
}

void UnCRCDatabase::OpenDB(System::String ^path) {
	dbsr = gcnew StreamReader(path);
	String^ data = dbsr->ReadToEnd();
	dbsr->Close();
	int linecount = 0;
	for(int lastpos = 0; lastpos != -1; linecount++) {
		lastpos = data->IndexOf(Environment::NewLine, lastpos+1);
	}
	linecount = (linecount-1)/3;
	names = gcnew array<String^>(linecount);
	crcs = gcnew array<Int64>(linecount);
	hashes = gcnew array<Int64>(linecount);
	array<String^>^ data_arr = data->Split( gcnew array<String^>{Environment::NewLine}, StringSplitOptions::None );
	int b = 0, c = 0, d = 0;
	for(int a = 0; a < linecount * 3; a += 3) {
		names[b] = data_arr[a];
		b++;
		crcs[c] = Int64::Parse(data_arr[a+1]);
		c++;
		hashes[d] = Int64::Parse(data_arr[a+2]);
		d++;
	}
}

String^ UnCRCDatabase::SearchDB(Int64 CRC, bool %iscrc) {
	for(int a = 0; a < crcs->Length; a++) {
		if(CRC == crcs[a]) {
			iscrc = true;
			return names[a];
		} else if(CRC == hashes[a]) {
			iscrc = false;
			return names[a];
		}
	}
	iscrc = true;
	return "Not Found!";
}

void UnCRCDatabase::Optimize() {
}

////////////////

UTF::UTF(String^ path) {
	FileStream^ fs = gcnew FileStream(path, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
	array<Byte>^ buf = gcnew array<Byte>(static_cast<int> (fs->Length));
	fs->Read(buf, 0, static_cast<int> (fs->Length));
	fs->Close();
	
	int pos = 0;
	int sig = BitConverter::ToInt32(buf, pos);
	pos += 4;
	int ver = BitConverter::ToInt32(buf, pos);
	if (sig != 0x20465455 || ver != 0x101)
		throw gcnew Exception("Unsupported");
	
	// get node chunk info
   int nodeBlockOffset = BitConverter::ToInt32(buf, pos); pos+=4;
   int nodeSize = BitConverter::ToInt32(buf, pos); pos+=12;

   // get string chunk info
   int stringBlockOffset = BitConverter::ToInt32(buf, pos); pos+=4;
   int stringBlockSize = BitConverter::ToInt32(buf, pos); pos+=8;

   // get data chunk info
   int dataBlockOffset = BitConverter::ToInt32(buf, pos); pos+=4;
   int dataBlockSize = buf->Length - dataBlockOffset;
   
   String^ depth = "+";
   this->ParseNode(buf, nodeBlockOffset, 0, stringBlockOffset, depth);
}

void UTF::ParseNode(array<Byte>^ buf, int nodeBlockStart, int nodeStart, int stringBlockOffset, String^ depth) {
	int offset = nodeBlockStart + nodeStart;
	
	while(true) {
		int nodeOffset = offset;

		int peerOffset = BitConverter::ToInt32(buf, offset); offset += 4;
		int nameOffset = BitConverter::ToInt32(buf, offset); offset += 4;
		int flags = BitConverter::ToInt32(buf, offset); offset += 4;
		int zero = BitConverter::ToInt32(buf, offset); offset += 4;
		int childOffset = BitConverter::ToInt32(buf, offset); offset += 4;
		int allocated_size = BitConverter::ToInt32(buf, offset); offset += 4;
		int size = BitConverter::ToInt32(buf, offset); offset += 4;
		int size2 = BitConverter::ToInt32(buf, offset); offset += 4;
		int u1 = BitConverter::ToInt32(buf, offset); offset += 4;
		int u2 = BitConverter::ToInt32(buf, offset); offset += 4;
		int u3 = BitConverter::ToInt32(buf, offset); offset += 4;

		// Extract the node name
		int len = 0;
		for (int i = stringBlockOffset + nameOffset; i < buf->Length && buf[i] != 0; i++, len++) ;
		String^ name = System::Text::Encoding::ASCII->GetString(buf, stringBlockOffset + nameOffset, len);
		
		if (childOffset > 0) {
			if ((flags&0x80)==0x80) {
				// data
			} else {
				ParseNode(buf, nodeBlockStart, childOffset, stringBlockOffset, depth + name + "+");
			}
		}
		
		if(peerOffset == 0)
			break;
	}
}

////////////////

static DWORD BSwap32(DWORD x)  {
	return  (x >> 24)
		| ((x >>  8) & 0x0000FF00ul)
		| ((x <<  8) & 0x00FF0000ul)
		|  (x << 24);
}

void InitFLHashContext(FLHashContext *ctx)  {
	DWORD i, bit;
	for (i = 0; i < 256; i++)  {
		DWORD x = i;
		for (bit = 0; bit < 8; bit++)
			x = x & 1 ? (x >> 1) ^ SHIFTED_POLY : x >> 1;
		ctx->lookup[i] = x;  }
}

/* note: not suitable for non-ASCII text because the result of tolower(c) is 
only defined if __isascii(c) && isupper(c). */
DWORD FLHash (FLHashContext const *ctx, char const *text, size_t length)  {
	DWORD hash = 0;
	size_t i;
	for (i = 0; i < length; i++)
		hash = (hash >> 8) ^ ctx->lookup[(BYTE)hash ^ (BYTE)tolower(text[i])];
	/* b0rken because byte swapping is not the same as bit reversing, but 
	that's just the way it is; two hash bits are shifted out and lost */
	return (BSwap32(hash) >> (PHYSICAL_BITS - LOGICAL_BITS)) | 0x80000000ul;
}