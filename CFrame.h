#ifndef _GG_CFRAME_H_
#define _GG_CFRAME_H_

#include "iframe.h"
namespace cio{ 
	class CFrame : public iFrame{
		int _row;
		int _col;
		int _width;
		int _height;
		bool _visible;
		void* _captured;
		char _border[9];
		CFrame* _frame;
		void setLine(char* str, char left, char fill, char right) const;
		void capture();
		
	protected:
		int absrow() const;
		int abscol() const;
	public:
		CFrame(int row = -1, int col = -1, int width = -1, int height = -1,
		bool visible = false,
		const char* border = C_BORDER_CHARS, CFrame* frame = (CFrame*)NULL);
		virtual ~CFrame();
		void goMiddle();
		void bordered(bool);
		bool bordered() const;
		void frame(CFrame*);
		CFrame* frame() const;
		void row(int);
		int row() const;
		void col(int);
		int col() const;
		void height(int);
		int height() const;
		void width(int);
		int width() const;
		void draw(int = C_FULL_FRAME);
		void hide(CDirection = C_STATIONARY);
		void move(CDirection);	
		bool fullscreen();
	};
	void move(iFrame&);
} 
#endif