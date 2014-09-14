//Consolebackup.h
#ifndef _GG_CONSOLE_BACKUP_H_
#define _GG_CONSOLE_BACKUP_H_

#include "cfg.h"
namespace cio{
void* capture(int r, int c, int h, int w);
void restore(int r, int c, int h, int w, CDirection d, void* b);
void release(void**);
}
#endif  

