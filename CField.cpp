//CField.cpp by Gabriel Gaglianone

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "cfield.h"
#include "consoleplus.h"

namespace cio{ 
//CField constructor 
	CField::CField(int row, int col,int width, int height, void* data, bool visible, const char* border)
    :CFrame(row, col, width, height, visible, border){
	CField::data(data);
	}
	 // Destructor
  CField::~CField(){
  }
bool CField::editable() const{
  return true;
}

void* CField::data() const{
return _data;
}

void CField::data(void* data){
	if (data != NULL) {
		int len = strlen((char*)data);
		_data = new void*[len + 1];
		strcpy((char*)_data, (char*)data);
		((char*)_data)[len] = '\0'; }
	else {
		_data = NULL; 
	} 
}
}
