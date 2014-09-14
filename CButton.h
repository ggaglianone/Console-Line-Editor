#ifndef _GG_CBUTTON_H_
#define _GG_CBUTTON_H_
#include "cfg.h"
#include "cfield.h"
#include "consoleplus.h"
#include "console.h"
#include "keys.h" 

namespace cio {
	class CField;
	
	class CButton : public CField {
		int _maxchar;
		bool _bordered;
		char* _data;
		void allocateAndCopy(const char* str);
	public:
		CButton(const char* str, int row, int col, bool bordered = true, 
			const char* border = C_BORDER_CHARS);
		~CButton();
		void draw(int fn = C_NO_FRAME);
		int edit();
		bool editable() const;
		void set(const void*);
	};
}
#endif