#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Text::RegularExpressions;

namespace Interfaces
{
	////////////////////////
	// In general, the following can be assumed as a naming convention:
	// [Block Header]
	// param = value
	//
	// "padding" refers to any blank character which is found BEFORE the rest of the line
	// "equal" stores the equal sign in parameters, as well as any spacing around it
	// "comment" stores any comment (text preceded by a semi-colon), as well as any spacing before and after it
	////////////////////////
	
	ref class PartialBlock;
	ref class BlockParamValue;
	ref class BlockParam;
	ref class Block;
	
	public ref class BlockParamValue {
		public:
			static Regex^ ValueRegexp = gcnew Regex("^[^<>?;]+$", RegexOptions::Compiled);
			
			BlockParamValue(String^ values);
			BlockParamValue(array<String^>^ values);
			virtual bool Equals(BlockParamValue^ test, bool matchcase);
			property int Count {
				int get() {
					return subvalues->Length;
				}
			}
			property String^ default[int] {
				String^ get (int index) {
					return subvalues[index];
				}
				void set (int index, String^ value) {
					Regex^ reg = ValueRegexp;
					if(reg->IsMatch(value))
						subvalues[index] = value;
				}
			}
			virtual String ^ToString() override;
		private:
			void Init(array<String^>^ values);
			array<String^>^ subvalues;
	};
	
	public ref class BlockParam {
		public:
			static Regex^ ParamRegexp = gcnew Regex("^(?<padding>[\f\t\v\\x85\\p{Z}]*)(?<param>[^\n\r=]+?)(?<equal>\\s*=\\s*)(?<value>[^\n\r;]*\\S)(?<comment>\\s*(;[^\n\r]*)?\r?)$", RegexOptions::Compiled);
			static Regex^ EmptyRegexp = gcnew Regex("^(?<padding>[\f\t\v\\x85\\p{Z}]*)(?<comment>(;[^\n\r]*)?\r?)$", RegexOptions::Compiled);
			static Regex^ ParamOnlyRegexp = gcnew Regex("^(?<padding>[\f\t\v\\x85\\p{Z}]*)(?<param>[^\n\r=]+?)(?<comment>(;[^\n\r]*)?\r?)$", RegexOptions::Compiled);
			BlockParam(String^ content);
			BlockParam(String^ param, BlockParamValue^ values);
			virtual String ^ToString() override;
			virtual bool Equals(BlockParam^ test, bool matchcase);
			property String^ Padding {
				String^ get() {
					return padding;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^[\f\t\v\\x85\\p{Z}]*$", RegexOptions::Compiled);
					if(reg->IsMatch(param))
						padding = param;
				}
			}
			property String^ Equal {
				String^ get() {
					return equal;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^\\s*=\\s*$", RegexOptions::Compiled);
					if(reg->IsMatch(param)) {
						equal = param;
						empty = IsEmpty();
					}
				}
			}
			property String^ Parameter {
				String^ get() {
					return parameter;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^[^\n\r=]+$", RegexOptions::Compiled);
					if(reg->IsMatch(param)) {
						parameter = param;
						empty = IsEmpty();
					}
				}
			}
			property BlockParamValue^ Value {
				BlockParamValue^ get() {
					return value;
				}
				void set(BlockParamValue^ param) {
					value = param;
					empty = IsEmpty();
				}
			}
			property String^ Comment {
				String^ get() {
					return comment;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^\\s*(;[^\n\r]*)?\r?$", RegexOptions::Compiled);
					if(reg->IsMatch(param)) {
						comment = param;
						empty = IsEmpty();
					}
				}
			}
			
			property bool Empty {
				bool get() {
					return empty;
				}
			}
		private:
			bool IsEmpty();
			
			String^ padding;
			String^ parameter;
			BlockParamValue^ value;
			String^ comment;
			String^ equal;
			bool empty;
	};
	
