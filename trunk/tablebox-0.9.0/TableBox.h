#ifndef _HBOX_H_
#define _HBOX_H_

#define NONE		0
#define EXPAND	2
#define FILL		4

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fltk/Group.h>
using namespace fltk;

namespace fltk {
	struct TABLE_CELL {
		Widget * o;
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
		TABLE_CELL * ** cell;
		CELL_GAP * gap;
	};

	class TableBox : public Group {
		private:
			TABLE * t;
			void layout ();
		
		public:
			TableBox (int _x, int _y, int _w, int _h);
			~TableBox ();
			void Size (uint _cols, uint _rows);
			void Resize (uint _cols, uint _rows);
			
			void Attach (
				Widget * _widget,
				uint _col, uint _row,
				uint _w = 100, uint _h = 25,
				uint _x_prop = FILL, uint _y_prop = FILL,
				uint _x_span = 1, uint _y_span = 1,
				float _x_align = 0.0f, float _y_align = 0.0f
			);
		
			Widget * Get (uint cols, uint rows);
		
			void Gap (uint _w, uint _h);
	};
}

#endif
