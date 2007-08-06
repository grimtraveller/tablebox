#include "TableBox.h"

TableBox::TableBox (int _x, int _y, int _w, int _h) : Group (_x, _y, _w, _h) {
	t = new TABLE;
	t->gap = new CELL_GAP;
	t->gap->w = 5;
	t->gap->h = 5;
}

TableBox::~TableBox () {
	delete [] t->cell;
	delete t->gap;
	delete t;
}

void TableBox::Size (uint _cols, uint _rows) {
	t->cols = _cols;
	t->rows = _rows;
	t->cell = new TABLE_CELL ** [_cols];
	for (uint i = 0; i < _cols; i++) {
		t->cell [i] = new TABLE_CELL * [_rows];
		for (uint j = 0; j < _rows; j++) {
			t->cell [i][j] = new TABLE_CELL;
			t->cell [i] [j]->o = NULL;
		}
	}
}

void TableBox::Attach (
	Widget * _widget,
	uint _col, uint _row,
	uint _w, uint _h,
	uint _x_prop, uint _y_prop,
	uint _x_span, uint _y_span,
	float _x_align, float _y_align
) {
	t->cell [_col] [_row]->o = _widget;
	t->cell [_col] [_row]->w = _w;
	t->cell [_col] [_row]->h = _h;	
	t->cell [_col] [_row]->x_fill = _x_prop & FILL;
	t->cell [_col] [_row]->y_fill = _y_prop & FILL;	
	t->cell [_col] [_row]->x_span = _x_span;
	t->cell [_col] [_row]->y_span = _y_span;
	t->cell [_col] [_row]->x_align = _x_align;
	t->cell [_col] [_row]->y_align = _y_align;
	
	for (uint j = 0; j < _y_span; j++) {
		for (uint i = 0; i < _x_span; i++) {
			t->cell [_col+i] [_row+j]->x_expand = _x_prop & EXPAND;
			t->cell [_col+i] [_row+j]->y_expand = _y_prop & EXPAND;
		}
	}
}

void TableBox::Gap (uint _w, uint _h) {
	t->gap->w = _w;
	t->gap->h = _h;
}

void TableBox::layout () {
	uint x_expand_items = 0;
	uint x_expand_size_item;
	uint x_fixed_size_item [t->cols];
	uint y_expand_items = 0;
	uint y_expand_size_item;
	uint y_fixed_size_item [t->rows];
	
	uint x_fixed_size_all_items = 0;
	uint y_fixed_size_all_items = 0;
	
	uint _x, _y, _w, _h;
	_x = _y = _w = _h = 0;
	
	// x-axes
	for (uint i = 0; i < t->cols; i++) {
		x_fixed_size_item [i] = 0;
		for (uint j = 0; j < t->rows; j++) {
			if (t->cell [i][j]->x_expand) {
				x_expand_items++;
				x_fixed_size_item [i] = 0;
				for (uint k = i; k < t->cols; k++)
					x_fixed_size_item [k] = 0;
				break;
			} else {
				if (x_fixed_size_item [i] < t->cell [i][j]->w)
					x_fixed_size_item [i] = t->cell [i][j]->w;
			}
		}
	}
	
	for (uint i = 0; i < t->cols; i++)
		if (x_fixed_size_item [i] > 0)
			x_fixed_size_all_items += x_fixed_size_item [i];
	
	if (x_expand_items > 0)
		x_expand_size_item = (uint)((w () - x_fixed_size_all_items - (t->cols - 1) * t->gap->w) / x_expand_items);
	
	// y-axes
	for (uint j = 0; j < t->rows; j++) {
		y_fixed_size_item [j] = 0;
		for (uint i = 0; i < t->cols; i++) {
			if (t->cell [i][j]->y_expand) {
				y_expand_items++;
				y_fixed_size_item [j] = 0;
				for (uint k = j; k < t->rows; k++)
					y_fixed_size_item [k] = 0;
				break;
			} else {
				if (y_fixed_size_item [j] < t->cell [i][j]->h)
					y_fixed_size_item [j] = t->cell [i][j]->h;
			}
		}
	}
	
	for (uint j = 0; j < t->rows; j++)
		if (y_fixed_size_item [j] > 0)
			y_fixed_size_all_items += y_fixed_size_item [j];
	
	if (y_expand_items > 0)
		y_expand_size_item = (uint)((h () - y_fixed_size_all_items - (t->rows - 1) * t->gap->h) / y_expand_items);
	
	uint Wv, Wm, Xm;
	uint Hv, Hm, Ym;
	
	// packing
	for (uint j = 0; j < t->rows; j++) {
		for (uint i = 0; i < t->cols; i++) {
			// w
			if (x_fixed_size_item [i] > 0) Wv = x_fixed_size_item [i];
			else Wv = x_expand_size_item;
			
			// x span
			if (t->cell [i][j]->x_span > 1) {
				for (uint k=1; k < t->cell [i][j]->x_span; k++) {
					if (x_fixed_size_item [i+k] > 0) Wv += x_fixed_size_item [i+k] + t->gap->w;
					else Wv += x_expand_size_item + t->gap->w;
				}
			}
			
			// x fill
			if (t->cell [i][j]->x_fill) Wm = Wv;
			else if (Wv > t->cell [i][j]->w) Wm = t->cell [i][j]->w;
			else Wm = Wv;
			
			Xm = (uint)(t->cell [i][j]->x_align * (Wv - Wm));
			
			// h
			if (y_fixed_size_item [j] > 0) Hv = y_fixed_size_item [j];
			else Hv = y_expand_size_item;
				
			// y span
			if (t->cell [i][j]->y_span > 1) {
				for (uint k=1; k < t->cell [i][j]->y_span; k++) {
					if (y_fixed_size_item [j+k] > 0) Hv += y_fixed_size_item [j+k] + t->gap->h;
					else Hv += y_expand_size_item + t->gap->h;
				}
			}
			
			// y fill
			if (t->cell [i][j]->y_fill) Hm = Hv;
			else if (Hv > t->cell [i][j]->h) Hm = t->cell [i][j]->h;
			else Hm = Hv;
			
			Ym = (uint)(t->cell [i][j]->y_align * (Hv - Hm));
			 
			// resizing / positioning
			if (t->cell [i][j]->o != NULL) t->cell [i][j]->o->resize (_x + Xm, _y + Ym, Wm, Hm);
			
			// update X
			if (x_fixed_size_item [i] > 0) _x += x_fixed_size_item [i] + t->gap->w;
			else _x += x_expand_size_item + t->gap->w;
		}
		
		// beginning of next row
		_x = 0;
		
		// update Y
		if (y_fixed_size_item [j] > 0) _y += y_fixed_size_item [j] + t->gap->h;
		else _y += y_expand_size_item + t->gap->h;
	}
}

Widget * TableBox::Get (uint cols, uint rows) {
	return t->cell [cols][rows]->o;
}
