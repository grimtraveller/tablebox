#ifndef _HBOX_H_
#define _HBOX_H_

#ifdef WIN32
#define uint unsigned int
#endif

#define NONE		0

#define EXPAND	2
#define FILL		4

#define TABLEBOX	1
#define VBOX		2
#define HBOX		3

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <fltk/Group.h>
using namespace fltk;

namespace fltk {
	struct TABLE_CELL {
		fltk::Widget * o;
		uint w, h;
		bool x_expand, y_expand;
		bool x_fill, y_fill;
		uint x_span, y_span;
		float x_align, y_align;
	};

	struct CELL_GAP {
		uint w, h;
	};

	struct TABLE {
		uint cols, rows;
		std::vector < std::vector <TABLE_CELL> > cell;
		CELL_GAP * gap;
	};

	class TableBox : public Group {
		private:
			int __type;
			uint cur_row, cur_col;
			TABLE * t;
			
		
		public:
			TableBox (int _x, int _y, int _w, int _h);
			~TableBox ();
		
			void layout ();		
		
			// get
			int Type ();
			void Size (uint & _rows, uint & _cols);
			uint Size ();
			uint Rows ();
			uint Cols ();
			CELL_GAP * Gap ();
			void Gap (uint & _w, uint & _h);
			fltk::Widget * Widget (uint _row, uint _col);
			TABLE_CELL * Cell (uint _row, uint _col);
			
			// set
			void Type (int _type);
			void Size (uint _rows, uint _cols);
			void Size (uint _len);
			void Rows (uint _len);
			void Cols (uint _len);
			void AddCell (uint _len);
			void Gap (CELL_GAP * _gap);
			void Gap (uint _w, uint _h);
			void Widget (fltk::Widget * _widget, uint cols, uint rows);
			void Cell (TABLE_CELL * _cell, uint _row, uint _col);
			void Attach (
				fltk::Widget * _widget,
				uint _col, uint _row,
				uint _w = 100, uint _h = 25,
				uint _x_prop = FILL, uint _y_prop = NONE,
				uint _x_span = 1, uint _y_span = 1,
				float _x_align = 0.0f, float _y_align = 0.0f
			);
			void Add (
				fltk::Widget * _widget,
				uint _w = 100, uint _h = 25,
				uint _x_prop = FILL, uint _y_prop = NONE,
				uint _x_span = 1, uint _y_span = 1,
				float _x_align = 0.0f, float _y_align = 0.0f
			);
	};
}

#endif
