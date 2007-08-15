#include "TableBox.h"

TableBox::TableBox (int _x, int _y, int _w, int _h) : Group (_x, _y, _w, _h) {
	t = new TABLE;
	t->gap = new CELL_GAP;
	Type (TABLEBOX);
	Size (1, 1);
	Gap (5, 5);
	cur_row = 0;
	cur_col = 0;
}

TableBox::~TableBox () {
	delete t->gap;
	delete t;
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
	
	uint _ox = 0;
	uint _oy = 0;
	uint _x = 0;
	uint _y = _oy;
	
	// x-axes
	for (uint i = 0; i < t->cols; i++) {
		x_fixed_size_item [i] = 0;
		
		for (uint j = 0; j < t->rows; j++) {
			if (t->cell [j][i].x_expand) {
				x_expand_items++;
				x_fixed_size_item [i] = 0;
				
				for (uint k = i; k < t->cols; k++)
					x_fixed_size_item [k] = 0;
				
				break;
			} else {
				if (x_fixed_size_item [i] < t->cell [j][i].w)
					x_fixed_size_item [i] = t->cell [j][i].w;
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
			if (t->cell [j][i].y_expand) {
				y_expand_items++;
				y_fixed_size_item [j] = 0;
				
				for (uint k = j; k < t->rows; k++)
					y_fixed_size_item [k] = 0;
				
				break;
			} else {
				if (y_fixed_size_item [j] < t->cell [j][i].h)
					y_fixed_size_item [j] = t->cell [j][i].h;
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
			if (t->cell [j][i].x_span > 1) {
				for (uint k=1; k < t->cell [j][i].x_span; k++) {
					if (x_fixed_size_item [i+k] > 0) Wv += x_fixed_size_item [i+k] + t->gap->w;
					else Wv += x_expand_size_item + t->gap->w;
				}
			}
			
			// x fill
			if (t->cell [j][i].x_fill) Wm = Wv;
			else if (Wv > t->cell [j][i].w) Wm = t->cell [j][i].w;
			else Wm = Wv;
			
			Xm = (uint)(t->cell [j][i].x_align * (Wv - Wm));
			
			// h
			if (y_fixed_size_item [j] > 0) Hv = y_fixed_size_item [j];
			else Hv = y_expand_size_item;
				
			// y span
			if (t->cell [j][i].y_span > 1) {
				for (uint k=1; k < t->cell [j][i].y_span; k++) {
					if (y_fixed_size_item [j+k] > 0) Hv += y_fixed_size_item [j+k] + t->gap->h;
					else Hv += y_expand_size_item + t->gap->h;
				}
			}
			
			// y fill
			if (t->cell [j][i].y_fill) Hm = Hv;
			else if (Hv > t->cell [j][i].h) Hm = t->cell [j][i].h;
			else Hm = Hv;
			
			Ym = (uint)(t->cell [j][i].y_align * (Hv - Hm));
			 
			// resizing / positioning
			if (t->cell [j][i].o != NULL)
				t->cell [j][i].o->resize (_x + Xm, _y + Ym, Wm, Hm);
			
			if (t->cell [j][i].o && t->cell [j][i].o->is_group () && !t->cell [j][i].o->is_window ())
				t->cell [j][i].o->layout ();
			
			// update X
			if (x_fixed_size_item [i] > 0) _x += x_fixed_size_item [i] + t->gap->w;
			else _x += x_expand_size_item + t->gap->w;
		}
		
		// beginning of next row
		_x = _ox;
		
		// update Y
		if (y_fixed_size_item [j] > 0) _y += y_fixed_size_item [j] + t->gap->h;
		else _y += y_expand_size_item + t->gap->h;
	}	
}

// get
int TableBox::Type () {
	return __type;
}

void TableBox::Size (uint & _rows, uint & _cols) {
	_rows = t->rows;
	_cols = t->cols;
}

uint TableBox::Size () {
	if (Type () == VBOX)
		return t->rows;
	else if (Type () == HBOX)
		return t->cols;
	else
		return 0;
}

uint TableBox::Rows () {
	return t->rows;
}

uint TableBox::Cols () {
	return t->rows;
}

CELL_GAP * TableBox::Gap () {
	return t->gap;
}

void TableBox::Gap (uint & _w, uint & _h) {
	_w = t->gap->w;
	_h = t->gap->h;
}

fltk::Widget * TableBox::Widget (uint _row, uint _col) {
	return t->cell [_row][_col].o;
}

TABLE_CELL * TableBox::Cell (uint _row, uint _col) {
	return & t->cell [_row][_col];
}

// set
void TableBox::Type (int _type) {
	__type = _type;
}

void TableBox::Size (uint _rows, uint _cols) {
	t->rows = _rows;
	t->cols = _cols;
	
	t->cell.resize (t->rows);
	
	for (uint j=0; j<t->rows; j++)
		t->cell [j].resize (t->cols);
}

void TableBox::Size (uint _len) {
	if (Type () == VBOX)
		Rows (_len);
	else if (Type () == HBOX)
		Cols (_len);
	else
		printf ("TableBox ... not recognized BOX type\n");
}

void TableBox::Rows (uint _len) {
	t->rows = _len;
	Size ((uint)t->rows, (uint)t->cols);
}

void TableBox::Cols (uint _len) {
	t->cols = _len;
	Size ((uint)t->rows, (uint)t->cols);
}

void TableBox::AddCell (uint _len) {
	Size (Size () + 1);
}

void TableBox::Gap (CELL_GAP * _gap) {
	t->gap = _gap;
}

void TableBox::Gap (uint _w, uint _h) {
	t->gap->w = _w;
	t->gap->h = _h;
}

void TableBox::Widget (fltk::Widget * _widget, uint _row, uint _col) {
	t->cell [_row][_col].o = _widget;
}

void TableBox::Cell (TABLE_CELL * _cell, uint _row, uint _col) {
	t->cell [_row][_col] = * _cell;
}

void TableBox::Attach (
	fltk::Widget * _widget,
	uint _col, uint _row,
	uint _w, uint _h,
	uint _x_prop, uint _y_prop,
	uint _x_span, uint _y_span,
	float _x_align, float _y_align
) {
	t->cell [_row] [_col].o = _widget;
	t->cell [_row] [_col].w = _w;
	t->cell [_row] [_col].h = _h;
	t->cell [_row] [_col].x_fill = _x_prop & FILL;
	t->cell [_row] [_col].y_fill = _y_prop & FILL;
	t->cell [_row] [_col].x_span = _x_span;
	t->cell [_row] [_col].y_span = _y_span;
	
	for (uint j = 0; j < _y_span; j++) {
		for (uint i = 0; i < _x_span; i++) {
			t->cell [_row+j] [_col+i].x_align = _x_align;
			t->cell [_row+j] [_col+i].y_align = _y_align;
			t->cell [_row+j] [_col+i].x_expand = _x_prop & EXPAND;
			t->cell [_row+j] [_col+i].y_expand = _y_prop & EXPAND;
		}
	}
}

void TableBox::Add (
	fltk::Widget * _widget,
	uint _w, uint _h,
	uint _x_prop, uint _y_prop,
	uint _x_span, uint _y_span,
	float _x_align, float _y_align
) {
	uint _row = cur_row;
	uint _col = cur_col;
	
	t->cell [_row] [_col].o = _widget;
	t->cell [_row] [_col].w = _w;
	t->cell [_row] [_col].h = _h;
	t->cell [_row] [_col].x_fill = _x_prop & FILL;
	t->cell [_row] [_col].y_fill = _y_prop & FILL;
	t->cell [_row] [_col].x_span = _x_span;
	t->cell [_row] [_col].y_span = _y_span;
	t->cell [_row] [_col].x_align = _x_align;
	t->cell [_row] [_col].y_align = _y_align;
	
	for (uint j = 0; j < _y_span; j++) {
		for (uint i = 0; i < _x_span; i++) {
			t->cell [_row+j] [_col+i].x_expand = _x_prop & EXPAND;
			t->cell [_row+j] [_col+i].y_expand = _y_prop & EXPAND;
		}
	}
	
	if (Type () == VBOX)
		cur_row++;
	else if (Type () == HBOX)
		cur_col++;
	else
		return;

}