	//public ref class Comment {
	//	public:
	//		static String^ CommentRegexp = "^(?<comment>(\\s)*(;[^\n\r]*)\r?)$";
	//		
	//		Comment( String^ content, int bID );
	//		
	//		property int BlockID {
	//			int get() {
	//				return blockID;
	//			}
	//			void set(int newid) {
	//				blockID = newid;
	//			}
	//		}
	//		
	//		property String^ Value {
	//			String^ get() {
	//				return comment;
	//			}
	//			void set(String^ newval) {
	//				Regex^ reg = gcnew Regex(CommentRegexp, RegexOptions::Multiline | RegexOptions::Compiled);
	//				if(reg->IsMatch(newval))
	//					comment = newval;
	//			}
	//		}
	//	private:
	//		String^ comment;
	//		int blockID;
	//};
	
	public ref class Block {
		public:
			static Regex^ BlockHeaderRegexp = gcnew Regex("^(?<padding>([\f\t\v\\x85\\p{Z}])*)(?<header>\\[[^\n\r\\]]+\\])(?<comment>\\s*(;[^\n\r]*)?\r?)$", RegexOptions::Compiled | RegexOptions::Multiline);
			
			Block( String ^blockContent);
			Block( String ^blockContent, Regex^ regexp );
			virtual String ^ToString() override;
			bool IsMatch(PartialBlock^ test, bool matchcase);
			
			property int Count {
				int get() {
					return params->Length;
				}
			}
			
			property String^ HeaderPadding {
				String^ get() {
					return headerpadding;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^([\f\t\v\\x85\\p{Z}])*$", RegexOptions::Compiled);
					if(reg->IsMatch(param))
						headerpadding = param;
				}
			}
			
			property String^ Header {
				String^ get() {
					return header;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^\\[[^\n\r\\]]+\\]$", RegexOptions::Compiled);
					Regex^ reg2 = gcnew Regex("^[^\n\r\\]]+$", RegexOptions::Compiled);
					if(reg->IsMatch(param))
						header = param;
					else if(reg2->IsMatch(param))
						header = "[" + param + "]";
				}
			}
			
			property String^ HeaderComment {
				String^ get() {
					return headercomment;
				}
				void set(String^ param) {
					Regex^ reg = gcnew Regex("^\\s*(;[^\n\r]*)?\r?$", RegexOptions::Compiled);
					if(reg->IsMatch(param))
						headercomment = param + Environment::NewLine;
				}
			}
			
			property int CountParam[String^] {
				int get(String^ index) {
					int count = 0;
					for each(BlockParam^ param in params) {
						if(param->Parameter == index)
							count++;
					}
					return count;
				}
			}
			
			property BlockParam^ default[int] {
				BlockParam^ get(int index) {
					return getDefaultInt(index, false);
				}
				void set(int index, BlockParam^ param) {
					setDefaultInt(index, false, param);
				}
			}
			property BlockParam^ default[int, bool] {
				BlockParam^ get(int index, bool createifundef) {
					return getDefaultInt(index, createifundef);
				}
				void set(int index, bool createifundef, BlockParam^ param) {
					setDefaultInt(index, createifundef, param);
				}
			}
			
			property BlockParam^ default[String^, int, bool] {
				BlockParam^ get(String^ index, int index2, bool createifundef) {
					return getDefaultString(index, index2, createifundef);
				}
				void set(String^ index, int index2, bool createifundef, BlockParam^ param) {
					setDefaultString(index, index2, createifundef, param);
				}
			}
			property BlockParam^ default[String^, int] {
				BlockParam^ get(String^ index, int index2) {
					return getDefaultString(index, index2, false);
				}
				void set(String^ index, int index2, BlockParam^ param) {
					setDefaultString(index, index2, false, param);
				}
			}
			property BlockParam^ default[String^] {
				BlockParam^ get(String^ index) {
					return getDefaultString(index, 0, false);
				}
				void set(String^ index, BlockParam^ param) {
					setDefaultString(index, 0, false, param);
				}
			}
			
