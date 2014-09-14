#ifndef _GG_CLINE_H_
#define _GG_CLINE_H_
#include "cfield.h"
namespace cio{
	  
class CLine : public CField{
	
	int curpos;
	int offset;
	int _max;
	bool _mode;
	char* _data;
	bool _allocate;
	
	void allocateAndCopy(const char*);
public:
	CLine(const char* str, int row, int col, int width, int maxline, bool* mode, bool visible = false, const char* border = C_BORDER_CHARS);
	CLine(int row, int col, int width, int max, bool* mode, bool visible = false, const char* border = C_BORDER_CHARS);
	~CLine();
	void draw(int draw = C_NO_FRAME);
	int edit();
	bool editable() const;
	void set(const void*);
	};
} 
#endif