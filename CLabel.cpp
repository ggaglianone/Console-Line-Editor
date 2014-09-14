#define _CRT_SECURE_NO_WARNINGS
#include "clabel.h"
#include "consoleplus.h"
#include <cstring>
namespace cio {
	CLabel::CLabel(const char* str, int row, int col, 
		int len) : CField (row, col, len < 0 ? strlen(str) : len-1) {
		
		allocateAndCopy(str);
	}

	CLabel::CLabel(int row, int col, int len) : CField (row, col, len) {
		allocateAndCopy("");
	}
	CLabel::CLabel(const CLabel& clb) : CField(clb) {
		allocateAndCopy((char*)clb.data());
	}

	CLabel::~CLabel() {
		if (_data != NULL){
			delete [] (char*)_data;
		}
	}
	void CLabel::allocateAndCopy(const char* str) {
		data((void*)str);
	}

	void CLabel::draw(int label) {
		cio::display((char*)data(), absrow(), abscol(), strlen((char*)data()) >= width() ? width() : strlen((char*)data()));
	}

	int CLabel::edit() {
		draw();
		return C_NOT_EDITABLE;
	}

	bool CLabel::editable() const {
		return false;
	}

	void CLabel::set(const void* str) {
		CField::width((int)strlen((const char*)str));
		
		allocateAndCopy((const char*)str); 
	}
}