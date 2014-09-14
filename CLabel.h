#ifndef _GG_CLABEL_H_
#define _GG_CLABEL_H_
#include "cfield.h"
namespace cio{  

class CLabel : public CField {

void allocateAndCopy(const char*);
int fieldLenght;
public:
CLabel(const char* str, int row, int col, int len = -1);
CLabel(int row, int col, int len);
CLabel(const CLabel& clb);
~CLabel();
void draw(int bordered = C_NO_FRAME);
int edit();
bool editable() const;
void set(const void* str);
};
}
#endif
