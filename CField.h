#ifndef _GG_CFIELD_H_
#define _GG_CFIELD_H_
#include "cframe.h"
#include "consoleplus.h"
#include <stdlib.h>
namespace cio{  

class CField : public CFrame{
public:
CField(int row = 0, int col = 0, int width = 0, int height = 0, void* data = NULL, bool visible = false, const char* border = C_BORDER_CHARS);
~CField();
void* data() const;
void data(void*);
virtual int edit() = 0;
virtual bool editable() const = 0;
virtual void set(const void*) = 0;
void* _data;
};
}
#endif