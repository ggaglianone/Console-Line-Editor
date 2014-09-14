//Console Line Edit.cpp by Gabriel Gaglianone
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "consoleplus.h"
#include "keys.h"
using namespace std;
namespace cio{

void display(const char *str, int row, int col, int fieldLen)
{
	console.setPosition(row, col);

	int len = std::strlen(str);
	int i = 0;

	if ((col + fieldLen) > console.getCols()) { 
		fieldLen = console.getCols() - col;
	}

	if(fieldLen <= 0) {
		console << str;
	}
	else if(len > fieldLen) {
		for(; i < fieldLen; ++i)
			console << str[i];
	} else {
		for(; i < len; ++i)
			console << str[i];
		for(; i < fieldLen; ++i)
			console << " ";
	}

	if(console.getCols() <= col + len + 1) {
		console.setPosition(row, col + len);
	}
	else {
		console.setPosition(row, col + len + 1);
	}
}

int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool *insertMode, int* strOffset, int *curPosition)
{
	int key = 0;
	int len = std::strlen(str);
	char *originalStr = new char[len+1];
	strcpy(originalStr, str);

	if(!strOffset) {
		*strOffset = 0;
	}

	if(*strOffset > len) {
		*strOffset = len;
	}

	if(!curPosition) {
		*curPosition = 0;
	}

	if(*curPosition >= fieldLength) {
		*curPosition = fieldLength-1;
	}

	if(*curPosition > len) {
		*curPosition = len;
	}

	bool done = false;
	while(!done) {
		display(str, row, col, fieldLength);
		console.setPosition(row, col + *curPosition);
		console >> key;

		switch (key)
		{
		case LEFT:
			if(*curPosition > 0)
				*curPosition -= 1;
			else if(*strOffset > 0)
				*strOffset -= 1;
			break;
		case RIGHT:
			if(*curPosition < fieldLength-1)
				*curPosition += 1;
			else
				*strOffset += 1;
			break;
		case HOME:
			*curPosition = 0;
			*strOffset = 0;
			break;
		case END:
			if(len > fieldLength) {
				*curPosition = fieldLength - 1;
				*strOffset = len - fieldLength;
			}
			else {
				*curPosition = len;
				*strOffset = 0;
			}
			break;
		case INSERT:
			*insertMode = !(*insertMode);
			break;
		case DEL:
			if(*strOffset + *curPosition < len) {
				for(int i = (*strOffset + *curPosition); i < len; ++i)
					str[i] = str[i+1];
			}
			break;
		case BACKSPACE:
			if(*strOffset + *curPosition > 0) {
				for(int i = (*strOffset + *curPosition)-1; i < len; ++i)
					str[i] = str[i+1];

				if(*curPosition > 0)
					*curPosition -= 1;
				else if(*strOffset > 0)
					*strOffset -= 1;
			}
			break;
		case ESCAPE:
			strcpy(str, originalStr);
			done = true;
			break;

		case ENTER:
		case TAB:
		case UP:
		case DOWN:
		case PGUP:
		case PGDN:
		case F(1):
		case F(2):
		case F(3):
		case F(4):
		case F(5):
		case F(6):
		case F(7):
		case F(8):
		case F(9):
		case F(10):
		case F(11):
		case F(12):
			done = true;
			break;
		default:
			if (key >= ' ' && key <= '~') {
				if(*insertMode) {
					if(len+1 <= maxStrLength) {
						for(int i = len; i >= *curPosition + *strOffset; i--)
							str[i+1] = str[i];
						
						str[*curPosition + *strOffset] = key;

						if(*curPosition < fieldLength)
							*curPosition += 1;
						else
							*strOffset += 1;
					}
				}
				else {
					str[*curPosition + *strOffset] = key;
					*curPosition += 1;
					if(*curPosition > fieldLength) {
						*strOffset += 1;
						*curPosition -= 1;
					}
				}
			}
			break;
		}
	}

	delete []originalStr;
	return key;
}
}//End of CIO