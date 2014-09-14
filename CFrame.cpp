//CFrame.cpp by Gabriel Gaglianone
#define _CRT_SECURE_NO_WARNINGS 
#include <cstdlib>
#include <cstring>
#include "keys.h"
#include "cframe.h"
#include "console.h"
#include "consolebackup.h"
#include "consoleplus.h"
 namespace cio{

CFrame::CFrame(int row, int col, int width, int height,
			bool visible,
			const char* border, CFrame* frame){
	if (height < 0) {
			_row = row;
			_col = col;
			_width = console.getCols();
			_height = console.getRows();
			_visible = false;
			_border[0] = '\0';
			_frame = frame;
			_captured = NULL;
		}
		else {
			_row = row;
			_col = col;
			_width = width;
			_height = height;
			_visible = visible;
			strcpy(_border, border);
			_frame = frame;
			_captured = NULL;
		}
	}

	CFrame::~CFrame() {
		release(&_captured);
	}

void CFrame::setLine(char* str, char left, char fill, char right) const{
	int i;
	str[0] = left;
	for (i = 1; i < _width - 1; i++){
		str[i]= fill;
	}
	str[i] = right;
	str[i+1] = '\0';
}
void CFrame::capture(){
	if(!_captured){
		if(!_frame || fullscreen()){
			_captured = cio::capture(0, 0, console.getRows(), console.getCols());	
		}
		else{
			_captured = cio::capture(absrow(), abscol(), _height, _width);
		}		
	}
}
bool CFrame::fullscreen(){
	return _height < 0 || _width < 0;
}
int CFrame::absrow() const{
	return _frame ? _row +_frame->row() : row();
}
int CFrame::abscol() const{
	return _frame ? _col + _frame->col() : col();
}
void CFrame::goMiddle(){
	if (!_visible) {
			console.setPosition(absrow() + 1, abscol() + _width / 2);
		}
		else {
			console.setPosition(absrow(), abscol() + _width / 2);
		}
}
void CFrame::bordered(bool val){
	_visible = val;
}
bool CFrame::bordered() const {
	return _visible;
}
void CFrame::frame(CFrame* fr){
	_frame = fr;
}
CFrame* CFrame::frame() const {
		return _frame;
	}
void CFrame::row(int row){
	_row = row;
}
int CFrame::row() const{
	return _row;
}
void CFrame::col(int col){
	_col = col;
}
int CFrame::col() const{
	return _col;
}
void CFrame::height(int h){
	_height = h;
}
int CFrame::height() const{
	return _height;
}
void CFrame::width(int wi){
	_width = wi;
}
int CFrame::width() const{
	return _width;
}
void CFrame::draw(int fn){ 
    int i;
    char *str = new char[_width + 1];
	str[0] = '\0';

    capture();
    if(_visible && fn != C_NO_FRAME){
		console.setPosition(absrow(), abscol());
		setLine(str, _border[0], _border[1], _border[2]);
		console << str;
 
      for(i=0 ;i< (height() -2) ; i++){
        console.setPosition((absrow() + 1 + i), abscol());
		 setLine (str, _border[7], ' ',_border[3]);
		 console << str;
      }
	  console.setPosition((absrow() + 1 + i), abscol());
	  setLine(str, _border[6], _border[5], _border[4]);
      console << str;
    }
    delete[] str;
  }

void CFrame::hide(CDirection dir){
    if (!_frame || fullscreen()){
		cio::restore(0, 0, console.getRows(), console.getCols(), dir, _captured);
	}
	else{
		cio::restore(absrow(), abscol(), _height, _width, dir, _captured);
	}
	cio::release(&_captured);
  }

void CFrame::move(CDirection dir){
	hide();

	switch(dir){
	case C_STATIONARY:
		draw();
		break;
	case C_MOVED_LEFT:
		if (_frame) {
			if (bordered()) {
				if (abscol() > _frame->abscol() + 1 && abscol() > 0){
					col(col() - 1);
					draw();
				}
			}
			else if (abscol() > _frame->abscol() && abscol() > 0) {
				col(col() - 1);
				draw();
			}
		}
		break;
	case C_MOVED_UP:
		if (_frame){
			if (bordered()){
				if (absrow() > _frame->absrow() + 1 && absrow() > 0) {
					row(row() - 1);
					draw();
				}
			}
			else if (absrow() > _frame->absrow() && absrow() > 0) {
				row(row() - 1);
				draw();
			}
		}
		break;
	case C_MOVED_DOWN:
		if (_frame){
			if(bordered()){
				if (absrow() + _height < _frame->absrow() + _frame->height() -1){
					row(row() +1);
					draw();
			}
		}
			else if (absrow()>_frame->absrow() && absrow() > 0){
					row(row() + 1);
					draw();
				}
			}
		
		break;
	case C_MOVED_RIGHT:
		if (_frame) {
			if (bordered()) {
				if (abscol() + _width<_frame->abscol() + _frame->width() - 1) {
					col(col() + 1);
					draw();
				}
			}
			else if (abscol() + _width < _frame->abscol() + _frame->width()) {
				col(col() + 1);
				draw();
			}
		}
		break;
	default:
		break;
	}
	draw();
}

	void move(iFrame& fr) {
		
		bool done = false;
		int key;

		while (!done) {
			cio::console.setPosition(1, console.getCols() - 20);
			cio::console << "Moving! ESC: exit";
			console >> key;
			switch (key) {
			case ESCAPE:
				done = true;
				fr.draw();
				break;
			case UP:
				fr.move(C_MOVED_UP);
				break;
			case DOWN:
				fr.move(C_MOVED_DOWN);
				break;
			case LEFT:
				fr.move(C_MOVED_LEFT);
				break;
			case RIGHT:
				fr.move(C_MOVED_RIGHT);
				break;
			default:
				break;
			}
		}
	}

}//End of CIO