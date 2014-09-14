//CButton.cpp by Gabriel Gaglianone
#define _CRT_SECURE_NO_WARNINGS 
#include <cstring>
#include "cbutton.h"

using namespace std;

namespace cio{
	CButton::CButton(const char* str, int row, int col, bool bordered, const char* border) : 
	CField(row, col, (bordered) ? (strlen(str) + 4) : (strlen(str) + 2), bordered ? 3 : 1, NULL, bordered, border) {
		allocateAndCopy(str);
	}
	CButton::~CButton() {
		delete[]data();
	}
	bool CButton::editable() const { 
		return true; 
	}

	void CButton::allocateAndCopy(const char* str) {
		_maxchar = strlen(str) + 3;
		_data = new char[_maxchar];
		for (int j = _maxchar - 2; j > 0; j--) {
		  _data[j] = str[j - 1];
		}
		_data[0] = ' ';
		_data[_maxchar - 1] = '\0';
		data(_data);
		
	}
	void CButton::draw(int fn) {
		CFrame::draw();
		int move = 0;
		if (bordered()) {
			move++;
		}
		cio::display(_data, absrow() + move, abscol() + move, strlen((char*)_data) >= width() ? width() : strlen((char*)_data));
	}
	int CButton::edit() {

		int key;
		_data[0] = '[';
		_data[_maxchar - 2] = ']';
		_data[_maxchar - 1] = '\0';
		draw();
		goMiddle();
		cio::console >> key;
		switch (key){
		case ENTER:
		case SPACE:
			key = C_BUTTON_HIT;
			goMiddle();
			break;
		case ESCAPE:
		case F(10):
			if (bordered())
				height(3);
			break;
		case TAB:
			_data[0] = ' ';
			_data[_maxchar-2] = ' ';
			draw();
			break;
		default:
			break;

		}//end of switch

		data(_data);
		return key;

	}
	void CButton::set(const void* str) {

		delete[]_data;
		allocateAndCopy((char*)str);
		CFrame::height((CFrame::bordered() ? (3) : (1)));
		CFrame::width((CFrame::bordered() ? (strlen((char*)str) + 4) : (strlen((char*)str) + 2)));
	}
}//End of CIO
 