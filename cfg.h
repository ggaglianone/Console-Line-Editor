//cfg.h
//Gabriel Gaglianone 
#ifndef _GG_CFG_H_
#define _GG_CFG_H_
#include <cstdlib>
#define C_MAX_NO_FIELDS 100
#define C_BORDER_CHARS "/-\\|/-\\|"
#define C_FULL_FRAME -1
#define C_NO_FRAME 0
#define C_NOT_EDITABLE 0
#define C_BUTTON_HIT 0

namespace cio{
	enum CDirection{C_STATIONARY, C_MOVED_LEFT, C_MOVED_RIGHT, C_MOVED_UP, C_MOVED_DOWN};
}
#endif