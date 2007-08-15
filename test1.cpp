#include <fltk/run.h>
#include <fltk/Button.h>
#include <fltk/Input.h>
#include <fltk/DoubleBufferWindow.h>
#include "TableBox.h"

using namespace fltk;

int main (int argc, char ** argv) {
	DoubleBufferWindow * win = new DoubleBufferWindow (420, 420, "Test 1");
	win->set_double_buffer ();
	win->begin ();
	
	TableBox * table1 = new TableBox (10, 10, win->w () - 20, win->h () - 20);
	
	table1->Size (3, 3);
	table1->box (fltk::BORDER_BOX);
	table1->begin ();
	
	//~ // row 0
	table1->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 1"), 0, 0, 100, 25, FILL, FILL, 1, 1, 0.0f, 0.5f);
	table1->Attach ((Widget *) new Input (0, 0, 0, 0), 1, 0, 200, 25, EXPAND | FILL, FILL, 1, 1, 0.5f, 0.5f);
	table1->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 2"), 2, 0, 100, 25, FILL | EXPAND, FILL, 1, 1, 0.5f, 0.5f);
	
	// row 2
	TableBox * table2 = new TableBox (0, 0, 0, 0);
	table2->Size (1, 3);
	table2->box (fltk::BORDER_BOX);
	table2->begin ();
	table2->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 3"), 0, 0, 100, 25);
	table2->Attach ((Widget *) new Button (0, 0, 0, 0, "B... 4"), 1, 0, 100, 25, EXPAND | FILL);
	table2->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 5"), 2, 0, 100, 25);
	table2->end ();
	table1->Attach ((Widget *) table2, 0, 1, 100, 25, FILL | EXPAND, FILL, 2, 1);
	
	// row 3
	TableBox * table3 = new TableBox (0, 0, 0, 0);
	table3->Size (2, 3);
	table3->box (fltk::BORDER_BOX);
	table3->begin ();
	table3->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 6"), 0, 0, 80, 25, NONE, NONE);
	table3->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 7"), 1, 0, 80, 25, NONE, NONE);
	table3->Attach ((Widget *) new Input (0, 0, 0, 0), 2, 0, 100, 25, FILL | EXPAND);
	table3->Attach ((Widget *) new Input (0, 0, 0, 0), 0, 1, 100, 25, FILL | EXPAND, FILL | EXPAND, 3, 1);
	table3->end ();
	table1->Attach ((Widget *) table3, 0, 2, 100, 25, FILL | EXPAND, FILL | EXPAND, 2, 1);
	
	// row 2-4
	TableBox * table4 = new TableBox (0, 0, 0, 0);
	table4->Size (2, 1);
	table4->box (fltk::BORDER_BOX);
	table4->begin ();
	table4->Attach ((Widget *) new Input (0, 0, 0, 0), 0, 0, 100, 25);
	table4->Attach ((Widget *) new Button (0, 0, 0, 0, "Button 8"), 0, 1, 80, 25, NONE, EXPAND, 1, 1, 0.5f, 1.0f);
	table4->end ();
	table1->Attach ((Widget *) table4, 2, 1, 100, 100, NONE, NONE, 1, 2, 0.5f, 0.5f);
	
	
	table1->end ();
	win->end ();
	win->resizable (table1);
	win->show (argc, argv);
	return run ();
}
