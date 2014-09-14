//consoleplus.h
//Gabriel Gaglianone
//OOP344
#ifndef _GG_CONSOLEPLUS_H_
#define _GG_CONSOLEPLUS_H_
#include "console.h"  
#include "keys.h"
namespace cio{
void display(const char *str, int row, int col, int fieldLen);

int edit(char *str, int row, int col, int fieldLength, int maxStrLength,
 bool* insertMode, int* strOffset, int* curPosition);
}; 
#endif