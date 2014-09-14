//consoleplus.h
//Gabriel Gaglianone
//OOP344

void display(const char *str, int row, int col, int fieldLen);

int edit(char *str, int row, int col, int fieldLength, int maxStrLength,
 bool* insertMode, int* strOffset, int* curPosition);
