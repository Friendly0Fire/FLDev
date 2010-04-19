#include "StdAfx.h"
#include "Misc.h"

using namespace System;
using namespace DLLEditor;

ProcessBarItem::ProcessBarItem(String^ text, int initTicks, bool prog)
{
	txt = text;
	timeleft = initTicks;
	progress = prog;
}

void ProcessBarItem::Decrement() {
	timeleft--;
}

bool ProcessBarItem::Equals(Object^ obj) {
	if( this->GetType()->Equals(obj->GetType()) && ((ProcessBarItem^) obj)->Text->Equals(this->Text) )
		return true;
	else if( obj->GetType()->Equals(Type::GetType("System.String")) && this->Text->Equals((String^) obj) )
		return true;
	else
		return false;
}

String^ ProcessBarItem::ToString() {
	return txt;
}