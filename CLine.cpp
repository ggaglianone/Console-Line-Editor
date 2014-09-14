//CLine.cpp by Gabriel Gaglianone
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "cline.h"
#include "consoleplus.h"
 
namespace cio{  
CLine::CLine(const char* str, int row, int col, int width, int max, bool* mode, bool visible, const char* border)
	:CField(row, col, width, visible? 3 : 1, 
	(void*)str, visible, border){
	
	_max = max;
	_mode = mode;
	offset = 0;
	curpos = 0;
	_data = NULL;
	_allocate = false;
	allocateAndCopy(str);

}

CLine::CLine(int row, int col, int width, int max, bool* mode, bool visible,
	const char* border):CField (row, col,width, visible ? 3 : 1,
	NULL, visible, border){
	_max = max;
	_mode = mode;
	offset = 0;
	curpos = 0;
	_data = NULL;
	allocateAndCopy("");
}

CLine::~CLine(){
	if (_data)
		delete[] _data;
}

void CLine::draw(int draw) {
	CFrame::draw();

	int move = 0;

	if(bordered()){
		move++;
	}
}

void CLine::allocateAndCopy(const char* str){
	_allocate = true;
	if (str){
		int len = strlen(str) + 1;

		if (len > _max){
			_max = len;
		}
		if (_data){
			delete[] _data;
		}
		_data = new char[_max];

		strcpy(_data, str);

		for (int i = _max - 1; i >= 0; i--){
			_data[len] = '\0';
		}
		data(_data);
	}
}

int CLine::edit(){
	int move = 0;

	if(bordered()){
		move++;
	}
	int temp = cio::edit(_data, absrow()+move, abscol()+move, width() - 2, _max, &_mode, &offset, &curpos);
	data(_data);
	return temp;
}

bool CLine::editable() const{
  return true;
}

void CLine::set(const void* str){
	if (_allocate){
			delete[] data();
		}
		allocateAndCopy((const char*)str);
	}
}