		protected:
			Block();
			void Init( String ^blockContent, Regex^ regexp );
			void setDefaultString(String^ index, int index2, bool createifundef, BlockParam^ param);
			BlockParam^ getDefaultString(String^ index, int index2, bool createifundef);
			void setDefaultInt(int index, bool createifundef, BlockParam^ param);
			BlockParam^ getDefaultInt(int index, bool createifundef);
			
			array<BlockParam^>^ params;
			
			String^ headerpadding;
			String^ header;
			String^ headercomment;
	};
	
	public ref class PartialBlock : Block {
		public:
		static Regex^ PartialBlockHeaderRegexp = gcnew Regex("^(?<padding>([\f\t\v\\x85\\p{Z}])*)(?<header>\\[[^\n\r\\]]*\\])(?<comment>\\s*(;[^\n\r]*)?\r?)$", RegexOptions::Compiled | RegexOptions::Multiline);
		static String^ EmptyHeader = "[]";
		PartialBlock();
		PartialBlock(String^ blockContent);
	};
	
	public ref class HeadlessBlock : Block {
		public:
		HeadlessBlock(String^ blockContent);
	};

	public ref class INIHandler {
		public:
			INIHandler( String^ content );
			INIHandler( FileStream^ file );
			
			virtual String ^ToString() override;
			void updateFile(FileStream^ file);
			void updateFile();
			void updateContent();
			void insertBlock(Block^ blck, int index);
			void moveBlock(int index, int newindex, bool relative);
			array<Block^>^ matchBlocks(PartialBlock^ blck, bool matchcase);
			/*void moveComments(int oldblockID, int newblockID);
			String^ getComments(int id);*/
			
			property int Count {
				int get() {
					return parsedContent->Length;
				}
			}

			property String^ FilePath {
				String^ get() {
					return this->path;
				}
				void set(String^ param) {
					if(Directory::Exists(Path::GetDirectoryName(param)))
						this->path = param;
				}
			}
			
			property int CountBlock[String^] {
				int get(String^ index) {
					int count = 0;
					for each(Block^ blck in parsedContent) {
						if(blck->Header == index)
							count++;
					}
					return count;
				}
			}
			
			property Block^ default[int, bool] {
				Block^ get(int index, bool createifundef) {
					return getDefaultInt(index, createifundef);
				}
				void set(int index, bool createifundef, Block^ param) {
					setDefaultInt(index, createifundef, param);
				}
			}
			property Block^ default[int] {
				Block^ get(int index) {
					return getDefaultInt(index, false);
				}
				void set(int index, Block^ param) {
					setDefaultInt(index, false, param);
				}
			}
			
			property Block^ default[String^, int, bool] {
				Block^ get(String^ index, int index2, bool createifundef) {
					return getDefaultString(index, index2, createifundef);
				}
				void set(String^ index, int index2, bool createifundef, Block^ param) {
					setDefaultString(index, index2, createifundef, param);
				}
			}
			property Block^ default[String^, int] {
				Block^ get(String^ index, int index2) {
					return getDefaultString(index, index2, false);
				}
				void set(String^ index, int index2, Block^ param) {
					setDefaultString(index, index2, false, param);
				}
			}
			property Block^ default[String^] {
				Block^ get(String^ index) {
					return getDefaultString(index, 0, false);
				}
				void set(String^ index, Block^ param) {
					setDefaultString(index, 0, false, param);
				}
			}

		private:
			array<String ^> ^ getRawBlocks();
			void Init(String^ content);
			Block^ getDefaultInt(int index, bool createifundef);
			void setDefaultInt(int index, bool createifundef, Block^ param);
			Block^ getDefaultString(String^ index, int index2, bool createifundef);
			void setDefaultString(String^ index, int index2, bool createifundef, Block^ param);
			
			String ^path;
			String ^content;
			array<Block ^> ^ parsedContent;
			//array<Comment^>^ comments;
	};
}